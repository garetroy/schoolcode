public class TwoStackQueue<E> {
    private Stack<E> instack;
    private Stack<E> outstack;

    public TwoStackQueue(){
        instack  = new Stack<>();
        outstack = new Stack<>();
    }

    public void enqueue(E newData) {

        instack.push(newData);
    }

    public Node<E> dequeue(){

        if(!outstack.isEmpty())
            return null;
        while(!instack.isEmpty()){
            outstack.push(instack.pop().getData());
        }
        return outstack.pop();
    }

    public boolean isEmpty(){

        return instack == null && outstack == null;
    }

    public void printQueue(){

        Node<E> printnode;
        if(instack.isEmpty() && outstack.isEmpty())
            return;

        if(instack.isEmpty()) {
            printnode = outstack.pop();
            outstack.push(printnode.getData());
        } else {
            printnode = instack.pop();
            instack.push(printnode.getData());
        }

        while(printnode != null){
            System.out.println(printnode.getData());
            printnode = printnode.getNext();
        }
    }
}
