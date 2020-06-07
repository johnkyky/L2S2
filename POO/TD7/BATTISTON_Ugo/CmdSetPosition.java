import java.util.ArrayList;

public class CmdSetPosition implements Commande
{
	private Drawable draw;

	public CmdSetPosition(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("setposition [nom] ... [position x] [position y]");
			return;
		}

		String[] buffer = argv.split(" ");
		
		if(buffer.length < 3)
		{
			System.out.println("setposition [nom] ... [position x] [position y]");
			return;
		}

		int x;
		int y;

		try
		{
			x = Integer.parseInt(buffer[buffer.length - 2]);
			y = Integer.parseInt(buffer[buffer.length - 1]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("setposition [nom] ... [position x] [position y]");
			return;
		}

		for(int i = 0; i < buffer.length - 2; i++)
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
				{
					t.setPositionX(x);
					t.setPositionY(y);
				}
			}
			else
			{
				trans.setPositionX(x);
				trans.setPositionY(y);
			}
		}
	}	
}