import java.util.ArrayList;

public class CmdMove implements Commande
{
	private Drawable draw;

	public CmdMove(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("move [nom] [offset x] [offset y]");
			return;
		}
		
		String[] buffer = argv.split(" ");

		if(buffer.length != 3)
		{
			System.out.println("move [nom] [offset x] [offset y]");
			return;
		}

		int[] tabl = new int[2];
		try
		{
			tabl[0] = Integer.parseInt(buffer[1]);
			tabl[1] = Integer.parseInt(buffer[2]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("move [nom] [offset x] [offset y]");
			return;
		}
		
		Transformable trans = draw.getHashMap().get(buffer[0]);
		if(trans != null)
		{
			trans.move(tabl[0], tabl[1]);
			return;
		}

		ArrayList<Transformable> list = draw.getHashMapGroupe().get(buffer[0]);
		if(list != null)
		{
			for (Transformable i : list)
  				i.move(tabl[0], tabl[1]);
			return;
		}

		System.out.println(buffer[0] + " introuvable");
	}	
}