#include "ModelLoader.h"

#include <iostream>
#include <fstream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Rendering/Texture.h>
#include <Rendering/MeshManager.h>
#include <Rendering/ShaderProgram.h>

using namespace std;

template<typename T>
void WriteOutBinary(std::vector<T> data, std::string filename) {
	ofstream fout(filename, ios::out | ios::binary);
	fout.write(reinterpret_cast<char*>(&data[0]), data.size() * sizeof(T));
	fout.close();
}

GameObject* ModelLoader::LoadModel(const string& name, const string& modelFilePath,
	const string& diffuseTextureFilePath)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(modelFilePath, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		cout << "ERROR::ASSIMP::" << import.GetErrorString() << endl;
		return nullptr;
	}

	auto gameObject = new GameObject(name);
	processNode(gameObject, scene->mRootNode, scene, diffuseTextureFilePath);
	
	return gameObject;
}

shared_ptr<ShaderProgram> ModelLoader::processMaterial()
{
	return ShaderProgram::get("temp_888", "shaders/Diffuse_Vertex.glsl", "shaders/Diffuse_Fragment.glsl");
}

void ModelLoader::processNode(GameObject* parent, aiNode* node, const aiScene* scene, const string& diffuseTextureFilePath)
{
	// Process meshes
	for (GLuint i = 0; i < node->mNumMeshes; i++) 	{
		aiMesh* mesh_ = scene->mMeshes[node->mMeshes[i]];
		auto gameObject = new GameObject(std::string(node->mName.C_Str()));
		auto mesh = processMesh(gameObject->name + "_mesh", mesh_, scene);

		gameObject->transform->setParent(parent->transform.get());

		auto material = processMaterial();
		gameObject->renderer = BaseRenderer::create(gameObject, material, mesh, diffuseTextureFilePath);
		//this->meshes.push_back(this->processMesh(mesh, scene));
	}

	// Recursively process child nodes
	for (GLuint i = 0; i < node->mNumChildren; i++) {
		processNode(parent, node->mChildren[i], scene, diffuseTextureFilePath);
	}
}

shared_ptr<LegacyMesh> ModelLoader::processMesh(const string& meshId, aiMesh* aiMesh_, const aiScene* scene)
{
	vector<VertexData> vertices;
	vector<GLuint> indices;
	vector<Texture> textures;

	// Process vertex data
	for (GLuint i = 0; i < aiMesh_->mNumVertices; ++i) {
		VertexData vertex{
			// position
			glm::vec3{aiMesh_->mVertices[i].x, aiMesh_->mVertices[i].y, aiMesh_->mVertices[i].z},
			// colour
			glm::vec4{1.0f, 1.0f, 1.0f, 1.0f},
			// texture coordinates (uvs)
			glm::vec2{aiMesh_->mTextureCoords[0][i].x, aiMesh_->mTextureCoords[0][i].y}
		};
		// normal
		if(aiMesh_->mNormals != nullptr)
			vertex._normal = glm::vec3{ aiMesh_->mNormals[i].x, aiMesh_->mNormals[i].y, aiMesh_->mNormals[i].z };
		
		vertices.push_back(vertex);
	}


	//WriteOutBinary<VertexData>(vertices, "vertices.data");

	// Process indices
	for (GLuint i = 0; i < aiMesh_->mNumFaces; ++i) {
		aiFace face = aiMesh_->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}

	//WriteOutBinary<GLuint>(indices, "indices.data");

	// Process material
    // don't know what is it
	//if (aiMesh_->mMaterialIndex >= 0) {
	//}

	return MeshManager::registerMesh(meshId, vertices, indices);
}
