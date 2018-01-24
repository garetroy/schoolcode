

        // Loop over the Scanner
        // Split each line into the task and the corresponding number (if one exists)
        // Depending on what the input task was, preform the corresponding function
        //      (ie) insert, delete, find, inoder, preorder, or postorder
        // Hint: Use a switch-case statement

        // Don't forget to close your Scanner!



import java.util.Scanner;

public class lab2 {
    public static void main(String[] args) {

        Scanner       scanner     = new Scanner(System.in);
        int           numProblems = scanner.nextInt();
        BST<Integer>  binarysearc = new BST<>();
        scanner.nextLine();

        for(int i = 0; i < numProblems; i++){
            String   k       = scanner.nextLine();
            String[] splits  = k.split(" ");
            String   command = splits[0];

            if(splits.length > 1) {
                int number = Integer.parseInt(splits[1]);

                switch (command) {
                    case "insert":
                        binarysearc.insert(number);
                        break;

                    case "delete":
                        binarysearc.delete(number);
                        break;

                    default:
                        break;
                }

            } else {

                    switch (command) {

                        case "preorder":
                            binarysearc.traverse("preorder", binarysearc.getRoot());
                            System.out.println();
                            break;

                        case "inorder":
                            binarysearc.traverse("inorder", binarysearc.getRoot());
                            System.out.println();
                            break;

                        case "postorder":
                            binarysearc.traverse("postorder", binarysearc.getRoot());
                            System.out.println();
                            break;

                        default:
                            break;
                    }
            }
        }
        scanner.close();
    }
}