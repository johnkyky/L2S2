public class CmdHelp implements Commande
{
	public CmdHelp()
	{

	}

	public void execute(String argv)
	{
		System.out.println("print       (nom)");
		System.out.println("cercle      [nom] [position x] [position y] [radius]");
		System.out.println("rectangle   [nom] [position x] [position y] [largeur] [hauteur]");
		System.out.println("setradius   [nom] ... [radius]");
		System.out.println("setsize     [nom] ... [largeur] [hauteur]");
		System.out.println("setposition [nom] ... [position x] [position y]");
		System.out.println("move        [nom] [offset x] [offset y]");
		System.out.println("rm          [nom] ...");
		System.out.println("groupe      [nom] ...");
		System.out.println("addgroupe   [groupe] [element] ...");
		System.out.println("rmgroupe    [groupe] [element] ...");
		System.out.println("help");
		System.out.println("exit");
	}	
}