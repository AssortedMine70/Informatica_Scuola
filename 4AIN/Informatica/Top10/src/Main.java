import java.awt.*;
import java.util.Random;
import javax.swing.*;

class Frame {

    public Frame() {
        JFrame frame = new JFrame("Random");
        JButton button = new JButton("Nuovo Numero");
        button.setPreferredSize(new Dimension(10, 30));
        JLabel label = new JLabel();
        label.setHorizontalAlignment(JLabel.CENTER);
        label.setPreferredSize(new Dimension(10, 30));
        button.addActionListener(e ->
            label.setText("" + (new Random()).nextInt(100))
        );
        frame.add(button, BorderLayout.NORTH);
        frame.add(label, BorderLayout.SOUTH);
        frame.pack();
        frame.setVisible(true);
    }
}

public class Main {

    public static void main(String[] args) {
        new Frame();
    }
}