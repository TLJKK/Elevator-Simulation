#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "BgScene.h"
using namespace cocos2d;
 
class help : public cocos2d::Layer
{
public:
	help();
	~help();
	virtual bool init();
	CREATE_FUNC(help);
	ui::Scale9Sprite* box;
	ui::Button* end_gameBtn;
	Bg* to;
	virtual void registerCallback(std::function<void()>continueCallback);
	virtual void onEnter();//show the fault there is less of ';' ,the possible season is the namespace;
protected:
	std::function<void()>endGamefunc;
private:
};
