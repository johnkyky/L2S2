public class Cercle extends Transformable
{
	private int radius;

	public Cercle()
	{
		super();
		radius = 5;
	}

	public Cercle(int x, int y, int radius)
	{
		super(x, y, "cercle");
		this.radius = radius;
	}

	public void setRadius(int radius)
	{
		this.radius = radius;
	}

	public void setSize(int x, int y)
	{
		this.setRadius(x);
	}

	public String toString()
	{
		return "Cercle(" + super.getPositionX() + "," + super.getPositionY() + "," + this.radius + ")";
	}
}