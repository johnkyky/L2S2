public class mainclass{
	static public void main(String[] argv)
	{
		clientclass Johnkyky = new clientclass("Johnkyky");
		clientclass Rulia974 = new clientclass("Rulia974");
		clientclass Rewayde = new clientclass("Rewayde");
		serveurclass serveur = new serveurclass();

		Johnkyky.seConnecter(serveur);
		Rulia974.seConnecter(serveur);
		Rewayde.seConnecter(serveur);

		Rewayde.envoyer("salut");
	}
}