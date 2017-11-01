public class Die {
  private int numsides;
  private int number;

  public Die(int sides) {
    numsides = sides;
    diceroll();
  }

  public void diceroll() {
    number = (int) (Math.random() * 6) + 1;
  }

  public int getnumber() {
    return number;
  }

  public int getnumsides() {
    return numsides;
  }
}
