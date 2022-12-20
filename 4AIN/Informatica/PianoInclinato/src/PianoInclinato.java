import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Graphics;
import java.awt.event.ActionListener;

import javax.swing.Timer;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JSlider;

@SuppressWarnings("serial")
public class PianoInclinato extends JPanel {
	private int xp, yp;
	private int height, width;
	private final static double M = 0.3;
	private final static int Q = 200;
	private final static double G = 9.81;
	private final static double MASS = 300;
	private final static double P = G * MASS;
	
	public PianoInclinato() {
		setBackground(Color.PINK);
		
		xp = 0;
		yp = f(0);
		
		int delay = 10; //milliseconds
		ActionListener taskPerformer = e -> {
			++xp;
			yp = f(xp);
			repaint();

			if(xp > getWidth() || yp > getHeight())
				((Timer)e.getSource()).stop();
		};
		new Timer(delay, taskPerformer).start();
	}
	
	
	private int f(int x) {
		return (int)(M*x - height);
	}
	
	@Override
	protected void paintComponent(Graphics g) {
		super.paintComponent(g);
		g.translate(0, getHeight());
		g.drawLine(0, f(0), width, f(width));
		g.drawOval(xp - 15, yp - 30, 30, 30);
	}

	public void setHeight(int height) {
		this.height = height;
	}
	
	public void setWidth(int width) {
		this.width = width;
	}

	public static void main(String[] args) {
		JFrame frame = new JFrame("Piano Inclinato");
		PianoInclinato plane = new PianoInclinato();
		plane.setPreferredSize(new Dimension(800, 400));
		frame.add(plane, BorderLayout.CENTER);
		
		JPanel panel = new JPanel();
		panel.setPreferredSize(new Dimension(800, 30));
		panel.setLayout(new FlowLayout());
		frame.add(panel, BorderLayout.SOUTH);
		
		frame.pack();
		
		JSlider height = new JSlider(0, plane.getHeight());
		height.addChangeListener(e -> {
			plane.setHeight(height.getValue());
			plane.repaint();
		});
		panel.add(height);
		
		JSlider width = new JSlider(0, plane.getWidth());
		System.out.println(plane.getWidth());
		width.addChangeListener(e -> {
			plane.setWidth(width.getValue());
			plane.repaint();
		});
		panel.add(width);
		
		frame.pack();
		frame.setVisible(true);
	}
}
