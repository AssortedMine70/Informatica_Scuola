import java.awt.Color;
import java.awt.Graphics;
import java.awt.Polygon;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

class Panel extends JPanel {
	private static final long serialVersionUID = 1L;
	private Polygon triangle;
	
	public Panel(Polygon triangle) {
		this.triangle = triangle;
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.drawPolygon(triangle);
	}
}

public class Triangles {
	public Triangles() {
		Polygon triangle = new Polygon();
		JTextField[] fields = new JTextField[6];
		JLabel[] labels = new JLabel[6];
		
		JFrame frame = new JFrame("Triangles");
		frame.setSize(800, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		frame.setResizable(false);
		
		KeyAdapter k = new KeyAdapter() {
			@Override
			public void keyReleased(KeyEvent e) {
				triangle.reset();
				try {
					for (int i = 0; i < fields.length; i+=2)
						triangle.addPoint(Integer.parseInt(fields[i].getText()), Integer.parseInt(fields[i+1].getText()));
				} catch (Exception ex) {
					triangle.reset();
				}
				frame.repaint();
			}
		};
		
		for (int i = 0; i < fields.length; ++i) {
			fields[i] = new JTextField("0");
			fields[i].setBounds(i%2==0 ? 630 : 715, 50+(i-i%2)*30, 60, 20);
			fields[i].addKeyListener(k);
			frame.add(fields[i]);
			
			labels[i] = new JLabel((i%2==0 ? "x " : "y ") + i/2);
			labels[i].setBounds(i%2==0 ? 610 : 695, 50+(i-i%2)*30, 20, 20);
			frame.add(labels[i]);
		}
		
		JPanel panel = new Panel(triangle);
		panel.setBounds(0, 0, 600, 600);
		panel.setBackground(Color.WHITE);
		frame.add(panel);
		
		frame.setVisible(true);
	}
}
