#ifndef GAME_OBJECT_MAN_H
#define GAME_OBJECT_MAN_H

#include "GameObject.h"
#include "PCSTree.h"
#include "TextureNode.h"


// Singleton
class GameObjectMan
{
public:

	static void Add(GameObject *pObj);
	static void Draw(void);
	static void Update(float currentTime);
	static void UpdateModel(ModelType p, TextureName upd);

private:
	GameObjectMan();
	static GameObjectMan *privGetInstance();
	PCSTree *pRootTree;

};

#endif