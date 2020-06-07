public class DnsApp
{
	private DnsTUI ui;
	private DNS dns;

	public DnsApp(String filename)
	{
		this.dns = new DNS(filename);
		this.ui = new DnsTUI(this.dns);
	}

	public void run()
	{
		while(true)
		{
			ui.nextCommande();
			ui.affiche();
		}
	}
}