#include "camera.h"
#include "time.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace kalsengi;
using namespace std;

Camera::Camera (glm::vec3 pos, glm::vec3 target, glm::vec3 up)
    : io (ImGui::GetIO()), _position(pos), _target(target), _up(up)
{
    _viewMat = glm::lookAt(_position, _target, _up);
    _dirty = false;
    _cameraMovSpeed = 1;
}

glm::mat4 Camera::view ()
{
    if (_dirty) {
        _viewMat = glm::lookAt(_position, _target, _up);
        _dirty = false; // consume new view matrix
    }

    return _viewMat;
}

void Camera::update ()
{
    glm::vec3 mov (0.0f);

    // left right movement
    if (io.KeysDown[GLFW_KEY_A]) {
        mov.x = -1;
    }
    if (io.KeysDown[GLFW_KEY_D]) {
        mov.x = 1;
    }

    // forward backward movement
    if (io.KeysDown[GLFW_KEY_W]) {
        mov.z = -1;
    }
    if (io.KeysDown[GLFW_KEY_S]) {
        mov.z = 1;
    }


    // first check if mov != 0.
    // otherwise it will produce nan as a result of normalize
    if (glm::length (mov) != 0) {
        // TODO: update target!!!
        _dirty = true;
        mov = glm::normalize (mov);
        mov *= _cameraMovSpeed * Time::getDeltaTime ();
        _position += mov;

        cout << "camera pos: " << _position.x << " " << _position.y << " " << _position.z << endl;
    }
}

bool Camera::isDirty ()
{
    return _dirty;
}
