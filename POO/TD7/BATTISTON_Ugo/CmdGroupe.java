import java.util.ArrayList;

public class CmdGroupe implements Commande
{
	private Drawable draw;

	public CmdGroupe(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("groupe [nom] ...");
			return;
		}

		String[] buffer = argv.split(" ");

		for(int i = 0; i < buffer.length; i++)
		{
			if(draw.getHashMap().get(buffer[i]) != null)
				System.out.println("Le nom " + buffer[i] + " est deja pris par un objet");
			if(draw.getHashMapGroupe().get(buffer[i]) != null)
				System.out.println("Le nom " + buffer[i] + " est deja pris par un groupe");
			else
				draw.getHashMapGroupe().put(buffer[i], new ArrayList<Transformable>());
		}
	}	
}