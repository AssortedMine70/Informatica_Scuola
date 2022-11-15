import java.awt.Color;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class Frame {
	public Frame() {
		JFrame frame = new JFrame("foo");
		frame.setSize(800, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		
		JPanel panel = new JPanel();
		panel.setBounds(0, 0, 800, 600);
		panel.setBackground(Color.WHITE);
		panel.setFocusable(true);		
		
		panel.addKeyListener(new KeyAdapter() {
			@Override
			public void keyPressed(KeyEvent e) {
				switch(e.getKeyCode()) {
					case KeyEvent.VK_LEFT ->
						panel.setBackground(Color.WHITE);
					case KeyEvent.VK_RIGHT ->
						panel.setBackground(Color.GREEN);
					case KeyEvent.VK_UP ->
						panel.setBackground(Color.BLUE);
					case KeyEvent.VK_DOWN ->
						panel.setBackground(Color.RED);
				}
			}
		});
		
		frame.add(panel);
		
		frame.setVisible(true);
	}
}
