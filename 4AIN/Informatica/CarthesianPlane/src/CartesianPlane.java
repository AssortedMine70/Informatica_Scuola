import javax.swing.*;
import java.awt.*;
// Xf = W/(Xmax-Xmin) x Xm + W/21
// Yf = -Ym[H/(Ymax-Ymin)] + H/2
class Panel extends JPanel {
    private final int DentsGap; private final int DentsSize;
    private final int ArrowSize;
    public Panel(int DentsGap, int DentsSize, int ArrowSize) {
        this.DentsGap = DentsGap;
        this.DentsSize = DentsSize;
        this.ArrowSize = ArrowSize;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        drawAxis(g); drawArrows(g); drawDents(g);
    }

    private void drawAxis(Graphics g) {
        g.drawLine(getWidth()/2, 0, getWidth()/2, getHeight());
        g.drawLine(0, getHeight()/2, getWidth(), getHeight()/2);
    }

    private void drawArrows(Graphics g) {
        g.fillPolygon(new int[] {getWidth(), getWidth() - ArrowSize, getWidth() - ArrowSize}, new int[] {getHeight() / 2, getHeight() / 2 + ArrowSize, getHeight() / 2 - ArrowSize}, 3);
        g.fillPolygon(new int[] {getWidth() / 2, getWidth() / 2 + ArrowSize, getWidth() / 2 - ArrowSize}, new int[] {0, ArrowSize, ArrowSize}, 3);
    }

    private void drawDents(Graphics g) {
        for (int i = 0; i < Math.max(getWidth(), getHeight()); i+= DentsGap) {
            if(i < getWidth()-ArrowSize)
                g.drawLine(i, getHeight() / 2 - DentsSize, i, getHeight() / 2 + DentsSize);
            if(i > ArrowSize)
                g.drawLine(getWidth() / 2 - DentsSize, i, getWidth() / 2 + DentsSize, i);
        }
    }
}
public class CartesianPlane {

    public CartesianPlane() {
        JFrame frame = new JFrame();
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new Panel(5, 1, 5);
        //panel.setDomainRange(xmin, xmax);
        //panel.setImagesRange(ymin, ymax);
        //panel.setFunction(Poly);
        panel.setBackground(Color.WHITE);
        frame.add(panel);

        frame.setVisible(true);
    }
}
