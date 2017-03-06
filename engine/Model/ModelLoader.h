#ifndef MODELLOADER_h
#define MODELLOADER_h

#include "GameObject.h"
#include <assimp/scene.h>

#include <memory>

class ModelLoader
{
private:
	static void processNode(GameObject*, aiNode* node, const aiScene* scene, const std::string& diffuseTextureFilePath);
	static std::shared_ptr<LegacyMesh> processMesh(const std::string& meshId, aiMesh* mesh, const aiScene* scene);
	static std::shared_ptr<ShaderProgram> processMaterial();
public:
	static GameObject* LoadModel(const std::string& gameObjectName, const std::string& modelFilePath, const std::string& diffuseTextureFilePath);
};

#endif //MODELLOADER_h