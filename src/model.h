#ifndef MODEL_H
#define MODEL_H 

#include "mesh.h"
#include "shader.h"

#include <vector>

namespace kalsengi
{

    class Model
    {
        public:
            Model (const char * path);

            void draw (Shader shader);
        private:
            std::vector<Mesh> meshes;

    };

}

#endif /* MODEL_H */
