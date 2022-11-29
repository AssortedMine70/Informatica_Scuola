import javax.swing.*;
import java.awt.*;
// Xf = W/(Xmax-Xmin) x Xm + W/2
// Yf = -Ym[H/(Ymax-Ymin)] + H/2
class Panel extends JPanel {
    private final int XOffset; private final int YOffset;
    private final int DentsGap; private final int DentsSize;
    private final int ArrowSize;
    public Panel(int XOffset, int YOffset, int DentsGap, int DentsSize, int ArrowSize) {
        this.XOffset = XOffset;
        this.YOffset = YOffset;
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
        g.drawLine(getWidth()/2 + XOffset, YOffset, getWidth()/2 + XOffset, getHeight() + YOffset);
        g.drawLine(XOffset, getHeight()/2 + YOffset, getWidth() + XOffset, getHeight()/2 + YOffset);
    }

    private void drawArrows(Graphics g) {
        g.fillPolygon(new int[] {getWidth(), getWidth()-ArrowSize, getWidth()-ArrowSize}, new int[] {getHeight()/2, getHeight()/2 + ArrowSize, getHeight()/2 - ArrowSize}, 3);
        g.fillPolygon(new int[] {getWidth()/2, getWidth()/2+ArrowSize, getWidth()/2-ArrowSize}, new int[] {0, ArrowSize, ArrowSize}, 3);
    }

    private void drawDents(Graphics g) {
        for (int i = 0; i < getWidth(); i+= DentsGap) {
            if(i < getWidth()-ArrowSize)
                g.drawLine(i + XOffset, getHeight() / 2 - DentsSize + YOffset, i  + XOffset, getHeight() / 2 + DentsSize + YOffset);
            if(i > ArrowSize)
            g.drawLine(getWidth() / 2 - DentsSize + XOffset, i  + YOffset, getWidth() / 2 + DentsSize + XOffset, i  + YOffset);
        }
    }
}
public class CartesianPlane {

    public CartesianPlane() {
        JFrame frame = new JFrame();
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JPanel panel = new Panel(0, 0, 5, 1, 5);
        panel.setBackground(Color.WHITE);
        frame.add(panel);

        frame.setVisible(true);
    }
}
