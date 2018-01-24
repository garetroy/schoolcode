
public class Queue<E> {
	private Node<E> head;
	private Node<E> tail;

	public Queue(){
		
		// We want to initialize our Queue to be empty
		// (ie) set head and tail to be null
		head = null;
		tail = null;
	}
	
	public void enqueue(E newData) {

		// Create a new node whose data is newData and whose next node is null
		// Update head and tail
		// Hint: Think about what's different for the first node added to the Queue
		Node<E> newnode = new Node<>(newData, null);
		if (head == null){
			head = newnode;
			head.setNext(tail);
			tail = head;
		} else {
			tail.setNext(newnode);
			tail = newnode;
		}
	}
	
	public Node<E> dequeue(){
	
		// Return the head of the Queue
		// Update head
		// Hint: The order you implement the above 2 tasks matters, so use a temporary node
	 	//	     to hold important information
		// Hint: Return null on a empty Queue
		if(isEmpty())
			return null;
		Node<E> returnednode = head;
		head = returnednode.getNext();
		return returnednode;

	}
	
	public boolean isEmpty(){
	
		// Check if the Queue is empty
		return head == null;
		
	}
	
	public void printQueue(){

		// Loop through your queue and print each Node's data
		if(isEmpty())
			return;
		Node<E> printnode = head;
		while(printnode != null){
			System.out.println(printnode.getData());
			printnode = printnode.getNext();
		}
		
	}
}
