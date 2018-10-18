//
// Created by Ryan on 26/03/2018.
//

#ifndef R3D_LOADSHADER_H
#define R3D_LOADSHADER_H

#include <string>

namespace r3d
{
    GLuint load_shader(std::string vertex_file_path, std::string fragment_file_path);
}

#endif //R3D_LOADSHADER_H