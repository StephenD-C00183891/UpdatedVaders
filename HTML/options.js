
function Options()
{

	this.menuY = 0
	this.logoX = 0
	this.muteX = 0

	this.menuY = 0
	this.logoY = 0
	this.muteY = 0

	this.optionsLogo = new Image();
	this.optionsLogo.src = "images/OptionsMenuScreen/Options_Menu.png";

	this.mute = new Image();
	this.mute.src = "images/OptionsMenuScreen/mute.png"

	this.mainMenu = new Image();
	this.mainMenu.src = "images/OptionsMenuScreen/Menu_Button.png";

}
Options.prototype = new Scene("Options");


Options.prototype.init = function(canvas)
{
	this.menuX = (canvas.width / 2) - (this.mainMenu.width / 2);
	this.logoX = (canvas.width / 2) - (this.optionsLogo.width / 2);
	this.muteX = (canvas.width / 2) - (this.mute.width / 2)

	this.menuY = (canvas.height / 1.5);
	this.logoY = (canvas.height / 5);
	this.muteY = (canvas.height / 2.6);
}

Options.prototype.menuClick = function(x, y) {

	if(x > game.manager.GameStates[5].menuX && x < game.manager.GameStates[5].menuX + game.manager.GameStates[5].mainMenu.width
	   && y > game.manager.GameStates[5].menuY && y < game.manager.GameStates[5].menuY + game.manager.GameStates[5].mainMenu.height)
	{
		game.changeMenu("title");
	}

	if(x > game.manager.GameStates[5].muteX && x < game.manager.GameStates[5].muteX + game.manager.GameStates[5].mute.width
	   && y > game.manager.GameStates[5].muteY && y < game.manager.GameStates[5].muteY + game.manager.GameStates[5].mute.height
	   && game.manager.GameStates[0].mute == false)
	{
		game.manager.GameStates[0].mute = true;
		console.log("changed to true")
	}
	else if(x > game.manager.GameStates[5].muteX && x < game.manager.GameStates[5].muteX + game.manager.GameStates[5].mute.width
	   && y > game.manager.GameStates[5].muteY && y < game.manager.GameStates[5].muteY + game.manager.GameStates[5].mute.height
	   && game.manager.GameStates[0].mute == true)
	{
		game.manager.GameStates[0].mute = false;
		console.log("changed to false")
	}
};

Options.prototype.render = function(dt)
{

    ctx.drawImage(this.optionsLogo, this.logoX, this.logoY);

    ctx.drawImage(this.mute, this.muteX, this.muteY);

	ctx.drawImage(this.mainMenu, this.menuX, this.menuY);  
}