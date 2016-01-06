function ScoreManager()
{
	var score
	var scoreBoard

	this.score = 0;
	this.scoreBoard = [5,4,3,2,1,0];
	var value;
	this.value = 3;

	this.replaceList();
}

ScoreManager.prototype.loop = function()
{

	
	console.log("gameloop");
	//window.requestAnimationFrame(scoreBoard.loop);
} 

ScoreManager.prototype.replaceList = function() {

	console.log(this.scoreBoard);

	for(var i = 4; i >= 0; i --) {
		if(this.value > this.scoreBoard[i]) {
			this.scoreBoard[i + 1] = this.scoreBoard[i];
			
		}
		if(this.value <= this.scoreBoard[i]) {
			this.scoreBoard[i + 1] = this.value;
			break;

		}
		else if(this.value > this.scoreBoard[0]) {
			this.scoreBoard[0] = this.value;
			break;

		}
	}

	console.log(this.scoreBoard);
	//for(var value = 5; value > 2; value --) {

	//	for(var i =0; i < 5; i ++) {
	//		if(value > this.scoreBoard[i])
	//		this.scoreBoard[i] = value;
	//		console.log(this.scoreBoard);
	//	}
	//}
	
}