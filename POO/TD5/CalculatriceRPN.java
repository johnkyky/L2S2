public class CalculatriceRPN
{
    private SaisieRPN saisie;

    public CalculatriceRPN(int min, int max)
    {
        saisie = new SaisieRPN(min, max);
    }

    public boolean loop()
    {
        String message = saisie.read();
        return saisie.analyse(message);
    }
}