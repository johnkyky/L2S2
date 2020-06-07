public class CmdExit implements Commande
{
	public CmdExit()
	{

	}

	public void execute(String argv)
	{
		System.exit(0);
	}	
}