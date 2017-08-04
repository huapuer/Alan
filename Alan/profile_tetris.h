#pragma once
#include <Windows.h>
#include <stdlib.h> 
#include <time.h>  
#include <irrlicht.h>
#include "../../Ludwig/Ludwig/ludwig_net_sync.h"

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

enum state {
	STATE_NEW_ITEM,
	STATE_REDUCE,
	STATE_COLLAPSE,
	STATE_FALLING,
	STATE_RESET,
};

enum direction {
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT,
};

enum rotate_direction {
	ROTATE_DIRECTION_CLOCKWISE,
	ROTATE_DIRECTION_COUNTERCLOCKWISE,
};

enum item_type {
	ITEM_CUBE,
	ITEM_STICK_HORIZONTAL,
	ITEM_STICK_VERTICAL,
	ITEM_ZIGZAG_HORIZONTAL,
	ITEM_ZIGZAG_VERTICAL,
	ITEM_ZAGZIG_HORIZONTAL,
	ITEM_ZAGZIG_VERTICAL,
	ITEM_PYRAMID_HORIZONTAL,
	ITEM_PYRAMID_VERTICAL,
	ITEM_DIMARYP_HORIZONTAL,
	ITEM_DIMARYP_VERTICAL,
	ITEM_RIGHT_CRUTCH_HORIZONTAL,
	ITEM_RIGHT_CRUTCH_VERTICAL,
	ITEM_RIGHT_CRUTCH_HORIZONTAL2,
	ITEM_RIGHT_CRUTCH_VERTICAL2,
	ITEM_LEFT_CRUTCH_HORIZONTAL,
	ITEM_LEFT_CRUTCH_VERTICAL,
	ITEM_LEFT_CRUTCH_HORIZONTAL2,
	ITEM_LEFT_CRUTCH_VERTICAL2,

	ITEM_TYPE_COUNT,
};

struct item {
	item_type t;
	int x;
	int y;
};

typedef void(*point_func)(int, int, void*);

const int w = 8;
const int h = 32;
const int scale = 20;
int canvas[w*h];
item current_item;
state game_state = STATE_NEW_ITEM;

bool check_reduce() {
	bool ret = false;
	for (int i = 0; i < h; i++) {
		int j = 0;
		for (; j < w; j++) {
			if (canvas[i * w + j] == 0) {
				break;
			}
		}
		if (j == w) {
			ret = true;
			for (int k = 0; k < w; k++) {
				canvas[i * w + k] = 0;
			}
		}
	}
	return ret;
}

bool check_collapse() {
	bool ret = false;
	for (int i = h - 1; i > 0; i--) {
		for (int j = w - 1; j >= 0; j--) {
			if (canvas[(i - 1) * w + j] == 1 && canvas[i * w + j] == 0 && (j > 0 && canvas[i * w + j - 1] == 0 || j < w - 1 && canvas[i * w + j + 1] == 0)) {
				ret = true;
				canvas[i * w + j] = 1;
				canvas[(i - 1) * w + j] = 0;
			}
		}
	}
	return ret;
}

bool check_collapse2() {
	bool ret = false;
	int i = h - 1;
	for (; i > 0; i--) {
		int j = 0;
		for (; j < w; j++) {
			if (canvas[i * w + j] == 1) {
				break;
			}
		}
		if (j == w) {
			for (int k = 0; k < w; k++) {
				if (canvas[(i - 1) * w + k] == 1) {
					ret = true;
					canvas[i * w + k] = 1;
					canvas[(i - 1) * w + k] = 0;
				}
			}
		}
	}
	return ret;
}

void traverse_cube_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1 , param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_cube_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_stick_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 3, i->y, param);
}

void traverse_stick_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 3, i->y, param);
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y, param);
}

void traverse_stick_vertical(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 3, param);
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_zigzag_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y + 1, param);
}

void traverse_zigzag_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y, param);
}

void traverse_zigzag_vertical_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_zigzag_vertical_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
}

void traverse_zagzig_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y, param);
}

void traverse_zagzig_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_zagzig_vertical_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
}

void traverse_zagzig_vertical_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_pyramid_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y + 1, param);
}

void traverse_pyramid_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 1, param);
}

void traverse_pyramid_vertical_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
}

void traverse_pyramid_vertical_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_dimaryp_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y, param);
}

void traverse_dimaryp_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y, param);
}

void traverse_dimaryp_vertical_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_dimaryp_vertical_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 1, param);
}

void traverse_right_crutch_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 2, i->y + 1, param);
}

void traverse_right_crutch_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_right_crutch_vertical_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_right_crutch_vertical_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_right_crutch_horizontal2_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y, param);
}

void traverse_right_crutch_horizontal2_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_right_crutch_vertical2_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_right_crutch_vertical2_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y, param);
}

void traverse_left_crutch_horizontal_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 2, i->y, param);
}

void traverse_left_crutch_horizontal_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x, i->y + 1, param);
}

void traverse_left_crutch_vertical_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y + 2, param);
}

void traverse_left_crutch_vertical_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x, i->y + 1, param);
	pfunc(i->x, i->y, param);
}

void traverse_left_crutch_horizontal2_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 2, i->y, param);
}

void traverse_left_crutch_horizontal2_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 2, i->y + 1, param);
	pfunc(i->x + 2, i->y, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y, param);
}

void traverse_left_crutch_vertical2_left(point_func pfunc, item* i, void* param) {
	pfunc(i->x, i->y + 2, param);
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
}

void traverse_left_crutch_vertical2_right(point_func pfunc, item* i, void* param) {
	pfunc(i->x + 1, i->y + 2, param);
	pfunc(i->x + 1, i->y + 1, param);
	pfunc(i->x + 1, i->y, param);
	pfunc(i->x, i->y + 2, param);
}

void traverse_item(item* i, point_func pfunc, direction d,void* param) {
	switch (i->t) {
	case ITEM_CUBE:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_cube_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_cube_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_STICK_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_stick_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_stick_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_STICK_VERTICAL:
		traverse_stick_vertical(pfunc, i, param);
		break;
	case ITEM_ZIGZAG_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_zigzag_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_zigzag_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_ZIGZAG_VERTICAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_zigzag_vertical_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_zigzag_vertical_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_ZAGZIG_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_zagzig_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_zagzig_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_ZAGZIG_VERTICAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_zagzig_vertical_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_zagzig_vertical_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_PYRAMID_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_pyramid_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_pyramid_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_PYRAMID_VERTICAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_pyramid_vertical_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_pyramid_vertical_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_DIMARYP_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_dimaryp_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_dimaryp_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_DIMARYP_VERTICAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_dimaryp_vertical_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_dimaryp_vertical_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_right_crutch_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_right_crutch_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_VERTICAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_right_crutch_vertical_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_right_crutch_vertical_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_HORIZONTAL2:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_right_crutch_horizontal2_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_right_crutch_horizontal2_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_VERTICAL2:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_right_crutch_vertical2_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_right_crutch_vertical2_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_HORIZONTAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_left_crutch_horizontal_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_left_crutch_horizontal_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_VERTICAL:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_left_crutch_vertical_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_left_crutch_vertical_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_HORIZONTAL2:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_left_crutch_horizontal2_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_left_crutch_horizontal2_right(pfunc, i, param);
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_VERTICAL2:
		switch (d) {
		case DIRECTION_DOWN:
		case DIRECTION_LEFT:
			traverse_left_crutch_vertical2_left(pfunc, i, param);
			break;
		case DIRECTION_RIGHT:
			traverse_left_crutch_vertical2_right(pfunc, i, param);
			break;
		}
		break;
	}
}

void check_down_collision(int x, int y, void* param) {
	*(bool*)param = *(bool*)param || y + 1 == h || canvas[(y + 1) * w + x] == 1;
}

void check_left_collision(int x, int y, void* param) {
	*(bool*)param = *(bool*)param || x - 1 < 0 || canvas[y * w + (x - 1)] == 1;
}

void check_right_collision(int x, int y, void* param) {
	*(bool*)param = *(bool*)param || x + 1 == w || canvas[y * w + x + 1] == 1;
}

void check_outbound_down(int x, int y, void* param) {
	*(bool*)param = *(bool*)param || y >= h || canvas[y * w + x] == 1;
}

void check_outbound_side(int x, int y, void* param) {
	item* i = ((item*)param);
	if (x < 0) {
		i->x += 1;
	}
	else if (x >= w) {
		i->x -= 1;
	}
}

void move_point_down(int x, int y, void* param) {
	canvas[(y + 1) * w + x] = 2;
	canvas[y * w + x] = 0;
}

void move_point_right(int x, int y, void* param) {
	canvas[y * w + x + 1] = 2;
	canvas[y * w + x] = 0;
}

void move_point_left(int x, int y, void* param) {
	canvas[y * w + x - 1] = 2;
	canvas[y * w + x] = 0;
}

void place_point(int x, int y, void* param) {
	canvas[y * w + x] = 1;
}

void clear_point(int x, int y, void* param) {
	canvas[y * w + x] = 0;
}

void mark_point(int x, int y, void* param) {
	if (canvas[y * w + x] == 0) {
		if (param) {
			(*(bool*)param) = true;
		}
		canvas[y * w + x] = 2;
	}
}

bool move_item_down() {
	bool c = false;
	traverse_item(&current_item, check_down_collision, DIRECTION_DOWN, (void*)&c);
	if (!c) {
		traverse_item(&current_item, move_point_down, DIRECTION_DOWN, nullptr);
		current_item.y += 1;
		return true;
	}
	else {
		traverse_item(&current_item, place_point, DIRECTION_DOWN, nullptr);
	}
	return false;
}

void move_item_right() {
	bool c = false;
	traverse_item(&current_item, check_right_collision, DIRECTION_RIGHT, (void*)&c);
	if (!c) {
		traverse_item(&current_item, move_point_right, DIRECTION_RIGHT, nullptr);
		current_item.x += 1;
	}
}

void move_item_left() {
	bool c = false;
	traverse_item(&current_item, check_left_collision, DIRECTION_LEFT, (void*)&c);
	if (!c) {
		traverse_item(&current_item, move_point_left, DIRECTION_LEFT, nullptr);
		current_item.x -= 1;
	}
}

void rotate_item(rotate_direction rd) {
	item_type t;
	int dx;
	int dy;
	switch (current_item.t) {
	case ITEM_CUBE:
		return;
	case ITEM_STICK_HORIZONTAL:
		t = ITEM_STICK_VERTICAL;
		dx = 1;
		dy = -3;
		break;
	case ITEM_STICK_VERTICAL:
		t = ITEM_STICK_HORIZONTAL;
		dx = -1;
		dy = 3;
		break;
	case ITEM_ZIGZAG_HORIZONTAL:
		t = ITEM_ZIGZAG_VERTICAL;
		dx = 1;
		dy = -1;
		break;
	case ITEM_ZIGZAG_VERTICAL:
		t = ITEM_ZIGZAG_HORIZONTAL;
		dx = -1;
		dy = 1;
		break;
	case ITEM_ZAGZIG_HORIZONTAL:
		t = ITEM_ZAGZIG_VERTICAL;
		dx = 0;
		dy = -1;
		break;
	case ITEM_ZAGZIG_VERTICAL:
		t = ITEM_ZAGZIG_HORIZONTAL;
		dx = 0;
		dy = 1;
		break;
	case ITEM_PYRAMID_HORIZONTAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_PYRAMID_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_DIMARYP_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		}
		break;
	case ITEM_PYRAMID_VERTICAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_DIMARYP_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_PYRAMID_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		}
		break;
	case ITEM_DIMARYP_HORIZONTAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_DIMARYP_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_PYRAMID_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		}
		break;
	case ITEM_DIMARYP_VERTICAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_PYRAMID_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_DIMARYP_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_HORIZONTAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_LEFT_CRUTCH_VERTICAL2;
			dx = 0;
			dy = -1;
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_VERTICAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_LEFT_CRUTCH_HORIZONTAL2;
			dx = 0;
			dy = 1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_HORIZONTAL2:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_VERTICAL2;
			dx = 0;
			dy = -1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_LEFT_CRUTCH_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		}
		break;
	case ITEM_RIGHT_CRUTCH_VERTICAL2:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_LEFT_CRUTCH_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_HORIZONTAL2;
			dx = 0;
			dy = 1;
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_HORIZONTAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_LEFT_CRUTCH_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_VERTICAL2;
			dx = 0;
			dy = -1;
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_VERTICAL:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_HORIZONTAL2;
			dx = 0;
			dy = 1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_LEFT_CRUTCH_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_HORIZONTAL2:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_LEFT_CRUTCH_VERTICAL2;
			dx = 0;
			dy = -1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_VERTICAL;
			dx = 0;
			dy = -1;
			break;
		}
		break;
	case ITEM_LEFT_CRUTCH_VERTICAL2:
		switch (rd) {
		case ROTATE_DIRECTION_CLOCKWISE:
			t = ITEM_RIGHT_CRUTCH_HORIZONTAL;
			dx = 0;
			dy = 1;
			break;
		case ROTATE_DIRECTION_COUNTERCLOCKWISE:
			t = ITEM_LEFT_CRUTCH_HORIZONTAL2;
			dx = 0;
			dy = 1;
			break;
		}
		break;
	}
	item i;
	i.t = t;
	i.x = current_item.x + dx;
	i.y = current_item.y + dy;
	bool c = false;
	traverse_item(&i, check_outbound_down, DIRECTION_DOWN, (void*)&c);
	//traverse_item(&i, check_left_collision, DIRECTION_LEFT, (void*)&c);
	//traverse_item(&i, check_right_collision, DIRECTION_RIGHT, (void*)&c);
	if (!c) {
		traverse_item(&i, check_outbound_side, DIRECTION_DOWN, (void*)&i);
		traverse_item(&current_item, clear_point, DIRECTION_DOWN, nullptr);
		current_item.t = t;
		current_item.x = i.x;
		current_item.y = i.y;
		traverse_item(&current_item, mark_point, DIRECTION_DOWN, nullptr);
	}
}

//int test_type= ITEM_RIGHT_CRUTCH_HORIZONTAL;
bool new_item() {
	current_item.t = (item_type)(ITEM_TYPE_COUNT * rand() / (RAND_MAX + 1));
	//current_item.t = (item_type)(test_type % ((int)ITEM_TYPE_COUNT));
	//test_type++;
	current_item.x = 3;
	current_item.y = 1;

	bool c = false;
	traverse_item(&current_item, mark_point, DIRECTION_DOWN, (void*)&c);

	return c;
}

void reset(){
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (i > h * 2 / 3) {
				canvas[i * w + j] = rand() % 2;
			}
			else {
				canvas[i * w + j] = 0;
			}
		}
	}
}

class MyEventReceiver : public IEventReceiver
{
public:
	// This is the one method that we have to implement
	virtual bool OnEvent(const SEvent& event)
	{
		// Remember whether each key is down or up
		if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
			KeyIsDown[event.KeyInput.Key] = true;

		return false;
	}

	// This is used to check whether a key is being held down
	virtual bool IsKeyDown(EKEY_CODE keyCode)
	{
		bool ret = KeyIsDown[keyCode];
		KeyIsDown[keyCode] = false;
		return ret;
	}

	MyEventReceiver()
	{
		for (u32 i = 0; i<KEY_KEY_CODES_COUNT; ++i)
			KeyIsDown[i] = false;
	}

private:
	// We use this array to store the current state of each key
	bool KeyIsDown[KEY_KEY_CODES_COUNT];
};

IrrlichtDevice *device;
video::IVideoDriver* driver;
MyEventReceiver receiver;

bool net_move_left = false;
bool net_move_right = false;
bool net_rotate = false;

#define MODE_NET
//#define MODE_LOCAL

void frame() {
	start:
	switch (game_state) {
	case STATE_NEW_ITEM:
		if (new_item()) {
			game_state = STATE_FALLING;
		}
		else {
			game_state = STATE_RESET;
			goto start;
		}
		break;
	case STATE_FALLING:
		if (!move_item_down()) {
			game_state = STATE_REDUCE;
			goto start;
		}
#ifdef MODE_LOCAL
		if (receiver.IsKeyDown(irr::KEY_KEY_A)) {
			move_item_left();
		}
		if (receiver.IsKeyDown(irr::KEY_KEY_D)) {
			move_item_right();
		}
		if (receiver.IsKeyDown(irr::KEY_KEY_S)) {
			rotate_item(ROTATE_DIRECTION_CLOCKWISE);
		}
#endif

#ifdef MODE_NET
		if (net_move_left) {
			move_item_left();
		}
		if (net_move_right) {
			move_item_right();
		}
		if (net_rotate) {
			rotate_item(ROTATE_DIRECTION_CLOCKWISE);
		}
#endif
		break;
	case STATE_REDUCE:
		if (check_reduce()) {
			game_state = STATE_COLLAPSE;
		}
		else {
			game_state = STATE_NEW_ITEM;
			goto start;
		}
		break;
	case STATE_COLLAPSE:
		if (!check_collapse2()) {
			game_state = STATE_REDUCE;
			goto start;
		}
		break;
	case STATE_RESET:
		reset();
		game_state = STATE_NEW_ITEM;
		goto start;
	}

	Sleep(200);
}

//net
void acts_state(char* c, int size) {
	net_move_left = false;
	net_move_right = false;
	net_rotate = false;
}

void acts_move_left(char* c, int size) {
	net_move_left = true;
	net_move_right = false;
	net_rotate = false;
}

void acts_move_right(char* c, int size) {
	net_move_left = false;
	net_move_right = true;
	net_rotate = false;
}

void acts_rotate(char* c, int size) {
	net_move_left = false;
	net_move_right = false;
	net_rotate = true;
}

int init() {
	alan_acts(net_events::EVENT_STATE, acts_state);
	alan_acts(net_events::EVENT_MOVE_LEFT, acts_move_left);
	alan_acts(net_events::EVENT_MOVE_RIGHT, acts_move_right);
	alan_acts(net_events::EVENT_ROTATE, acts_rotate);
	alan_talking("127.0.0.1", 9999);

	srand((unsigned)time(NULL));

	// create device
	device = createDevice(video::EDT_SOFTWARE,
		core::dimension2d<u32>(w * scale, h * scale), 16, false, false, false, &receiver);

	if (device == 0)
		return 1; // could not create selected driver.

	device->setWindowCaption(L"Irrlicht Engine - 2D Graphics Demo");

	driver = device->getVideoDriver();
}

bool render() {
	if (device->run()) {
		driver->beginScene(true, true, video::SColor(255, 120, 102, 136));

		//core::position2d<s32> m = device->getCursorControl()->getPosition();

		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				if (canvas[i * w + j]) {
					int x = j * scale;
					int y = i * scale;
					driver->draw2DRectangle(video::SColor(100, 255, 255, 255),
						core::rect<s32>(x, y, x+scale, y+scale));
				}
			}
		}

		driver->endScene();

#ifdef MODE_NET
		alan_says(net_events::EVENT_STATE, (char*)canvas, w * h * sizeof(int));
		alan_hearing();
#endif
		return true;
	}
	return false;
}

void deinit() {
	device->drop();
}