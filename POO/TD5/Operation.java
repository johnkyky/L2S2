public enum Operation
{
	PLUS("+")
	{
		@Override
		public double eval(double operande1, double operande2)
		{
			return operande1 + operande2;
		}
	},

	MOINS("-")
	{
		@Override
		public double eval(double operande1, double operande2)
		{
			return operande2 - operande1;
		}
	},

	MULT("*")
	{
		@Override
		public double eval(double operande1, double operande2)
		{
			return operande1 * operande2;
		}
	},

	DIV("/") 
	{
		@Override
		public double eval(double operande1, double operande2)
		{
			if(operande1 == 0)
			{
				new OperationException("Division par 0 interdite");
				return operande2;
			}
			else
				return operande2 / operande1;
		}
	};
 
 
	Operation(String operateur)
	{
		
	}

	public abstract double eval(double operande1, double operande2) throws OperationException;
}

//////////////////////////////////////////////////////////////////////////////////////

class OperationException extends Exception
{
    public OperationException(String message)
    {
        System.out.println("OperationException -> " + message);
    }
}