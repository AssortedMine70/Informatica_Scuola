import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JTextArea;

/**
 * @author Federico Santucci
 */
public class Main implements ActionListener {
	private JTextArea textArea;
	
	public static void main(String[] args) {
		Main m = new Main();
		m.realMain();
	}
	
	public Main() {
		JTextArea textArea = new JTextArea();
		textArea.setEditable(false);
		textArea.setBounds(250, 50, 500, 450);
		this.textArea = textArea;
	}
	
	public void realMain() {
		JFrame frame = new JFrame("Ascoltatori");
		frame.setSize(800, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setLayout(null);
		frame.add(textArea);
		
		// Punto 1
		JButton P1 = new JButton("P1");
		P1.setBounds(50, 50, 50, 50);
		frame.add(P1);
		JButton P2 = new JButton("P2");
		P2.setBounds(150, 50, 50, 50);
		frame.add(P2);
		
		P1.addActionListener(e -> {
			textArea.append("P1\n");
		});
		P2.addActionListener(e -> {
			textArea.append("P2\n");
		});
		
		// Punto 2
		JButton P3 = new JButton("P3");
		P3.setBounds(50, 150, 50, 50);
		frame.add(P3);
		JButton P4 = new JButton("P4");
		P4.setBounds(150, 150, 50, 50);
		frame.add(P4);
		
		P3.setActionCommand("P3");
		P4.setActionCommand("P4");
		P3.addActionListener(new MioAscoltatore(textArea));
		P4.addActionListener(new MioAscoltatore(textArea));
		
		// Punto 3
		JButton P5 = new JButton("P5");
		P5.setBounds(50, 250, 50, 50);
		frame.add(P5);
		JButton P6 = new JButton("P6");
		P6.setBounds(150, 250, 50, 50);
		frame.add(P6);
		
		P5.addActionListener(this);
		P6.addActionListener(this);

		frame.setVisible(true);
	}
	
	@Override
	public void actionPerformed(ActionEvent e) {
		JButton c = (JButton)e.getSource();
		textArea.append(c.getText() + "\n");
	}

}
