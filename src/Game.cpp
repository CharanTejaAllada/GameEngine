#include <assert.h>
#include <sb6.h>
#include <math.h>
#include <vmath.h>
#include "GameObject.h"
#include "MathEngine.h"
#include "Game.h"
#include "ShaderObject.h"
#include "CubeModel.h"
#include "GraphicsObject.h"
#include "GraphicsObject_ColorByPosition.h"
#include "GraphicsObject_Wireframe.h"
#include "sb6ktx.h"
#include "GraphicsObject_FlatTexture.h"
#include "TextureManager.h"
#include "InputMan.h"
#include "InputTest.h"
#include "Trace.h"
#include "Camera.h"
#include "GameObjectMan.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ConstColor.h"
#include "CameraMan.h"

Camera *pCam = 0;
CameraMan *manager;

//constructor
Game::Game(const char* windowName, const int Width, const int Height)
	:Engine(windowName, Width, Height)
{

}

//Init()
void Game::Initialize()
{
	InputMan::Create();
	manager = new CameraMan();
}

//to load sprites etc
void Game::LoadContent()
{

	//first Camera
	pCam = new Camera();
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);;
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(-0.7f, 7.71f, 0.53f));
	pCam->updateCamera();
	manager->Add(pCam, CameraName::three);
//second
	pCam = new Camera();
	pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);;
	pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(0.0f, 0.0f, 6.20f));
	pCam->updateCamera();
	manager->Add(pCam, CameraName::one);

	////Third Camera
	//pCam = new Camera();
	//pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);;
	//pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	//pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(-0.7f,7.71f,0.53f));
	//pCam->updateCamera();
	//manager->Add(pCam, CameraName::three);

	////Fourth Camera
	//pCam = new Camera();
	//pCam->setViewport(0, 0, this->info.windowWidth, this->info.windowHeight);;
	//pCam->setPerspective(50.0f, float(pCam->getScreenWidth()) / float(pCam->getScreenHeight()), 0.10f, 1000.0f);
	//pCam->setOrientAndPosition(Vect(0.0f, 1.0f, 0.0f), Vect(0.0f, 0.0f, 0.0f), Vect(8.0f, 0.0f, -3.9f));
	//pCam->updateCamera();
	//manager->Add(pCam, CameraName::four);

	// Load the model
	CubeModel *pCubeModel = new CubeModel("cubeModel.azul");
	assert(pCubeModel);

	CubeModel *pCylinderModel = new CubeModel("cylinder.azul");
	assert(pCylinderModel);

	CubeModel *pSphereModel = new CubeModel("sphere.azul");
	assert(pSphereModel);

	CubeModel *pPyramidModel = new CubeModel("pyramid.azul");
	assert(pPyramidModel);

	// Create/Load Shader 
	ShaderObject *pShaderObject_color = new ShaderObject(ShaderName::COLOR_LIGHT, "colorRender");
	assert(pShaderObject_color);
	ShaderObject *pShaderObject_texture = new ShaderObject(ShaderName::TEXTURE_SIMPLE, "textureRender");
	assert(pShaderObject_texture);
	ShaderObject *pShaderObject_textureLight = new ShaderObject(ShaderName::TEXTURE_POINT_LIGHT, "texturePointLightDiff");
	assert(pShaderObject_textureLight);
	ShaderObject *pShaderObject_constColor = new ShaderObject(ShaderName::CONST_COLOR, "constcolorRender");
	assert(pShaderObject_constColor);

	//---------------------------

	TextureMan::addTexture("Rocks.tga", TextureName::ROCKS);
	TextureMan::addTexture("Stone.tga", TextureName::STONES);
	TextureMan::addTexture("RedBrick.tga", TextureName::RED_BRICK);
	TextureMan::addTexture("Duckweed.tga", TextureName::DUCKWEED);
	//---------------------------

	GraphicsObject_ColorByPosition *pGraphics_ColorByPosition;
	GraphicsObject_Wireframe *pGraphics_Wireframe;
	GraphicsObject_FlatTexture *pGraphics_FlatTexture;
	GraphicsObject_TextureLight *pGraphics_TextureLight;
	GraphicsObject_ConstColor *pGraphics_ConstColor;

	GameObject *pGameObj;
	Vect color(1.50f, .0f, .0f, .0f);
	Vect pos(1, 1, 1);

	//First column------------------------------------------------------------------
	pGraphics_ColorByPosition = new GraphicsObject_ColorByPosition(pCubeModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_ColorByPosition);
	pGameObj->SetPos(Vect(-3.0f, 0.0f, 0.0f));
	pGameObj->deltaRot = -0.07f;
	pGameObj->SetScale(Vect(0.5f, 0.5f, 0.50f));
//	pGameObj->type = ModelType::Cube;
	GameObjectMan::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pCubeModel, pShaderObject_texture, TextureName::RED_BRICK);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(-3.0f, 1.0f, 0.0f));
	pGameObj->deltaRot = 0.1f;
	pGameObj->type = ModelType::Cube;
	pGameObj->SetScale(Vect(0.5f, 0.5f, 0.50f));
	GameObjectMan::Add(pGameObj);

	color.set(1.250f, 1.250f, 1.250f, 1.0f);
	pGraphics_ConstColor = new GraphicsObject_ConstColor(pCubeModel, pShaderObject_constColor, color, pos);
	pGameObj = new GameObject(pGraphics_ConstColor);
	pGameObj->SetPos(Vect(-3.0f, -1.0f, 0.0f));
	pGameObj->deltaRot = 0.002f;
	//	pGameObj->type = ModelType::Cube;
	pGameObj->SetScale(Vect(0.5f, 0.5f, 0.50f));
	GameObjectMan::Add(pGameObj);

	pGraphics_Wireframe = new GraphicsObject_Wireframe(pCubeModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(-3.0f, 2.0f, 0.0f));
	pGameObj->deltaRot = 0.052f;
	//	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(0.5f, 0.5f, 0.50f));
	GameObjectMan::Add(pGameObj);


	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pCubeModel, pShaderObject_texture, TextureName::DUCKWEED);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(-3.0f, -2.0f, 0.0f));
	pGameObj->deltaRot = -0.013f;
	pGameObj->type = ModelType::Cube;
	pGameObj->SetScale(Vect(0.5f, 0.5f, 0.50f));
	GameObjectMan::Add(pGameObj);
//2nd column ----------------------------------------------------------------------
	pGraphics_Wireframe = new GraphicsObject_Wireframe(pCylinderModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(-1.5f, 0.0f, 0.0f));
	pGameObj->deltaRot = 0.052f;
//	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(0.2f, 0.2f, 0.20f));
	GameObjectMan::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pCylinderModel, pShaderObject_texture, TextureName::ROCKS);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(-1.5f, 2.0f, 0.0f));
	pGameObj->deltaRot = -0.013f;
	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(0.2f, 1.0f, 0.20f));
	GameObjectMan::Add(pGameObj);

	pGraphics_ColorByPosition = new GraphicsObject_ColorByPosition(pCylinderModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_ColorByPosition);
	pGameObj->SetPos(Vect(-1.5f, -1.0f, 0.0f));
	pGameObj->deltaRot = -0.007f;
	//	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(0.2f, 0.2f, 0.20f));
	GameObjectMan::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pCylinderModel, pShaderObject_texture, TextureName::STONES);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(-1.5f, -2.0f, 0.0f));
	pGameObj->deltaRot = -0.013f;
	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(0.2f, 0.2f, 0.20f));
	GameObjectMan::Add(pGameObj);

	//3rd column------------------------------------------------------------------------


	pGraphics_TextureLight = new GraphicsObject_TextureLight(pSphereModel, pShaderObject_textureLight, TextureName::DUCKWEED, color, pos);
	pGameObj = new GameObject(pGraphics_TextureLight);
	pGameObj->SetPos(Vect(1.9f, 0.0f, 0.0f));
	pGameObj->deltaRot = -0.065f;
	pGameObj->type = ModelType::Sphere;
	pGameObj->SetScale(Vect(0.4f, 0.4f, 0.40f));
	GameObjectMan::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pSphereModel, pShaderObject_texture, TextureName::STONES);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(1.9f, 1.0f, 0.0f));
	pGameObj->deltaRot = 0.03f;
	pGameObj->type = ModelType::Sphere;
	pGameObj->SetScale(Vect(0.4f, 0.4f, 0.40f));
	GameObjectMan::Add(pGameObj);

	pGraphics_Wireframe = new GraphicsObject_Wireframe(pSphereModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(1.9f, -1.0f, 0.0f));
	pGameObj->deltaRot = 0.082f;
//	pGameObj->type = ModelType::Sphere;
	pGameObj->SetScale(Vect(0.4f, 0.4f, 0.40f));
	GameObjectMan::Add(pGameObj);

	color.set(1.50f, 1.0f, 0.0f, 0.0f);
	pGraphics_ConstColor = new GraphicsObject_ConstColor(pSphereModel, pShaderObject_constColor, color, pos);
	pGameObj = new GameObject(pGraphics_ConstColor);
	pGameObj->SetPos(Vect(1.9f, -2.0f, 0.0f));
	pGameObj->deltaRot = 0.002f;
	//	pGameObj->type = ModelType::Cube;
	pGameObj->SetScale(Vect(0.5f, 0.5f, 0.50f));
	GameObjectMan::Add(pGameObj);

	//4th column
	pGraphics_Wireframe = new GraphicsObject_Wireframe(pPyramidModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_Wireframe);
	pGameObj->SetPos(Vect(0.5f, -1.0f, 0.0f));
	pGameObj->deltaRot = 0.092f;
	//	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(0.2f, 1.2f, 0.50f));
	GameObjectMan::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pPyramidModel, pShaderObject_texture, TextureName::DUCKWEED);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(0.5f, 2.0f, 0.0f));
	pGameObj->deltaRot = -0.013f;
	pGameObj->type = ModelType::Pyramid;
	pGameObj->SetScale(Vect(1.0f, 0.5f, 1.20f));
	GameObjectMan::Add(pGameObj);

	pGraphics_ColorByPosition = new GraphicsObject_ColorByPosition(pPyramidModel, pShaderObject_color);
	pGameObj = new GameObject(pGraphics_ColorByPosition);
	pGameObj->SetPos(Vect(0.5f, 0.5f, 0.0f));
	pGameObj->deltaRot = -0.17f;
	//	pGameObj->type = ModelType::Cylinder;
	pGameObj->SetScale(Vect(1.0f, 0.5f, 0.20f));
	GameObjectMan::Add(pGameObj);

	pGraphics_FlatTexture = new GraphicsObject_FlatTexture(pPyramidModel, pShaderObject_texture, TextureName::RED_BRICK);
	pGameObj = new GameObject(pGraphics_FlatTexture);
	pGameObj->SetPos(Vect(0.5f, -2.0f, 0.0f));
	pGameObj->deltaRot = -0.013f;
	pGameObj->type = ModelType::Pyramid;
	pGameObj->SetScale(Vect(0.8f, 0.8f, 0.80f));
	GameObjectMan::Add(pGameObj);


	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
}


Vect obj(1.0f, 0.0f, 0.0f);
void Game::Update(float currentTime)
{
	//KeyboardTest();
	//MouseTest();

	pCam->updateCamera();

	GameObjectMan::Update(currentTime);

	Keyboard *pKeyCam = InputMan::GetKeyboard();

	Vect vUp;
	Vect vLookAt;
	Vect vPos;
	pCam->getLookAt(vLookAt);
	pCam->getUp(vUp);
	pCam->getPos(vPos);

	Trace::out("camera: pos:%f %f %f  at:%f %f %f \n", vPos[x], vPos[y], vPos[z], vLookAt[x], vLookAt[y], vLookAt[z]);

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_ARROW_UP) == true)
	{
		Vect vPos2 = vPos;
		vPos2[z] -= 0.04f;

		if (vPos2[z] > 0.5f)
		{
			pCam->setOrientAndPosition(vUp, vLookAt, vPos2);
		}
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_ARROW_DOWN) == true)
	{
		Vect vPos2 = vPos;
		vPos2[z] += 0.04f;
		pCam->setOrientAndPosition(vUp, vLookAt, vPos2);
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT) == true)
	{
		Vect vPos2 = vPos;
		Vect vLookAt2 = vLookAt;
		vPos2[x] += 0.04f;
		vLookAt2[x] += 0.04f;
		pCam->setOrientAndPosition(vUp, vLookAt2, vPos2);
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_ARROW_LEFT) == true)
	{

		Vect vPos2 = vPos;
		Vect vLookAt2 = vLookAt;
		vPos2[x] -= 0.04f;
		vLookAt2[x] -= 0.04f;
		pCam->setOrientAndPosition(vUp, vLookAt2, vPos2);
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_END) == true)
	{

		Vect vPos2 = vPos;
		Vect vLookAt2 = vLookAt;
		vPos2[y] -= 0.04f;
		vLookAt2[y] -= 0.04f;
		pCam->setOrientAndPosition(vUp, vLookAt2, vPos2);
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_DELETE) == true)
	{

		Vect vPos2 = vPos;
		Vect vLookAt2 = vLookAt;
		vPos2[y] += 0.04f;
		vLookAt2[y] += 0.04f;
		pCam->setOrientAndPosition(vUp, vLookAt2, vPos2);
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_D))
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		tar = obj;

		Matrix Trans(TRANS, tar);
		Matrix NegTrans(TRANS, -tar);

		Matrix Rot;
		Rot.set(upNorm, +0.01f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->setHelper(up, tar, pos);
	}

	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_A))
	{

		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);



		tar = obj;

		Matrix Trans(TRANS, tar);
		Matrix NegTrans(TRANS, -tar);

		Matrix Rot;
		Rot.set(upNorm, -0.01f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->setHelper(up, tar, pos);
	}



	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_S))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);

		tar = obj;


		Matrix Trans(TRANS, tar);
		Matrix NegTrans(TRANS, -tar);
		Matrix Rot;
		Rot.set(rightNorm, 0.01f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->setHelper(up, tar, pos);
	}


	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_W))
	{
		Vect pos;
		Vect tar;
		Vect up;
		Vect upNorm;
		Vect forwardNorm;
		Vect rightNorm;

		pCam->getHelper(up, tar, pos, upNorm, forwardNorm, rightNorm);


		tar = obj;

		Matrix Trans(TRANS, tar);
		Matrix NegTrans(TRANS, -tar);
		Matrix Rot;
		Rot.set(rightNorm, -0.01f);

		Matrix M = NegTrans * Rot * Trans;

		up = up * M;
		pos = pos * M;
		tar = tar * M;

		pCam->setHelper(up, tar, pos);
	}

	pKeyCam = InputMan::GetKeyboard();
	if (pKeyCam->GetKeyState(AZUL_KEY::KEY_C) == true)
	{
		pCam = manager->getOtherCamera();
	}


	Keyboard *pKey = InputMan::GetKeyboard();
	if (pKey->GetKeyState(AZUL_KEY::KEY_1) == true)
	{
		GameObjectMan::UpdateModel(ModelType::Cylinder, TextureName::RED_BRICK);
		GameObjectMan::UpdateModel(ModelType::Pyramid, TextureName::RED_BRICK);
		GameObjectMan::UpdateModel(ModelType::Sphere, TextureName::RED_BRICK);
		GameObjectMan::UpdateModel(ModelType::Cube, TextureName::RED_BRICK);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_2) == true)
	{
		GameObjectMan::UpdateModel(ModelType::Cylinder, TextureName::ROCKS);
		GameObjectMan::UpdateModel(ModelType::Pyramid, TextureName::ROCKS);
		GameObjectMan::UpdateModel(ModelType::Sphere, TextureName::ROCKS);
		GameObjectMan::UpdateModel(ModelType::Cube, TextureName::ROCKS);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_3) == true)
	{
		GameObjectMan::UpdateModel(ModelType::Cylinder, TextureName::STONES);
		GameObjectMan::UpdateModel(ModelType::Pyramid, TextureName::STONES);
		GameObjectMan::UpdateModel(ModelType::Sphere, TextureName::STONES);
		GameObjectMan::UpdateModel(ModelType::Cube, TextureName::STONES);
	}
	if (pKey->GetKeyState(AZUL_KEY::KEY_4) == true)
	{
		GameObjectMan::UpdateModel(ModelType::Cylinder, TextureName::DUCKWEED);
		GameObjectMan::UpdateModel(ModelType::Pyramid, TextureName::DUCKWEED);
		GameObjectMan::UpdateModel(ModelType::Sphere, TextureName::DUCKWEED);
		GameObjectMan::UpdateModel(ModelType::Cube, TextureName::DUCKWEED);
	}
	
}

//rendering here
void Game::Draw()
{
	GameObjectMan::Draw();
}

//
void Game::UnLoadContent()
{
	manager->deleteCameras();

}


//screen color overloads
void Game::ClearBufferFunc()
{
	const GLfloat grey[] = { 0.1f, 0.0f, 0.0f, 0.0f };
	const GLfloat one = 1.0f;

	glViewport(0, 0, info.windowWidth, info.windowHeight);
	glClearBufferfv(GL_COLOR, 0, grey);
	glClearBufferfv(GL_DEPTH, 0, &one);
}
