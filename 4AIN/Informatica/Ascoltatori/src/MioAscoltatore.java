import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JTextArea;

/**
 * @author Federico Santucci
 */
public class MioAscoltatore implements ActionListener {
	private JTextArea textArea;
	
	public MioAscoltatore(JTextArea textArea) {
		this.textArea = textArea;
	}

	
	@Override
	public void actionPerformed(ActionEvent e) {
		textArea.append(e.getActionCommand() + "\n");
	}
	
}
