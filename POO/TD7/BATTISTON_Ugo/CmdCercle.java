public class CmdCercle implements Commande
{
	private Drawable draw;

	public CmdCercle(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		String[] buffer = argv.split(" ");

		if(buffer.length != 4)
		{
			System.out.println("cercle [nom] [position x] [position y] [radius]");
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

		int[] tabl = new int[3];
		try
		{
			tabl[0] = Integer.parseInt(buffer[1]);
			tabl[1] = Integer.parseInt(buffer[2]);
			tabl[2] = Integer.parseInt(buffer[3]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("cercle [nom] [position x] [position y] [radius]");
			return;
		}
		draw.getHashMap().put(buffer[0], new Cercle(tabl[0], tabl[1], tabl[2]));
	}	
}