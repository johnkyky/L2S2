import java.util.ArrayList;

public class CmdSetSize implements Commande
{
	private Drawable draw;

	public CmdSetSize(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("setsize [nom] ... [largeur] [hauteur]");
			return;
		}

		String[] buffer = argv.split(" ");
		
		if(buffer.length < 3)
		{
			System.out.println("setsize [nom] ... [largeur] [hauteur]");
			return;
		}

		int largeur;
		int hauteur;

		try
		{
			largeur = Integer.parseInt(buffer[buffer.length - 2]);
			hauteur = Integer.parseInt(buffer[buffer.length - 1]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("setsize [nom] ... [largeur] [hauteur]");
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
					if(t.getShape() == "rectangle")
						t.setSize(largeur, hauteur);
			}
			else
				if(trans.getShape() == "rectangle")
					trans.setSize(largeur, hauteur);
				else
					System.out.println("L'element " + buffer[i] + " n'est pas un rectangle");
		}
	}	
}