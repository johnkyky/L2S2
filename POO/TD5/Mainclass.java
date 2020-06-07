public class Mainclass
{
	public static void main(String[] args)
	{
		CalculatriceRPN calculateur = new CalculatriceRPN(0, 1000);

		boolean done = true;
		while(done)
			calculateur.loop();
	}
}

///faire l exception sur le div 0