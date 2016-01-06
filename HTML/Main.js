//global variable
var game
var scene

touchable = 'createTouch' in document

function main()
{
	this.game = new Game();
	this.scene = new Scene();

	game.gameloop();
}