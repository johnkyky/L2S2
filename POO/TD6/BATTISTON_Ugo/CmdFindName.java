public class CmdFindName implements Commande
{
	private DNS dns;

	public CmdFindName(DNS dns)
	{
		this.dns = dns;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("└── searchName |machine name|");
			return;
		}

		String[] stringArgv = argv.split("\\.");
		
		if(stringArgv.length == 3)
		{
			DnsItem item = dns.getItem(stringArgv[0], stringArgv[1], stringArgv[2]);
			if(item == null)
			{
				System.out.println("└── Machine name not found");
				return;
			}
			System.out.println(item.toStringIP());
		}
		else
			System.out.println("└── searchName |machine name|");
	}	
}