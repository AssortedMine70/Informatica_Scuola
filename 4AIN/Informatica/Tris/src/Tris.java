import java.awt.Dimension;
import java.awt.Image;
import java.awt.event.ActionListener;
import java.util.Random;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

//actionCommand
public class Tris {
	private JButton[] fields;
	private Boolean player;
	private int screenSize;
	
	private ImageIcon empty;
	private ImageIcon x;
	private ImageIcon o;
	
	public Tris() {
		player = new Random().nextBoolean();
		
		screenSize = 100*3;
		JFrame frame = new JFrame("Tris");
		frame.setSize(screenSize, screenSize);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.setLayout(null);
		
        empty = new ImageIcon(new ImageIcon("./resources/empty.png").getImage().getScaledInstance(screenSize/3, screenSize/3, Image.SCALE_SMOOTH));
        x = new ImageIcon(new ImageIcon("./resources/X.png").getImage().getScaledInstance(screenSize/3, screenSize/3, Image.SCALE_SMOOTH));
        o = new ImageIcon(new ImageIcon("./resources/O.png").getImage().getScaledInstance(screenSize/3, screenSize/3, Image.SCALE_SMOOTH));
        
        ActionListener al = e -> {
			int buttonIndex = Integer.parseInt(e.getActionCommand());
			if(fields[buttonIndex].getIcon() == empty) {
				fields[buttonIndex].setIcon(player ? x : o);
				Boolean winner;
				if((winner = check()) != null) {
					System.out.println(winner);
					frame.getContentPane().removeAll();
					frame.repaint();
					
					JLabel label = new JLabel((player ? "X" : "O") + " wins", JLabel.CENTER);
					label.setBounds(0, 0, screenSize, screenSize);
					frame.add(label);
				} else
					player = !player;
			}
		};
        
		fields = new JButton[9];
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j) {
				fields[i*3+j] = new JButton(empty);
				fields[i*3+j].setActionCommand("" + (i*3 + j));
				fields[i*3+j].setBounds(j*(screenSize/3), i*(screenSize/3), screenSize/3, screenSize/3);
				fields[i*3+j].addActionListener(al);
				frame.add(fields[i*3+j]);
			}
		
		frame.getContentPane().setPreferredSize(new Dimension(screenSize, screenSize));
        frame.pack();
		frame.setVisible(true);
	}
	
	private Boolean check() {
		// Rows & Columns
		for(int i = 0; i<fields.length; i+=3) {
			// Rows
			if((fields[i].getIcon() == o) && (fields[i+1].getIcon() == o) && (fields[i+2].getIcon() == o))
				return true;
			if((fields[i].getIcon() == x) && (fields[i+1].getIcon() == x) && (fields[i+2].getIcon() == x))
				return false;
			// Columns
			if((fields[i/3].getIcon() == o) && (fields[(i/3)+3].getIcon() == o) && (fields[(i/3)+6].getIcon() == o))
				return true;
			if((fields[i/3].getIcon() == x) && (fields[(i/3)+3].getIcon() == x) && (fields[(i/3)+6].getIcon() == x))
				return false;
		}
		// Diagonals
		if(((fields[4].getIcon() == o) && fields[0].getIcon() == o) && (fields[8].getIcon() == o))
			return true;
		if(((fields[4].getIcon() == x) && fields[0].getIcon() == x) && (fields[8].getIcon() == x))
			return false;
		if(((fields[4].getIcon() == o) && fields[2].getIcon() == o) && (fields[6].getIcon() == o))
			return true;
		if(((fields[4].getIcon() == x) && fields[2].getIcon() == x) && (fields[6].getIcon() == x))
			return false;
		
		return null;
	}
}
