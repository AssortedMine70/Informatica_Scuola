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

    private Node root;

    public BinaryTree(Node root) {
        this.root = root;
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
        toStringRec(root, "", str, 0);
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