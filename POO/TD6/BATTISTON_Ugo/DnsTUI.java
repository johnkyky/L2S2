import java.util.HashMap;
import java.util.Scanner;

public class DnsTUI
{
	private final HashMap<String, Commande>	commandes;
	private Commande commande;
	private Scanner scanner;

	private String argvBuffer;

	public DnsTUI(DNS dns)
	{
		this.commandes = new HashMap<>();
		this.commandes.put("searchIP", new CmdFindIP(dns));
		this.commandes.put("searchName", new CmdFindName(dns));
		this.commandes.put("ls", new CmdFindDomaine(dns));
		this.commandes.put("help", new CmdHelp());
		this.commandes.put("exit", new CmdExit());

		this.commande = null;

		this.scanner = new Scanner(System.in);
	}

	public void nextCommande()
	{
		System.out.print("[DNS]$ ");
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
			System.out.println("└── command not found");
		this.commande = null;
		this.argvBuffer = null;
	}
}