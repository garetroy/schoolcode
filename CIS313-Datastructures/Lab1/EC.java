import java.util.Scanner;
public class EC {
        public static void main(String[] args) {

            // Create a Scanner that reads system input

            // Loop over the scanner's input
            // For each line of the input, send it to isPalindrome()
            // If isPalindrome returns true, print "This is a Palindrome."
            // Otherwise print "Not a Palindrome."

            // Close the Scanner
            Scanner scanner = new Scanner(System.in);
            int numProblems = scanner.nextInt();
            for (int i = 0; i < numProblems; i++) {
                if (isPalindromeEC(scanner.next()))
                    System.out.println("This is a Palindrome.");
                else
                    System.out.println("Not a Palindrome.");

            }
            scanner.close();

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
