#include "profile.h"

#include "../../Ludwig/Ludwig/ludwig_net.h"
#pragma comment(lib, "../../Ludwig/Debug/Ludwig.lib")

#include "net.h"

int main()
{


	//alan_talking("127.0.0.1", 9999);
	//for (int i = 0; i < 10000; i++) {
	//	alan_says(net_events::EVENT_TEST, "Hello, Friedrich!", 17);
	//}

	init();
	frame();
	while (render())
	{
		frame();
	}

	deinit();

	return 0;
}
