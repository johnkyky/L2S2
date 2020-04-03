import org.apache.commons.math3.complex.*;

public class Mainclass
{
    public static void main(String[] args)
    {
        Complex complex1 = new Complex(3.0, 2.0);
		Complex complex2 = new Complex(1.0, 4.0);

		double complex1R = complex1.getReal();
		double complex1I = complex1.getImaginary();

		Complex multiply2 = complex2.multiply(2);

		boolean equals = complex1.equals(complex2);


        System.out.println("complex1 = " + complex1.toString() + " | real_part = " + complex1R + " | imaginary_part = " + complex1I);
        System.out.println("complex2 = " + complex2.toString() + " | complex2 * 2 = " + multiply2.toString());

        System.out.println("(complex1 = complex2) = " + equals);
    }
}