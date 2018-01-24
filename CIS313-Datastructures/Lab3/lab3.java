import java.util.Scanner;


public class lab3 {
    public static void main(String[] args) {
    
    	// Loop over the Scanner
        // Split each line into the task and the corresponding number (if one exists)
        // Depending on what the input task was, preform the corresponding function
        //      (ie) insert, maximum, extractMax, isEmpty, or print
        // Hint: Use a switch-case statement

        // Don't forget to close your Scanner!

        Scanner          scanner     = new Scanner(System.in);
        int              numProblems = scanner.nextInt();
        int              number      = 0;
        pQueue<Integer>  pqueue      = new pQueue<>(numProblems);
        scanner.nextLine();

        for(int i = 0; i < numProblems; i++){
            String   k       = scanner.nextLine();
            String[] splits  = k.split(" ");
            String   command = splits[0];
            if(splits.length > 1) {
                number = Integer.parseInt(splits[1]);
            }

            if(k == null){
                continue;
            }

            switch (command) {
                case "insert":
                    pqueue.insert(number);
                    break;

                case "print":
                    pqueue.print();
                    System.out.println();
                    break;

                case "isEmpty":
                    if(pqueue.isEmpty()){
                        System.out.println("Empty");
                    } else {
                        System.out.println("Not Empty");
                    }
                    break;

                case "maximum":
                    System.out.println(pqueue.maximum());
                    break;

                case "extractMax":
                    System.out.println(pqueue.extractMax());
                    break;

                default:
                    break;
            }
        }
        scanner.close();
    }
}
