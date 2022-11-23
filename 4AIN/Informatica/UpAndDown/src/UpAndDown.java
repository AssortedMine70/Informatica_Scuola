import javax.swing.*;
import java.awt.*;
import java.util.Arrays;
import java.util.Random;

class Panel extends JPanel {
    private int[] heights;

    public Panel(int[] heights) {
        this.heights = heights;
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        int[] xArray = new int[heights.length];
        for (int i = 0; i < xArray.length; i++)
            xArray[i] = i*(getWidth()/(xArray.length-1));

        int[] yArray = new int[heights.length];
        for (int i = 0; i < yArray.length; i++)
            yArray[i] = getHeight()/2-heights[i];

        g.drawPolyline(xArray, yArray, heights.length);
    }
}

public class UpAndDown {
    private int[] heights;
    private int up;
    private int down;
    public UpAndDown(int n, int bound) {
        heights = new int[n];
        for (int i = 0; i < heights.length; ++i)
            heights[i] = new Random().nextInt(bound);

        for (int i = 0; i < heights.length-1; i++)
            if(heights[i] < heights[i+1])
                up += heights[i+1]-heights[i];
            else
                down += heights[i]-heights[i+1];

        JFrame frame = new JFrame("Up & Down");
        frame.setSize(800, 600);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);

        JPanel panel = new Panel(heights);
        panel.setBounds(0, 0, 600, 600);
        panel.setBackground(Color.WHITE);
        frame.add(panel);

        JLabel upLabel = new JLabel("Up = " + up);
        upLabel.setBounds(650, 100, 100, 50);
        frame.add(upLabel);

        JLabel downLabel = new JLabel("Down = " + down);
        downLabel.setBounds(650, 150, 100, 50);
        frame.add(downLabel);

        frame.setVisible(true);
    }

    @Override
    public String toString() {
        return getClass().getSimpleName() + "{" +
                "heights=" + Arrays.toString(heights) +
                ", up=" + up +
                ", down=" + down +
                '}';
    }
}
