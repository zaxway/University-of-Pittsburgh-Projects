public class Dragon {
  private int hp;
  private int [] randomselection;
  private int attack;
  private int fire;

  public Dragon() {

  }

  public void hitpoints() {
    hp = 120;
  }

  public int gethitpoints() {
    return hp;
  }

  public void basicattack() {
    attack = 15;
    hp = hp - attack;
  }

  public void fireball() {
    fire = (int) (Math.random() * 30) + 1;
    hp = hp - fire;
  }

  public void flail() {
    System.out.println("The dragon flailed around.");
  }

}
