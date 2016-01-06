var canvas
var ctx

touches = []

function Game()
{
	var currentFrame
	var prevFrame
	this.dt =0;
	var manager 
	this.manager = new SceneManager();
	this.init();


}

Game.prototype.init = function()
{
	canvas= document.createElement("canvas");
	ctx = canvas.getContext("2d");
	document.body.appendChild(canvas);
	canvas.width = window.innerWidth;
	canvas.height = window.innerHeight;

	this.manager.GameStates[1].init(canvas);
	this.changeMenu("title");

	if(touchable) 
	{
        document.addEventListener( 'touchstart', this.onTouchStart, true );
        document.addEventListener( 'touchend', this.onTouchEnd, true );
	}
	else
	{
		canvas.addEventListener("click",this.keyDownHandler, false);
	}

}



Game.prototype.changeMenu = function(string)
{
	if(string == "title")
	{
		clearCanvas();
		this.manager.goToScene("title");
		this.manager.state.init(canvas);
	}

	if(string == "playing")
	{
		clearCanvas();
		this.manager.goToScene("playing");
	}

	if(string == "pause")
	{
		clearCanvas();
		this.manager.goToScene("pause");
		this.manager.state.init(canvas);
	}

	if(string == "gameOver")
	{
		clearCanvas();
		this.manager.goToScene("gameOver");
		this.manager.state.init(canvas);
	}

	if(string == "score")
	{
		clearCanvas();
		this.manager.goToScene("highScore");
		this.manager.state.init(canvas);
	}

	if(string == "option")
	{
		clearCanvas();
		this.manager.goToScene("option");
		this.manager.state.init(canvas);
	}
}

Game.prototype.gameloop = function()
{
	this.prevFrame = this.currentFrame;
		
	if(this.prevFrame == undefined)
	{
		this.prevFrame = 0;
	}

	this.currentFrame = (new Date().getTime());
	this.dt = this.currentFrame - this.prevFrame;

	game.manager.state.update(this.dt);
	game.draw(this.dt);
	
	window.requestAnimationFrame(game.gameloop);
} 

Game.prototype.draw = function(dt)
{
	this.manager.state.render(dt);
}

function clearCanvas()
{
	canvas.width = canvas.width;
}

Game.prototype.onTouchStart = function(e)
{
	e.preventDefault();
	touches = e.touches; 

	for(var i = 0; i < touches.length; i ++)
	{

		game.manager.GameStates[1].checkCollision(e.touches[i].clientX, e.touches[i].clientY);
		game.manager.GameStates[1].checkBulletCollision(e.touches[i].clientX, e.touches[i].clientY);

		if(game.manager.state.name == "Game Playing")
		{
			game.manager.GameStates[1].menuClick(e.touches[i].clientX, e.touches[i].clientY);
		}

		if(game.manager.state.name == "Pause")
		{
			game.manager.GameStates[2].menuClick(e.touches[i].clientX, e.touches[i].clientY);
		}

		if(game.manager.state.name == "Title")
		{
			game.manager.GameStates[0].menuClick(e.touches[i].clientX, e.touches[i].clientY);
		}

		if(game.manager.state.name == "Game Over")
		{
			game.manager.GameStates[3].menuClick(e.touches[i].clientX, e.touches[i].clientY);
		}

		if(game.manager.state.name == "Score")
		{
			game.manager.GameStates[4].menuClick(e.touches[i].clientX, e.touches[i].clientY);
		}

		if(game.manager.state.name == "Options")
		{
			game.manager.GameStates[5].menuClick(e.touches[i].clientX, e.touches[i].clientY);
		}
	}
}

Game.prototype.onTouchEnd = function(e)
{
	e.preventDefault();
	touches = e.touches;

	game.manager.GameStates[1].checkEndCollision();
}

Game.prototype.keyDownHandler = function(e)
{
	game.manager.GameStates[1].checkCollision(e.clientX,e.clientY);
	game.manager.GameStates[1].checkBulletCollision(e.clientX,e.clientY);

	if(game.manager.state.name == "Game Playing")
	{
		game.manager.GameStates[1].menuClick(e.clientX, e.clientY);
	}

	if(game.manager.state.name == "Pause")
	{
		game.manager.GameStates[2].menuClick(e.clientX, e.clientY);
	}

	if(game.manager.state.name == "Title")
	{
		game.manager.GameStates[0].menuClick(e.clientX, e.clientY);
	}

	if(game.manager.state.name == "Game Over")
	{
		game.manager.GameStates[3].menuClick(e.clientX, e.clientY);
	}

	if(game.manager.state.name == "Score")
	{
		game.manager.GameStates[4].menuClick(e.clientX, e.clientY);
	}

	if(game.manager.state.name == "Options")
	{
		game.manager.GameStates[5].menuClick(e.clientX, e.clientY);
	}
}


