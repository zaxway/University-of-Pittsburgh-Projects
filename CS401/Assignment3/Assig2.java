import java.util.Scanner;
import java.io.*;

public class Assig2 {
  public static void main (String [] args) throws IOException {
    Scanner console = new Scanner(System.in);
    Die b1 = new Die(6);
    Die b2 = new Die(6);
    System.out.println("Enter first name.");
    String fname = console.nextLine();
    System.out.println("Enter last name.");
    String lname = console.nextLine();
    Player a = new Player(fname, lname);
    a.setname1(fname);
    a.setname2(lname);
    System.out.println("How much money do you have?");
    double monkey = console.nextDouble();
    System.out.println("How much money do you want to bet?");
    double bet = console.nextDouble();
    while (bet > monkey || bet <= 0) {
      System.out.println("You do not have enough money to make that bet.");
      System.out.println("Bet again.");
      bet = console.nextDouble();
    }
    System.out.println("Want to play a round? Type yes or no.");
    String yesno = console.next();
    int numrounds = 0;
    int wintimes = 0;
    while (yesno.equals("yes")) {
      System.out.println("(U)nder seven, (O)ver seven, or (S)even");
      String uos = console.next();
      b1.diceroll();
      b2.diceroll();
      int z = b1.getnumber() + b2.getnumber();
      if (uos.equals("U") && z < 7) {
        System.out.println("The number was " + z);
        monkey = bet * 2 + monkey;
        System.out.println("Your amount of money is $" + monkey);
        wintimes++;
      }
      else if (uos.equals("O") && z > 7) {
        System.out.println("The number was " + z);
        monkey = bet * 2 + monkey;
        System.out.println("Your amount of money is $" + monkey);
        wintimes++;
      }
      else if (uos.equals("S") && z == 7) {
        System.out.println("The number was " + z);
        monkey = bet * 4 + monkey;
        System.out.println("Your amount of money is $" + monkey);
        wintimes++;
      }
      else {
        monkey = monkey - bet;
        System.out.println("Your amount of money is $" + monkey);
      }
      if (monkey < bet) {
        System.out.println("You ran out of money. Would you like to add more money? Type yes or no.");
        String yesno2 = console.next();
        if (yesno2.equals("yes")) {
          System.out.println("How much more would you like to add?");
          double moremoney = console.nextDouble();
          while (moremoney < bet) {
            System.out.println("Add more money.");
            moremoney = console.nextDouble();
          }
          monkey = moremoney + monkey;
          System.out.println("You now have $" + monkey);
        }
        else {
          System.out.println("Thank you for playing the game.");
          System.exit(0);
        }
      }
      numrounds++;
      System.out.println("Want to play again? Type yes or no.");
      yesno = console.next();
    }
    a.setmoney(monkey);
    a.setwtimes(wintimes);
    a.setrounds(numrounds);
    System.out.println("You played " + a.getrounds() + " rounds." );
    System.out.println("Out of those rounds, you won " + a.getwtimes() + " times.");
    boolean blah = createNewFile(a);
  }

  public static boolean createNewFile(Player a) throws IOException {
    PrintWriter outputFile = new PrintWriter(a.getname1() + ".txt");
    outputFile.println("First Name = " + a.getname1());
    outputFile.println("Last Name = " + a.getname2());
    outputFile.println("Money = $" + a.getmoney());
    outputFile.println("Number of rounds = " + a.getrounds());
    outputFile.println("Number of rounds won = " + a.getwtimes());
    outputFile.flush();
    outputFile.close();
    return true;
  }
}
