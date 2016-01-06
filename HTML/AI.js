var data
function AI(tempSpeed)
{
	
	var enemies
	var list
	var timer
	var frameCount
	var enemyXPos
	var enemyYPos
	
	var mSpeed
 
	this.frameCount = 0;
	this.timer = 0;
	this.mSpeed = tempSpeed;
	this.x =((Math.random() * 600) - 1300);
	this.y =((Math.random() * (canvas.height / 1.8) + (canvas.height / 5)));

	this.enemies = new Image();
	this.enemies.src = "images/GameScreen/enemies.png"
     
	this.init();
}

function clearCanvas()
{
	canvas.width = canvas.width;
}

AI.prototype.init = function()
{
	this.loadAnimationMetadata("enemies.json");	
}

AI.prototype.update = function()
{
	clearCanvas();
	this.x += this.mSpeed;
}

AI.prototype.render = function(dt)
{
	this.timer += dt;

 	if(this.timer > 100)
 	{
 		this.frameCount ++;
 		this.timer = 0;

 		if (this.frameCount > 5)
 		{
 			this.frameCount = 0;
 		}
 	}
	if (data != undefined){
		ctx.drawImage(this.enemies, data.frames[this.frameCount].frame.x, data.frames[this.frameCount].frame.y, data.frames[this.frameCount].frame.w, data.frames[this.frameCount].frame.h, this.x, this.y, 30, 21);
	}


}

	AI.prototype.loadAnimationMetadata = function(filename) {

    	var jsonfile = new XMLHttpRequest();
         
    	jsonfile.open("GET", filename, true);
     
    //when the message comes back from the server this function is called
    jsonfile.onreadystatechange = function() {

        if (jsonfile.readyState == 4) {
            if (jsonfile.status == 200) {
                 
                //data now contains the data from your json file
                data = JSON.parse(jsonfile.responseText);
                            
            }
 
        }
    };
    
     
    //This sends the request
    jsonfile.send(null);
}