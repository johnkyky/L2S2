import java.util.ArrayList;

public class serveurclass
{
	ArrayList<clientclass> Array_client;

	public serveurclass()
	{
		Array_client = new ArrayList<>();
	}

	public boolean connecter(clientclass client)
	{
		if(Array_client.contains(client))
		{
			System.out.println("client deja connecter");
			return false;
		}
		
		Array_client.add(client);
		return true;
	}

	public void diffuser(String message)
	{
		for(clientclass i : Array_client)
			i.recevoir(message);
	}
}
