#ifndef CAMERA_H
#define CAMERA_H 

#include <glm/mat4x4.hpp>
#include "imgui.h"

namespace kalsengi
{
    class Camera
    {
        ImGuiIO& io;

        public:
            Camera (
                    glm::vec3 pos = glm::vec3(0.f, 0.f, 5.f),
                    glm::vec3 target = glm::vec3(0.f, 0.f, 0.f),
                    glm::vec3 up = glm::vec3(0.f, 1.f, 0.f));
            void        update ();
            glm::mat4   view ();
            bool        isDirty ();


        private:
            glm::vec3   _position;
            glm::vec3   _target;
            glm::vec3   _up;

            glm::mat4   _viewMat;

            bool        _dirty;

            float       _cameraMovSpeed;

    };
}
#endif /* CAMERA_H */
