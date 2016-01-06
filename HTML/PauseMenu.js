function PauseMenu()
{
	this.resumeX = 0
	this.quitX = 0
	this.menuX = 0
	
	this.resumeY = 0
	this.quitY = 0
	this.menuY = 0

	this.backGround = new Image();
	this.backGround.src = "images/PauseScreen/background.png";

	this.resume = new Image();
	this.resume.src = "images/PauseScreen/Resume_Button.png";

	this.mainMenu = new Image();
	this.mainMenu.src = "images/PauseScreen/Menu_Button.png";

	this.quit = new Image();
	this.quit.src = "images/PauseScreen/Quit_Button.png";
}
PauseMenu.prototype = new Scene("Pause");

PauseMenu.prototype.init = function(canvas)
{
	this.resumeX = (canvas.width / 2) - (this.resume.width / 2);
	this.quitX = (canvas.width / 2) - (this.quit.width / 2);
	this.menuX = (canvas.width / 2) - (this.mainMenu.width / 2);
	
	this.resumeY = (canvas.height / 3);
	this.quitY = (canvas.height / 1.95);
	this.menuY = (canvas.height / 1.3);
}

PauseMenu.prototype.menuClick = function(x, y) {

	if(x > game.manager.GameStates[2].resumeY && x < game.manager.GameStates[2].resumeX + game.manager.GameStates[2].resume.width
	   && y > game.manager.GameStates[2].resumeY && y < game.manager.GameStates[2].resumeY + game.manager.GameStates[2].resume.height)
	{
		game.changeMenu("playing");
		audioContext.resume();
	}

	if(x > game.manager.GameStates[2].quitX && x < game.manager.GameStates[2].quitX + game.manager.GameStates[2].quit.width
	   && y > game.manager.GameStates[2].quitY && y < game.manager.GameStates[2].quitY + game.manager.GameStates[2].quit.height)
	{
		game.changeMenu("gameOver");
	}

	if(x > game.manager.GameStates[2].menuX && x < game.manager.GameStates[2].menuX + game.manager.GameStates[2].mainMenu.width
	   && y > game.manager.GameStates[2].menuY && y < game.manager.GameStates[2].menuY + game.manager.GameStates[2].mainMenu.height)
	{
		game.changeMenu("title");
	}
};

PauseMenu.prototype.render = function(dt)
{
	ctx.drawImage(this.backGround, 0, 0, canvas.width, canvas.height);
    ctx.drawImage(this.resume, this.resumeX, this.resumeY);
    ctx.drawImage(this.quit, this.quitX, this.quitY);
    ctx.drawImage(this.mainMenu, this.menuX, this.menuY);
}