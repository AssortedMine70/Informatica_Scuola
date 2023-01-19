import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.io.File;
import java.io.IOException;

public class Game extends JPanel {
    private Rectangle[] tubes[];
    private Image tubesImage;
    private Rectangle player;
    private Image[] playerImages;
    private int frameRate;
    private double t;
    private double g = 9.81;
    private double v0y = 0;
    private int y0 = 300;
    public Game() throws IOException {
        setFocusable(true);
        setBackground(Color.CYAN);

        player = new Rectangle(150, y0, 68, 48);
        playerImages = new Image[4];
        for (int i = 0; i < playerImages.length; ++i)
            playerImages[i] = ImageIO.read(new File("assets/bird" + i + ".png")).getScaledInstance(player.width, player.height, Image.SCALE_SMOOTH);

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
        g.drawImage(playerImages[0], player.x, getHeight() - player.y, null);
        //g.drawRect(player.x, getHeight() - player.y, player.width, player.height);

        Image temp = playerImages[0];
        for (int i = 0; i < playerImages.length-1; i++)
            playerImages[i] = playerImages[i+1];
        playerImages[playerImages.length-1] = temp;
    }

    public static void main(String[] args) throws IOException {
        JFrame frame = new JFrame("Flappy Bird");
        frame.setSize(800, 600);
        frame.add(new Game(), BorderLayout.CENTER);
        frame.setVisible(true);
    }
}
