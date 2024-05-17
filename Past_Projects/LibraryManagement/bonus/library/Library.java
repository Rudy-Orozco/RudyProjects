package library;
import java.util.ArrayList;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;

/**
* Models a library containing various publications.
*
* @author Rudy Orozco
* @version 1.0
* @since 1.0
* @license.agreement Gnu General Public License 3.0
*/
public class Library
{
    private String name;
    private ArrayList<Publication> publication = new ArrayList<Publication>();
    private ArrayList<Patron> patron = new ArrayList<Patron>();

    /**
    * Models a library containing various publications.
    *
    * @param name name of the library
    */
    public Library(String name)
    {
        this.name = name;
    }

    /**
    * Reads the buffer into the Library.
    *
    * @param br buffered stream that takes in each line
    */
    public Library(BufferedReader br)
    {   
        ArrayList<Publication> emptyPub = new ArrayList<Publication>();
        ArrayList<Patron> emptyPat = new ArrayList<Patron>();

        try
        {
            String line=br.readLine(); //line 1
            this.name = line;

            line=br.readLine(); //line 2
            int Pubsize = Integer.parseInt(line);
            for(int i = 0 ; i < Pubsize ; i++)
            {
                line=br.readLine();

                if(line.equals("publication"))
                {
                    Publication pub = new Publication(br);

                    emptyPub.add(pub);
                }
                else
                {
                    Video vid = new Video(br);

                    emptyPub.add(vid);
                }
            }

            line=br.readLine();
            int Patsize = Integer.parseInt(line);
            for(int i = 0 ; i < Patsize ; i++)
            {
                Patron pat = new Patron(br);

                emptyPat.add(pat);                           
            }

            publication = emptyPub;
            patron = emptyPat;
        }
        catch(IOException e)
        {
            System.err.println("Failed to read: " + e);
        }

    }

    /**
    * Save and write inputs to file from buffer.
    *
    * @param bw buffered stream that takes in each line
    */
    public void save(BufferedWriter bw)
    {
        try
        {
            bw.write(this.name + '\n'); //line 1
            bw.write("" + publication.size() + '\n'); //line 2

            for (Publication s : publication)
            {
                if(s.getClass().getSimpleName().equals("Publication")) // had to use this because I instanceof didn't work
                {
                    bw.write("publication" + "\n");
                    s.save(bw);
                }
                else
                {               
                    bw.write("video" + "\n");
                    s.save(bw);
                }
            }

            bw.write("" + patron.size() + '\n'); // line 3 if pub is empty

            for (Patron p : patron)
            {
                p.save(bw);
            }
        }
        catch(Exception e)
        {
            System.err.println("Failed to write: " + e);
        }
    }

    /**
    * Adds a publication to the list.
    *
    * @param publication name of the library
    */
    public void addPublication(Publication publication)
    {
        this.publication.add(publication);
    }

    /**
    * Adds a patron to the patron list.
    *
    * @param patron the name of the patron
    */
    public void addPatron(Patron patron)
    {
        this.patron.add(patron);
    }

    /**
    * checks out the publicaton based on the patron and publication chose.
    *
    * @param publicationIndex the index of the publication array
    * @param patronIndex index of the patron array
    */
    public void checkOut(int publicationIndex, int patronIndex)
    {
        publication.get(publicationIndex).Checkout(patron.get(patronIndex));
    }

    /**
    * checks in the publicaton based on the publication chosen.
    *
    * @param publicationIndex the index of the publication array
    */
    public void checkIn(int publicationIndex)
    {
        publication.get(publicationIndex).Checkin();
    }
    
    /**
    * prints out the patron array.
    *
    */
    public void patronMenu()
    {
        StringBuffer buf1 = new StringBuffer();

        int j = 0;

        buf1.append(String.format("\n\n"));
        for (Patron t : patron) 
        {   
            buf1.append(String.format("%d] ", j));
            buf1.append(t + "\n");
            j++;
        }

        System.out.println(buf1);
    }

    @Override
    /**
    * Returns a string.
    */
    public String toString()
    {
        StringBuffer buf = new StringBuffer();

        int i = 0;
        for (Publication s : publication) 
        {   
            buf.append(String.format("%d] ", i));
            buf.append(s);
            i++;
        }

        return "\n\n" + this.name + "\n\n" + buf;
    }
        
}
