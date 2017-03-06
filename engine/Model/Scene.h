#ifndef MODELS_H
#define MODELS_H

#include <iostream>
#include <map>
#include "GameObject.h"

namespace Models
{
	class Scene
	{
	private:
		// todo: here must be smart pointer
		std::map<std::string, GameObject*> _gameModelList;
		Scene(const Scene&);
		void operator=(const Scene&);
	public:
		Scene(); // todo: make it private
		~Scene();
		// todo: there must be smart pointer passed
		void AddModel(const std::string &gameModelName, GameObject * gameObject);
		void DeleteModel(const std::string &gameModelName);
		const GameObject& GetModel(const std::string &gameModelName);
		// iterator
		std::map<std::string, GameObject*>::iterator begin();
		std::map<std::string, GameObject*>::iterator end();
	};
}

#endif // MODELS_H