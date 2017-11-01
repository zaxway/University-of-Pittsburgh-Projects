public class game {
  public static void main (String [] args) {
    // A dragon has 120 hit points. The goal of this game is to strategically
    // defeat as many dragons as possible within a set number of player lives.
    // Dragons have three moves. 1st is basic attack. 2nd is fireball. 3rd is flail.
    // basic attack does a constant amount of damage --> has the greatest probability of happening. 50%
    // fireball and flail have equal chances of occuring --> each 25%.
    // fireball is the same as a players magic attack.
    // flail causes dragon to cause no damage.
    Dragon a = new Dragon();
    // A player has 100 hit points.
    // Player can use a basic attack, magic attack, or a heal.
    // basic attack does a constant amount of damage.
    // magic attack has a range that could be much greater or much less than the basic attack
    // a heal will restore the player by 20 hit points.
    Player b = new Player();
  }
}
