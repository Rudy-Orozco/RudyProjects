package library;

import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;

/**
* A library resource that can be checked out by a patron.
*
* @author Rudy Orozco
* @version 1.0
* @since 1.0
* @license.agreement Gnu General Public License 3.0
*/
public class Publication
{
    private String title;
    private String author;
    private int copyright;
    private Patron loanedTo;
    private LocalDate dueDate;

    /**
    * A library resource that can be checked out by a patron.
    *
    * @param title title of the video
    * @param author author of the video
    * @param copyright the year of the copyright
    * @since 1.0
    */
    public Publication(String title, String author, int copyright)
    {
        this.title = title;
        this.author = author;
        
        LocalDate x = LocalDate.now();
        int ld = x.getYear();

        //Check for copyright Validity
        if(copyright < 1900 || copyright > ld) throw new IllegalArgumentException("Year is out of bounds.");
        this.copyright = copyright;
    }

    /**
    * Reads the buffer into the Publication.
    *
    * @param br buffered stream that takes in each line
    */
    public Publication(BufferedReader br)
    {
        try
        {
            String line;

            line=br.readLine(); // Start on line, loop again if there is still information
            this.title = line;

            line = br.readLine();
            this.author = line;

            line = br.readLine();
            this.copyright = Integer.parseInt(line);

            line = br.readLine();
            if(line.equals("checkedin"))                                                                
            {
                this.loanedTo = null;
                this.dueDate = null;
            }
            else
            {
                this.loanedTo = new Patron(br);

                line = br.readLine();
                DateTimeFormatter format = DateTimeFormatter.ofPattern("yyyy-MM-dd");
                LocalDate date = LocalDate.parse(line, format);
                this.dueDate = date;
            }
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
            String loanto;

            if(this.loanedTo == null)
            {
                bw.write(this.title + '\n');
                bw.write(this.author + '\n');          
                bw.write( "" + this.copyright + '\n');
                bw.write("checkedin" + '\n');
            }
            else
            {
                bw.write(this.title + '\n');
                bw.write(this.author + '\n');
                bw.write( "" + this.copyright + '\n');
                bw.write("checkedout" + '\n');
                loanedTo.save(bw);
                bw.write( "" + this.dueDate + '\n');
                
            } 
        }
        catch(IOException e)
        {
            System.err.println("Failed to write: " + e);
        }
    }

    /**
    * Gives and assigns a patron and due date.
    *
    * @param patron name of the patron
    */
    public void Checkout(Patron patron)
    {
        this.loanedTo = null;
        this.loanedTo = patron;

        LocalDate x = LocalDate.now();
        
        this.dueDate = x.plusDays(14);
    }

    /**
    * Resets patron and due date for publication.
    *
    * @param patron name of the patron
    */
    public void Checkin()
    {
        this.loanedTo = null;
        this.dueDate = null;
    }
 
    @Override
    /**
    * Returns a string.
    */
    public String toString()
    {
        String lnto;

        // If Loaned to is Empty, put new line
        if(this.loanedTo == null)
        {           
            // If it is not a special publication, put new line
            lnto = (this.getClass().getSimpleName().equals("Publication")) ? "\n" : " ";
        }
        else
        {
            lnto = String.format("- [Loaned to %s until %s]\n", this.loanedTo, this.dueDate);
        }

        // Determine the type of Publication (if class name equals Publication, set book, otherwise set video)
        String type = (this.getClass().getSimpleName().equals("Publication")) ? "Book:" : "Video:";

        return String.format("%s %s by %s. Copyright %d.", type, this.title, this.author, this.copyright) + lnto;
    }
}