//
// Created by Ryan on 08/06/2018.
//

#ifndef R3D_TIME_HPP
#define R3D_TIME_HPP

namespace r3d
{
    class time
    {
    public:
        float delta_time;

        time();

        void update();

    private:
        double last_time;
        double current_time;
    };
}


#endif //R3D_TIME_HPP

