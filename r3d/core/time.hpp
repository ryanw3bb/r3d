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
            time();
            void update();
            float delta_time;

        private:
            double last_time;
            double current_time;
    };
}


#endif //R3D_TIME_HPP
