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

	IMeshSceneNode* node = smgr->addSphereSceneNode(1.0f,4);

	ITexture* texture_red = driver->getTexture("red.bmp");
	ITexture* texture_gray = driver->getTexture("gray.bmp");
	
	if (node)
	{
		node->setMaterialFlag(EMF_LIGHTING, false);
		node->setMaterialTexture(0, texture_red);
	}
	scene::ICameraSceneNode* cam = smgr->addCameraSceneNodeMaya();
	cam->setTarget(vector3df(0, 0, 0));

	alan_acts(net_events::EVENT_TEST, acts_test);

	//alan_talking("127.0.0.1", 9999);
	//for (int i = 0; i < 10000; i++) {
	//	alan_says(net_events::EVENT_TEST, "Hello, Friedrich!", 17);
	//}

	int frame_count = 0;
	while (device->run())
	{
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
	}

	device->drop();

	return 0;
}
