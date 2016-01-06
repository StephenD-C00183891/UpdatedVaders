
function GameOver()
{
	this.resumeX = 0
	this.scoreX = 0
	this.menuY = 0
	this.logoX = 0
	
	this.resumeY = 0
	this.scoreY = 0
	this.menuY = 0
	this.logoY = 0

	this.backGround = new Image();
	this.backGround.src = "images/GameOverScreen/background.png";

	this.gOver = new Image();
	this.gOver.src = "images/GameOverScreen/Game_Over.png";

	this.mainMenu = new Image();
	this.mainMenu.src = "images/GameOverScreen/Menu_Button.png";

	this.retry = new Image();
	this.retry.src = "images/GameOverScreen/Retry_Button.png";

	this.score = new Image();
	this.score.src = "images/GameOverScreen/High_Scores.png"
}
GameOver.prototype = new Scene("Game Over");


GameOver.prototype.init = function(canvas)
{
	this.resumeX = (canvas.width / 2) - (this.retry.width / 2);
	this.scoreX = (canvas.width / 2) - (this.score.width / 2);
	this.menuX = (canvas.width / 2) - (this.mainMenu.width / 2);
	this.logoX = (canvas.width / 2) - (this.gOver.width / 2);
	
	this.resumeY = (canvas.height / 3);
	this.scoreY = (canvas.height / 2.3);
	this.menuY = (canvas.height / 1.3);
	this.logoY = (canvas.height / 5);
}

GameOver.prototype.menuClick = function(x, y) {

	if(x > game.manager.GameStates[3].resumeX && x < game.manager.GameStates[3].resumeX + game.manager.GameStates[3].retry.width
	   && y > game.manager.GameStates[3].resumeY && y < game.manager.GameStates[3].resumeY + game.manager.GameStates[3].retry.height)
	{
		game.changeMenu("playing");

		game.manager.GameStates[1].playerOneScore = 0;
		game.manager.GameStates[1].playerTwoScore = 0;
		game.manager.GameStates[1].totalEnemies = 24;
		game.manager.GameStates[1].addAI();
		game.manager.GameStates[1].m_Shields[0].reset();
		game.manager.GameStates[1].m_Shields[1].reset();
		game.manager.GameStates[1].m_Shields[2].reset();
		game.manager.GameStates[1].m_Shields[3].reset();
		game.manager.GameStates[1].m_Shields[4].reset();
		game.manager.GameStates[1].m_Shields[5].reset();
		game.manager.GameStates[1].wave = 1;
			
		audioContext.resume();
	}

	if(x > game.manager.GameStates[3].scoreX && x < game.manager.GameStates[3].scoreX + game.manager.GameStates[3].score.width
	   && y > game.manager.GameStates[3].scoreY && y < game.manager.GameStates[3].scoreY + game.manager.GameStates[3].score.height)
	{
		game.changeMenu("score");
		game.manager.GameStates[4].fillScore(game.manager.GameStates[1].playerOneScore, game.manager.GameStates[1].playerTwoScore);
	}

	if(x > game.manager.GameStates[3].menuX && x < game.manager.GameStates[3].menuX + game.manager.GameStates[3].mainMenu.width
	   && y > game.manager.GameStates[3].menuY && y < game.manager.GameStates[3].menuY + game.manager.GameStates[3].mainMenu.height)
	{
		game.changeMenu("title");
	}
};

GameOver.prototype.render = function(dt)
{
    ctx.drawImage(this.gOver, this.logoX, this.logoY);

	ctx.drawImage(this.mainMenu, this.menuX, this.menuY);

	ctx.drawImage(this.score, this.scoreX, this.scoreY)

	ctx.drawImage(this.retry, this.resumeX, this.resumeY);    
}