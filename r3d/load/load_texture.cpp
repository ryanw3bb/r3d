#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "load_texture.hpp"
#include "../util/file.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../external/include/stb_image.h"

GLuint r3d::load_texture(std::string image_path)
{
    image_path.insert(0, get_running_dir());

    printf("Reading image %s\n", image_path.c_str());

    int width, height, bpp;

    unsigned char* rgb_image = stbi_load(image_path.c_str(), &width, &height, &bpp, STBI_rgb);

    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, rgb_image);

    // OpenGL has now copied the data. Free our own version
    stbi_image_free(rgb_image);

    // trilinear filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    // which requires mipmaps. Generate them automatically.
    glGenerateMipmap(GL_TEXTURE_2D);

    return textureID;
}

GLuint r3d::load_cubemap(std::vector<std::string> faces)
{
    unsigned int textureID;

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, bpp;

    for(unsigned int i = 0; i < faces.size(); i++)
    {
        // use full directory
        faces[i].insert(0, get_running_dir());

        unsigned char* image = stbi_load(faces[i].c_str(), &width, &height, &bpp, 0);
        if(image)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

            stbi_image_free(image);
        }
        else
        {
            printf("Cubemap texture failed to load: %s\n", faces[i].c_str());
            stbi_image_free(image);
        }
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}

#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

GLuint r3d::load_dds(std::string image_path)
{
    image_path.insert(0, get_running_dir());

    unsigned char header[124];

    FILE* fp;

    /* try to open the file */
    fp = fopen(image_path.c_str(), "rb");
    if(fp == NULL)
    {
        printf("%s could not be opened.\n", image_path.c_str());
        getchar();
        return 0;
    }

    /* verify the type of file */
    char filecode[4];
    fread(filecode, 1, 4, fp);
    if(strncmp(filecode, "DDS ", 4) != 0)
    {
        fclose(fp);
        return 0;
    }

    /* get the surface desc */
    fread(&header, 124, 1, fp);

    unsigned int height = *(unsigned int*) &(header[8]);
    unsigned int width = *(unsigned int*) &(header[12]);
    unsigned int linearSize = *(unsigned int*) &(header[16]);
    unsigned int mipMapCount = *(unsigned int*) &(header[24]);
    unsigned int fourCC = *(unsigned int*) &(header[80]);

    unsigned char* buffer;
    unsigned int bufsize;
    /* how big is it going to be including all mipmaps? */
    bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
    buffer = (unsigned char*) malloc(bufsize * sizeof(unsigned char));
    fread(buffer, 1, bufsize, fp);
    /* close the file pointer */
    fclose(fp);

    unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
    unsigned int format;
    switch(fourCC)
    {
        case FOURCC_DXT1:
            format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
            break;
        case FOURCC_DXT3:
            format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
            break;
        case FOURCC_DXT5:
            format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
            break;
        default:
            free(buffer);
            return 0;
    }

    // Create one OpenGL texture
    GLuint texture_id;
    glGenTextures(1, &texture_id);

    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    // anisotropic filtering
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2);

    unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
    unsigned int offset = 0;

    /* load the mipmaps */
    for(unsigned int level = 0; level < mipMapCount && (width || height); ++level)
    {
        unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
        glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height, 0, size, buffer + offset);

        offset += size;
        width /= 2;
        height /= 2;

        // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
        if(width < 1)
        { width = 1; }
        if(height < 1)
        { height = 1; }
    }

    free(buffer);

    return texture_id;
}
