//an object to hold a name for each sound and its associated buffer (memory holding the sound)
var audioBuffers={}
var audioContext;
var soundLoaded = false;

function GameScene()
{

	this.p1leftButtonX = 0;
	this.p1leftButtonY = 0;

	this.p2leftButtonX = 0;
	this.p2leftButtonY = 0;

	this.p1rightButtonX = 0;
	this.p1rightButtonY = 0;

	this.p2rightButtonX = 0;
	this.p2rightButtonY = 0;

	this.pauseButtonX = 0;
	this.pauseButtonY = 0;

	this.score1X = 0;
	this.score1Y = 0;

	this.score2X = 0;
	this.score2Y = 0;

	this.waveX = 0;
	this.waveY = 0;

	this.loadSoundFile('BGM', "BGM2.mp3");
	this.loadSoundFile('explode', "explode.wav");
	this.loadSoundFile('shoot', "shoot.wav");
    this.move = false;
    this.AIList =[];
    this.playerList = [];
    this.m_Shields = [];
    this.wave = 1;
    this.totalenemies = 24;
    this.playerOneScore = 0;
    this.playerTwoScore = 0;
    this.m_fireRequest = false;
    this.m_fireRequest2 = false;
    this.flipped = false;
    this.flipped2 = true;
    this.playing = false;

    this.p1MoveLeft = false;
    this.p1MoveRight = false;
    this.p2MoveLeft = false;
    this.p2MoveRight = false;

    //this.p1SlowLeft = false;
  //  this.p1SlowRight = false;
   // this.p2SlowLeft = false;
   // this.p2SlowRight = false;

}
GameScene.prototype = new Scene("Game Playing");

GameScene.prototype.update = function(dt)
{
	if(this.playerList[0] != null)
	{
    	this.playerList[0].update(dt);
    	this.playerList[1].update(dt);

		for (var i = 0; i < this.AIList.length; i++) {
			this.AIList[i].update();

		}
		for (var i = 0; i < this.AIList.length; i++) 
		{
			if (this.AIList[i].x > canvas.width)
			{
				this.AIList[i].x = ((Math.random() * 400) - 700);
	    	}
		}
		for (var i = 0; i < game.manager.GameStates[1].playerList[0].m_projectiles.length; i++) 
		{
			if (game.manager.GameStates[1].playerList[0].m_projectiles.y < 0)
			{
				game.manager.GameStates[1].playerList[0].m_projectiles.splice(i,1);
	    	}
		}

		for (var i = 0; i < game.manager.GameStates[1].playerList[0].m_projectiles2.length; i++) 
		{
			if (game.manager.GameStates[1].playerList[0].m_projectiles2.y > canvas.height)
			{
				game.manager.GameStates[1].playerList[0].m_projectiles2.splice(i,1);
	    	}
		}
	}
	if(this.totalenemies == 0 && this.wave == 1)
    {
        this.wave += 1;
        this.addAI(5,  4);
    }
    if(this.totalenemies == 0 && this.wave == 2)
    {
        this.wave += 1;
        this.addAI(20, 6);
    }
    if(this.totalenemies == 0 && this.wave == 3)
    {
        this.wave += 1;
        this.addAI(25, 8);
    }
    if(this.totalenemies == 0 && this.wave == 4)
    {
        this.wave += 1;
        this.addAI(10, 7);
    }


	if(this.wave == 5 && this.totalenemies == 0)
	{
		game.changeMenu("gameOver");
	}

	for(var j = 0; j < this.m_Shields.length; j ++)
	{
		if(this.wave >= 2 && this.m_Shields[j].health <= 0)
		{
			 this.m_Shields[j].y = -500;
		}
	}

	if ( this.p1MoveLeft == true) {
		 game.manager.GameStates[1].playerList[0].moveLeft();   
	}

	if ( this.p1MoveRight == true ) {
		 game.manager.GameStates[1].playerList[0].moveRight();   
	}

	if ( this.p2MoveLeft == true) {
		 game.manager.GameStates[1].playerList[1].moveLeft();   
	}

	if ( this.p2MoveRight == true) {
		 game.manager.GameStates[1].playerList[1].moveRight();   
	}

	else if (this.p1MoveLeft == false && this.p1MoveRight == false && this.p2MoveLeft == false && this.p2MoveRight == false) {
		game.manager.GameStates[1].playerList[0].Stop();
		game.manager.GameStates[1].playerList[1].Stop();
	}
	//if(game.manager.GameStates[1].playerList[0].speed >= 0 && this.p1MoveLeft == false) {

		//	game.manager.GameStates[1].playerList[0].speed -= 0.03;
			//console.log(game.manager.GameStates[1].playerList[0].speed)
	//	}

	this.detectCollisions();
}

GameScene.prototype.detectCollisions = function()
{

	
	for(var i =0; i < game.manager.GameStates[1].playerList[0].m_projectiles.length; i ++)
	{
		for(var j =0; j < this.AIList.length; j ++)
		{
			if(game.manager.GameStates[1].playerList[0].m_projectiles[i] != undefined)
			{
				if(game.manager.GameStates[1].playerList[0].m_projectiles[i].detectCollisions(this.AIList[j].x, this.AIList[j].y, this.AIList[j].width, this.AIList[j].height) == true)
				{
					this.AIList.splice(j, 1);
					game.manager.GameStates[1].playerList[0].m_projectiles.splice(i, 1);
				
					this.totalenemies--;
					this.playerOneScore ++;
					this.playSound("explode");
				}
			}			
		}
	}

	for(var i =0; i < game.manager.GameStates[1].playerList[0].m_projectiles2.length; i ++) 
	{
		for(var j =0; j < this.AIList.length; j ++)
		{
			if(game.manager.GameStates[1].playerList[0].m_projectiles2[i] != undefined)
			{
				if(game.manager.GameStates[1].playerList[0].m_projectiles2[i].detectCollisions(this.AIList[j].x, this.AIList[j].y, this.AIList[j].width, this.AIList[j].height ) == true) 
				{	
					this.AIList.splice(j, 1);
					game.manager.GameStates[1].playerList[0].m_projectiles2.splice(i, 1);
				
					this.totalenemies --;
					this.playerTwoScore ++;
					this.playSound("explode");
				}
			}
		}
	}

	for(var j = 0; j < this.m_Shields.length; j ++)
	{
		for(var i = 0; i < game.manager.GameStates[1].playerList[0].m_projectiles.length; i ++)
		{
			if(game.manager.GameStates[1].playerList[0].m_projectiles[i].detectCollisions(this.m_Shields[j].x, this.m_Shields[j].y, this.m_Shields[j].width, this.m_Shields[j].height) == true) {
				game.manager.GameStates[1].playerList[0].m_projectiles.splice(i, 1);
				if(this.wave >= 2 )
				{
					game.manager.GameStates[1].m_Shields[j].health =  -10;
				}
			}
		}
	}
	for(var j = 0; j < this.m_Shields.length; j ++)
	{
		for(var i = 0; i < game.manager.GameStates[1].playerList[0].m_projectiles2.length; i ++)
		{
			if(game.manager.GameStates[1].playerList[0].m_projectiles2[i].detectCollisions(this.m_Shields[j].x, this.m_Shields[j].y, this.m_Shields[j].width, this.m_Shields[j].height) == true) {
				game.manager.GameStates[1].playerList[0].m_projectiles2.splice(i, 1);
				if(this.wave >= 2 )
				{
					game.manager.GameStates[1].m_Shields[j].health = game.manager.GameStates[1].m_Shields[j].health -10;
				}
			}
		}
	}

	for(var i =0; i < game.manager.GameStates[1].playerList[0].m_projectiles.length; i ++) 
	{
		if(game.manager.GameStates[1].playerList[0].m_projectiles[i].detectCollisions(this.playerList[1].x, this.playerList[1].y, this.playerList[1].width, this.playerList[1].height ) == true) {
			game.manager.GameStates[1].playerList[0].m_projectiles.splice(i, 1);
			this.playerList.splice(j, 1);

			this.playerTwoScore --;
			this.playSound("explode");
		}
	}


	for(var i =0; i < game.manager.GameStates[1].playerList[0].m_projectiles2.length; i ++) 
	{
		if(game.manager.GameStates[1].playerList[0].m_projectiles2[i].detectCollisions(this.playerList[0].x, this.playerList[0].y, this.playerList[0].width, this.playerList[0].height ) == true) {
			game.manager.GameStates[1].playerList[0].m_projectiles2.splice(i, 1);
			this.playerList.splice(j, 1);

			this.playerOneScore --;
			this.playSound("explode");

		}
	}

}

GameScene.prototype.menuClick = function(x, y)
{
	if(x > game.manager.GameStates[1].pauseButtonX && x < game.manager.GameStates[1].pauseButtonX + game.manager.GameStates[1].pauseButton.width
	&& y > game.manager.GameStates[1].pauseButtonY && y < game.manager.GameStates[1].pauseButtonY + game.manager.GameStates[1].pauseButton.height)
	{
		game.changeMenu("pause");
		audioContext.suspend();
	}
};

GameScene.prototype.createPlayer = function(){

	this.playerList = [new Player((canvas.width/2), (canvas.height / 1.13)), new Player((canvas.width / 2), (canvas.height / 40))];

}
GameScene.prototype.addAI = function(maxAi, tempSpeed){

	this.totalenemies = maxAi;

	for(var i = 0; i < this.totalenemies; i ++) {
     	this.AIList.push(new AI(tempSpeed));
 	}
}

GameScene.prototype.playMusic = function()
{
	this.playSound("BGM");
	this.playing = true;
}

GameScene.prototype.init = function(canvas)
{
	try {
    	window.AudioContext = window.AudioContext||window.webkitAudioContext;
    	audioContext = new AudioContext();
  	}
  	catch(e) {
    	alert('Web Audio API is not supported in this browser');
  	}

	this.createPlayer();
	
    this.createShields();
 
	this.addAI(4, 3);
	
	for (var i = 0; i < 2; i++) {
		this.playerList[i].init();
	}

	this.backGround = new Image();
	this.backGround2 = new Image();
	this.backGround3 = new Image();
	this.backGround4 = new Image();
	this.backGround5 = new Image();

	this.backGround.src = "images/GameScreen/Background.png";
	this.backGround2.src = "images/GameScreen/level2.png";
	this.backGround3.src = "images/GameScreen/level3.png";
	this.backGround4.src = "images/GameScreen/level4.png";
	this.backGround5.src = "images/GameScreen/level5.png";

	this.pauseButton = new Image();
	this.pauseButton.src = "images/GameScreen/Pause_Button.png";

    this.p1leftButton = new Image();
	this.p1leftButton.src = "images/GameScreen/buttonleft.png";

    this.p1rightButton = new Image();
	this.p1rightButton.src = "images/GameScreen/buttonright.png";

	this.p2leftButton = new Image();
	this.p2leftButton.src = "images/GameScreen/buttonleft.png";

    this.p2rightButton = new Image();
	this.p2rightButton.src = "images/GameScreen/buttonright.png";

	//Button Positions
	this.p1leftButtonX = (canvas.width / 40);
	this.p1leftButtonY = (canvas.height / 1.13);

	this.p1rightButtonX = (canvas.width / 1.1);
	this.p1rightButtonY = (canvas.height / 1.13);

	this.p2leftButtonX = (canvas.width / 40);
	this.p2leftButtonY = (canvas.height / 40);

	this.p2rightButtonX = (canvas.width / 1.1);
	this.p2rightButtonY = (canvas.height / 40);

	this.pauseButtonX = (canvas.width / 1.1);
	this.pauseButtonY = (canvas.height / 2);

	this.score1X = (canvas.width / 1.6);
	this.score1Y = (canvas.height / 1.05);

	this.score2X = (canvas.width / 1.6);
	this.score2Y = (canvas.height / 40);

	this.waveX = (canvas.width / 2.2);
	this.waveY = (canvas.height / 2);
}

function clearCanvas()
{
	canvas.width = canvas.width;
}

GameScene.prototype.createShields = function()
{
	var x = 0;
	var y =0;
	for (var i = 0; i < 6; i++)
	 {
	 	
		if(i < 3){
			if (i == 0) 
			{
	         x = (canvas.width / 7);
	         y = (canvas.height / 6.5);
	     	}
	     	if (i == 1) 
			{
	         x = (canvas.width / 1.8);
	         y = (canvas.height / 6.5);
	     	}
	     	if (i == 2) 
			{
	         x = (canvas.width / 1.2);
	         y = (canvas.height / 6.5);
	     	}
         }
         else{
         	if (i == 3) 
			{
	         x = (canvas.width / 5);
	         y = (canvas.height / 1.25);
	     	}
	     	if (i == 4) 
			{
	         x = (canvas.width / 2);
	         y = (canvas.height / 1.25);
	     	}
	     	if (i == 5) 
			{
	         x = (canvas.width / 1.5);
	         y = (canvas.height / 1.25);
	     	}

         }
		
		this.m_Shields.push(new Shield(x,y));
	}
}

GameScene.prototype.checkCollision = function(mousex, mousey)
{
   if (mousex > game.manager.GameStates[1].p1leftButtonX && mousex < game.manager.GameStates[1].p1leftButtonX + game.manager.GameStates[1].p1leftButton.width 
   	&& mousey > game.manager.GameStates[1].p1leftButtonY && mousey < game.manager.GameStates[1].p1leftButtonY + game.manager.GameStates[1].p1leftButton.height)
	{	
	    this.p1MoveLeft = true;  
	   // this.p1SlowLeft = false; 
	}
	else if (mousex > game.manager.GameStates[1].p1rightButtonX && mousex < game.manager.GameStates[1].p1rightButtonX +  game.manager.GameStates[1].p1rightButton.width
		 && mousey >  game.manager.GameStates[1].p1rightButtonY && mousey < game.manager.GameStates[1].p1rightButtonY +  game.manager.GameStates[1].p1rightButton.height)
	{	
	   	this.p1MoveRight = true;
	   //	this.p1SlowRight = false; 
	}

	if (mousex > game.manager.GameStates[1].p2leftButtonX && mousex < game.manager.GameStates[1].p2leftButtonX + game.manager.GameStates[1].p2leftButton.width 
   	&& mousey > game.manager.GameStates[1].p2leftButtonY && mousey < game.manager.GameStates[1].p2leftButtonY + game.manager.GameStates[1].p2leftButton.height)
	{	
	   this.p2MoveLeft = true;  
	  // this.p2SlowLeft = false; 
	}
	else if (mousex > game.manager.GameStates[1].p2rightButtonX && mousex < game.manager.GameStates[1].p2rightButtonX +  game.manager.GameStates[1].p2rightButton.width
		 && mousey >  game.manager.GameStates[1].p2rightButtonY && mousey < game.manager.GameStates[1].p2rightButtonY +  game.manager.GameStates[1].p2rightButton.height)
	{	
	   	this.p2MoveRight = true;
	   //	this.p2SlowRight = false; 
	}
}

GameScene.prototype.checkEndCollision = function()
{
	//this.p1SlowLeft = true;
	//this.p1SlowRight = true;
	//this.p2SlowLeft = true;
	//this.p2SlowRight = true;
	game.manager.GameStates[1].p1MoveLeft = false;
	game.manager.GameStates[1].p1MoveRight = false;

	game.manager.GameStates[1].p2MoveLeft = false;
	game.manager.GameStates[1].p2MoveRight = false;

	//game.manager.GameStates[1].playerList[0].Stop();
}

GameScene.prototype.checkBulletCollision = function(mousex, mousey)
{
	if (mousex> (canvas.width / 9.2) && mousex < (canvas.width / 1.15) && mousey > (canvas.height / 1.3) && mousey < (canvas.height / 1))
	{
		game.manager.GameStates[1].m_fireRequest = true;
		//this.playSound("shoot");
    }

   if (mousex> (canvas.width / 9.2) && mousex < (canvas.width / 1.15) && mousey > 0 && mousey < (canvas.height / 6))
	{
		game.manager.GameStates[1].m_fireRequest2 = true;
		//this.playSound("shoot");
	}
}

GameScene.prototype.render = function(dt)
{
   	if(this.playerList[0] != null)
	{
		clearCanvas();

		if(this.wave == 1)
		{
   			ctx.drawImage(this.backGround, 0, 0, canvas.width, canvas.height);
		}
		else if(this.wave == 2)
		{
   			ctx.drawImage(this.backGround2, 0, 0, canvas.width, canvas.height);
   		}
   		else if(this.wave == 3)
		{
   			ctx.drawImage(this.backGround3, 0, 0, canvas.width, canvas.height);
   		}
   		else if(this.wave == 4)
		{
   			ctx.drawImage(this.backGround4, 0, 0, canvas.width, canvas.height);
   		}
   		else if(this.wave == 5)
		{
   			ctx.drawImage(this.backGround5, 0, 0, canvas.width, canvas.height);
   		}

		for (var i = 0; i < this.AIList.length; i++) 
		{
    		this.AIList[i].render(dt);
    	}

    	this.playerList[0].render(this.flipped, dt);
    	this.playerList[1].render(this.flipped2, dt);

    	for (var i =0; i < this.m_Shields.length; i ++) 
    	{
    		this.m_Shields[i].render();
    	}

    	ctx.drawImage(this.pauseButton, this.pauseButtonX, this.pauseButtonY);
    	ctx.drawImage(this.p1leftButton, this.p1leftButtonX, this.p1leftButtonY);
		ctx.drawImage(this.p1rightButton, this.p1rightButtonX, this.p1rightButtonY);	

		ctx.drawImage(this.p2leftButton, this.p2leftButtonX, this.p2leftButtonY);
		ctx.drawImage(this.p2rightButton, this.p2rightButtonX, this.p2rightButtonY);

		ctx.font = "20px Ariel";
		ctx.fillStyle = "white";
		ctx.fillText("Player one Score: " + this.playerOneScore.toString(), this.score1X, this.score1Y);
		ctx.fillText(this.playerTwoScore.toString() + " :ǝɹoɔS oʍʇ ɹǝʎɐlԀ", this.score2X, this.score2Y);

		if(this.wave < 5)
		{
			ctx.fillText("Level: " + this.wave.toString(), this.waveX, this.waveY);
		}
		else if (this.wave == 5)
		{
			ctx.fillText("Final Level ", this.waveX, this.waveY);
		}
	}
}

GameScene.prototype.playSound = function(name) {

  if(audioBuffers[name] == undefined || !soundLoaded)

  if(!  soundLoaded)
  {
    	console.log("Sound doesn't exist or hasn't been loaded")
    	return;
  	}

  	audioBuffer = audioBuffers[name];

  	//create a buffer source - used to play once and then a new one must be made
  	var source = audioContext.createBufferSource();
  	source.buffer = audioBuffer;
  	if(name == "BGM")
  	{
  		source.loop = true;
  	}
  	else
  	{
  		source.loop = false;
  	}
  	source.connect(audioContext.destination);
  	
  	//source.noteOn(0);
  	
  	source.start(0);
}


GameScene.prototype.loadSoundFile = function(name, url) {
 // console.log(url);
  var xhr = new XMLHttpRequest();
  xhr.open('GET', url, true);
  xhr.responseType = 'arraybuffer';
 
  xhr.onload = function(e) {
      
      //buffer containing sound returned by xhr
      var arrayBuffer=this.response;
      audioContext.decodeAudioData(arrayBuffer, function(buffer) {
      //associate the audio buffer with the sound name so can use the decoded audio later.
      audioBuffers[name]=buffer; 
      soundLoaded = true;
      //console.log(soundLoaded);
      //initSound(this.response); // this.response is an ArrayBuffer.
      }, function(e) {
      console.log('Error decoding file', e);
    }); 

  };
  xhr.send();
}

