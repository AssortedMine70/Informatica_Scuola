import java.awt.Color;
import java.util.Random;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.JTextField;

/**
 * @author Federico Santucci
 */
public class Main {

	public static void main(String[] args) {
		JFrame frame = new JFrame("foo");
		frame.setSize(800, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		
		JTextField textField = new JTextField();
		textField.setBounds(270, 100, 150, 50);
		frame.add(textField);
		
		JTextArea textArea = new JTextArea();
		textArea.setBounds(100, 170, 320, 250);
		textArea.setLineWrap(true);
		textArea.setEditable(false);
		frame.add(textArea);
		
		JButton button = new JButton("add");
		button.setBounds(100, 100, 150, 50);
		button.addActionListener(e -> {
			if(textArea.getText() != null)
				textArea.append(" " + textField.getText() + "\n");
			else
				textArea.append(textField.getText() + "\n");
			textField.setText("");
			System.out.println("x: " + frame.getMousePosition().x + ", y: " + frame.getMousePosition().y);
			button.setBackground(new Color(new Random().nextFloat(), new Random().nextFloat(), new Random().nextFloat()));
		});
		frame.add(button);
		
		frame.setVisible(true);
	}
}