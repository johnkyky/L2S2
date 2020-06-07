import java.util.ArrayList;

public class CmdAddGroupe implements Commande
{
	private Drawable draw;

	public CmdAddGroupe(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("addgroupe [groupe] [element] ...");
      		return;
		}

		String[] buffer = argv.split(" ");
		
		ArrayList<Transformable> list = draw.getHashMapGroupe().get(buffer[0]);
		if(list != null)
		{
			for(int i = 1; i < buffer.length; i++)
			{
				Transformable trans = draw.getHashMap().get(buffer[i]);
				if(trans == null)
					System.out.println("L'element " + buffer[i] + " est introuvable");

				if(list.contains(trans))
					System.out.println("L'element " + buffer[i] + " est deja dans le groupe " + buffer[0]);
				else
					list.add(trans);
			}
		}
		else
			System.out.println("Le groupe " + buffer[0] + " est introuvable");
	}	
}