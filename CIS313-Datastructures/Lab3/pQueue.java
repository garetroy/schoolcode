public class pQueue<E extends Comparable> {
    private MaxHeap myHeap;

    public pQueue (int s) {
        myHeap = new MaxHeap<E>(s);
    }

    public void insert(E data){
        myHeap.insert(data);
    }

    public Comparable<E> maximum(){
        return myHeap.maximum();
    }

    public Comparable<E> extractMax(){
        return myHeap.extractMax();
    }

    public boolean isEmpty(){
        boolean isempty = true;
        for (Comparable element : myHeap.getArray()){
            if(element != null){
                isempty = false;
            }
        }
        return isempty;
    }

	public void build(E[] arr){
        myHeap.buildHeap(arr);
    }
    
    public void print(){
        // print out ”Current Queue: ”
        System.out.print("Current Queue: ");
        Comparable[] myarray = myHeap.getArray();
        int          length  = myHeap.getLength();
        for (int i = 1; i <= length; i++){
            System.out.printf("%s", myarray[i]);
            if(i != length){
                System.out.print(", ");
            }
        }
    }
}