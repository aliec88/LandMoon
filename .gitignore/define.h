#pragma once
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define FPS 60
#define PI 3.14159265358979
#define ROTATION_PER_SECOND 3.0
#define GRAVITY 1.63
#define THRUST_PER_SECOND 6000.0
#define SHIPMASS 100.0
#define DISTTOPAD 10
#define SPEEDLAND 10
#define ROTATIONLAND 3.14159265358979/16
#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code)&0x8000)?1:0)
