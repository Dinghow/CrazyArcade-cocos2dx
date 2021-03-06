#include "LoginScene.h"
#include "MenuScene.h"
#include "../GamePlay/HallScene.h"

Scene* Login::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Login::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Login::init()
{
	if (!Layer::init())
	{
		return false;
	}
	
	//get the csb file and the elements on it
	auto rootNode = CSLoader::createNode("LoginScene/LoginScene.csb");
	Layout* background = (Layout*)rootNode->getChildByName("background");
	Button* btnMenu = (Button*)Helper::seekWidgetByName(background, "menubutton");
	Button* btnStartGame = (Button*)Helper::seekWidgetByName(background, "playbutton");
	Button* btnExit = (Button*)Helper::seekWidgetByName(background, "exitbutton");

	//set touch event listener on the buttons 
	btnMenu->addTouchEventListener(CC_CALLBACK_2(Login::MenuTouch, this));
	btnStartGame->addTouchEventListener(CC_CALLBACK_2(Login::StartGameTouch, this));
	btnExit->addTouchEventListener(CC_CALLBACK_2(Login::ExitTouch, this));

	addChild(rootNode);
	//play background music after start
	this->scheduleOnce(schedule_selector(Login::playMusic),0.5f);

	//add cursor
	auto cursor = Sprite::create("cursor_nor.png");
	this->_cursor = Node::create();
	this->_cursor->addChild(cursor);
	this->addChild(this->_cursor, 10000);

	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseMove = [&](cocos2d::EventMouse* event) {
		Point mouse = event->getLocation();
		mouse.y = 600 - mouse.y;

		this->_cursor->setPosition(Point(mouse.x + 20, mouse.y - 30));
	};
	listenerMouse->onMouseDown = [&](cocos2d::EventMouse* event) {
		this->_cursor->removeAllChildren();
		auto cursor = Sprite::create("cursor_pre.png");
		this->_cursor->addChild(cursor);
	};
	listenerMouse->onMouseUp = [&](cocos2d::EventMouse* event) {
		this->_cursor->removeAllChildren();
		auto cursor = Sprite::create("cursor_nor.png");
		this->_cursor->addChild(cursor);
	};
	this->_eventDispatcher->addEventListenerWithFixedPriority(listenerMouse, 1);

	return true;
}

//set the touch event after click menubutton
void Login::MenuTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		//transfer to MenuScene
		auto director = Director::getInstance();
		auto scene = MenuTable::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

		break;
	}
}

//set the touch event after click playbutton
void Login::StartGameTouch(Ref* pSender, Widget::TouchEventType type) {
	switch (type) {
	case Widget::TouchEventType::ENDED:
		auto director = Director::getInstance();
		//transfer to MapScene
		auto scene = Hall::createScene();
		auto transition = TransitionCrossFade::create(1.0f, scene);
		director->pushScene(transition);

		break;
	}
}

//set the touch event after click exitbutton
void Login::ExitTouch(Ref* pSender, Widget::TouchEventType type) {
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

void Login::playMusic(float dt) {
	SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Prepare.mp3", true);
}

void Login::onEnter() {
	Layer::onEnter();
}

void Login::onEnterTransitionDidFinish() {
	Layer::onEnterTransitionDidFinish();
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("MusicSource/bg/Prepare.mp3", true);
}

void Login::onExit() {
	Layer::onExit();
}

void Login::onExitTransitionDidStart() {
	Layer::onExitTransitionDidStart();
}

void Login::cleanup() {
	Layer::cleanup();
}