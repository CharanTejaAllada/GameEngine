#include <assert.h>

#include "NullModel.h"
#include "GraphicsObject_Null.h"
#include"GraphicsObject_FlatTexture.h"
#include "GameObject.h"
#include "GameObjectMan.h"
#include "PCSTreeForwardIterator.h"

void GameObjectMan::Add(GameObject *pObj)
{
	assert(pObj != 0);

	// Get singleton
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();

	// Get root node
	PCSNode *pRootNode = pGOM->pRootTree->getRoot();

	// insert object to root
	pGOM->pRootTree->insert(pObj, pRootNode);
}

void GameObjectMan::UpdateModel(ModelType p, TextureName upd)
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;

		if (pGameObj->type == p)
		{
			GraphicsObject_FlatTexture *pGraphicsObj = (GraphicsObject_FlatTexture *)pGameObj->getGraphicsObject();
			pGraphicsObj->textName = upd;
		}
		pNode = pForwardIter.Next();
	}
}


void GameObjectMan::Update(float currentTime)
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		pGameObj->Process(currentTime);

		pNode = pForwardIter.Next();
	}
}

void GameObjectMan::Draw()
{
	GameObjectMan *pGOM = GameObjectMan::privGetInstance();
	assert(pGOM);

	PCSNode *pRootNode = pGOM->pRootTree->getRoot();
	assert(pRootNode);

	PCSTreeForwardIterator pForwardIter(pRootNode);
	PCSNode *pNode = pForwardIter.First();

	GameObject *pGameObj = 0;

	while (!pForwardIter.IsDone())
	{
		assert(pNode);
		// Update the game object
		pGameObj = (GameObject *)pNode;
		pGameObj->Draw();

		pNode = pForwardIter.Next();
	}
}

GameObjectMan::GameObjectMan()
{
	// Create the root node (null object)
	NullModel *pModel = new NullModel(0);
	ShaderObject *pShader = new ShaderObject(ShaderName::NULL_SHADER, "nullRender");
	GraphicsObject_Null *pGraphicsObject = new GraphicsObject_Null(pModel, pShader);
	GameObject *pGameRoot = new GameObject(pGraphicsObject);
	pGameRoot->setName("GameObject_Root");

	// Create the tree
	this->pRootTree = new PCSTree();
	assert(this->pRootTree);

	// Attach the root node
	this->pRootTree->insert(pGameRoot, this->pRootTree->getRoot());


}

GameObjectMan * GameObjectMan::privGetInstance(void)
{
	// This is where its actually stored (BSS section)
	static GameObjectMan gom;
	return &gom;
}
