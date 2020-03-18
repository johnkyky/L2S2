public class mainclass{
	
	public static void main(String[] argv)
	{
		System.out.println("----------------------");
		


		Animal parent1, parent2, rulia974;
		parent1 = new Animal("Philippe", "Humain", 52, true, 15);
		parent2 = new Animal("Nathalie", "Humain", 51, false, 8);
		rulia974 = new Animal("Julie", "Humain", 20, true, 90);


		parent1.affiche();
		parent2.affiche();
		rulia974.affiche();
		System.out.println();

		Humain demo = new Humain();

		demo.affiche();


		System.out.println("----------------------");
	}
}