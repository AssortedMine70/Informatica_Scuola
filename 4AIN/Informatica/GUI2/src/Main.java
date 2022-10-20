import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;

import javax.swing.JFrame;
import javax.swing.JTextArea;

public class Main {

	public static void main(String[] args) {
		JFrame frame = new JFrame("foo");
		frame.setSize(800, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		
		JTextArea textArea = new JTextArea();
		textArea.setBounds(100, 170, 320, 250);
		textArea.setLineWrap(true);
		textArea.setEditable(false);
		frame.add(textArea);
		
		frame.addMouseListener(new MouseListener() {
			@Override
			public void mousePressed(MouseEvent e) {
				textArea.append("x: " + frame.getMousePosition().x + ", y: " + frame.getMousePosition().y + "\n");
			}

			@Override
			public void mouseClicked(MouseEvent e) {}

			@Override
			public void mouseReleased(MouseEvent e) {}

			@Override
			public void mouseEntered(MouseEvent e) {}

			@Override
			public void mouseExited(MouseEvent e) {}
		});
		
		frame.setVisible(true);
	}

}
