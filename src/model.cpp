#include "model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace kalsengi;
using namespace std;

Model::Model (const char * path)
{
    loadModel (path);
}

void Model::loadModel (const char * path)
{
    Assimp::Importer import;
    const aiScene *scene = import.ReadFile (
            path,
            aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        cerr << "ERROR: ASSIMP: " << import.GetErrorString () << endl;
        return;
    }

    // processNode (scene->mRootNode, scene);
}

void Model::draw (Shader shader)
{
    for (unsigned i = 0; i < meshes.size(); i++) {
        meshes[i].draw (shader);
    }
}
