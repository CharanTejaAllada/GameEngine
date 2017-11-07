#include"CameraMan.h"

CameraLink::CameraLink()
{

}

CameraLink::~CameraLink()
{
	this->next = 0;
	this->prev = 0;
	this->camData = 0;
}

CameraMan* CameraMan::getHead()
{
	static CameraMan camMan;
	return &camMan;
}

void CameraMan::deleteCameras()
{
	CameraLink *p = active;

	while (p != 0)
	{
		CameraLink *tmp = p;
		p = p->next;

		tmp->camData = 0;
		tmp->next = 0;
		tmp->prev = 0;
	}
}

Camera* CameraMan::FindCamera(CameraName n)
{
	CameraLink *p = active;

	while (p != 0)
	{
		if (p->Name == n)
		{
			break;
		}
		p = p->next;
	}

	return p->camData;
}


Camera* CameraMan::getOtherCamera()
{
	CameraLink *p = active;

	if (p->status)
	{
		p->status = false;
		p->next->status = true;
		p = p->next;
	}
	else
	{
		p->status = true;
		p->next->status = false;
	}
	return p->camData;
}

void CameraMan::Add(Camera *p,CameraName c)
{
	CameraLink *pNode = new CameraLink();
	pNode->camData = p;
	pNode->Name = c;

	if (active == 0)
	{
		pNode->next = 0;
		pNode->prev = 0;
		active = pNode;
		pNode->status = true;
	}
	else
	{
		pNode->status = false;
		pNode->prev = 0;
		pNode->next = active;
		pNode->next->prev = pNode;
		active = pNode;
	}
}
