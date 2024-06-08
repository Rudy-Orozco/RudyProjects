package uta.cse3310;
import java.util.*;

public class GameLobby 
{
    // private int gameNum = 0;        // Number of players needed for game to start
    //private int playersInGame = 0;  // Number of players currently in a game
    private int gtWanted = 0;       // Game type the player is seeking
    private Game G = null;          // Game that will be returned 

    public GameLobby() {}

    // MATCHMAKING REDONE - Now only makes a new game when ther is enough players that want to play it
    // instead of making a new game whenever a player requests a game type that has not already been requested
    public Game matchMaking(Vector<Player> PlayerList, Vector<Game> ActiveGames ) 
    {
        int pForTwo = 0; // The number of players that currently want a 2 player game
        int pForThree = 0; // 3 player game
        int pForFour = 0; // 4 player game

        G = null;

        // Count up how many players currently want each type of game
        for (Player p : PlayerList) 
        {
            gtWanted = p.PlayerNum;
            // player will have a PlayerNum of 0 after they are put into a game 

            if (gtWanted == 2)
            {
                ++pForTwo;
            }
            else if (gtWanted == 3)
            {
                ++pForThree;
            }
            else if (gtWanted == 4)
            {
                ++pForFour;
            }
        }

        System.out.println("Players that want 2 player: "+pForTwo);
        System.out.println("Players that want 3 player: "+pForThree);
        System.out.println("Players that want 4 player: "+pForFour);

        Player player1 = null;
        Player player2 = null;
        Player player3 = null;
        Player player4 = null;
        Player currPlayer = null;
        int playersNeeded = 0;
        int player1idx = 0; // Position the player is in in the PlayerList vector
        int player2idx = 0;
        int player3idx = 0;
        int player4idx = 0;

        // If there are enough players create and start the game 
        if (pForTwo >= 2)
        {
            playersNeeded = 0;

            // Get the first 2 players that want to join a 2 player game
            while(playersNeeded < 2 )
            {
                for (int i = 0; i < PlayerList.size(); i++)
                {
                    currPlayer = PlayerList.get(i);
                    gtWanted = currPlayer.PlayerNum;

                    if (gtWanted == 2 && playersNeeded == 0)
                    {
                        player1 = currPlayer;
                        player1idx = i;
                        ++playersNeeded;

                    }
                    else if (gtWanted == 2 && playersNeeded == 1)
                    {
                        player2 = currPlayer;
                        player2idx = i;
                        ++playersNeeded;
                    }
                }
            }

            // Make new game
            G = new Game(player1, player2);
            pForTwo = 0;

            return G;
        }
        else if (pForThree >= 3)
        {
            playersNeeded = 0;

            // Get the first 3 players that want to join a 3 player game
            while(playersNeeded < 3 )
            {
                for (int i = 0; i < PlayerList.size(); i++)
                {
                    currPlayer = PlayerList.get(i);
                    gtWanted = currPlayer.PlayerNum;

                    if (gtWanted == 3 && playersNeeded == 0)
                    {
                        player1 = currPlayer;
                        player1idx = i;
                        ++playersNeeded;

                    }
                    else if (gtWanted == 3 && playersNeeded == 1)
                    {
                        player2 = currPlayer;
                        player2idx = i;
                        ++playersNeeded;
                    }
                    else if (gtWanted == 3 && playersNeeded == 2)
                    {
                        player3 = currPlayer;
                        player3idx = i;
                        ++playersNeeded;
                    }

                }
            }

            // Make new game
            G = new Game(player1, player2, player3);
            pForThree = 0;

            return G;
        }
        else if (pForFour >= 4)
        {
            playersNeeded = 0;

            // Get the first 4 players that want to join a 4 player game
            while(playersNeeded < 4 )
            {
                for (int i = 0; i < PlayerList.size(); i++)
                {
                    currPlayer = PlayerList.get(i);
                    gtWanted = currPlayer.PlayerNum;

                    if (gtWanted == 4 && playersNeeded == 0)
                    {
                        player1 = currPlayer;
                        player1idx = i;
                        ++playersNeeded;
                    }
                    else if (gtWanted == 4 && playersNeeded == 1)
                    {
                        player2 = currPlayer;
                        player2idx = i;
                        ++playersNeeded;
                    }
                    else if (gtWanted == 4 && playersNeeded == 2)
                    {
                        player3 = currPlayer;
                        player3idx = i;
                        ++playersNeeded;
                    }
                    else if (gtWanted == 4 && playersNeeded == 3)
                    {
                        player4 = currPlayer;
                        player4idx = i;
                        ++playersNeeded;
                    }
                }
            }

            // Make new game
            G = new Game(player1, player2, player3, player4);
            pForFour = 0;

            return G;
        }
        return G; // Returns null if not enough players for any game
    }

    public void Update(UserEvent U) {

    }
}