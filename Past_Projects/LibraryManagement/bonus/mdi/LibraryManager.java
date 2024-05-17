package mdi;

import java.util.Scanner;
import library.Library;
import library.Patron;
import library.Publication;
import library.Video;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;

public class LibraryManager
{
    public static void main(String[] args)
    {   
        // PUBLICATIONS
        Publication book1 = new Publication("To Kill a Mockingbird", "Harper Lee", 1960);
        Publication book2 = new Publication("The Great Gatsby", "F. Scott Fitzgerald", 1925);
        Publication book3 = new Publication("Fahrenheit 451", "Ray Bradbury", 1953);
        Publication vid1 = new Video("Star Wars Episode I", "George Lucas", 1999, 136);
        Publication vid2 = new Video("Interstellar", "Christopher Nolan", 2014, 169);
        Publication vid3 = new Video("Talk to Me", "Danny Philippou", 2022, 95);
        
        // PATRONS
        Patron pat1 = new Patron("Rudy Orozco", "rjo4902@mavs.uta.edu");
        Patron pat2 = new Patron("Alex Lee", "anl2948@mavs.uta.edu");
        Patron pat3 = new Patron("Leo Gam", "lag3241@mavs.uta.edu");

        // CALL NEW LIBRARY
        Library lib = new Library("Arlington Public Library");

    /*
        //ADD PUBLICATIONS
        lib.addPublication(book1);
        lib.addPublication(book2);
        lib.addPublication(book3);
        lib.addPublication(vid1);             // CUTTING OUT FOR P06
        lib.addPublication(vid2); 
        lib.addPublication(vid3); 

        // ADD PATRONS
        lib.addPatron(pat1);
        lib.addPatron(pat2);
        lib.addPatron(pat3);

    */
        //System.out.println(lib);

        Scanner obj = new Scanner(System.in);

        while(true) 
        {
            try
            {
                System.out.println("\n[Library Menu: Arlington Public Library]\n");
                System.out.println("0] Show Publications");
                System.out.println("1] Check IN Publication");
                System.out.println("2] Check OUT Publication");
                System.out.println("3] Add Book");
                System.out.println("4] Add Video");
                System.out.println("5] Add Patron");
                System.out.println("6] Show Patrons");
                System.out.println("7] Save");
                System.out.println("8] Open");

                String s = System.console().readLine("\n[Type any index to choose or type x to exit]: ");
                if(s.charAt(0) == 'x') break;
                int indx = Integer.parseInt(s);

                // MENU INTERFACE
                if(indx == 0) // SHOW PUBLIX
                    System.out.println(lib);             
                else if(indx == 1) // CHECK IN PUBLIX
                {
                    System.out.println(lib);

                    System.out.print("Which book to checkin: ");
                    String booknm = obj.nextLine();
                    int ndxb = Integer.parseInt(booknm);
                    System.out.print("\n\n");

                    lib.checkIn(ndxb);
                    System.out.println(lib); 
                }
                else if(indx == 2) // CHECK OUT PUBLIX
                {
                    System.out.println(lib);

                    System.out.print("Which book to checkout: ");
                    String booknm = obj.nextLine();
                    int ndxb = Integer.parseInt(booknm);
                    System.out.print("\n\n");

                    lib.patronMenu();
                    System.out.print("\n");

                    System.out.print("What is your name: ");
                    String usnm = obj.nextLine();
                    int ndxp = Integer.parseInt(usnm);
                    System.out.print("\n\n");

                    lib.checkOut(ndxb, ndxp);
                    System.out.println(lib); 
                }
                else if(indx == 3) // ADD BOOK
                {
                    String Name = System.console().readLine("Name of the book: ");
                    String Author = System.console().readLine("Name of the Author: ");
                    String str = System.console().readLine("Year of Copyright: ");
                    int copyright = Integer.parseInt(str);

                    Publication addbook = new Publication(Name, Author, copyright);
                    lib.addPublication(addbook);

                    str = String.format("\n\nAdded book %s by %s, Copyright %d", Name, Author, copyright);
                    System.out.println(str);
                }
                else if(indx == 4) // ADD VIDEO
                {
                    String Name = System.console().readLine("Name of the Video: ");
                    String Author = System.console().readLine("Name of the Author: ");

                    String str = System.console().readLine("Year of Copyright: ");
                    int copyright = Integer.parseInt(str);

                    str = System.console().readLine("Runtime in Minutes: ");
                    int runtime = Integer.parseInt(str);

                    Publication addvideo = new Video(Name, Author, copyright, runtime);
                    lib.addPublication(addvideo);

                    str = String.format("\n\nAdded video %s by %s, Copyright %d, Runtime %d minutes", Name, Author, copyright, runtime);
                    System.out.println(str);
                }
                else if(indx == 5) // ADD PATRONS
                {
                    String Name = System.console().readLine("What is the name of the Patron: ");
                    String Email = System.console().readLine("What is the Email of that patron: ");

                    Patron addpat = new Patron(Name, Email);
                    lib.addPatron(addpat);

                    String str = String.format("\n\nAdded Patron %s [EMAIL: %s]", Name, Email);
                    System.out.println(str);
                }
                else if(indx == 6) // SHOW PATRONS
                {
                    lib.patronMenu();
                }
                else if(indx == 7) // SAVE (WORK ON THIS FIRST)
                {
                    String filename = System.console().readLine("Please enter the Filename: ");

                    // Do a for loop while there is values in 

                    try (BufferedWriter bw = new BufferedWriter(new FileWriter(filename)))
                    {
                        lib.save(bw);
                        bw.close();
                    }
                    catch (Exception e)
                    {
                        System.err.println("Could not open file");
                    }

                    
                }              
                else if(indx == 8) // OPEN
                {
                    String filename = System.console().readLine("Please enter the Filename: ");

                    try (BufferedReader br = new BufferedReader(new FileReader(filename)))
                    {
                        lib = new Library(br);
                    }
                    catch (Exception e)
                    {
                        System.err.println("Could not open file");
                    }
                }
                else throw new IllegalArgumentException(s + " - Value not between 0-6");
            }
            catch(Exception e)
            {
                System.err.println("ERROR: " + e);
            }
        }
    }
}