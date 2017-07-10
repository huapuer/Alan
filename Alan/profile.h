#pragma once

#define PROFILE_TETRIS
//#define PROFILE_DEBUG

#ifdef PROFILE_TETRIS
#include "profile_tetris.h"
#endif // PROFILE_TETRIS

#ifdef PROFILE_DEBUG
#include "profile_debug.h"
#endif // PROFILE_DEBUG
