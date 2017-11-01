import javax.swing.*;
import java.awt.event.*;
import java.awt.*;

public class CastVote extends JPanel {
  private JButton voted;

  public CastVote() {
    // Creates the cast your vote button.
    setLayout(new GridLayout(1,1));
    voted = new JButton("Cast Your Vote");
    add(voted);
    // Now we need to decide what happens when this button is clicked therefore, we require
    // the use of the ActionListener interface.
    voted.addActionListener(new VoteButtonListener());
  }
}

class VoteButtonListener implements ActionListener {
  public void actionPerformed(ActionEvent e) {
    int dialogresult = JOptionPane.showConfirmDialog(null, "Confirm your vote?","Confirmation", JOptionPane.YES_NO_OPTION);
    if (dialogresult == 0) {
      JOptionPane.showMessageDialog(null, "You have voted.");
    }
  }
}
