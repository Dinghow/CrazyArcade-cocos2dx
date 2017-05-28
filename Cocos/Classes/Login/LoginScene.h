#ifndef __LOGIN_SCENE_H__
#define __LOGIN_SCENE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d::ui;

class Login : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Login);

private:
	void MenuTouch(cocos2d::Ref* pSender, Widget::TouchEventType type);
	void StartGameTouch(Ref* pSender, Widget::TouchEventType type);
	void ExitTouch(Ref* pSender, Widget::TouchEventType type);
};

#endif // __LOGIN_SCENE_H__
#pragma once
