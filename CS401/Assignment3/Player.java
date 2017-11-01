import java.util.Scanner;

public class Player {
  private String name1;
  private String name2;
  private double money;
  private int rounds;
  private int wtimes;

  public Player(String fname, String lname) {
    name1 = fname;
    name2 = lname;
  }

  public void setname1(String fname) {
    name1 = fname;
  }

  public String getname1() {
    return name1;
  }

  public void setname2(String lname) {
    name2 = lname;
  }

  public String getname2() {
    return name2;
  }

  public void setmoney(double monkey) {
    money = monkey;

  }

  public double getmoney() {
    return money;
  }

  public void setrounds(int numrounds) {
    rounds = numrounds;
  }

  public int getrounds() {
    return rounds;
  }

  public void setwtimes(int wintimes) {
    wtimes = wintimes;
  }

  public int getwtimes() {
    return wtimes;
  }

}
