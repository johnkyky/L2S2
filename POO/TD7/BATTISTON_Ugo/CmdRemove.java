import java.util.ArrayList;

public class CmdRemove implements Commande
{
	private Drawable draw;

	public CmdRemove(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("rm [nom] ...");
			return;
		}

		String[] buffer = argv.split(" ");

		for(int i = 0; i < buffer.length; i++)
		{
			Transformable trans = draw.getHashMap().remove(buffer[i]);
			if(trans == null)
			{
				ArrayList<Transformable> list = draw.getHashMapGroupe().remove(buffer[i]);
				if(list == null)
					System.out.println("L'element " + buffer[i] + " introuvable");
			}
			else
			{
				for (ArrayList<Transformable> x : draw.getHashMapGroupe().values())
				{
					if(x.remove(trans))
						return;
				}
			}
		}
	}	
}