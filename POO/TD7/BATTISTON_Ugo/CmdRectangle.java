public class CmdRectangle implements Commande
{
	private Drawable draw;

	public CmdRectangle(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		String[] buffer = argv.split(" ");

		if(buffer.length != 5)
		{
			System.out.println("rectangle [nom] [position x] [position y] [largeur] [hauteur]");
			return;
		}

		if(draw.getHashMap().containsKey(buffer[0]))
		{
			System.out.println("Le nom est deja pris par un element");
			return;
		}
		if(draw.getHashMapGroupe().containsKey(buffer[0]))
		{
			System.out.println("Le nom est deja pris par un groupe");
			return;
		}

		int[] tabl = new int[4];
		try
		{
			tabl[0] = Integer.parseInt(buffer[1]);
			tabl[1] = Integer.parseInt(buffer[2]);
			tabl[2] = Integer.parseInt(buffer[3]);
			tabl[3] = Integer.parseInt(buffer[4]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("rectangle [nom] [position x] [position y] [largeur] [hauteur]");
			return;
		}
		draw.getHashMap().put(buffer[0], new Rectangle(tabl[0], tabl[1], tabl[2], tabl[3]));
	}	
}