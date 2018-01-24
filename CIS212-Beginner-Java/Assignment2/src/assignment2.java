import java.util.ArrayList;
import java.util.InputMismatchException;
import java.util.Scanner;
import java.util.Random;

public class assignment2 {
	
	public static void main( String[] args ){
		
		Scanner input = new Scanner ( System.in );
		
		int arrlength = 0;
		double density = 0;
		boolean correct = false;
		
		System.out.print("Please array length:");
		while (correct != true){
			try {
				arrlength = input.nextInt();
				correct = true;
		} catch (InputMismatchException ex){
				System.out.println("Put in valid integer");
				correct = false;
			}
		}
		correct = false;
		System.out.println("Enter density:");
		while (correct != true){
			try{
				density = input.nextDouble();
				correct = true;
			} catch (InputMismatchException ex){
				System.out.println("Put in valid double desnsity");
				correct = false;
			}
		}
		int[] thedensearray = createDenseArray(arrlength, density);
		ArrayList thesparsearray = createSparseArray(arrlength, density);
		findMaxArray(thedensearray);
		findMaxArrayList(thesparsearray);
		
		
	}
	
	public static int[] createDenseArray(int arrlength, double density){
		long start_time = System.nanoTime();
		int[] new_array = new int[arrlength];
		Random rand_num = new Random();
		
		for(int i = 0; i < arrlength; i++){
			double num = Math.random();
			if (num < density) {
				int rand_int = rand_num.nextInt(1000000);
				new_array[i] = rand_int;
			}
		}
		long totaltime = System.nanoTime() - start_time;
		System.out.println("createDenseArray() length: " + arrlength + " time: " + totaltime);
		return new_array;
	}
	
	public static ArrayList createSparseArray(int arrlength, double density){
		long start_time = System.nanoTime();
		ArrayList<int[]> list = new ArrayList<int[]>();
		Random rand_num = new Random();
		for(int i = 0; i < arrlength; i++){
			double num = Math.random();
			if (num < density){
				int[] new_array = new int[2];
				new_array[0] = i;
				new_array[1] = rand_num.nextInt(1000000);
				list.add(new_array);
			}
		}
		long totaltime = System.nanoTime() - start_time;
		System.out.println("createSparseArray() length: " + list.size() + " time: " + totaltime);
		return list;
	}

	public static void findMaxArray(int[] array){
		long start_time = System.nanoTime();
		int maxvalue = 0;
		int maxi = 0;
		for(int i = 0; i < array.length; i++){
			if (array[i] > maxvalue){
				maxvalue = array[i];
				maxi = i;
			}
		}
		long totaltime = System.nanoTime() - start_time;
		System.out.println("findMax (array): " + maxvalue + " at: " + maxi);
		System.out.println("dense findMax() time: " + totaltime);
	}
	
	public static void findMaxArrayList(ArrayList<int[]> array){
		long start_time = System.nanoTime();
		int maxvalue = 0;
		int maxi = 0;
		for(int i = 0; i < array.size(); i++){
			int maxvaluetemp = array.get(i)[1];
			int maxitemp = array.get(i)[0];
			if (maxvaluetemp > maxvalue){
				maxvalue = maxvaluetemp;
				maxi = maxitemp;
			}
		}
		long totaltime = System.nanoTime() - start_time;
		System.out.println("findMax (list): " + maxvalue + " at: " + maxi);
		System.out.println("sparse findMax() time: " + totaltime);
	}
}