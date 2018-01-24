
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

public class Main {
	
	//This initializes randommaker (which is the random number generator), 
	//counters which is a "dictionary" that I store the counter for each shape in
	//shapes which is an ArrayList of the shapes that we go through
	static Random randommaker = new Random();
	public static Map<Integer, Double> counters = new HashMap<Integer, Double>();
	static ArrayList<AreaMeasurable> shapes = new ArrayList<AreaMeasurable>();
	
	public static void main( String[] args){
		for(int i = 0; i < 6; i++) // This is where it adds values and default keys to the dictionary
			counters.put(i,(double) 0);
		for(int i = 0; i < 1001; i++){
			//It randomly picks a int between 0 and 5, then creates a new shape dependant on the number
			int x = randommaker.nextInt(6);
			if (x==0){
				shapes.add(new Rectangle(nextRandomDouble(), nextRandomDouble()));
			} else if (x==1){
				shapes.add(new Circle(nextRandomDouble()));
			} else if (x==2){
				shapes.add(new Cube(nextRandomDouble(), nextRandomDouble(), nextRandomDouble()));
			}else if (x==3){
				shapes.add(new Sphere(nextRandomDouble()));
			}else if (x==4){
				shapes.add(new Square(nextRandomDouble()));
			}else if (x==5){
				shapes.add(new Box(nextRandomDouble(), nextRandomDouble(), nextRandomDouble()));
			}
			counters.put(x, counters.get(x) + 1);
		}
		System.out.println("circles: "+ counters.get(1) + " rects: " + counters.get(0) + 
				" squares: "+ counters.get(4) + " spheres: " + counters.get(3) + " boxes: " + 
				counters.get(5) + " cubes: " + counters.get(2));
		System.out.println(calculateSum(shapes));
	}
	
	private static double nextRandomDouble(){
		//Generates random doubles for the shapes we are making
		double radomnum = randommaker.nextDouble();
		return radomnum;
	}
	
	private static double calculateSum(ArrayList<AreaMeasurable> arrayList){
		//Gets all the elements in the ArrayList and gets the area, then adds them together
		double total = 0;
		for(int i = 0; i < arrayList.size(); ++i){
			total += arrayList.get(i).getArea();
		}
		return total;
	}
}
