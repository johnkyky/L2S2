public class DrawableApp
{
	private DrawableUI ui;
	private Drawable drawable;
	
	public DrawableApp()
	{
		this.drawable = new Drawable();
		this.ui = new DrawableUI(this.drawable);
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