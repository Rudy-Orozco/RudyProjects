package uta.cse3310;

import java.text.SimpleDateFormat;
import java.util.*;

public class MessageBoard {
    private Vector<String> messages = new Vector<>();

    public MessageBoard() {
    }

    // Add a message to the board
    public void addMessage(String playNick, String message) {
        String fullMessage = playNick + ": " + message;
        messages.add(fullMessage);
    }
    
    // Generate a formatted message and add it to the messages
    public void generateMessage(String message) {
        messages.add("System: " + message);
    }

    // Simulate receiving input from a user interface
    public void receiveInput(String playNick, String message) {
        if (!message.trim().isEmpty()) {
            addMessage(playNick, message);
        }
    }

    // Get all the messages from the board
    public Vector<String> getMessages() {
        return messages;
    }

    // This can be used for display in the UI / for logging
    public void printMessages() {
        for(String message : messages) {
            System.out.println(message);
        }
    }
}
