class BinaryTree {
    static class Node {
        int data;
        Node L, R;

        public Node(int data) {
            this.data = data;
            L = null;
            R = null;
        }

        public void linkLeft(Node n) {
            L = n;
        }

        public void linkRight(Node n) {
            R = n;
        }
    }

    Node root;

    public BinaryTree(Node root) {
        this.root = root;
    }

    public void toStringRec(Node node, StringBuilder str) {
        if(node == null)
            return;

        str.append(node.data + " ");

        toStringRec(node.L, str);
        toStringRec(node.R, str);
    }

    @Override
    public String toString() {
        StringBuilder str = new StringBuilder();
        toStringRec(root, str);
        return str.toString();
    }
}

public class Main {
    public static void main(String[] args) {
        BinaryTree.Node root = new BinaryTree.Node(12);

        BinaryTree.Node L = new BinaryTree.Node(5);
        root.linkLeft(L);
        BinaryTree.Node LL = new BinaryTree.Node(8);
        L.linkLeft(LL);

        BinaryTree.Node R = new BinaryTree.Node(12);
        root.linkRight(R);
        BinaryTree.Node LR = new BinaryTree.Node(7);
        R.linkLeft(LR);
        BinaryTree.Node RR = new BinaryTree.Node(3);
        R.linkRight(RR);

        BinaryTree t = new BinaryTree(root);
        System.out.println(t);
    }
}