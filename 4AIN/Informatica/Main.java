import javax.swing.*;
import javax.swing.border.Border;
import java.awt.*;

public class Main {
    final String alphabet = "abcdefghijklmnopqrstuvwxyz0123456789 ";
    public Main() {
        JFrame frame = new JFrame("Crypt - Decrypt");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(800, 600);

        JFileChooser chooser = new JFileChooser();
        frame.add(chooser, BorderLayout.NORTH);
        JTextArea textArea = new JTextArea();
        frame.add(textArea, BorderLayout.CENTER);

        JPanel labelsPanel = new JPanel();
        labelsPanel.setLayout(new GridLayout(2, 1));
        JTextField[] keys = new JTextField[2];
        for (int i = 0; i < keys.length; i++) {
            keys[i] = new JTextField();
            labelsPanel.add(keys[i]);

        }
        labelsPanel.setPreferredSize(new Dimension(200, 100));
        frame.add(labelsPanel, BorderLayout.EAST);

        JPanel buttonsPanel = new JPanel(new GridLayout(1, 2));
        JButton crypt = new JButton("crypt");
        buttonsPanel.add(crypt, BorderLayout.SOUTH);
        JButton decrypt = new JButton("decrypt");
        buttonsPanel.add(decrypt, BorderLayout.SOUTH);
        frame.add(buttonsPanel, BorderLayout.SOUTH);

        crypt.addActionListener(e ->
            System.out.println(crypt(textArea.getText(), Integer.parseInt(keys[0].getText()), Integer.parseInt(keys[1].getText())))
        );

        decrypt.addActionListener(e ->
            System.out.println(decrypt(textArea.getText(), Integer.parseInt(keys[0].getText()), Integer.parseInt(keys[1].getText())))
        );

        frame.setVisible(true);
    }

    public static void main(String[] args) {
        new Main();
    }

    String crypt(String str, int m, int q) {
        byte[] bytes = str.getBytes();
        for (int i = 0; i < bytes.length; i++) {
            if(Character.isUpperCase(bytes[i]))
                bytes[i] = (byte) (65 + (m*(bytes[i] - 65) + q)%26);
            else
                bytes[i] = (byte) (97 + (m*(bytes[i] - 97) + q)%26);
        }
        return new String(bytes);
    }
// x = ((y - q) * 1/m)%26
    String decrypt(String str, int m, int q) {
        byte[] bytes = str.getBytes();
        for (int i = 0; i < bytes.length; i++) {
            if(Character.isUpperCase(bytes[i]))
                bytes[i] = (byte) (65 + ((bytes[i] - 65) - q /* * 1/m TODO*/)%26);
            else
                bytes[i] = (byte) (97 + ((bytes[i] - 97) - q /* * 1/m TODO*/)%26);
        }
        return new String(bytes);
    }
}