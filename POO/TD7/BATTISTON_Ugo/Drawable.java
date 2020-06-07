import java.util.HashMap;
import java.util.ArrayList;

public class Drawable
{	
	private HashMap<String, Transformable> mapDrawable;
	private HashMap<String, ArrayList<Transformable>> mapDrawableGroupe;
	
	public Drawable()
	{
		mapDrawable = new HashMap<>();
		mapDrawableGroupe = new HashMap<>();
	}


	public Transformable getShape(String name)
	{
		return mapDrawable.get(name);
	}

	public HashMap<String, Transformable> getHashMap()
	{
		return mapDrawable;
	}

	public HashMap<String, ArrayList<Transformable>> getHashMapGroupe()
	{
		return mapDrawableGroupe;
	}
}