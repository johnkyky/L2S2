import java.util.HashMap;
import java.util.Scanner;

public class DrawableUI
{
	private final HashMap<String, Commande>	commandes;
	private Commande commande;
	private Scanner scanner;
	private String argvBuffer;

	public DrawableUI(Drawable draw)
	{
		this.commandes = new HashMap<>();
		this.commandes.put("print", new CmdPrint(draw));
		this.commandes.put("cercle", new CmdCercle(draw));
		this.commandes.put("rectangle", new CmdRectangle(draw));
		this.commandes.put("setradius", new CmdSetRadius(draw));
		this.commandes.put("setposition", new CmdSetPosition(draw));
		this.commandes.put("setsize", new CmdSetSize(draw));
		this.commandes.put("mv", new CmdMove(draw));
		this.commandes.put("rm", new CmdRemove(draw));
		this.commandes.put("groupe", new CmdGroupe(draw));
		this.commandes.put("addgroupe", new CmdAddGroupe(draw));
		this.commandes.put("rmgroupe", new CmdRemoveGroupe(draw));
		this.commandes.put("help", new CmdHelp());
		this.commandes.put("exit", new CmdExit());

		this.commande = null;
		this.scanner = new Scanner(System.in);
	}

	public void nextCommande()
	{
		System.out.print("[Drawable]$ ");
    	String userInput = scanner.nextLine();

    	String[] userCmd = userInput.split(" ", 2);

		if(userCmd.length < 4 && this.commandes.containsKey(userCmd[0]))
		{
			this.commande = this.commandes.get(userCmd[0]);
			if(userCmd.length == 2)
				argvBuffer = userCmd[1];
		}
	}

	public void affiche()
	{
		if(this.commande != null)
			this.commande.execute(argvBuffer);
		else
			System.out.println("Command not found");
		this.commande = null;
		this.argvBuffer = null;
	}
}