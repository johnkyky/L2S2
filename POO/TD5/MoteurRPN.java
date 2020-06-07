import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class MoteurRPN
{
    private final int MAX_VALUE;
    private final int MIN_VALUE;

    Stack<Double> pile;
   
    public MoteurRPN(int min, int max)
    {
        MAX_VALUE = max;
        MIN_VALUE = min;

        pile = new Stack<>();
    }

    public void addPile(double val) throws AddPileException
    {
        if(val < MIN_VALUE || val > MAX_VALUE)
            throw new AddPileException();
        else
            pile.push(val);
    }

    public void printPile()
    {
        System.out.println(pile);
    }

    public double getHeadPile()
    {
        return pile.pop();
    }

    public int sizePile()
    {
        return pile.size();
    }

    public boolean stringToDouble(String message) throws StringToDoubleException
    {
        try
        {
            Double.parseDouble(message);
        }
        catch (Exception ex)
        {
            new StringToDoubleException();
            return false;
        } 
        
        return true;
    }
}

//////////////////////////////////////////////////////////////////////////////////////

class MoteurRPNException extends Exception {
    public MoteurRPNException() {
        System.out.println("MoteurRPNException -> ");
    }
}

class AddPileException extends MoteurRPNException {
    public AddPileException() {
        System.out.println("AddPileException -> valeur non prise en compte dans l'interval");
    }
}

class StringToDoubleException extends MoteurRPNException {
    public StringToDoubleException() {
        System.out.println("StringToDoubleException -> l'entrée n'est pas un nombre");
    }
}