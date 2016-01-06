function MainMenu()
{	
	this.mute = false

	this.logoX = 0
	this.playX = 0
	this.scoreX = 0
	this.optionX = 0
	
	this.logoY = 0
	this.playY = 0
	this.scoreY = 0
	this.optionY = 0

	this.logo = new Image();
	this.logo.src = "images/MainMenuScreen/Game_Title.png";

	this.option = new Image();
	this.option.src = "images/MainMenuScreen/Options_Menu.png";

	this.play = new Image();
	this.play.src = "images/MainMenuScreen/Play_Button.png";

	this.highScore = new Image();
	this.highScore.src = "images/MainMenuScreen/High_Scores.png"
}
MainMenu.prototype = new Scene("Title");

MainMenu.prototype.init = function(canvas) 
{
	this.logoX = (canvas.width / 2) - (this.logo.width / 2);
	this.playX = (canvas.width / 2) - (this.play.width / 1.5);
	this.scoreX = (canvas.width / 2) - (this.highScore.width / 2);
	this.optionX = (canvas.width / 2) - (this.option.width / 2)
	
	this.logoY = (canvas.height / 4);
	this.playY = (canvas.height / 2.2);
	this.scoreY = (canvas.height / 1.5);
	this.optionY = (canvas.height / 1.8)
}

MainMenu.prototype.menuClick = function(x, y)
{

	if (x > game.manager.GameStates[0].playX && x < game.manager.GameStates[0].playX + game.manager.GameStates[0].play.width 
		&& y > game.manager.GameStates[0].playY && y < game.manager.GameStates[0].playY + game.manager.GameStates[0].play.height)
	{
		game.changeMenu("playing");

		if(game.manager.GameStates[1].wave >= 5)
		{
				
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
		
		}

		if(game.manager.GameStates[1].playing == false && game.manager.GameStates[0].mute == false)
		{
			game.manager.GameStates[1].playMusic();
		}
		else if (game.manager.GameStates[1].playing == true && game.manager.GameStates[0].mute == false)
		{
			audioContext.resume();
		}
	}

	if (x > game.manager.GameStates[0].scoreX && x < game.manager.GameStates[0].scoreX + game.manager.GameStates[0].highScore.width 
		&& y > game.manager.GameStates[0].scoreY && y < game.manager.GameStates[0].scoreY + game.manager.GameStates[0].highScore.height)
	{
		game.changeMenu("score");
	}

	if (x > game.manager.GameStates[0].optionX && x < game.manager.GameStates[0].optionX + game.manager.GameStates[0].option.width 
		&& y > game.manager.GameStates[0].optionY && y < game.manager.GameStates[0].optionY + game.manager.GameStates[0].option.height)
	{
		game.changeMenu("option");
	}
}

MainMenu.prototype.render = function(dt)
{
    ctx.drawImage(this.logo, this.logoX, this.logoY);

    ctx.drawImage(this.play, this.playX, this.playY);

    ctx.drawImage(this.highScore, this.scoreX, this.scoreY);

    ctx.drawImage(this.option, this.optionX, this.optionY);
}
