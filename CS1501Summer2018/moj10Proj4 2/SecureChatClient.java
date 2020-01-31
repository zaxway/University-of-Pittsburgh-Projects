import java.util.*;
import java.io.*;
import java.net.*;
import javax.swing.*;
import java.awt.event.*;
import java.awt.*;
import java.math.*;

public class SecureChatClient extends JFrame implements Runnable, ActionListener {

    public static final int PORT = 8765;

    ObjectInputStream myReader;
    ObjectOutputStream myWriter;
    JTextArea outputArea;
    JLabel prompt;
    JTextField inputField;
    String myName, serverName, addORSub;
	  Socket connection;
    private byte[] encryptionForName;
    BigInteger E, N, key, encryptedKey;
    SymCipher cipher;

    public SecureChatClient ()
    {
        try {
        myName = JOptionPane.showInputDialog(this, "Enter your user name: ");
        serverName = JOptionPane.showInputDialog(this, "Enter the server name: ");
        InetAddress addr = InetAddress.getByName(serverName);
        //System.out.println("gets to address at least");
        connection = new Socket(addr, PORT);   // Connect to server with new
                                               // Socket
        //System.out.println("Establishes connection.");
        myReader = new ObjectInputStream(connection.getInputStream());   // Get Reader and Writer
        //System.out.println("Establishes reader");
        myWriter = new ObjectOutputStream(connection.getOutputStream());
        //System.out.println("Establishes writer");
        myWriter.flush(); // to avoid deadlocking

        //System.out.println("Gets through part 1");

        E = (BigInteger) myReader.readObject();
        N = (BigInteger) myReader.readObject();
        System.out.println("These are the keys: ");
        System.out.println("E = " + E);
        System.out.println("N = " + N);

        //System.out.println("Gets through part 2");

        addORSub = (String) myReader.readObject(); // gets the encryption type (Add128 or subs)
        System.out.println("This is the encryption type: " + addORSub);

        if (addORSub.equalsIgnoreCase("sub")) {
          cipher = new Substitute();
        }
        else if (addORSub.equalsIgnoreCase("add")) {
          cipher = new Add128();
        }
        else {
          System.out.println("ERROR, encryption type not found!!");
          System.exit(0);
        }

        // now cipher has methods encode(), decode(), and getKey()
        key = new BigInteger(1, cipher.getKey()); // first argument will make sure that key is positive
        encryptedKey = key.modPow(E, N); // RSA-encryption
        myWriter.writeObject(encryptedKey);
        myWriter.flush();

        encryptionForName = cipher.encode(myName);
        myWriter.writeObject(encryptionForName); // not sure if it can write a byte array, need to check.
        myWriter.flush();

        System.out.println("Completed Handshaking!");

        this.setTitle(myName);      // Set title to identify chatter

        Box b = Box.createHorizontalBox();  // Set up graphical environment for
        outputArea = new JTextArea(8, 30);  // user
        outputArea.setEditable(false);
        b.add(new JScrollPane(outputArea));

        outputArea.append("Welcome to the Chat Group, " + myName + "\n");

        inputField = new JTextField("");  // This is where user will type input
        inputField.addActionListener(this);

        prompt = new JLabel("Type your messages below:");
        Container c = getContentPane();

        c.add(b, BorderLayout.NORTH);
        c.add(prompt, BorderLayout.CENTER);
        c.add(inputField, BorderLayout.SOUTH);

        Thread outputThread = new Thread(this);  // Thread is to receive strings
        outputThread.start();                    // from Server

		addWindowListener(
                new WindowAdapter()
                {
                    public void windowClosing(WindowEvent e)
                    {
                      try {
                        String message = "CLIENT CLOSING";
                        byte [] closingMessage = cipher.encode(message);
                        myWriter.writeObject(closingMessage);
                        myWriter.flush();
                      }
                      catch (IOException ee) {
                        System.out.println("Problem with closing the client! ERROR!");
                        System.exit(0);
                      }
                    }
                }
            );

        setSize(500, 200);
        setVisible(true);

        }
        catch (Exception e)
        {
            System.out.println("Problem starting client!");
        }
    }

    public void run()
    {
        while (true)
        {
             try {
                byte [] encryptedMessage = (byte[]) myReader.readObject();
                String currentMessage = cipher.decode(encryptedMessage);
			          outputArea.append(currentMessage + "\n");
                byte[] bite = currentMessage.getBytes();
                System.out.println("Array of Bytes Recieved: " + Arrays.toString(encryptedMessage));
                System.out.println("Decrypted Array of Bytes: " + Arrays.toString(bite));
                System.out.println("Corresponding String: " + currentMessage);
             }
             catch (Exception e)
             {
                System.out.println(e +  ", closing client!");
                break;
             }
        }
        System.exit(0);
    }

    public void actionPerformed(ActionEvent e)
    {
        String currMsg = myName + ":" + e.getActionCommand();
        byte [] newMessage = cipher.encode(currMsg);
        byte [] bite = currMsg.getBytes();
        inputField.setText("");
        try {
          myWriter.writeObject(newMessage);
          myWriter.flush();
          System.out.println("Original String Message: " + currMsg);
          System.out.println("Corresponding Array of Bytes: " + Arrays.toString(bite));
          System.out.println("Encrypted Array of Bytes: " + Arrays.toString(newMessage));
        }
        catch (IOException ee) {
          System.out.println("Failed to send the message!!!");
        }
    }

    public static void main(String [] args)
    {
         SecureChatClient JR = new SecureChatClient();
         JR.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
    }
}
