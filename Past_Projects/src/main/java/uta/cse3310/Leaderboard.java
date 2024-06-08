//Kaitlin Martin
//Group 6

package uta.cse3310;
import java.util.Vector;
import java.util.Collections;
import java.util.Comparator;

public class Leaderboard {
    //private Vector<Player> GamesWonPlace = new Vector<>();
    private Vector<Player> PointsEarnedPlace = new Vector<>();

    public Leaderboard (Vector<Player> PointsEarnedPlace) {
        this.PointsEarnedPlace = PointsEarnedPlace;
    }

    public void sortPlayer() {
        Collections.sort(PointsEarnedPlace, new Comparator<Player>() {
        @Override
        public int compare(Player first, Player sec) {
            return Integer.compare(first.getPoints(), sec.getPoints());
         }
      });
    }

    /*public Vector<Player> getGamesWon() {
        return GamesWonPlace;
    }*/

    public Vector<Player> getPointsEarned() {
        return PointsEarnedPlace;
    }
    
    public void setGamesWon(Player p) {
       //GamesWonPlace.add(p);    
    }
    
    public void setPointsEarned(Player p) {
       PointsEarnedPlace.add(p);
    }

    public int calWinner() {    
        return PointsEarnedPlace.get(0).getPoints();
    }
}
