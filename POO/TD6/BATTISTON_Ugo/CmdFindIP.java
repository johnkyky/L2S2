public class CmdFindIP implements Commande
{
	private DNS dns;

	public CmdFindIP(DNS dns)
	{
		this.dns = dns;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("└── searchIP |ip adress|");
			return;
		}

		String[] stringArgv = argv.split("\\.");
		
		int[] intArgv = new int[4];
		try
		{
			intArgv[0] = Integer.parseInt(stringArgv[0]);
			intArgv[1] = Integer.parseInt(stringArgv[1]);
			intArgv[2] = Integer.parseInt(stringArgv[2]);
			intArgv[3] = Integer.parseInt(stringArgv[3]);
		}
		catch(NumberFormatException e)
		{
			System.out.println("└── searchIP |ip adress|");
			return;
		}

		DnsItem item = dns.getItem(intArgv[0], intArgv[1], intArgv[2], intArgv[3]);
		if(item == null)
		{
			System.out.println("└── IP adress not found");
			return;
		}
		System.out.println(item.toStringName());
	}
}