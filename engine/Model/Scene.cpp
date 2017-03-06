#include "Scene.h"

using namespace std;
using namespace Models;

// Scene
Scene::Scene()
{
}

Scene::~Scene()
{
	for (auto it = _gameModelList.begin(); it != _gameModelList.end(); ++it) {
		delete it->second;
	}
	_gameModelList.clear();
}

void Scene::AddModel(const string &gameModelName, GameObject * gameObject)
{
	_gameModelList[gameModelName] = gameObject;
}

void Scene::DeleteModel(const std::string &gameModelName)
{
}

const GameObject& Scene::GetModel(const std::string &gameModelName)
{
	return *_gameModelList[gameModelName];
}

std::map<std::string, GameObject*>::iterator Scene::begin()
{
	return _gameModelList.begin();
}

std::map<std::string, GameObject*>::iterator Scene::end()
{
	return _gameModelList.end();
}
