import java.awt.Dimension;

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
		
		screenSize = 300;
		JFrame frame = new JFrame("Tris");
		frame.setSize(screenSize, screenSize);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		
		ImageIcon empty = new ImageIcon("./resources/empty.png");
		ImageIcon x = new ImageIcon("./resources/X.png");
		ImageIcon o = new ImageIcon("./resources/O.png");
		
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
						System.out.println("yay");
					}
				});
				frame.add(fields[i*3+j]);
			}
		
		frame.getContentPane().setPreferredSize(new Dimension(screenSize, screenSize));
        frame.pack();
		frame.setVisible(true);
		}
}
