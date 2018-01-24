import java.util.Scanner;

public class lab0 {
 public static void main(String[] args){
  Scanner scanner = new Scanner(System.in);
  int numProblems = scanner.nextInt();
  for(int i = 0; i < numProblems; ++i){
    int a = scanner.nextInt();
    int b = scanner.nextInt();
    int g = gcd(a,b);
    int l = lcm(a,b);
    System.out.println(g + " " + l);
  }
 }

 public static int gcd(int a, int b){
  // Find the greatest common divisor of a and b
  // Hint: Use Euclids Algorithm
 }

 public static int lcm(int a, int b){
  // Find the least common multiple of a and b
  // Hint: Use the gcd of a and b
 }
}
