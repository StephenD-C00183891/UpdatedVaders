var data3
function Projectile(x,y)
{
	this.x = x;
	this.y = y;
	this.width = 13;
	this.height = 13;
	this.image = new Image();
	this.image.src = "images/GameScreen/laser.png";  
	this.image2 = new Image();
	this.image2.src = "images/GameScreen/laserf.png";  
	this.m_Velocity = -5.5;

	this.frameCount = 0;
	this.timer = 0;
	this.init();
}

Projectile.prototype.update = function(speed){ 
  this.y += speed;
}

Projectile.prototype.init = function()
{
	this.loadAnimationMetadata("laser.json");
}

Projectile.prototype.detectCollisions = function(X, Y, Width, Height) {

	if(Width == undefined)
	{
		Width = 30;
	}
	if(Height == undefined)
	{
		Height = 30;
	}

	var rect1 = {x: this.x, y: this.y, width: this.width, height: this.height}
	var rect2 = {x: X, y:Y , width: Width, height: Height}

	if (rect1.x < rect2.x + rect2.width &&
   		rect1.x + rect1.width > rect2.x &&
   		rect1.y < rect2.y + rect2.height &&
   		rect1.height + rect1.y > rect2.y) {
		return true;
	}
};

Projectile.prototype.render = function(flipped, dt)
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

 	if(data3 != undefined) {
 		if(flipped == true)
		{
			ctx.drawImage(this.image2, data3.frames[this.frameCount].frame.x, data3.frames[this.frameCount].frame.y, data3.frames[this.frameCount].frame.w, data3.frames[this.frameCount].frame.h, this.x, this.y,  data3.frames[this.frameCount].frame.w, data3.frames[this.frameCount].frame.h);
		}
		if(flipped == false)
		{
			ctx.drawImage(this.image, data3.frames[this.frameCount].frame.x, data3.frames[this.frameCount].frame.y, data3.frames[this.frameCount].frame.w, data3.frames[this.frameCount].frame.h, this.x, this.y,  data3.frames[this.frameCount].frame.w, data3.frames[this.frameCount].frame.h);
		}
 		//ctx.drawImage(this.image, data3.frames[this.frameCount].frame.x, data3.frames[this.frameCount].frame.y, data3.frames[this.frameCount].frame.w, data3.frames[this.frameCount].frame.h, this.x, this.y, 30,26);
	}
	//ctx.drawImage(this.image, 0,0, this.width,this.height, this.x, this.y, this.width,this.height);	
}
function clearCanvas()
{
	canvas.width = canvas.width;
}


Projectile.prototype.loadAnimationMetadata = function(filename) {

    	var jsonfile = new XMLHttpRequest();

    	jsonfile.open("GET", filename, true);
     
    //when the message comes back from the server this function is called
    jsonfile.onreadystatechange = function() {

        if (jsonfile.readyState == 4) {
            if (jsonfile.status == 200) {
                 
                //data now contains the data from your json file
                data3 = JSON.parse(jsonfile.responseText);
                            
            }
 
        }
    }; 
    //This sends the request
    jsonfile.send(null);
}
