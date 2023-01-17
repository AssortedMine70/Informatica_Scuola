import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

public class Game extends JPanel {
    private Rectangle player;
    private Rectangle[] tubes[];
    private ImageIcon[] playerImages;
    private Image tubesImage;

    private int frameRate;
    private double t;
    private double g = 9.81;
    private double v0y = 0;
    private int y0 = 300;
    public Game() {
        setFocusable(true);
        setBackground(Color.CYAN);

        player = new Rectangle(150, y0, 18*3, 12*3);
        playerImages = new ImageIcon[4];
        for (int i = 0; i < playerImages.length; ++i)
            playerImages[i] = new ImageIcon(new ImageIcon("assets/bird (" + i+1 +").png").getImage().getScaledInstance(player.width, player.height, Image.SCALE_SMOOTH));

        frameRate = 10;
        t = 0;
        Timer playerUpdater = new Timer(frameRate, e -> {
            player.y = (int) (-0.5 * g * t*t + v0y * t + y0);
            t+=1./frameRate;

            repaint();

            if(player.y < 0)
                ((Timer)e.getSource()).stop();
        });
        playerUpdater.start();

        this.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_SPACE) {
                    y0 = player.y;
                    t = 0;
                    v0y = 25;
                }
            }
        });
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        g.drawImage(playerImages[0].getImage(), player.x, getHeight() - player.y, null);
        g.drawRect(player.x, getHeight() - player.y, player.width, player.height);

        //ImageIcon temp = playerImages[0];
        //for (int i = 0; i < playerImages.length-1; i++)
        //    playerImages[i] = playerImages[i+1];
        //playerImages[playerImages.length-1] = temp;
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame("Flappy Bird");
        frame.setSize(800, 600);
        frame.add(new Game(), BorderLayout.CENTER);
        frame.setVisible(true);
    }
}
