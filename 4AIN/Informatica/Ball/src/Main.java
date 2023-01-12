import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.MouseMotionListener;
import java.util.Random;

class Panel extends JPanel {
    private final int x0 = 0, y0 = 150;
    private int x, y;
    private static final int v0 = 90;
    private static final double g = 9.81;
    private static final double alpha = Math.toRadians(60);
    private static final double v0x = v0 * Math.cos(alpha), v0y = v0 * Math.sin(alpha);
    private double t = 0;
    private int frameRate = 10;
    private Polygon tail;
    public Panel() {
        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                e.getPoint();
            }
        });

        setBackground(new Color(new Random().nextInt(256), new Random().nextInt(256), new Random().nextInt(256)));
        tail = new Polygon();

        Timer timer = new Timer(frameRate, e -> {
            x = (int) (v0x * t + x0);
            y = (int) (-0.5 * g * t*t + v0y * t + y0);
            //y = (int) (50 * Math.sin(1.2 * t) + y0);
            t+=1./frameRate;

            System.out.println(x + " " + y);

            repaint();
            if(x > getWidth() || y > getHeight() || x < 0 || y < 0)
                ((Timer)e.getSource()).stop();
        });

        timer.start();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.GREEN);
        tail.addPoint(x + 10, getHeight() - y + 10);
        g.drawPolyline(tail.xpoints, tail.ypoints, tail.npoints);
        g.setColor(Color.RED);
        g.fillOval(x, getHeight() - y, 20, 20);
    }
}

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("foo");
        frame.setSize(800, 600);
        frame.add(new Panel(), BorderLayout.CENTER);
        frame.setVisible(true);
    }
}