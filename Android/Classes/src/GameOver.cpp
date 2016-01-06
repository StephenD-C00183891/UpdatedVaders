#include "GameOver.h"

USING_NS_CC;

Scene* GameOver::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = GameOver::create();

	scene->addChild(layer);

	return scene;
}


bool GameOver::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//auto label = Label::createWithSystemFont("Hello World", "Arial", 96);

	//label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
	//Vec2 lablepos = label->getAnchorPoint();
	//this->addChild(label, 1);
	auto menuTitle =
		MenuItemImage::create("GameOverScreen/Game_Over.png",
		"GameOverScreen/Game_Over.png");
	auto retryItem =
		MenuItemImage::create("GameOverScreen/Retry_Button.png",
		"GameOverScreen/Retry_Button1(Click).png",
		CC_CALLBACK_1(GameOver::activateGameScene, this));
	auto mainMenuItem =
		MenuItemImage::create("GameOverScreen/Menu_Button.png",
		"GameOverScreen/Menu_Button(Click).png",
		CC_CALLBACK_1(GameOver::activateMainMenuScene, this));
	auto HighScoreItem =
		MenuItemImage::create("GameOverScreen/High_Scores.png",
		"GameOverScreen/High_Scores.png",
		CC_CALLBACK_1(GameOver::activateHighScoreScene, this));
	auto menu = Menu::create(menuTitle, retryItem, mainMenuItem, HighScoreItem,
		NULL);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	menu->alignItemsVerticallyWithPadding(visibleSize.height / 6);
	this->addChild(menu);
	return true;
}

void GameOver::activateGameScene(cocos2d::Ref *pSender)
{
	auto scene = GameScene::createScene();
	Director::getInstance()->replaceScene(scene);
}

void GameOver::activateHighScoreScene(cocos2d::Ref *pSender)
{
	auto scene = HighScore::createScene();
	Director::getInstance()->replaceScene(scene);
	//m_Score->fillScoreBoard(gscene->playerOneScore, gscene->playerTwoScore);
}


void GameOver::activateMainMenuScene(cocos2d::Ref *pSender)
{
	auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(scene);
}