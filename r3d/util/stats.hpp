//
// Created by Ryan on 17/10/2018.
//

#ifndef R3D_FPS_HPP
#define R3D_FPS_HPP

#include "../ui/text.hpp"

namespace r3d
{
    class fps: public text
    {
    public:
        fps(std::shared_ptr<r3d::font> font, GLfloat x, GLfloat y);

        void render(GLuint& vertex_buffer_object);
        
    private:
        const int REFRESH_RATE = 30;

        double last_time;
        std::vector<double> frame_times;
        double frame_time = 0.01;
    };
}

#endif //R3D_FPS_HPP