
public class Stack<E> {
	private Node<E> top;
	
	public Stack(){
	
		// We want to initialize our Stack to be empty
		// (ie) Set top as null
		top = null;
		
	}
	
	public void push(E newData){
	
		// We want to create a node whose data is newData and next node is top
		// Push this new node onto the stack
		// Update top
		Node<E> newnode = new Node<>(newData,null);
		newnode.setNext(top);
		top = newnode;

	}
	
	public Node<E> pop(){
	
		// Return the Node that currently represents the top of the stack
		// Update top
		// Hint: The order you implement the above 2 tasks matters, so use a temporary node
	 	//	     to hold important information
		// Hint: Return null on a empty stack
		if(isEmpty())
			return null;
		Node<E> returningnode = top;
		top = returningnode.getNext();
		return returningnode;
	}
	
	public boolean isEmpty(){

		//Check if the Stack is empty
		return top == null;
	}
	
	public void printStack(){

		// Loop through your stack and print each Node's data
		if(isEmpty())
			return;
		Node<E> printnode = top;
		while(printnode != null) {
			System.out.println(printnode.getData());
			printnode = printnode.getNext();
		}
	}
}