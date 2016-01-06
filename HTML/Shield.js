function Shield(x,y)
{
	this.shieldImage = new Image();
	this.shieldImage.src = "images/GameScreen/shield.png"

    this.shieldImage1 = new Image();
    this.shieldImage1.src = "images/GameScreen/shield1.png"

    this.shieldImage2 = new Image();
    this.shieldImage2.src = "images/GameScreen/shield2.png"

    this.shieldImage3 = new Image();
    this.shieldImage3.src = "images/GameScreen/shield3.png"

    this.x = x;
    this.y = y;
    this.originalX = x;
    this.originalY = y;
    this.width = 50;
    this.height = 10;
    this.health =100;

}

Shield.prototype.reset = function()
{
	this.x = this.originalX;
	this.y = this.originalY
	console.log("reset");
}

Shield.prototype.render = function()
{
    if(this.health > 80)
    {
	   ctx.drawImage(this.shieldImage, 0, 0, this.width, this.height, this.x, this.y, this.width, this.height);
    }
    else if(this.health > 60)
    {
       ctx.drawImage(this.shieldImage1, 0, 0, this.width, this.height, this.x, this.y, this.width, this.height);
    }
    else if(this.health > 40)
    {
       ctx.drawImage(this.shieldImage2, 0, 0, this.width, this.height, this.x, this.y, this.width, this.height);
    }
    else if(this.health > 0)
    {
       ctx.drawImage(this.shieldImage3, 0, 0, this.width, this.height, this.x, this.y, this.width, this.height);
    }
}

