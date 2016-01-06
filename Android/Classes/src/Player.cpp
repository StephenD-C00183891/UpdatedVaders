#include "Player.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Player::Player(Vec2 pos, GameStates & gameState) :
m_gameState(gameState),
m_touched(false)
{
	vel = Vec2(10,0);
	timer = 0;
	timer2 = 0;
    createAnimation(pos);
	
}
cocos2d::Sprite *& Player::spritereturn(){

	return m_Sprite;
}

void Player::createAnimation(Vec2 pos){

	std::shared_ptr<GameData> ptr = GameData::sharedGameData();
	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(ptr->m_playerplistfile);
	int frames = 5;
	for (int i = 1; i < frames; i++)
	{
		m_animFrames.pushBack(spritecache->getSpriteFrameByName("player" + std::to_string(i) + ".png"));
	}
	Animation* animation = Animation::createWithSpriteFrames(m_animFrames, 0.05f);
	Animate* animate = Animate::create(animation);

	 m_Sprite = Sprite::createWithSpriteFrame(m_animFrames.at(0));
	 m_Sprite->setPosition(Vec2(pos));
	 m_Sprite->setScale(1);
	 m_Sprite->runAction(RepeatForever::create(animate));

}
void Player::update(float dt){
	if (m_fireRequest == true)
	{
		openFire();
		m_fireRequest = false;
	}
	if (m_fireRequest2 == true)
	{
		openFire2();
		m_fireRequest2 = false;
	}

	for (int i = 0; i < m_projectiles.size(); i++)
	{

		m_projectiles[i]->update();


		if (m_projectiles[i]->getPosition().y > 490)
		{
			Director::getInstance()->getRunningScene()->removeChild((m_projectiles[i]));
			m_projectiles.erase(m_projectiles.begin() +i);
		}
	}

	for (int i = 0; i < m_projectiles2.size(); i++)
	{

		m_projectiles2[i]->update();


		if (m_projectiles2[i]->getPosition().y < 40)
		{
			Director::getInstance()->getRunningScene()->removeChild((m_projectiles2[i]));
			m_projectiles2.erase(m_projectiles2.begin() + i);
		}
	}
	timer += dt;
	timer2 += dt;
}


void Player::openFire()
{
	if (timer > DELAY)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GameScreen/shoot.wav");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
		std::shared_ptr<GameData> ptr = GameData::sharedGameData();
		//SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_projectileFile);
		// projectile = new Projectile(Vec2(m_Sprite->getPosition().x, m_Sprite->getPosition().y + 20));
		auto projectile = Projectile::create(Vec2(m_Sprite->getPosition().x, m_Sprite->getPosition().y + 20));
		Director::getInstance()->getRunningScene()->addChild(projectile, 1);
		//Director::getInstance()->getRunningScene()->addChild(projectile->spritereturn(), 1);
		//spritebatch->addChild(projectile->spritereturn(), 1);
		projectile->m_dirVec = Vec2(0, 10);
		m_projectiles.push_back(projectile);
		timer = 0;
	}
}
void Player::openFire2()
{
	if (timer2 > DELAY)
	{
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("GameScreen/shoot.wav");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
		//std::shared_ptr<GameData> ptr = GameData::sharedGameData();
		//SpriteBatchNode* spritebatch = SpriteBatchNode::create(ptr->m_projectileFile);
		// projectile2 = new Projectile(Vec2(m_Sprite->getPosition().x, m_Sprite->getPosition().y - 20));
		auto projectile2 = Projectile::create(Vec2(m_Sprite->getPosition().x, m_Sprite->getPosition().y - 20));
		Director::getInstance()->getRunningScene()->addChild(projectile2, 1);
	//	Director::getInstance()->getRunningScene()->addChild(projectile2->spritereturn(), 1);
		
		projectile2->m_dirVec = Vec2(0, -10);
		m_projectiles2.push_back(projectile2);
		timer2 = 0;

	}
}

void Player::initOptions(Vec2 position, bool rotate)
{
	if (rotate == true)
	{
		m_Sprite->setRotation(80.0f);
	}
	Point origin = Director::getInstance()->getVisibleOrigin();
	m_Sprite->setPosition(position.x + origin.x, position.y + origin.y);
}
void Player::moveLeft(){

	auto action = MoveBy::create(1,Point(-2,0));
	m_Sprite->runAction(action);
	
}
void Player::moveRight(){
	auto action = MoveBy::create(1, Point(2, 0));
	m_Sprite->runAction(action);
}


void Player::handleTouchEvent(cocos2d::Touch* touch)
{
	m_gameState = GameStates::GameInit;
	m_touched = true;
}

bool Player::isTouched() const
{
	return m_touched;
}
