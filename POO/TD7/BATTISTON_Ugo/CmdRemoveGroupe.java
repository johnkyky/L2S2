import java.util.ArrayList;

public class CmdRemoveGroupe implements Commande
{
	private Drawable draw;

	public CmdRemoveGroupe(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("rmgroupe [groupe] [element] ...");
			return;
		}
		
		String[] buffer = argv.split(" ");

		ArrayList<Transformable> list = draw.getHashMapGroupe().get(buffer[0]);

		if(buffer.length < 2)
		{
			System.out.println("rmgroupe [groupe] [element] ...");
			return;
		}

		if(list == null)
		{
			System.out.println("Le groupe n'existe pas");
			return;
		}
		
		for(int i = 1; i < buffer.length; i++)
		{
			Transformable trans = draw.getHashMap().get(buffer[i]);

			if(trans == null)
			{
				System.out.println("L'element " + buffer[i] + " n'existe pas");
				continue;
			}

			if(list.remove(trans) == false)
				System.out.println("L'element " + buffer[i] + " n'est pas dans le groupe " + buffer[0]);
		}
	}	
}