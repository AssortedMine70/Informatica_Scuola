import java.awt.Dimension;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;

//actionCommand
public class Tris {
	JButton[] fields;
	Boolean player;
	int screenSize;
	
	
	
	public Tris() {
		player = true;
		
		screenSize = 100*3;
		JFrame frame = new JFrame("Tris");
		frame.setSize(screenSize, screenSize);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		
        ImageIcon empty = new ImageIcon(new ImageIcon("./resources/empty.png").getImage().getScaledInstance(screenSize/3, screenSize/3, Image.SCALE_SMOOTH));
        ImageIcon x = new ImageIcon(new ImageIcon("./resources/X.png").getImage().getScaledInstance(screenSize/3, screenSize/3, Image.SCALE_SMOOTH));
        ImageIcon o = new ImageIcon(new ImageIcon("./resources/OVerde.png").getImage().getScaledInstance(screenSize/3, screenSize/3, Image.SCALE_SMOOTH));

		fields = new JButton[9];
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j) {
				fields[i*3+j] = new JButton(empty);
				fields[i*3+j].setActionCommand("" + (i*3 + j));
				fields[i*3+j].setBounds(j*(screenSize/3), i*(screenSize/3), screenSize/3, screenSize/3);
				fields[i*3+j].addActionListener(e -> {
					int buttonIndex = Integer.parseInt(e.getActionCommand());
					System.out.println(buttonIndex);
					if(fields[buttonIndex].getIcon() == empty) {
						fields[buttonIndex].setIcon(player ? x : o);
						player = !player;
					}
				});
				frame.add(fields[i*3+j]);
			}
		
		frame.getContentPane().setPreferredSize(new Dimension(screenSize, screenSize));
        frame.pack();
		frame.setVisible(true);
		}
}
