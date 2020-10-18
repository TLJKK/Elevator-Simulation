#include "WorldTime.h"
#include<ctime>

WorldTime* WorldTime::_instance = nullptr;

WorldTime* WorldTime::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new (std::nothrow)WorldTime;
		_instance->init();
	}
	return _instance;
}

bool WorldTime::init()
{
	if (!Sprite::init())
	{
		return false;
	}
	DelayBegin = DelayEnd = DelayTime = 0;
	return true;
}

clock_t  WorldTime::getTime()
{
	return clock()- DelayTime;
}