package library;

import java.time.Duration;
import java.io.BufferedWriter;
import java.io.BufferedReader;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.IOException;

/**
* A library video that can be checked out by a patron.
*
* @author Rudy Orozco
* @version 1.0
* @since 1.0
* @license.agreement Gnu General Public License 3.0
*/
public class Video extends Publication
{
    private Duration runtime;

    /**
    * A library video that can be checked out by a patron.
    *
    * @param title title of the video
    * @param author author of the video
    * @param copyright the year of the copyright
    * @param runtime the runtime of the movie in minutes
    * @since 1.0
    */
    public Video(String title, String author, int copyright, int runtime)
    {   
        super(title, author, copyright);

        try
        {
            if(runtime <= 0) throw new IllegalArgumentException("\n[ERROR: One or more videos has Invalid Runtime]\n");
            this.runtime = Duration.ofMinutes(runtime);
        }
        catch(ArithmeticException e)
        {
            System.out.println("\n[ERROR: Runtime Exceeds Duration]\n");
            System.exit(-1);
        }
        catch(Exception e)
        {
            System.err.println(e.getMessage());
            System.exit(-1);
        }
    }

    /**
    * Reads the buffer into Video.
    *
    * @param br buffered stream that takes in each line
    */
    public Video(BufferedReader br)
    {
        super(br);
        try
        {
            String line = br.readLine();

            int mins = Integer.parseInt(line);
            this.runtime = Duration.ofMinutes(mins);
        }
        catch(IOException e)
        {
            System.err.println("Failed to read: " + e);
        }
    }

    @Override
    /**
    * Save and write inputs to file from buffer.
    *
    * @param bw buffered stream that takes in each line
    */
    public void save(BufferedWriter bw)
    {
        super.save(bw);

        try
        {
        bw.write("" + this.runtime.toMinutes() + '\n');
        }
        catch(Exception e)
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
        String str;
        String publication = super.toString();
        int strNDX = publication.indexOf("- [");

        // If Publication has been loaned, Append Additional Info, Otherwise ignore.
        if(strNDX != -1)
        {
            str = publication.substring(0,strNDX) + " Runtime " + this.runtime.toMinutes() + " minutes." + " " + publication.substring(strNDX);
        }
        else
        {
            str = publication + "Runtime " + this.runtime.toMinutes() + " minutes." + "\n";
        }

        return str;
    }
}