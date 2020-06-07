public abstract class Transformable
{
	private int positionX;
	private int positionY;
	private String shape;

	public Transformable()
	{
		this.positionX = 0;
		this.positionY = 0;
	}

	public Transformable(int x, int y, String shape)
	{
		this.positionX = x;
		this.positionY = y;
		this.shape = shape;
	}

	public void setPositionX(int x)
	{
		this.positionX = x;
	}

	public void setPositionY(int y)
	{
		this.positionY = y;
	}

	public int getPositionX()
	{
		return this.positionX;
	}

	public int getPositionY()
	{
		return this.positionY;
	}

	public void move(int x, int y)
	{
		this.positionX += x;
		this.positionY += y;
	}

	public String getShape()
	{
		return shape;
	}

	public void setSize(int x, int y)
	{
		System.out.println("set");
	}

	public String toString()
	{
		return "transformable";
	}
}