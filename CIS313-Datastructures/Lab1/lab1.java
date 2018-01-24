import java.util.Scanner;

public class lab1 {
	public static void main(String[] args){
	
		// Create a Scanner that reads system input
		
		// Loop over the scanner's input
		// For each line of the input, send it to isPalindrome()
		// If isPalindrome returns true, print "This is a Palindrome." 
		// Otherwise print "Not a Palindrome."
		
		// Close the Scanner
		Scanner scanner = new Scanner(System.in);
		int numProblems = scanner.nextInt();
		for(int i = 0; i < numProblems; i++){
			if(isPalindrome(scanner.next()))
				System.out.println("This is a Palindrome.");
			else
				System.out.println("Not a Palindrome.");

		}
		scanner.close();

	}
	
	private static boolean isPalindrome(String s){
	
		// Create a stack and a Queue of chars that represents the passed in string
		// Hint: While you loop through the given string, push the same char onto your stack
		//		 that you enqueue into your Queue. This way you can use dequeue to get 
		//       the string from left to right, but you pop the string from right to left
		
		// Compare your Queue and Stack to see if the input String was a Palindrome or not
		Queue<Character> fronttoback = new Queue<>();
		Stack<Character> backtofront = new Stack<>();
		char c;
		int i;
		for(i = 0; i < s.length(); i++){
			c = s.charAt(i);
			fronttoback.enqueue(c);
			backtofront.push(c);
		}
		while(!fronttoback.isEmpty() && !backtofront.isEmpty()){
			if(fronttoback.dequeue().getData() != backtofront.pop().getData())
				return false;
		}
		return true;

	}
	
    public static boolean isPalindromeEC(String s){
	
		// Implement if you wish to do the extra credit.
		TwoStackQueue<Character> twoqueue = new TwoStackQueue<>();
		char   c;
		String instring = "";
		String outstring = "";
		for(int i = 0; i < s.length(); i ++){
			c = s.charAt(i);
			twoqueue.enqueue(c);
		}
		Node<Character> comeparenode = twoqueue.instack.pop();
		twoqueue.instack.push(comeparenode.getData());
		while(comeparenode != null){
			instring += comeparenode.getData();
			comeparenode = comeparenode.getNext();
		}
		comeparenode = twoqueue.dequeue();
		while(comeparenode != null){
			outstring += comeparenode.getData();
			comeparenode = comeparenode.getNext();
		}

		if(instring.equals(outstring))
			return true;

		return false;
		
	}
}
