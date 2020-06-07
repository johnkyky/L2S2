public class CmdHelp implements Commande
{
	public CmdHelp()
	{

	}

	public void execute(String argv)
	{
		System.out.println("├── help");
		System.out.println("├── searchIP |ip adress|");
		System.out.println("├── searchName |machine name|");
		System.out.println("├── ls [-a] |domaine|");
		System.out.println("└── exit");
	}	
}