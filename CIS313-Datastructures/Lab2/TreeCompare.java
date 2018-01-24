import java.util.Scanner;

public class TreeCompare {
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
            }
        }

                      numProblems  = scanner.nextInt();
        BST<Integer>  binarysearc2 = new BST<>();
        scanner.nextLine();

        for(int i = 0; i < numProblems; i++) {
            String k = scanner.nextLine();
            String[] splits = k.split(" ");
            String command = splits[0];

            if (splits.length > 1) {
                int number = Integer.parseInt(splits[1]);

                switch (command) {
                    case "insert":
                        binarysearc2.insert(number);
                        break;

                    case "delete":
                        binarysearc2.delete(number);
                        break;

                    default:
                        break;
                }
            }
        }
        scanner.close();

        if(compare(binarysearc.getRoot(),binarysearc2.getRoot())){
            System.out.println("The trees have the same shape.");
        } else {
            System.out.println("The trees do not have the same shape.");
        }
    }

    public static boolean compare(Node<Integer> bsnode1, Node<Integer> bsnode2){

        if(bsnode1 == null && bsnode2 == null){
            return true;
        }

        if(bsnode1.getData() != bsnode2.getData()){
            return false;
        }

        return compare(bsnode1.getLeftChild(),bsnode2.getLeftChild()) && compare(bsnode1.getRightChild(),bsnode2.getRightChild());
    }
}