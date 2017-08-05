#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace kalsengi;
using namespace std;

Model::Model (const char * /*path*/)
{

}

void Model::draw (Shader shader)
{
    for (unsigned i = 0; i < meshes.size(); i++) {
        meshes[i].draw (shader);
    }
}
