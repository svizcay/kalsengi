#include "mesh.h"

using namespace kalsengi;
using namespace std;

Mesh::Mesh (vector<Vertex> _vertices, vector<unsigned> _indices, vector<Texture> _textures)
    : vertices(_vertices), indices(_indices), textures(_textures)
{
    setupMesh ();
}

void Mesh::setupMesh ()
{
    glGenVertexArrays (1, &vao);
    glGenBuffers (1, &vbo);
    glGenBuffers (1, &ebo);
    
    glBindVertexArray (vao);

    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    glBufferData (GL_ARRAY_BUFFER,
            vertices.size() * sizeof(Vertex),
            &vertices[0],
            GL_STATIC_DRAW);

    glBindBuffer (GL_ARRAY_BUFFER, ebo);
    glBufferData (GL_ARRAY_BUFFER,
            indices.size() * sizeof(unsigned),
            &indices[0],
            GL_STATIC_DRAW);

    // TODO: make sure to follow this convention
    // layout 0: pos
    // layout 1: normal
    // layour 2: texcoord

    glEnableVertexAttribArray (0);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

    glEnableVertexAttribArray (1);
    glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, normal));

    glEnableVertexAttribArray (2);
    glVertexAttribPointer (2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, texcoord));

    glBindVertexArray (0);
}

void Mesh::draw (Shader /*shader*/)
{
    glBindVertexArray (vao);
    glDrawElements (GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray (0);
}
