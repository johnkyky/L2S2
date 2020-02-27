public class clientclass
{
	static public int number = 0;
	String name;
	int id;
	serveurclass serveur;
	
	public clientclass(String name)
	{
		this.name = new String(name);
		this.id = number;
		number++;
	}

	public boolean seConnecter(serveurclass serv)
	{
		this.serveur = serv;

		if(!this.serveur.connecter(this))
			return false;

		return true;
	}

	public void envoyer(String message)
	{
		if(serveur == null)
			return;

		this.serveur.diffuser(message);
	}

	public void recevoir(String message)
	{
		System.out.println("name" + this.name + " | id " + this.id + " |->" + message);
	}
}