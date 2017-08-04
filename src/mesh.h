#ifndef MESH_H
#define MESH_H 

#include <glm/mat4x4.hpp>
#include <vector>
#include <string>

#include "shader.h"

namespace kalsengi
{
    struct Vertex
    {
        glm::vec3 pos;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

    struct Texture
    {
        unsigned id;
        std::string type;
    };

    class Mesh
    {
        public:
            std::vector<Vertex> vertices;
            std::vector<unsigned> indices;
            std::vector<Texture> textures;

            Mesh (std::vector<Vertex> _vertices, 
                std::vector<unsigned> _indices, 
                std::vector<Texture> _textures);

            void draw (Shader shader);

        private:
            GLuint vao;
            GLuint vbo, ebo;
            void setupMesh ();

    };

}
#endif /* MESH_H */
