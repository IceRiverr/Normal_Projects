
#pragma once

//��ȫ�ͷ�COM�ڶ���ĺ�
#define SAFE_RELEASE(p) {if(p){(p)->Release(); p=0;}}
