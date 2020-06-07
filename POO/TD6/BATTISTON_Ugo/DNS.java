import java.util.HashMap;
import java.util.ArrayList;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class DNS
{	
	private final HashMap<String, DnsItem> dataIP;
	private final HashMap<String, DnsItem> dataName;
	private final HashMap<String, ArrayList<DnsItem>> dataDomaine;
	
	public DNS(String filename)
	{
		dataIP = new HashMap<>();
		dataName = new HashMap<>();
		dataDomaine = new HashMap<>();

		try
		{
			File f = new File(filename);
			Scanner readf = new Scanner(f);
			while (readf.hasNextLine())
			{
				String data = readf.nextLine();
				String[] splitData = data.split(" ");

				dataIP.put(splitData[1], new DnsItem(splitData[1], splitData[0]));
				dataName.put(splitData[0], new DnsItem(splitData[1], splitData[0]));

				String[] domaine = splitData[0].split("\\.");
				ArrayList<DnsItem> itemBuffer = dataDomaine.get(domaine[1]);
				if(itemBuffer == null)
				{
					ArrayList<DnsItem> list = new ArrayList<>();
					list.add(new DnsItem(splitData[1], splitData[0]));
					dataDomaine.put(domaine[1], new ArrayList<DnsItem>(list));
				}
				else
					dataDomaine.get(domaine[1]).add(new DnsItem(splitData[1], splitData[0]));
			}
			readf.close();
		}
		catch(FileNotFoundException e)
		{
			System.out.println("An error occurred in the open of file");
			System.exit(1);
		}
	}

	public DnsItem getItem(int adr, int es, int se, int ip)
	{
		return dataIP.get(new String(adr + "." + es + "." + se + "." + ip));
	}

	public DnsItem getItem(String nom, String qualifie, String machine)
	{
		return dataName.get(nom + "." + qualifie + "." + machine);
	}

	public ArrayList<DnsItem> getItems(String domaine)
	{
		return dataDomaine.get(domaine);
	}
}