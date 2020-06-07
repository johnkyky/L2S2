import java.util.Scanner;

public class SaisieRPN
{
	private MoteurRPN moteur;
	private Operation operation;

	public SaisieRPN(int min, int max)
	{
		moteur = new MoteurRPN(min, max);
	}

	public static String read()
	{
		Scanner scan = new Scanner(System.in);
		String input = scan.nextLine();

		return input;
	}

	public boolean analyse(String message)
	{
		boolean do_changement = false;
		if(message.equals("exit"))
			return false;
		if(message.equals("+"))
		{
			operation = Operation.PLUS;
			do_changement = true;
		}
		else if(message.equals("-"))
		{
			operation = Operation.MOINS;
			do_changement = true;
		}
		else if(message.equals("*"))
		{
			operation = Operation.MULT;
			do_changement = true;
		}
		else if(message.equals("/"))
		{
			operation = Operation.DIV;
			do_changement = true;
		}
		else
		{
			try
			{
				if(moteur.stringToDouble(message))
					moteur.addPile(Double.parseDouble(message));
			}
			catch(AddPileException ex) {}
			catch(StringToDoubleException ex) {}
		}

		if(do_changement && moteur.sizePile() > 1)
		{
			try
			{
				moteur.addPile(operation.eval(moteur.getHeadPile(), moteur.getHeadPile()));
			}
			catch(AddPileException ex) {}
			catch(OperationException ex) {}
		}
		moteur.printPile();
		return true;
	}
}