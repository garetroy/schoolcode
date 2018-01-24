
public class BST<E extends Comparable<E>> {
    private Node<E> root;

    public BST(){
        root = null;
    }

    public Node<E> getRoot(){
        return root;
    }

    private void   setRoot(Node<E> newroot) {root = newroot;}

    public void insert(E data) {

        // Find the right spot in the tree for the new node
        // Make sure to check if anything is in the tree
        // Hint: if a node n is null, calling n.getData() will cause an error

        if (root == null) {
            root = new Node<E>(data);
            return;
        }

        int comparisonResult = data.compareTo(root.getData());
        Node<E> nodepointer = root;

        while (true) {
            if (comparisonResult < 0) {
                if (nodepointer.getLeftChild() == null) {
                    Node<E> newnode = new Node<>(data);
                    newnode.setParent(nodepointer);
                    nodepointer.setLeftChild(newnode);
                    return;
                }
                nodepointer = nodepointer.getLeftChild();
                comparisonResult = data.compareTo(nodepointer.getData());
            } else if (comparisonResult > 0) {
                if (nodepointer.getRightChild() == null) {
                    Node<E> newnode = new Node<>(data);
                    newnode.setParent(nodepointer);
                    nodepointer.setRightChild(newnode);
                    return;
                }
                nodepointer = nodepointer.getRightChild();
                comparisonResult = data.compareTo(nodepointer.getData());
            } else {
                return;
            }
        }
    }

    public Node<E> find(E data){

        // Search the tree for a node whose data field is equal to data

        if(root == null){
            return null;
        }
        int  comparisonResult  = data.compareTo(root.getData());
        if (comparisonResult == 0) {
            return root;
        }

        Node<E> currentnode = root;
        Node<E> nextnode    = root;

        while(nextnode != null && data.compareTo(currentnode.getData()) != 0){
            currentnode = nextnode;
            if(data.compareTo(currentnode.getData()) < 0){
                nextnode = currentnode.getLeftChild();
            } else {
                nextnode = currentnode.getRightChild();
            }
        }
        return currentnode;
    }

    public void delete(E data) {
        // Find the right node to be deleted

        // If said node has no children, simply remove it by setting its parent to point to null instead of it.
        // If said node has one child, delete it by making its parent point to its child.
        // If said node has two children, then replace it with its successor,
        //          and remove the successor from its previous location in the tree.
        // The successor of a node is the left-most node in the node's right subtree.
        // If the value specified by delete does not exist in the tree, then the structure is left unchanged.

        // Hint: You may want to implement a findMin() method to find the successor when there are two children
        Node<E> foundnode = find(data);
        Node<E> newnode   = null;
        if (foundnode == null) {
            return;
        } else if (foundnode.getLeftChild() == null && foundnode.getRightChild() == null) {
            if(foundnode == root){
                root = null;
                return;
            }
            replaceParent(foundnode,null);
        } else if (foundnode.getLeftChild() != null && foundnode.getRightChild() == null) {
            if(foundnode == root){
                root = root.getLeftChild();
                return;
            }
            newnode   = foundnode.getLeftChild();
            replaceParent(foundnode,newnode);
        } else if (foundnode.getRightChild() != null && foundnode.getLeftChild() == null) {
            if(foundnode == root){
                root = root.getRightChild();
                return;
            }
            newnode   = foundnode.getRightChild();
            replaceParent(foundnode,newnode);
        } else {
            newnode                 = findsuccessor(foundnode);
            newnode.setLeftChild(foundnode.getLeftChild());
            newnode.setRightChild(foundnode.getRightChild());
            if(foundnode == root){
                replaceParent(newnode,null);
                root = newnode;
                return;
            }
            newnode.setParent(foundnode.getParent());
            replaceParent(foundnode,newnode);
        }
    }

    private void replaceParent(Node<E> inputnode, Node<E> swapvalue){
        Node<E> parentnode = inputnode.getParent();
        if(parentnode.getLeftChild() != null){
            if(parentnode.getLeftChild() == inputnode){
                parentnode.setLeftChild(swapvalue);
            }
        } else if(parentnode.getRightChild() != null){
            if(parentnode.getRightChild() == inputnode){
                parentnode.setRightChild(swapvalue);
            }
        }
    }

    private Node<E> findsuccessor(Node<E> inputnode){
        Node<E> leastnode = inputnode.getRightChild();
        while(leastnode.getLeftChild() != null){
            leastnode = leastnode.getLeftChild();
        }
        return leastnode;
    }

    public void traverse(String order, Node<E> top) {
        if (top != null){
            switch (order) {
                case "preorder":
                    System.out.print(top.getData() + " ");
                    traverse("preorder",top.getLeftChild());
                    traverse("preorder",top.getRightChild());
                    break;
                case "inorder":
                    traverse("inorder",top.getLeftChild());
                    System.out.print(top.getData() + " ");
                    traverse("inorder",top.getRightChild());
                    break;
                case "postorder":
                    traverse("postorder",top.getLeftChild());
                    traverse("postorder",top.getRightChild());
                    System.out.print(top.getData() + " ");
                    break;
            }
        }
    }
}
