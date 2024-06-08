// This is example code provided to CSE3310 Fall 2022
// You are free to use as is, or changed, any of the code provided

// Please comply with the licensing requirements for the
// open source packages being used.

// This code is based upon, and derived from the this repository
//            https:/thub.com/TooTallNate/Java-WebSocket/tree/master/src/main/example

// http server include is a GPL licensed package from
//            http://www.freeutils.net/source/jlhttp/

/*Copyright (c) 2010-2020 Nathan Rajlich

Permission is hereby granted, free of charge, to any person
obtaining a copy of this software and associated documentation
files (the "Software"), to deal in the Software without
restriction, including without limitation the rights to use,
copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following
conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.*/

package uta.cse3310;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.InputStream;
import java.net.InetSocketAddress;
import java.net.UnknownHostException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Collections;
import java.util.Date;

import org.java_websocket.WebSocket;
import org.java_websocket.drafts.Draft;
import org.java_websocket.drafts.Draft_6455;
import org.java_websocket.handshake.ClientHandshake;
import org.java_websocket.server.WebSocketServer;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;
import java.time.Instant;
import java.time.Duration;
import java.util.Arrays;
import java.lang.String;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;
import com.google.gson.JsonArray;
import com.google.gson.annotations.SerializedName;

public class App extends WebSocketServer {

    // All games currently underway on this server are stored in
    // the vector ActiveGames

    private Vector<Player> PlayerList = new Vector<Player>();

    private Vector<Player> SavedPlayerList = new Vector<Player>();

    private Vector<Word> WordList = new Vector<Word>();

    private Vector<Game> ActiveGames = new Vector<Game>();

    private int GameId = 1;

    private int connectionId = 0;

    private Instant startTime;

    private Statistics stats;

    private ChatHandler chatHandler;

    private static String hash = null;

    private int pnum = 0;

    WordBank W = new WordBank();
    
    GameLobby GL = new GameLobby();

    public WordBank getWordBankW() 
    {
        return W;
    }

    public App(int port) {
        super(new InetSocketAddress(port));
        this.chatHandler = new ChatHandler(this);
    }

    public App(InetSocketAddress address) {
        super(address);
    }

    public App(int port, Draft_6455 draft) {
        super(new InetSocketAddress(port), Collections.<Draft>singletonList(draft));
    }

    public static void currHash(){ // Enviorment variable version always null, adding this back in to change it to the current hash
        String sResults = null;
        try{
            Process process = Runtime.getRuntime().exec("git rev-parse HEAD"); // Starts a process to get the hash

            InputStream results = process.getInputStream(); // Capture results of command 

            BufferedReader reader = new BufferedReader(new InputStreamReader(results));
            StringBuilder output = new StringBuilder();
            while((sResults = reader.readLine()) != null) {
                output.append(sResults).append("\n");
            }
            hash = output.toString().trim();
        }
        catch(IOException e){}
    } 

    @Override
    public void onOpen(WebSocket conn, ClientHandshake handshake) {
        connectionId++;
        System.out.println(conn.getRemoteSocketAddress().getAddress().getHostAddress() + " connected");
        ServerEvent E = new ServerEvent();

        Gson gson = new Gson();

        // Note only send to the single connection
        String jsonString = gson.toJson(E);
        conn.send(jsonString);
        System.out.println("> " + Duration.between(startTime, Instant.now()).toMillis() + " " + connectionId + " " + escape(jsonString));

        // Update the running time
        stats.setRunningTime(Duration.between(startTime, Instant.now()).toSeconds());

        // The state of the game has changed, so lets send it to everyone
        //jsonString = gson.toJson(G);
        System.out.println("< " + Duration.between(startTime, Instant.now()).toMillis() + " " + "*" + " " + escape(jsonString));
        broadcast(jsonString);
    }

    @Override
    public void onClose(WebSocket conn, int code, String reason, boolean remote) {
        System.out.println(conn + " has closed");
        
        // Retrieve the game tied to the websocket connection
        Game G = conn.getAttachment();
        G = null;
    }
    
    @Override
    public void onMessage(WebSocket conn, String message) {
        
        System.out.println("\nincoming < " + Duration.between(startTime, Instant.now()).toMillis() 
            + " " + "-" + " " + escape(message) + "\n");

        /*Checks to see if it is a type 'chat' message string. If its not a type 'chat' message, it will continue 
        with rest of the logic for other type of message string.*/
        try {
            JsonObject jsonMessage = JsonParser.parseString(message).getAsJsonObject();
            // Check if the message is a chat message
            if ("chat".equals(jsonMessage.get("type").getAsString())) {
                String chatMessage = jsonMessage.get("text").getAsString();
                // Handle anonymous or default nicknames
                String playerNick = jsonMessage.has("playerNick") ? jsonMessage.get("playerNick")
                    .getAsString() : "Anonymous"; 
                String GameId = jsonMessage.get("GameId").getAsString();
                chatHandler.handleMessage(conn, chatMessage, playerNick, GameId);
                return;
            } 
        } catch (Exception e) {
            System.err.println("Error processing message: " + e.getMessage());
            //e.printStackTrace();
        }
        
        // Bring in the data from the webpage
        // A UserEvent is all that is allowed at this point
        GsonBuilder builder = new GsonBuilder();
        Gson gson = builder.create();

        ServerEvent E = gson.fromJson(message, ServerEvent.class);
        UserEvent U = gson.fromJson(message, UserEvent.class);

        System.out.println("On message: " + message);

        // Update the running time
        stats.setRunningTime(Duration.between(startTime, Instant.now()).toSeconds());

        Player P = null;
        Game G = null;
        
        System.out.println("\n\nInvoke Call: " + U.Invoke);

        // Reset any new game flags before invoke
        for(Game gam : ActiveGames)
        {
            if(gam.gameNew == 1)
            {
                gam.gameNew = 0;
            }
        }

        if(U.Invoke == 1)   // FindGame() and New Player
        {
            // Create a new default blank Player and save the nickname and pin
            P = new Player(U.PlayerNick, pnum);
            P.setSavedPin(U.Pin);

            System.out.println("\n\nPlayer:" + P.getPlayerNick() + U.PlayerNick + "Sent to Lobby");
            
            if(U.Type == 2)
            {
                P.PlayerNum = 2;
            }
            else if(U.Type == 3)
            {
                P.PlayerNum = 3;
            }
            else if(U.Type == 4)
            {
                P.PlayerNum = 4;
            }

            System.out.println("\n\nPlayerType: " + P.getPlayerType());

            PlayerList.add(P);
            SavedPlayerList.add(P);

            // Test message to see all current players and the games they want
            for (Player p : PlayerList)
            {
                System.out.println("Player: "+P.PlayerNum+" "+P.getPlayerNick()+"\n");
            }

            G = GL.matchMaking(PlayerList, ActiveGames);
            //PlayerList = GL.RemovePlayers(G, PlayerList); // Null pointer exception
            U.Invoke = -1;

            if(G != null) // If game is not null remove the players that are now in game from the playerlist
            { // This is so they won't be chosen to create a new game
                G.state = 1;
                G.GameId = GameId;
                G.gameNew = 1;
                GameId++;

                String inGamePNick = "";
                String inListPNick = "";

                Vector<Player> tempPlayerList = G.getplayerVector();

                for(Player Q : tempPlayerList)
                {
                    inGamePNick = Q.getPlayerNick();

                    for(int i = 0; i < PlayerList.size(); i++)
                    {
                        Player R = PlayerList.get(i);
                        inListPNick = R.getPlayerNick();

                        if(inListPNick.equals(inGamePNick))
                        {
                            PlayerList.remove(i);
                        }
                    }
                }
                
                ActiveGames.add(G); // Since this is here it will be taken out of GameLobby to prevent a game from being added twice
                //G.Update(U);
                System.out.println("\n\n/// Game Has Been Created ///\n\n");

                // Call all clients to switch to the game screen
                //conn.send(G);
            }

            // allows the websocket to give us the Game when a message arrives
            conn.setAttachment(G);

            gson = new Gson();
            // Note only send to the single connection
            //conn.send(gson.toJson(E));
            //System.out.println(gson.toJson(E));

            // send out the game state every time
            // to everyone
            String jsonString;
            jsonString = gson.toJson(G);
            System.out.println("> " + Duration.between(startTime, Instant.now()).toMillis() + " " + "*" + " " + escape(jsonString));
            broadcast(jsonString);
        }
        if(U.Invoke == 2)   // Check Word and Update Board
        {
            // Get the game that the player is in
            for(int i = 0; i < ActiveGames.size(); i++)
            {
                if(U.GameId == ActiveGames.get(i).GameId)
                {
                    G = ActiveGames.get(i);
                }
            }

            //Get 2D start Coordinates
            int[] startCoord = new int[2];
            startCoord[0] = ((U.StartCoordinate + 1) / 50);
            startCoord[1] = ((U.StartCoordinate + 1) % 50) - 1;
            String sCstr = Arrays.toString(startCoord);

            //Get 2D end Coordinates
            int[] endCoord = new int[2];
            endCoord[0] = ((U.EndCoordinate + 1) / 50);
            endCoord[1] = ((U.EndCoordinate + 1) % 50) - 1;
            String eCstr = Arrays.toString(endCoord);
            
            JsonObject jsObj = new JsonObject();
            String jsonStringPlayer = null;
            if(G.verifyWord(startCoord, endCoord, G.totalwords))
            {   
                System.out.println("\n\n/// Word has been found by " + U.PlayerNick + "///\n\n" + "");
                jsObj.addProperty("wordchosen", 1);

                
                for(Player p : G.player)
                {   
                    System.out.println(p.PlayerNick + " " + U.PlayerNick + " " + p.getPoints());
                    if(p.PlayerNick.equals(U.PlayerNick))
                    {
                        System.out.println("Applying Points");
                        p.updateScore();
                        jsObj.addProperty("points", p.getPoints());
                    }
                }
            }
            else
            {
                jsObj.addProperty("wordchosen", 0);
            }
            

            jsObj.addProperty("state", 2);
            jsObj.addProperty("startCoordinate", U.StartCoordinate);
            jsObj.addProperty("endCoordinate", U.EndCoordinate);
            jsObj.addProperty("GameId", G.GameId);
            jsObj.addProperty("PlayerNick", U.PlayerNick);
            jsObj.addProperty("idx", U.idx);
            jsObj.addProperty("Button", U.Button);
            

            //conn.setAttachment(G);
            G.state = 2;
            G.startCoordinate = U.StartCoordinate;
            G.endCoordinate = U.EndCoordinate;
            G.Button = U.Button;

            String jsonString = gson.toJson(jsObj);
            
            System.out.println("> " + Duration.between(startTime, Instant.now()).toMillis() + " " + "*" + " " + escape(jsonString));
            broadcast(jsonString);
        }
        if(U.Invoke == 3) // Game Ended
        {   
            // Get the game that the player is currently in
            for(int i = 0; i < ActiveGames.size(); i++)
            {
                if(U.GameId == ActiveGames.get(i).GameId)
                {
                    G = ActiveGames.get(i);
                    ActiveGames.remove(G);
                }
            }

            Leaderboard LeadB = new Leaderboard(G.player);
            LeadB.sortPlayer();

            LBJS lbjs = new LBJS();

            lbjs.LeadB = LeadB;
            lbjs.GameId = U.GameId;
            lbjs.state = 3;
            
            String jsonString = gson.toJson(lbjs);

            broadcast(jsonString);

            System.out.println("\n\n /// ENDING GAME /// ");
        }
    }

    @Override
    public void onMessage(WebSocket conn, ByteBuffer message) {
        System.out.println(conn + ": " + message);
    }

    @Override
    public void onError(WebSocket conn, Exception ex) {
        ex.printStackTrace();
        if (conn != null) {
        // some errors like port binding failed may not be assignable to a specific
        // websocket
        }
    }

    @Override
    public void onStart() {
        setConnectionLostTimeout(0);
        stats = new Statistics();
        startTime = Instant.now();
    }

    private String escape(String S) {
        // turns " into \"
        String retval = new String();
        // this routine is very slow.
        // but it is not called very often
        for (int i = 0; i < S.length(); i++) {
        Character ch = S.charAt(i);
        if (ch == '\"') {
        retval = retval + '\\';
        }
        retval = retval + ch;
        }
        return retval;
    }


    public static void main(String[] args) {
        //9080 or 9006 for HttpPort
        //9880 or 9106 for Websocket

        String HttpPort = System.getenv("HTTP_PORT");
        int port = 9006;
        if (HttpPort!=null) {
            port = Integer.valueOf(HttpPort);
        }

        HttpServer H = new HttpServer(port, "./html");
        H.start();
        System.out.println("http Server started on port: " + port);

        port = 9106;
        String WSPort = System.getenv("WEBSOCKET_PORT");
        if (WSPort!=null) {
            port = Integer.valueOf(WSPort);
        }

        App A = new App(port);
        A.setReuseAddr(true);
        A.start();
        System.out.println("websocket Server started on port: " + port);

        currHash();// System.getenv("VERSION"); alwways gives null
        System.out.println("Current github hash : " + A.hash);
    }
}
