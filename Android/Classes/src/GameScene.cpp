#include "GameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();
	auto layer = GameScene::create();

	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	playerOneScore = 0;
	playerTwoScore = 0;

	//if (Mute::muted == false)
	//{
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("GameScreen/BGM.mp3", true);
	//	CocosDenshion::SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5f);
	//}

	wave = 1;
	for (int i = 0; i < 6; i++)
	{
		m_ScoreBoard.push_back(0);
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	auto pauseItem =
		MenuItemImage::create("GameScreen/Pause_Button.png",
		"GameScreen/Pause_Button(Click).png",
		CC_CALLBACK_1(GameScene::activatePauseScene, this));
	
	pauseItem->setPosition(Point(visibleSize.width/1.05,visibleSize.height / 2));

	buttonLeft = cocos2d::Sprite::create("GameScreen/buttonLeft.png");
	buttonLeft->setPosition(Point(visibleSize.width/20, visibleSize.height / 13));

	buttonLeft2 = cocos2d::Sprite::create("GameScreen/buttonLeft.png");
	buttonLeft2->setPosition(Point(visibleSize.width / 20, visibleSize.height / 1.1f));
	player1istouchedLeft = false;
	buttonRight = cocos2d::Sprite::create("GameScreen/buttonRight.png");
	buttonRight->setPosition(Point(visibleSize.width /1.05f, visibleSize.height / 13));

	buttonRight2 = cocos2d::Sprite::create("GameScreen/buttonRight.png");
	buttonRight2->setPosition(Point(visibleSize.width / 1.05f, visibleSize.height / 1.1f));
	addBackGroundSprite(visibleSize);
	m_gameState = GameStates::GameInit;
	alive = true;
	addAI();
	createPlayer(); // call createTowerBases() here.
	label = Label::createWithTTF("Player one Score: " + std::to_string(playerOneScore), "fonts/Marker Felt.ttf", 20);
	label->setPosition(Point(visibleSize.width / 1.3, visibleSize.height*0.6 / 30));
	this->addChild(label);

	label_two = Label::createWithTTF("Player two Score: " + std::to_string(playerTwoScore), "fonts/Marker Felt.ttf", 20);
	label_two->setPosition(Point(visibleSize.width / 1.3, visibleSize.height / 1.05));
	label_two->setScaleY(-1);
	label_two->setScaleX(-1);
	this->addChild(label_two);

	WaveLabel = Label::createWithTTF("Level : " + std::to_string(wave), "fonts/Marker Felt.ttf", 20);
	WaveLabel->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(WaveLabel);

	createShields(visibleSize);
	auto menu = Menu::create(pauseItem, buttonLeft, buttonLeft2, buttonRight, buttonRight2, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	this->scheduleUpdate(); // add this
	return true;
}

void GameScene::activatePauseScene(Ref *pSender)
{
	
	auto scene = PauseMenu::createScene();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();
	Director::getInstance()->pushScene(scene);
}
void GameScene::addBackGroundSprite(cocos2d::Size const & visibleSize)
{
	auto backgroundSprite = cocos2d::Sprite::create("GameScreen/Background.png");
	auto backgroundSprite2 = cocos2d::Sprite::create("GameScreen/level2.png");
	auto backgroundSprite3 = cocos2d::Sprite::create("GameScreen/level3.png");
	auto backgroundSprite4 = cocos2d::Sprite::create("GameScreen/level4.png");
	auto backgroundSprite5 = cocos2d::Sprite::create("GameScreen/level5.png");
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	if (wave == 1)
	{
	
		backgroundSprite->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
		this->addChild(backgroundSprite, -5);
	}
	if (wave == 2)
	{
		backgroundSprite2->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
		this->addChild(backgroundSprite2, -4);
	}
	if (wave == 3)
	{
		backgroundSprite3->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
		this->addChild(backgroundSprite3, -3);
	}
	if (wave == 4)
	{
		backgroundSprite4->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
		this->addChild(backgroundSprite4, -2);
	}
	if (wave == 5)
	{
		backgroundSprite5->setPosition(Point((visibleSize.width / 2), (visibleSize.height / 2)));
		this->addChild(backgroundSprite5, -1);
	}
}

void GameScene::activateGameOverScene()
{
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();	
	auto scene = GameOver::createScene();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseAllEffects();	
	auto scene1 = Director::getInstance()->getRunningScene();
	Director::getInstance()->replaceScene(scene);	
}

void GameScene::createPlayer()
{
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_player_base_file);

	m_Player1 = new Player(Vec2(visibleSize.width/2, visibleSize.height/15), m_gameState);
	m_Player2 = new Player(Vec2(visibleSize.width / 2, visibleSize.height / 1.07), m_gameState);

	spritebatch->addChild(m_Player1->spritereturn(), 1);
	spritebatch->addChild(m_Player2->spritereturn(), 1);

	m_Player2->spritereturn()->setRotation(180.0f);
	this->addChild(spritebatch, 1, PLAYERS_SPRITE_BATCH);
	this->addChild(spritebatch, 1, PLAYERS_SPRITE_BATCH);

}


void GameScene::createShields(cocos2d::Size const & visibleSize){
        
	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_shieldImage);
	for (int i = 0; i < 6; i++)
	{
		if (i == 1 )
		{
			position = Vec2(visibleSize.width/10, visibleSize.height / 5);
		}
		if (i == 3)
		{
			position = Vec2(visibleSize.width / 2, visibleSize.height / 5);
		}
		if (i == 5)
		{
			position = Vec2(visibleSize.width / 1.3, visibleSize.height / 5);
		}
		if (i == 0)
		{
			position = Vec2(visibleSize.width / 10, visibleSize.height / 1.25);
		}
		if (i == 2)
		{
			position = Vec2(visibleSize.width / 2, visibleSize.height / 1.25);
		}
		if (i == 4)
		{
			position = Vec2(visibleSize.width / 1.3, visibleSize.height / 1.25);
		}
		

		Shield *mShield = Shield::create(position);
		m_Shields.push_back(mShield);
		spritebatch->addChild(m_Shields[i], 1);
	}
	this->addChild(spritebatch, 1);
}

void GameScene::createPauseMenuItem()
{
	auto leftItem  =
		MenuItemImage::create("PauseScreen/Resume_Button.png",
		"PauseScreen/Resume_Button(Click).png",
		CC_CALLBACK_1(GameScene::activatePauseScene, this));

	auto pauseItem =
		MenuItemImage::create("GameScreen/Pause_Button.png",
		"GameScreen/Pause_Button(Click).png",
		CC_CALLBACK_1(GameScene::activatePauseScene, this));

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	leftItem->setPosition(Point(pauseItem->getContentSize().width -
		(pauseItem->getContentSize().width / 2) + origin.x,
		visibleSize.height - pauseItem->getContentSize().height +
		(pauseItem->getContentSize().width / 2) + origin.y));

	pauseItem->setPosition(Point(pauseItem->getContentSize().width -
		(pauseItem->getContentSize().width / 4) + origin.x,
		visibleSize.height - pauseItem->getContentSize().height +
		(pauseItem->getContentSize().width / 4) + origin.y));

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu);
	
}
void GameScene::addAI(){
//	m_ai->m_aiSprites.clear();
	m_ai = std::make_shared<AI>(m_gameState, *this, 4);

}

void GameScene::update(float dt)
{

	switch (m_gameState)
	{
	case GameStates::GameInit:
		addEvents();
	
		m_gameState = GameStates::GameRunning;
		break;

	case GameStates::GameRunning:
		
		m_ai->update(dt, aiSpeed);
		m_Player1->update(dt);
		m_Player2->update(dt);
		detectCollisions();
		if (wave == 1)
		{
			aiSpeed = 10;
		}
		if (wave == 2)
		{
			aiSpeed = 12;
		}
		if (wave == 3)
		{
			aiSpeed = 6;
		}
		if (wave == 4)
		{
			aiSpeed = 3;
		}
		if (wave == 5)
		{
			aiSpeed = 10;
		}
		if (player1istouchedLeft == true)
		{
			m_Player1->moveLeft();
		}
		if (player1istouchedRight == true)
		{
			m_Player1->moveRight();
		}
		if (player2istouchedLeft == true)
		{
			m_Player2->moveLeft();
		}
		if (player2istouchedRight == true)
		{
			m_Player2->moveRight();
		}
		//label->setString("Player One Score: " + std::to_string(playerOneScore));
		label->setString("ai size " + std::to_string(m_ai->m_aiSprites.size()));
		label_two->setString("Player Two Score: " + std::to_string(playerTwoScore));
		if (wave < 5)
		{
			WaveLabel->setString("Current Level : " + std::to_string(wave));
		}
		if (wave == 5)
		{
			WaveLabel->setString(" Final Level ");
		}
		detectWaveOver();
		for (int i = 0; i < m_Shields.size(); i++)
		{
			m_Shields[i]->Update();
		}
		break;
	case GameStates::GameOver:
		activateGameOverScene();
		break;
	}
}

void GameScene::detectWaveOver()
{
	

	Size visibleSize = Director::getInstance()->getVisibleSize();
			if (m_ai->m_aiSprites.size() == 1  && wave == 1)
			{
				wave++;
				addBackGroundSprite(visibleSize);
				m_ai = std::make_shared<AI>(m_gameState, *this, 5);
			}
			
			if (wave == 2 && m_ai->m_aiSprites.size() <= 0)
			{
				wave++;
				addBackGroundSprite(visibleSize);
				m_ai = std::make_shared<AI>(m_gameState, *this, 20);
			}
			if (wave == 3 && m_ai->m_aiSprites.size() <= 0)
			{
				wave++;
				addBackGroundSprite(visibleSize);
				m_ai->m_aiSprites.clear();
				m_ai = std::make_shared<AI>(m_gameState, *this, 25);
			}
			if (wave == 4 && m_ai->m_aiSprites.size() <= 0)
			{
				wave++;
				addBackGroundSprite(visibleSize);
				m_ai->m_aiSprites.clear();
				m_ai = std::make_shared<AI>(m_gameState, *this, 10);
			}
		
		if (m_ai->m_aiSprites.size() <= 0 && wave == 5)
		{
			m_gameState = GameStates::GameOver;	
		}
}


void GameScene::addEvents()
{
	
	//Create a "one by one" touch event listener (processes one touch at a time)
	auto listener1 = EventListenerTouchOneByOne::create();
	// When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
	listener1->setSwallowTouches(true);


	// Example of using a lambda expression to implement onTouchBegan event callback function
	listener1->onTouchBegan = [this](Touch* touch, Event* event){
		Vec2 pos = touch->getLocation();
		cocos2d::Rect recLeft = buttonLeft->boundingBox();
		cocos2d::Rect recRight = buttonRight->boundingBox();
		cocos2d::Rect recLeft2 = buttonLeft2->boundingBox();
		cocos2d::Rect recRight2 = buttonRight2->boundingBox();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		cocos2d::Rect rect1 = cocos2d::Rect(visibleSize.width / 10,0, visibleSize.width / 1.3, visibleSize.width / 8);
		cocos2d::Rect rect2 = cocos2d::Rect(visibleSize.width / 10, visibleSize.height/1.25, visibleSize.width / 1.3, visibleSize.width / 8);
		if (recLeft.containsPoint(pos))
		{
			player1istouchedLeft = true;	
		}
		if (recRight.containsPoint(pos))
		{
			player1istouchedRight = true;
		}
		if (recLeft2.containsPoint(pos))
		{
			player2istouchedLeft = true;
		}
		if (recRight2.containsPoint(pos))
		{
			player2istouchedRight = true;
			fillScoreBoard(playerOneScore, playerTwoScore);
		}
		if (rect1.containsPoint(pos))
		{
			m_Player1->m_fireRequest = true;
			
		}
		if (rect2.containsPoint(pos))
		{
			m_Player2->m_fireRequest2 = true;	
		}	
		shoot = true;
		return true;
	};

	listener1->onTouchEnded = [=](Touch* touch, Event* event){
		player1istouchedLeft = false;
		player2istouchedRight = false;
		player2istouchedLeft = false;
		player1istouchedRight = false;
	};

	cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener1, 30);
}


void GameScene::fillScoreBoard(int p1Score, int p2Score)
{
	for (int i = 4; i >= 0; i--) {
		if (p1Score > m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = m_ScoreBoard[i];
		}

		if (p1Score <= m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = p1Score;
			break;
		}
		if (p1Score > m_ScoreBoard[0]) {
			m_ScoreBoard[0] = p1Score;
			break;
		}
	}

	for (int i = 4; i >= 0; i--) {
		if (p2Score > m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = m_ScoreBoard[i];
		}
		if (p2Score <= m_ScoreBoard[i]) {
			m_ScoreBoard[i + 1] = p2Score;
			break;
		}
		if (p2Score > m_ScoreBoard[0]) {
			m_ScoreBoard[0] = p2Score;
			break;
		}
	}
}


void GameScene::detectCollisions()
{
	cocos2d::Vector<cocos2d::Sprite *> & aiSprites = m_ai->getAISpriteList();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//Player one bullet collision with shields and player
	for (auto projectile1Iter = m_Player1->m_projectiles.begin(); projectile1Iter != m_Player1->m_projectiles.end();)
	{
		bool collision = false;
		Sprite * target1 = (*projectile1Iter);
		Rect targetRect(target1->getBoundingBox());
		Rect player2 = m_Player2->spritereturn()->boundingBox();
		if (targetRect.intersectsRect(player2))
		{
			Director::getInstance()->getRunningScene()->removeChild(target1);
			projectile1Iter = m_Player1->m_projectiles.erase(projectile1Iter);
			playerTwoScore--;
			collision = true;
		}
		for (int i = 0; i < m_Shields.size(); i++)
		{
			
			cocos2d::Rect shieldRect = m_Shields[i]->boundingBox();

			if (targetRect.intersectsRect(shieldRect))
			{
				if (wave >1 )
				{
					m_Shields[i]->setHealth(10);
				}
				Director::getInstance()->getRunningScene()->removeChild(target1);
				projectile1Iter = m_Player1->m_projectiles.erase(projectile1Iter);
				collision = true;
				break;
			}
		}
////////////////////////////////////////////////////////////////////////////////////////////////////
		if (collision == false){
			for (auto aiIter = aiSprites.begin(); aiIter != aiSprites.end();)
			{
				Sprite * aiTarget = (*aiIter);
				Rect aiRect = (aiTarget->getBoundingBox());
				if (targetRect.intersectsRect(aiRect))
				{
					Director::getInstance()->getRunningScene()->removeChild(target1);
					projectile1Iter = m_Player1->m_projectiles.erase(projectile1Iter);

					this->removeChild(aiTarget);
					aiTarget->cleanup();
					aiIter = aiSprites.erase(aiIter);
					playerOneScore++;
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GameScreen/explode.wav");
					CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
					collision = true;
					break;
				}
				else
				{
					aiIter++;
				}
			}
		}
		if (collision == false)
		{
			projectile1Iter++;
		}
	}	


	//Player two bullet collision with shields and player

	for (auto projectile2Iter = m_Player2->m_projectiles2.begin(); projectile2Iter != m_Player2->m_projectiles2.end();)
	{
		bool collision = false;
		Sprite * target1 = (*projectile2Iter);
		Rect targetRect(target1->getBoundingBox());
		Rect player1 = m_Player1->spritereturn()->boundingBox();
		if (targetRect.intersectsRect(player1))
		{
			Director::getInstance()->getRunningScene()->removeChild(target1);
			projectile2Iter = m_Player2->m_projectiles2.erase(projectile2Iter);
			playerOneScore--;
			collision = true;
		}
		for (int i = 0; i < m_Shields.size(); i++)
		{

			cocos2d::Rect shieldRect = m_Shields[i]->boundingBox();

			if (targetRect.intersectsRect(shieldRect))
			{
				if (wave >1)
				{
					m_Shields[i]->setHealth(10);
				}
				Director::getInstance()->getRunningScene()->removeChild(target1);
				projectile2Iter = m_Player2->m_projectiles2.erase(projectile2Iter);
				collision = true;
				break;
			}
		}
		////////////////////////////////////////////////////////////////////////////////////////////////////
		if (collision == false){
			for (auto aiIter = aiSprites.begin(); aiIter != aiSprites.end();)
			{
				Sprite * aiTarget = (*aiIter);
				Rect aiRect = (aiTarget->getBoundingBox());
				if (targetRect.intersectsRect(aiRect))
				{
					Director::getInstance()->getRunningScene()->removeChild(target1);
					projectile2Iter = m_Player2->m_projectiles2.erase(projectile2Iter);

					this->removeChild(aiTarget);
					aiTarget->cleanup();
					aiIter = aiSprites.erase(aiIter);
					CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GameScreen/explode.wav");
					playerTwoScore++;
					collision = true;
					break;
				}
				else
				{
					aiIter++;
				}
			}
		}
		if (collision == false)
		{
			projectile2Iter++;
		}
	}

	auto aiIter = aiSprites.begin();

	for (; aiIter != aiSprites.end();)
	{
		Sprite * target = (*aiIter);
		Rect targetRect(target->getBoundingBox());
		Rect rec = cocos2d::Rect(visibleSize.width, 100, 50, 300);
		if (rec.intersectsRect(targetRect))
		{
			target->setPosition(-20, rand() % (350 - 120) + 120);

		}
		else
		{
			++aiIter;

		}
	}
	for (int i = 0; i < m_Shields.size(); i++)
	{
		if (m_Shields[i]->getHealth() <= 0)
		{
			m_Shields[i]->setPosition(500, -700);
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GameScreen/explode.wav");
			break;
		}
	}
	
}

