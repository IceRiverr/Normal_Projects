
#pragma once

//安全释放COM口定义的宏
#define SAFE_RELEASE(p) {if(p){(p)->Release(); p=0;}}
