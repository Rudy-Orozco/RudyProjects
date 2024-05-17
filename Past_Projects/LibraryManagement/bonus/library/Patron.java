package library;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;

/**
* A person authroized to check out a library resource.
*
* @author Rudy Orozco
* @version 1.0
* @since 1.0
* @license.agreement Gnu General Public License 3.0
*/
public class Patron
{
    private String patrname;
    private String email;

    /**
    * A person authroized to check out a library resource.
    *
    * @param patrname name of the patron
    * @param email the patron's email
    * @since 1.0
    */
    public Patron(String patrname, String email)
    {
        this.patrname = patrname;
        this.email = email;
    }
    
    /**
    * Reads the buffer into Patron.
    *
    * @param br buffered stream that takes in each line
    */
    public Patron(BufferedReader br)
    {
        try
        {
            String line = br.readLine();
            this.patrname = line;

            line = br.readLine();
            this.email = line;
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
            bw.write(this.patrname + '\n');
            bw.write(this.email + '\n');
        }
        catch(IOException e)
        {
            System.err.println("Failed to write: " + e);
        }
    }

    @Override
    /**
    * Returns a string.
    */
    public String toString()
    {
        return String.format("%s [EMAIL: %s]", patrname, email);
    }
}