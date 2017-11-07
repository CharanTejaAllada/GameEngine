#ifndef CAMERA_MAN_H
#define CAMERA_MAN_H

class  Camera;

enum  CameraName
{
	one,
	two,
	three,
	four,
	uninitialised,
};


class CameraLink
{
public:
	CameraLink();
	~CameraLink();
	CameraLink *next;
	CameraLink *prev;
	Camera	   *camData;
	CameraName  Name;
	bool		status;
};

class CameraMan
{
public:
	void Add(Camera *p, CameraName c);
	void deleteCameras();
	Camera* FindCamera(CameraName n);
	Camera* getOtherCamera();
	CameraMan* getHead();
	CameraLink *active;
};



/*

void CameraMan::initialise()
{
	pHead = new CameraMan();
}*/

#endif CAMERA_MAN_H