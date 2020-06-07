public class DnsItem
{
	private AdresseIP ip;
	private NomMachine name;
	
	public DnsItem(String ip, String name)
	{
		this.ip = new AdresseIP(ip);
		this.name = new NomMachine(name);
	}

	public String toString()
	{
		return name + " " + ip;
	}

	public String toStringIP()
	{
		return ip.toString();
	}

	public String toStringName()
	{
		return name.toString();
	}
}