#pragma once
#include <irrlicht.h>
#include <windows.h>
using namespace irr;
using namespace gui;

#include <stdio.h>
#include "../../Ludwig/Ludwig/ludwig_net.h"

IGUIEnvironment* guienv;

void acts_test(char* c, int size) {
	guienv->clear();
	guienv->addStaticText(L"From Friedrich£º", rect<s32>(10, 10, 260, 22), true);
	wchar_t* wp = new wchar_t[size];
	MultiByteToWideChar(CP_ACP, 0, c, -1, wp, size);
	guienv->addStaticText(wp, rect<s32>(70, 10, 260, 22), true);
}