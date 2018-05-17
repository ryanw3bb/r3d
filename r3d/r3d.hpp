//
// Created by Ryan on 08/04/2018.
//

#ifndef R3D_MAIN_H
#define R3D_MAIN_H

class r3d
{
    public:
        r3d::r3d(int width, int height);

    protected:
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void error_callback(int error, const char* description);
};

#endif //R3D_MAIN_H