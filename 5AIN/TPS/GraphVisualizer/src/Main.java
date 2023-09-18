import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

class LabelsBuilder {
    static List getLabels() {
        ArrayList<String> labels = new ArrayList<String>();
        for (int i = 'A'; i < 'Z'; ++i)
            labels.add(Character.toString(i));
        return labels;
    }
}

class NodoGrafico {
    private static final List<String> labels = LabelsBuilder.getLabels();
    private final Point position;
    private final String label;
    private final Color color;

    public NodoGrafico(int x, int y, Color color) {
        position = new Point();
        position.x = x;
        position.y = y;
        this.color = color;

        //TODO gestisci fine labels
        this.label = labels.remove(0);
    }

    public int getX() {
        return position.x;
    }

    public int getY() {
        return position.y;
    }

    public Color getColor() {
        return color;
    }

    public String getLabel() {
        return label;
    }
}

class GraphPanel extends JPanel {
    private final List<NodoGrafico> nodes = new ArrayList<>();
    private final int diameter = 50;
    private NodoGrafico lastSelectedNode = null;
    private Point draggingPosition = null;

    public GraphPanel() {
        addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                super.mouseClicked(e);
                if(getClickedNode(e.getPoint()) == null) {
                    addNode(e.getX(), e.getY(), new Color(new Random().nextInt(256), new Random().nextInt(256), new Random().nextInt(256)));
                    repaint();
                }
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                super.mouseReleased(e);
                lastSelectedNode = null;
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                super.mouseDragged(e);

                NodoGrafico clickedNode = getClickedNode(e.getPoint());
                if(clickedNode != null) {
                    lastSelectedNode = clickedNode;
                }
                draggingPosition = e.getPoint();
            }
        });
    }

    private NodoGrafico getClickedNode(Point point) {
        for (NodoGrafico node : nodes) {
            Rectangle nodeBounds = new Rectangle(node.getX() - diameter/2, node.getY() - diameter/2, diameter, diameter);
            if(nodeBounds.contains(point)) {
                System.out.println("sei dentro un nodo");
                return node;
            }
        }
        return null;
    }

    private void addNode(int x, int y, Color color) {
        NodoGrafico node = new NodoGrafico(x, y, color);
        nodes.add(node);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        for (NodoGrafico node : nodes) {
            g.setColor(node.getColor());
            g.fillOval(node.getX() - diameter/2, node.getY() - diameter/2, diameter, diameter);
        }

        if(lastSelectedNode != null)
            // TODO SYSO
            g.drawLine(lastSelectedNode.getX(), lastSelectedNode.getY(), (int) draggingPosition.getX(), (int) draggingPosition.getY());
    }
}

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Graph Visualizer");
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        GraphPanel panel = new GraphPanel();
        frame.add(panel);

        frame.setVisible(true);
    }
}