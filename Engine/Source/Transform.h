#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#pragma once

enum TRANSFORM_TYPE
{
    STATIC_TRANSFORM,
    DYNAMIC_TRANSFORM
};

struct Transform
{
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    glm::vec3 AxisX;
    glm::vec3 AxisY;
    glm::vec3 AxisZ;

    TRANSFORM_TYPE type;

    Transform()
        : position(glm::vec3(0, 0, 0))
        , scale(glm::vec3(1, 1, 1))
        , rotation(glm::vec3(0, 0, 0))
        , type(DYNAMIC_TRANSFORM)
    {
        AxisX = glm::vec3(1, 0, 0);
        AxisY = glm::vec3(0, 1, 0);
        AxisZ = glm::vec3(0, 0, 1);
    }

    Transform(glm::vec3 pos, glm::vec3 scale, glm::vec3 rot, TRANSFORM_TYPE type)
        : position(pos)
        , scale(scale)
        , rotation(rot)
        , type(type)
    {

        glm::mat4 mrot(1.f);

        glm::vec3 rotation = glm::radians(this->rotation);

        mrot = glm::mat4(1.f);
        mrot = glm::rotate(mrot, rotation.x, glm::vec3(1, 0, 0));
        mrot = glm::rotate(mrot, rotation.y, glm::vec3(0, 1, 0));
        mrot = glm::rotate(mrot, rotation.z, glm::vec3(0, 0, 1));

        AxisX = glm::vec3(mrot * glm::vec4(1, 0, 0, 0.f));
        AxisY = glm::vec3(mrot * glm::vec4(0, 1, 0, 0.f));
        AxisZ = glm::vec3(mrot * glm::vec4(0, 0, 1, 0.f));
    }

};