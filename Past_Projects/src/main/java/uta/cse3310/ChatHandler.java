package uta.cse3310;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
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

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

public class ChatHandler {
    private WebSocketServer server;
    private MessageBoard messageBoard;

    public ChatHandler(WebSocketServer server) {
        this.server = server;
        this.messageBoard = new MessageBoard();
    }

    public void handleMessage(WebSocket conn, String text, String playerNick, String GameId) {
        // Correctly using playerNick instead of hardcoded "playerNick"
        messageBoard.addMessage(playerNick, text);
        broadcastToAllChatParticipants(text, playerNick, GameId);
    }

    private void broadcastToAllChatParticipants(String message, String playerNick, String GameId) {
        JsonObject jsonMessage = new JsonObject();
        jsonMessage.addProperty("type", "chat");
        jsonMessage.addProperty("text", formatChatMessage(message, playerNick));
        jsonMessage.addProperty("GameId", GameId);
    
        String jsonStr = jsonMessage.toString();
        for (WebSocket conn : server.getConnections()) {
            try {
                if (conn.isOpen()) {
                    conn.send(jsonStr);
                }
            } catch (Exception e) {
                System.err.println("Failed to send message to a client: " + e.getMessage());
            }
        }
    }
      
    private String formatChatMessage(String message, String playerNick) {
        String timeStamp = new SimpleDateFormat("HH:mm:ss").format(new Date());
        return "[" + timeStamp + "] " + playerNick + ": " + message;
    }    
    
}


