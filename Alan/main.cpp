#include <irrlicht.h>

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

#include "../../Ludwig/Ludwig/ludwig_net.h"
#pragma comment(lib, "../../Ludwig/Debug/Ludwig.lib")

#include "net.h"

int main()
{
	IrrlichtDevice *device =
		createDevice(video::EDT_SOFTWARE, dimension2d<u32>(640, 480), 16,
			false, false, false, 0);

	if (!device)
		return 1;
	device->setWindowCaption(L"Hello World! - Irrlicht Engine Demo");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	guienv = device->getGUIEnvironment();
	guienv->addStaticText(L"Hello World! This is the Irrlicht Software renderer!",
		rect<s32>(10, 10, 260, 22), true);

	IAnimatedMesh* mesh = smgr->getMesh("D:/irrlicht-1.8.4/media/sydney.md2");
	if (!mesh)
	{
		device->drop();
		return 1;
	}
	//IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	IMeshSceneNode* node = smgr->addSphereSceneNode();
	
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMD2Animation(scene::EMAT_STAND);
		node->setMaterialTexture(0, driver->getTexture("D:/irrlicht-1.8.4/media/sydney.bmp"));
	}
	scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeMaya();
		//addCameraSceneNode(0, vector3df(0, 30, -40), vector3df(0, 5, 0));
	cam->setTarget(vector3df(0, 0, 0));
	//((scene::ISceneNodeAnimatorCameraMaya*)cam)->setZoomSpeed(100.0f);

	alan_acts(net_events::EVENT_TEST, acts_test);

	alan_talking("127.0.0.1", 9999);
	//alan_says(net_events::EVENT_TEST, "Hello, Friedrich!", 17);

	while (device->run())
	{
		driver->beginScene(true, true, SColor(255, 100, 101, 140));

		smgr->drawAll();
		guienv->drawAll();

		driver->endScene();
	}

	device->drop();

	return 0;
}
