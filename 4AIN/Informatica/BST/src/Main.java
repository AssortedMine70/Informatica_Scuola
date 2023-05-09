class BST{
    Node head;
    static class Node{
        int data;
        Node L, R;
        public Node(int data) {
            this.data = data;
            L = null;
            R = null;
        }

        @Override
        public String toString() {
            return "" + data;
        }
    }

    public BST(Node root) {
        this.head = root;
    }
    private void toStringRec(Node node, String side, StringBuilder str, int lv) {
        if(node == null)
            return;

        for(int i = 0; i < (lv - 1)*2; ++i)
            str.append(" ");
        if(lv != 0)
            str.append("└─");
        str.append(side + node.data + "\n");

        toStringRec(node.L, "L: ", str, lv+1);
        toStringRec(node.R, "R: ", str, lv+1);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        toStringRec(head, "", str, 0);
        return str.toString();
    }
    private Node minRec(Node n){
        if(n.L ==null)
            return n;
        return minRec(n.L);
    }
    public Node min(){
        return minRec(head);
    }
    private Node maxRec(Node n){
        if(n.R ==null)
            return n;
        return maxRec(n.R);
    }
    public Node max(){
        return maxRec(head);
    }
    private int sumRec(Node n){
        if(n==null)
            return 0;
        return sumRec(n.L) + sumRec(n.R)+ n.data;
    }
    public int sum() {
        return sumRec(head);
    }
    public Node minIt() {
        Node n = head;
        while(n.L != null)
            n = n.L;
        return n;
    }
    public Node maxIt() {
        Node n = head;
        while(n.R != null)
            n = n.R;
        return n;
    }
    private int heightRec(Node n) {
        if(n == null)
            return 0;
        return Integer.max(heightRec(n.L), heightRec(n.R)) + 1;
    }
    public int height() {
        return heightRec(head);
    }
    private int nodeCountRec(Node n) {
        if(n == null)
            return 0;
        return nodeCountRec(n.L) + nodeCountRec(n.R) + 1;
    }
    public int nodeCount() {
        return nodeCountRec(head);
    }
    private boolean isBinarySearchRec(Node n) {
        if(n == null)
            return true;
        if(n.L != null && n.L.data > n.data)
            return false;
        if(n.R != null && n.R.data < n.data)
            return false;
        return isBinarySearchRec(n.L) && isBinarySearchRec(n.R);
    }
    public boolean isBinarySearch() {
        return isBinarySearchRec(head);
    }
    private int countKeyRec(Node n, int k){
        if(n==null)
            return 0;
        return countKeyRec(n.L, k) + countKeyRec(n.R, k) + (n.data <= k ? 1 : 0);
    }
    public int countKey(int k) {
        return countKeyRec(head, k);
    }
}
public class Main {
    public static void main(String[] args) {
        BST.Node n1 = new BST.Node(1);
        BST.Node n2 = new BST.Node(2);
        BST.Node n3 = new BST.Node(3);
        BST.Node n4 = new BST.Node(4);
        BST.Node n5 = new BST.Node(5);

        n4.L = n2;
        n4.R = n5;
        n2.R = n3;
        n2.L = n1;
        BST tree = new BST(n4);
        System.out.println(tree);
        System.out.println("E' Binario di Ricerca?  " + (tree.isBinarySearch() ? "Sì" : "No"));
        System.out.println("Minimo:                 " + tree.min() + " (" + tree.minIt() + ")");
        System.out.println("Massimo:                " + tree.max() + " (" + tree.maxIt() + ")");
        System.out.println("Somma:                  " + tree.sum());
        System.out.println("Altezza:                " + tree.height());
        System.out.println("Numero di Nodi:         " + tree.nodeCount());
        System.out.println("Nodi con n <= 3:        " + tree.countKey(3));
        // aggiungi dal 5 in poi
    }
}