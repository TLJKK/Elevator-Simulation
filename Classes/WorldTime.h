#pragma once
#include<cocos2d.h>
#include<ctime>
USING_NS_CC;

class WorldTime : public Sprite
{
public:
	CREATE_FUNC(WorldTime);
	virtual bool init();
	static WorldTime* getInstance();
	clock_t  getTime();
	DWORD DelayBegin, DelayEnd, DelayTime;
private:
	static WorldTime* _instance;
};