import javax.swing.*;
import java.awt.*;
import java.util.Random;

class Panel extends JPanel {
    private int x0 = 0, y0 = 150;
    private int x, y;
    private static final int v0 = 90;
    private static final double g = 9.81;
    private static final double alpha = Math.toRadians(45);
    private static final double v0x = v0 * Math.cos(alpha), v0y = v0 * Math.sin(alpha);
    private int t = 0;
    public Panel() {
        setBackground(new Color(new Random().nextInt(256), new Random().nextInt(256), new Random().nextInt(256)));

        Timer timer = new Timer(60, e -> {
            x = (int) (v0x * t + x0);
            y = (int) (-0.5 * g * t*t + v0y * t + y0);
            y = (int) (50 * Math.sin(5 * t) + y0);
            ++t;

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