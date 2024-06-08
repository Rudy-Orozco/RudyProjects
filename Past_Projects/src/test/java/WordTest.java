package uta.cse3310;
import junit.framework.TestCase;
import junit.framework.Assert;

//Unit test for nontrivial methods in Word class
public class WordTest extends TestCase {
    public void testWord() {
        //Simplest way I found to assertTrue and print since you can't use assertTrue in an if statement
        boolean bool = false;
        int[] arr = new int[2];
        Word w = new Word("test");

        System.out.println("");
        System.out.println("Word Unit Test");
        System.out.println("--------------");
        System.out.println("");
        
        Word w2 = new Word("bear");
        //commonLetter returns first common letter found in the pair of words, 0-indexed. Expected result is [1, 1] since e is the second letter in both words
        arr = w.commonLetter(w2);
        if(arr[0] == 1 && arr[1] == 1) {
            bool = true;
        }
        assertTrue(bool);
        if(bool) {
            System.out.println("commonLetter positive success");
        }
        
        arr[0] = 0;
        arr[1] = 0;
        bool = false;
        Word w3 = new Word("abcd");
        //In the case of no common letter, commonLetter returns [-1, -1], which is the expected result here
        arr = w.commonLetter(w3);
        if(arr[0] == -1 && arr[1] == -1) {
            bool = true;
        }
        assertTrue(bool);
        if(bool) {
            System.out.println("commonLetter negative success");
        }

        bool = false;
        String s = w.getLetter(1);
        //getLetter gets the 0-indexed letter of the string, so by inputting 1 we are requesting the second letter of test, "e"
        if(s.equals("e")) {
            bool = true;
        }
        assertTrue(bool);
        if(bool) {
            System.out.println("getLetter success");
        }
        System.out.println("");
    }
}