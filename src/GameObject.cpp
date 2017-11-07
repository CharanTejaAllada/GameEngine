#include <math.h>
#include <assert.h>

#include "Game.h"
#include "MathEngine.h"
#include "GameObject.h"

// YUCK - refactor
extern Game *pGame;

GameObject::GameObject(GraphicsObject  *graphicsObject)
	: pGraphicsObject(graphicsObject)
{
	this->pWorld = new Matrix(IDENTITY);
	this->pTrans = new Vect(0.0f, 0.0f, 0.0f);
	this->pScale = new Vect(1.0f, 1.0f, 1.0f);
	assert(pWorld);
	assert(pTrans);
	assert(pScale);
	assert(graphicsObject != 0);

	this->rotY = 0.0f;
	this->rotZ = 0.0f;
	this->deltaRot = 0.0f;
}

GraphicsObject *GameObject::getGraphicsObject()
{
	return this->pGraphicsObject;
}

GameObject::~GameObject()
{
	delete this->pWorld;
}

Matrix *GameObject::getWorld()
{
	return this->pWorld;
}


void GameObject::Update(float currentTime)
{
	currentTime;

	// Goal: update the world matrix

	this->rotY += deltaRot;
	this->rotZ += 0.01f;

	Matrix Scale(SCALE, *this->pScale);
	Matrix TransA(TRANS, *this->pTrans);
	Matrix RotY(ROT_Y, this->rotY);
	Matrix RotZ(ROT_Z, this->rotZ);

	// world matrix
	*this->pWorld = Scale * RotY * RotZ * TransA;
}

void GameObject::Process(float currentTime)
{
	// Goal: update the world matrix
	this->Update(currentTime);

	// push to graphics object
	this->pGraphicsObject->SetWorld(*this->pWorld);
}


void GameObject::setWorld(Matrix *world)
{
	assert(world);
	*this->pWorld = *world;
}


void GameObject::Draw()
{
	assert(this->pGraphicsObject);
	this->pGraphicsObject->Render();
}


void GameObject::SetPos(const Vect &pos)
{
	*this->pTrans = pos;
}


void GameObject::SetScale(const Vect &inScale)
{
	*this->pScale = inScale;
}





