//
// Created by Ryan on 24/05/2018.
//

#ifndef R3D_BEHAVIOUR_HPP
#define R3D_BEHAVIOUR_HPP

#include "component.hpp"

namespace r3d
{
    class behaviour : public component
    {
    public:
        behaviour();

        virtual void init();

        virtual void update() const;
    };
}

#endif //R3D_BEHAVIOUR_HPP
