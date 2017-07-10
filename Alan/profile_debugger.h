#pragma once
#include <stdlib.h> 
#include <time.h>  
#include <irrlicht.h>

#include "net.h"

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

IrrlichtDevice *device;
video::IVideoDriver* driver;
ISceneManager* smgr;
IMeshSceneNode* node;
int frame_count = 0;
ITexture* texture_red;
ITexture* texture_gray;

int init() {
	device =
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

	if (!device)
		return 1;
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	driver = device->getVideoDriver();
	smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	node = smgr->addSphereSceneNode(1.0f, 4);

	texture_red = driver->getTexture("red.bmp");
	texture_gray = driver->getTexture("gray.bmp");

	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, texture_red);
	}
	scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeMaya();
	cam->setTarget(vector3df(0, 0, 0));

	alan_acts(net_events::EVENT_TEST, acts_test);
}

void frame() {

}

bool render() {
	if (device->run()) {
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();

		frame_count++;
		if (frame_count % 1000 == 0) {
			if ((frame_count / 1000) % 2 == 0) {
				node->setMaterialTexture(0, texture_red);
			}
			else {
				node->setMaterialTexture(0, texture_gray);
			}
		}
		return true;
	}
	return false;
}

void deinit() {
	device->drop();
}