public class Animal{
	String name;
	String type;
	int age;
	boolean sauvage;
	int life;
	int degat;


	public Animal(String name, String type, int age, boolean sauvage, int degat)
	{
		this.name = name;
		this.type = type;
		this.age = age;
		this.sauvage = sauvage;
		this.life = 100;
		this.degat = degat;
	}


	public void frapper(Animal victime)
	{
		if(sauvage)
		{
			System.out.println(name + " vient de frapper " + victime.get_name());
			victime.set_life(victime.get_life() - degat);
		}
		else
		{
			System.out.println(name + " n est pas assez sauvage");
		}
	}

	public void affiche()
	{
		System.out.println(name + " " + type + " " + age + " " + sauvage + " " + life + " " + degat);
	}

	//////////////////////////////

	public void set_life(int life)
	{

		this.life = life;
		if(this.life < 0)
		{
			this.life = 0;
			System.out.println(name + " est mort !");
		}
		else if(this.life < 50)
		{
			sauvage = true;
		}
	}

	public int get_life()
	{
		return life;
	}

	public String get_name()
	{
		return name;
	}
}