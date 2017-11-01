import java.awt.*;
import javax.swing.*;

public class Ballot2 extends JPanel {
  //Create 4 buttons
  private JButton yolo;
  private JButton lol;
  private JButton idk;
  private JButton ikr;

  //Constructor

  public Ballot2() {
    // 4 rows and 1 column
    setLayout(new GridLayout(4,1));
    // Creates 4 JButtons
    yolo = new JButton("YOLO");
    lol = new JButton("LOL");
    idk = new JButton("IDK");
    ikr = new JButton("IKR");
    // Creates the Action Listeners.
    yolo.addActionListener(new ButtonListener());
    lol.addActionListener(new ButtonListener());
    idk.addActionListener(new ButtonListener());
    ikr.addActionListener(new ButtonListener());
    // Sets a border around the panel and titles it.
    setBorder(BorderFactory.createTitledBorder("Most Used Texting Acronym"));
    // add buttons to panel
    add(yolo);
    add(lol);
    add(idk);
    add(ikr);
  }
}
