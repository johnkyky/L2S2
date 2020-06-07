import java.util.ArrayList;

public class CmdSetRadius implements Commande
{
	private Drawable draw;

	public CmdSetRadius(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("setradius [nom] ... [radius]");
			return;
		}

		String[] buffer = argv.split(" ");
		
		if(buffer.length < 2)
		{
			System.out.println("setradius [nom] ... [radius]");
			return;
		}

		int rad;
		try
		{
			rad = Integer.parseInt(buffer[buffer.length - 1]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("setradius [nom] ... [radius]");
			return;
		}

		for(int i = 0; i < buffer.length - 1; i++)
		{
			Transformable trans = draw.getHashMap().get(buffer[i]);
			if(trans == null)
			{
				ArrayList<Transformable> list = draw.getHashMapGroupe().get(buffer[i]);
				if(list == null)
				{
					System.out.println("L'element " + buffer[i] + " est introuvable");
					continue;
				}

				for(Transformable t : list)
					if(t.getShape() == "cercle")
						t.setSize(rad, rad);
			}
			else
				if(trans.getShape() == "cercle")
					trans.setSize(rad, rad);
				else
					System.out.println("L'element " + buffer[i] + " n'est pas un cercle");
		}
	}	
}