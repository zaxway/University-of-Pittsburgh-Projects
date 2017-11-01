import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Ballot extends JPanel {

  //Create 4 buttons
  private JButton oreo;
  private JButton chipsahoy;
  private JButton sunnyselect;
  private JButton mothers;

  // Constructor

  public Ballot(){
    // 4 rows and 1 column
    setLayout(new GridLayout(4,1));
    // Creates 4 JButtons
    oreo = new JButton("Oreo");
    chipsahoy = new JButton("Chips Ahoy");
    sunnyselect = new JButton("Sunny Select");
    mothers = new JButton("Mother's");
    // Sets a border around the panel and titles it.
    setBorder(BorderFactory.createTitledBorder("Favorite Cookies"));
    // add buttons to panel
    add(oreo);
    add(chipsahoy);
    add(sunnyselect);
    add(mothers);
    //Create the action listeners
    oreo.addActionListener(new ButtonListener());
    chipsahoy.addActionListener(new ButtonListener());
    sunnyselect.addActionListener(new ButtonListener());
    mothers.addActionListener(new ButtonListener());
  }
}
