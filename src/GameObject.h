#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "MathEngine.h"
#include "ShaderObject.h"
#include "Model.h"
#include "GraphicsObject.h"
#include "PCSNode.h"

enum ModelType {
	Sphere,
	Pyramid,
	Cube,
	Cylinder,
};

class GameObject : public PCSNode
{
public:
	GameObject(GraphicsObject  *graphicsObject);

	// Big four
	GameObject() = delete;
	GameObject( const GameObject &) = delete;
	GameObject &operator=(GameObject &) = delete;
	~GameObject();

	void Update(float t);

    void Process(float t);
	void Draw();

	GraphicsObject *getGraphicsObject();



	Matrix *getWorld();
	void setWorld(Matrix *world);

	void SetPos( const Vect &pos );
	void SetScale( const Vect &scale );
	float deltaRot;
	ModelType type;
protected:
	Matrix *pWorld;

private:
	GraphicsObject  *pGraphicsObject;

	Vect *pTrans;
	Vect *pScale;
	float rotY;
	float rotZ;

};


#endif