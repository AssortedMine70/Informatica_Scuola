import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.IOException;

class Panel extends JPanel implements ActionListener, KeyListener, MouseListener {
    JButton in, out;
    Image image;
    int y, circleX, circleY;

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

    private int f(int i) {
        return (int) Math.sin((double) i);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        g.drawImage(image,0, 0, null);

        g.drawOval(circleX, circleY, 70, 70);

        for (int i = 0; i < getWidth(); ++i)
            g.drawLine(i, y + f(i), i, y + f(i));
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        switch (e.getActionCommand()) {
            case "in":
                image = image.getScaledInstance(image.getWidth(null) + 20, image.getHeight(null) + 20, Image.SCALE_SMOOTH);
                break;
            case "out":
                image = image.getScaledInstance(image.getWidth(null) - 20, image.getHeight(null) - 20, Image.SCALE_SMOOTH);
                break;
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
