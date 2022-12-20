import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;

class Panel extends JPanel implements ActionListener, KeyListener, MouseListener {
    private final int X_MAX = 100;
    private final int X_MIN = -X_MAX;
    private final int Y_MAX = 100;
    private final int Y_MIN = -Y_MAX;
    private final JButton in;
    private final JButton out;
    private Image image;
    private int y, circleX, circleY;

    public Panel() throws IOException {
        setFocusable(true);
        addMouseListener(this);
        addKeyListener(this);

        in = new JButton("Zoom In");
        in.setActionCommand("in");
        in.setBounds(300, 300, 50, 50);
        in.addActionListener(this);
        add(in);

        out = new JButton("Zoom Out");
        out.setActionCommand("out");
        out.setBounds(350, 300, 50, 50);
        out.addActionListener(this);
        add(out);

        image = ImageIO.read(new File("assets/frassino.jpg"));

        y = 0;

        circleX = -300;
        circleY = -300;
    }

    private double f(double x) {
        return 30*Math.sin(x);
    }

    // Xm = (Xf - Width/2) / [Width / (Xmax-Xmin)]
    private double fxToMx(int fx) {
        return (fx - getWidth()/2.) / (float)(getWidth() / X_MAX-X_MIN);
    }

    // Yf = -Ym*[Height/(Ymax-Ymin)]+ Height/2
    private int myToFy(double my) {
        return (int) my * (getHeight()/(Y_MAX-Y_MIN)) + getHeight()/2;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.drawImage(image,0, 0, null);

        g.drawOval(circleX, circleY, 70, 70);

        for (int fx = 0; fx < getWidth(); ++fx) {
            double mx = fxToMx(fx);
            double my = f(mx);
            int fy = myToFy(my);
            System.out.println(fx + " " + mx);
            System.out.println(fy + " " + my);
            g.drawLine(fx, y + fy, fx, y + fy);
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        switch (e.getActionCommand()) {
            case "in" ->
                    image = image.getScaledInstance(image.getWidth(null) + 20, image.getHeight(null) + 20, Image.SCALE_SMOOTH);
            case "out" ->
                    image = image.getScaledInstance(image.getWidth(null) - 20, image.getHeight(null) - 20, Image.SCALE_SMOOTH);
        }
        repaint();
    }

    @Override
    public void mouseClicked(MouseEvent e) {
        circleX = e.getX();
        circleY = e.getY();
        repaint();
    }

    @Override
    public void keyPressed(KeyEvent e) {
        switch (e.getKeyCode()) {
            case KeyEvent.VK_UP:
                if(y > 0)
                    --y;
                break;
            case KeyEvent.VK_DOWN:
                if(y < getHeight())
                    ++y;
                break;
        }
        repaint();
    }

    @Override
    public void keyTyped(KeyEvent e) {

    }

    @Override
    public void keyReleased(KeyEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}

public class ImageFrame {
    public ImageFrame() throws IOException {
        JFrame frame = new JFrame("foo");
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.add(new Panel());
        frame.setVisible(true);

        JOptionPane.showMessageDialog(frame, "Freccia-Giù/Su, Click del Pulsante, Bottone");
    }
}
