function HighScore()
{
	this.logoX = 0;
	this.logoY = 0;

	this.menuX = 0;
	this.menuY = 0;

	this.scoreBoardX = 0;
	this.scoreBoardY = 0;

	this.score1 = 0;
	this.score2 = 0;
	this.score3 = 0;
	this.score4 = 0;
	this.score5 = 0;

	this.test = 0;
	this.scoreBoard = [0,0,0,0,0,0];

	this.scores = new Image();
	this.scores.src = "images/HighScoreScreen/High_Scores.png";

	this.menu = new Image();
	this.menu.src = "images/HighScoreScreen/Menu_Button.png";

}
HighScore.prototype = new Scene("Score");


HighScore.prototype.init = function(canvas) 
{
	this.logoX = (canvas.width / 2) - (this.scores.width / 2);
	this.menuX = (canvas.width / 2) - (this.menu.width / 2);

	this.logoY = (canvas.height / 6);
	this.menuY = (canvas.height / 1.3);

	this.scoreBoardX = (canvas.width / 2.5);
	this.scoreBoardY = (canvas.height / 3)

	console.log(this.scoreBoard);
}

HighScore.prototype.menuClick = function(x, y)
{
	if(x > game.manager.GameStates[4].menuX && x < game.manager.GameStates[4].menuX + game.manager.GameStates[4].menu.width
	   && y > game.manager.GameStates[4].menuY && y < game.manager.GameStates[4].menuY + game.manager.GameStates[4].menu.height)
	{
		game.changeMenu("title");
	}
}

HighScore.prototype.fillScore = function(p1Score, p2Score)
{
	for(var i = 4; i >= 0; i --) {
		if(p1Score > this.scoreBoard[i]) {
			this.scoreBoard[i + 1] = this.scoreBoard[i];	
		}

		if(p1Score <= this.scoreBoard[i]) {
			this.scoreBoard[i + 1] = p1Score;
			break;
		}
		if(p1Score > this.scoreBoard[0]) {
			this.scoreBoard[0] = p1Score;
			break;
		}
	}

	for(var i = 4; i >= 0; i --) {
		if(p1Score > this.scoreBoard[i]) {
			this.scoreBoard[i + 1] = this.scoreBoard[i];	
		}
		if(p2Score <= this.scoreBoard[i]) {
			this.scoreBoard[i + 1] = p2Score;
			break;
		}
		if(p2Score > this.scoreBoard[0]) {
			this.scoreBoard[0] = p2Score;
			break;
		}
	}

	this.score1 = this.scoreBoard[0];
	this.score2 = this.scoreBoard[1];
	this.score3 = this.scoreBoard[2];
	this.score4 = this.scoreBoard[3];
	this.score5 = this.scoreBoard[4];
}

HighScore.prototype.render = function(scoreboard, dt)
{
	ctx.drawImage(this.scores, this.logoX, this.logoY);
	ctx.drawImage(this.menu, this.menuX, this.menuY);

	ctx.font = "30px Ariel";
	ctx.fillStyle = "white";

	ctx.fillText("1st: " + this.score1, this.scoreBoardX, this.scoreBoardY + 30);
	ctx.fillText("2nd: " + this.score2, this.scoreBoardX, this.scoreBoardY + 60);
	ctx.fillText("3rd: " + this.score3, this.scoreBoardX, this.scoreBoardY + 90);
	ctx.fillText("4th: " + this.score4, this.scoreBoardX, this.scoreBoardY + 120);
	ctx.fillText("5th: " + this.score5, this.scoreBoardX, this.scoreBoardY + 150);

};
