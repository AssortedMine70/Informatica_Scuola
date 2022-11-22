import javax.swing.*;
import java.awt.event.*;

public class Ripasso {
    public Ripasso() {
        JFrame frame = new JFrame("foo");
        frame.setSize(335, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(null);

        JLabel label = new JLabel("Federico Santucci, 2022");
        label.setBounds(0, 430, 330, 15);
        label.setHorizontalAlignment(JLabel.CENTER);
        frame.add(label);

        JTextField textField = new JTextField();
        textField.setBounds(10, 40, 300, 40);
        frame.add(textField);

        JTextArea textArea = new JTextArea();
        textArea.setBounds(10, 80, 300, 300);
        textArea.setLineWrap(true);
        textArea.setEditable(false);
        frame.add(textArea);

        JButton add = new JButton();
        add.setBounds(10, 10, 150, 30);
        add.setActionCommand("Aggiungi");
        add.setText(add.getActionCommand());
        frame.add(add);

        JButton remove = new JButton();
        remove.setBounds(160, 10, 150, 30);
        remove.setActionCommand("Svuota");
        remove.setText(remove.getActionCommand());
        remove.setEnabled(false);
        frame.add(remove);

        JComboBox<String> comboBox = new JComboBox<>();
        comboBox.addItem("Ciao 1");
        comboBox.addItem("Ciao 2");
        comboBox.addItem("Ciao 3");
        comboBox.setBounds(10, 380, 150, 30);
        frame.add(comboBox);

        JTextField field = new JTextField("" + comboBox.getSelectedItem());
        field.setEditable(false);
        field.setBounds(160, 380, 150, 30);
        frame.add(field);

        comboBox.addActionListener(e -> field.setText("" + comboBox.getSelectedItem()));

        add.addActionListener(e -> {
            System.out.println(e.getActionCommand());
            textArea.append(textField.getText());
            textField.setText("");
            remove.setEnabled(true);
        });

        remove.addActionListener(e -> {
            System.out.println(e.getActionCommand());
            textArea.setText("");
            remove.setEnabled(false);
        });

        textField.addKeyListener(new KeyAdapter() {
            @Override
            public void keyPressed(KeyEvent e) {
                if(e.getKeyCode() == KeyEvent.VK_ENTER) {
                    System.out.println(e.getKeyChar());
                    textArea.append(textField.getText());
                    textField.setText("");
                    remove.setEnabled(true);
                }
            }
        });

        textArea.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
                System.out.println("X: " + e.getX() + ", Y: " + e.getY());
                System.out.println("X: " + e.getXOnScreen() + ", Y: " + e.getYOnScreen());
            }
        });

        frame.setVisible(true);
    }
}
