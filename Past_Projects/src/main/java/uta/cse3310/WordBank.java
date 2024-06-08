package uta.cse3310;

import java.util.Scanner;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.Random;
import java.util.*;

public class WordBank
{
   private List<Integer> elements = new ArrayList<>();
   private Vector<String> totalList = new Vector<>();
   private Vector<Word> WordList = new Vector<>();
   private Vector<Word> foundWords = new Vector<>();
   private int numwords;

   public WordBank() {
      // Checking the amount of lines in a file
       // Amount of words 
      try { 
         File file = new File("words.txt");
         Scanner scan = new Scanner(file);

         while(scan.hasNextLine()) {
            String s = scan.nextLine();
            if(s.length() > 4) {
               totalList.add(s);
               numwords++;
            }
         }
         scan.close();
      }
      catch (Exception e) {
         e.getStackTrace();
      }
   }

   public String[] getWordString() {
      String[] result = new String[this.WordList.size()];
      int i = 0;
      for(Word w: this.WordList) {
         result[i] = w.getWord();
         i++;
      }
      return result;
   }
   
   public void add(Word newWord) {
      this.foundWords.add(newWord);   // adds new word to the foundwords
   }

   public void addList(Word newWord) {
      this.WordList.add(newWord);
   }

   public Vector<Word> getWordList() {
      return this.WordList;                 // returns the word list
   }

   public Vector<String> getTotalList() {
      return this.totalList;
   }
   
   public Vector<Word> getFoundWords() {
      return this.foundWords;               // returns the foundwords list
   }

   public void printWordList(Vector<Word> wordList) {
      for(Word w: wordList) {
         System.out.println(w);
      }
      System.out.println("");
   }

   public void wordSort(Vector<Word> wordList) {
      Collections.sort(wordList, new Comparator<Word>() {
         @Override
         public int compare(Word first, Word sec) {
            return first.getWord().compareTo(sec.getWord());
         }
      });
   }
   
   public void generateWords() {
      //Random rng = new Random();

      // Generate 100 words from the total list
      /*for(int i = 0; i < 100; i++) {                            // For each word
         int rand = rng.nextInt(numwords);                     // create a random word 

         for(int j = 0; j < this.elements.size(); j++) {
            if(this.elements.contains(rand))                        // if an element already exists
            {
               rand = rng.nextInt(numwords);                   // run the random generator again
               j = 0;                                          // set the increment back to 0 and run the for loop again
            }
         }

         this.WordList.add(new Word(this.totalList.get(rand)));   
      }*/

      wordSort(this.WordList);
   }
}
