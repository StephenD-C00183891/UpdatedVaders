var data2

function Player(x,y)
{
	this.x = x;
	this.y = y;
	this.width = 40;
	this.height = 40;
	this.speed = 0;
    this.firetimer1 =0;
    this.firetimer2 =0;
    this.delay = 500;
	this.image = new Image();
	this.image.src = "player1.png"
	this.image2 = new Image();
	this.image2.src = "player2.png"

    this.m_projectiles =  [];
    this.m_projectiles2 = [];
	this.frameCount = 0;
	this.timer = 0;
	this.init();
}

function clearCanvas()
{
	canvas.width = canvas.width;
}

Player.prototype.init = function()
{
	this.loadAnimationMetadata("player1.json");
}
Player.prototype.update = function(dt)
{
	this.firetimer1 += dt;
    this.firetimer2 += dt;
  	

	if (game.manager.GameStates[1].m_fireRequest == true)
	{
		this.openFire();
        game.manager.GameStates[1].m_fireRequest = false;
	}

	if (game.manager.GameStates[1].m_fireRequest2 == true)
	{
		this.openFire2();
        game.manager.GameStates[1].m_fireRequest2 = false;
	}

    for (var i = 0; i < this.m_projectiles.length; i++) 
    {
    	this.m_projectiles[i].update(-5);
    }

    for (var i = 0; i < this.m_projectiles2.length; i++)
    {
    	this.m_projectiles2[i].update(5);
    }

    //this.Stop();
}


Player.prototype.openFire = function()
{
	if(this.firetimer1 > this.delay)
  	{
  		this.m_projectiles.push(new Projectile(game.manager.GameStates[1].playerList[0].x +8,game.manager.GameStates[1].playerList[0].y));
  		game.manager.GameStates[1].playSound("shoot");
		this.firetimer1 =0;
	}
}
Player.prototype.openFire2 = function()
{
	if(this.firetimer2 > this.delay)
  	{
  		this.m_projectiles2.push(new Projectile(game.manager.GameStates[1].playerList[1].x +8, game.manager.GameStates[1].playerList[1].y + 20));
  		game.manager.GameStates[1].playSound("shoot");
  		this.firetimer2 = 0;
  	}
}

Player.prototype.moveLeft = function()
{	
	this.speed += 0.15;

	this.x -= this.speed;
}

Player.prototype.moveRight = function()
{	
	this.speed += 0.15;

	this.x += this.speed;
}

Player.prototype.Stop = function()
{	
	/*if (game.manager.GameStates[1].p1SlowLeft == true && this.speed > 0) {
		this.speed -= 0.01;
		this.x += this.speed;
	}

	if(this.speed == 0)
	{
		game.manager.GameStates[1].p1MoveLeft = false;
		game.manager.GameStates[1].p1MoveRight = false;

		game.manager.GameStates[1].p2MoveLeft = false;
		game.manager.GameStates[1].p2MoveRight = false;

		game.manager.GameStates[1].p1SlowLeft = false;
	}*/
	this.speed = 0;
}

Player.prototype.render = function(flipped, dt)
{
	this.timer += dt;

 	if(this.timer > 100)
 	{
 		this.frameCount ++;
 		this.timer = 0;

 		if (this.frameCount > 3)
 		{
 			this.frameCount = 0;
 		}
 	}

	for (var i = 0; i < this.m_projectiles.length; i++) 
	{
		this.m_projectiles[i].render(flipped, dt);
	}
	 for (var i = 0; i < this.m_projectiles2.length; i++) 
	{
		this.m_projectiles2[i].render(flipped, dt);
	}

	if (data2 != undefined)
	{
		if(flipped == true)
		{
			ctx.drawImage(this.image2, data2.frames[this.frameCount].frame.x, data2.frames[this.frameCount].frame.y, data2.frames[this.frameCount].frame.w, data2.frames[this.frameCount].frame.h, this.x, this.y, 29,61);
		}
		if(flipped == false)
		{
			ctx.drawImage(this.image, data2.frames[this.frameCount].frame.x, data2.frames[this.frameCount].frame.y, data2.frames[this.frameCount].frame.w, data2.frames[this.frameCount].frame.h, this.x, this.y, 29,61);
		}
	}
}



Player.prototype.loadAnimationMetadata = function(filename) {

    	var jsonfile = new XMLHttpRequest();
         
    	jsonfile.open("GET", filename, true);
     
    //when the message comes back from the server this function is called
    jsonfile.onreadystatechange = function() {

        if (jsonfile.readyState == 4) {
            if (jsonfile.status == 200) {
                 
                //data now contains the data from your json file
                data2 = JSON.parse(jsonfile.responseText);
                            
            }
 
        }
    }; 
    //This sends the request
    jsonfile.send(null);
}
