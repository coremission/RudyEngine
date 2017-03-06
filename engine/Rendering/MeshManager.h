#ifndef MESHMANAGER_h
#define MESHMANAGER_h

#include "Mesh.h"

#include <map>
#include <string>
#include <memory>

class MeshManager
{
private:
	static std::map<std::string, std::shared_ptr<LegacyMesh>> meshMap;
public:
	static std::shared_ptr<LegacyMesh> registerMesh(std::string id, std::vector<VertexData> vertices);
	static std::shared_ptr<LegacyMesh> registerMesh(std::string id, std::vector<VertexData> vertices, std::vector<GLuint> indices);
	static std::shared_ptr<LegacyMesh> getQuadMesh();
	static std::shared_ptr<LegacyMesh> getIndexedQuadMesh();
	static std::shared_ptr<BaseMesh> MeshManager::getSkyboxMesh();
	static std::shared_ptr<BaseMesh> getDefaultSpriteMesh();
};

#endif //MESHMANAGER_h