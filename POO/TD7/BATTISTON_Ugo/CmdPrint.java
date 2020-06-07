import java.util.ArrayList;

public class CmdPrint implements Commande
{
	private Drawable draw;

	public CmdPrint(Drawable draw)
	{
		this.draw = draw;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			for (String i : draw.getHashMap().keySet())
      			System.out.println(i + " : " + draw.getHashMap().get(i));
      		for (String i : draw.getHashMapGroupe().keySet())
      			System.out.println(i + " : " + draw.getHashMapGroupe().get(i));
      		return;
		}
		
		String[] buffer = argv.split(" ");

		for(int i = 0; i < buffer.length; i++)
		{
			Transformable trans = draw.getHashMap().get(buffer[i]);
			if(trans != null)
				System.out.println(buffer[i] + " : " + trans);
			
			ArrayList<Transformable> list = draw.getHashMapGroupe().get(buffer[i]);
			if(list != null)
				System.out.println(buffer[i] + " : " + list);
		}
	}	
}