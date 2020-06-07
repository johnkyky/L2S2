public class Rectangle extends Transformable
{
	private int largeur;
	private int hauteur;
	
	public Rectangle()
	{
		largeur = 5;
		hauteur = 5;
	}

	public Rectangle(int x, int y, int largeur, int hauteur)
	{
		super(x, y, "rectangle");
		this.largeur = largeur;
		this.hauteur = hauteur;
	}

	public void setSize(int x, int y)
	{
		this.largeur = x;
		this.hauteur = y;
	}

	public String toString()
	{
		return "Rectangle(" + super.getPositionX() + "," + super.getPositionY() + 
			   "," + this.largeur + "," + this.hauteur + ")";
	}
}