//
// Created by Ryan on 23/05/2018.
//

#include "light.hpp"

using namespace r3d;

light::light()
{

}

light::light(glm::vec3 position, glm::vec3 color, float intensity)
{
    this->position = position;
    this->color = color;
    this->intensity = intensity;
}