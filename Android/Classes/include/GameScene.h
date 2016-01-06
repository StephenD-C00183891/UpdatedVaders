#pragma once

#include "cocos2d.h"
#include "PauseMenu.h"
#include "GameOver.h"
#include "GameData.h"
#include "GameStates.h"
#include "AI.h"
#include "OptionsMenu.h"
#include "Player.h"
#include "Bullet.h"
#include <string>
#include "Shield.h"
#include "HighScore.h"



class GameScene : public cocos2d::Layer
{
public:
	void fillScoreBoard(int p1Score, int p2Score);
	static cocos2d::Scene* createScene();
	virtual bool init();
	std::vector<int> m_ScoreBoard;
	std::shared_ptr<AI> m_ai;
	std::shared_ptr<Projectile> m_B;	
//	OptionsMenu m_option;
	Player  * m_Player1;
	Player * m_Player2;
	HighScore *  m_Score;
	bool shoot = false;
	void createPauseMenuItem();
	void addAI();
	void detectCollisions();
	std::vector<Shield*> m_Shields;
	void createShields(cocos2d::Size const & visibleSize);
	void detectWaveOver();
	std::string const PLAYERS_SPRITE_BATCH = "TowerBases"; // don't forget to #include <string>
	void createPlayer();    // add this
	// Called when user pauses gameplay.
	void activatePauseScene(Ref *pSender);
	// Called at game over 
	void activateGameOverScene();
	void addBackGroundSprite(cocos2d::Size const & visibleSize);
	CREATE_FUNC(GameScene);
	void update(float dt);	// dt = delta time - the time between frames.
	void addEvents();
	bool alive;
	int playerOneScore, wave, playerTwoScore;
	float aiSpeed;
	cocos2d::Label* label;
	cocos2d::Label* label_two;
	cocos2d::Label* WaveLabel;
	
	cocos2d::Vec2 position;
	bool player1istouchedLeft, player1istouchedRight, player2istouchedLeft, player2istouchedRight;
	

private:
	
   // add this
	GameStates m_gameState; // add this
	cocos2d::Sprite* buttonLeft;
	cocos2d::Sprite* buttonRight;
	cocos2d::Sprite* buttonLeft2;
	cocos2d::Sprite* buttonRight2;
	cocos2d::Sprite* background;
};