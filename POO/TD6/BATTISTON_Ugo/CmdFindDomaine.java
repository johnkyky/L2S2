import java.util.ArrayList;


public class CmdFindDomaine implements Commande
{
	private DNS dns;

	public CmdFindDomaine(DNS dns)
	{
		this.dns = dns;
	}

	public void execute(String argv)
	{
		if(argv == null)
		{
			System.out.println("└── ls [-a] |domaine|");
			return;
		}

		String[] stringSplit = argv.split(" ");

		if(stringSplit[0].equals("-a") && stringSplit.length == 2)
		{
			ArrayList<DnsItem> listItem = dns.getItems(stringSplit[1]);
			if(listItem == null)
			{
				System.out.println("└── Domaine not found");
				return;
			}
			for (DnsItem item : listItem)
			    System.out.println(item.toStringIP());
		}
		else if(!stringSplit[0].equals("-a"))
		{
			ArrayList<DnsItem> listItem = dns.getItems(stringSplit[0]);
			if(listItem == null)
			{
				System.out.println("└── Domaine not found");
				return;	
			}
			for (DnsItem item : listItem)
			    System.out.println(item.toStringName());
		}
		else
			System.out.println("└── ls [-a] |domaine|");
	}
}