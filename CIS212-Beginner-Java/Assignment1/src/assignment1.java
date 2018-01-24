import java.util.Scanner;

public class assignment1
{
	//main method
	public static void main( String[] args )
	{
		//creates a scanner to obtain input
		Scanner input = new Scanner( System.in );

		int current; //The inputted number
		int total = 0; //The total value

		while (true) {
			System.out.print("Enter a positive integer (-1 to print, -2 to reset, -3 to exit)");
			current = input.nextInt();

			if (current == -1){
				System.out.println(total);
			}

			if (current == -2){
				total = 0;
			}

			if (current == -3){
				System.exit(0);
			}

			if (current >= 0){
				total = total + current;	
			}
		}		

	}

}
