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
            Camera (glm::vec3 pos = glm::vec3(0.f, 0.f, 5.f));
            void        update ();
            glm::mat4   view ();
            bool        isDirty ();


        private:
            glm::vec3   _position;
            glm::vec3   _forward;
            glm::vec3   _up;

            glm::mat4   _viewMat;

            bool        _dirty;

            float       _cameraMovSpeed;

    };
}
#endif /* CAMERA_H */
