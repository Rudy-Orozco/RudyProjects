package main.java.dbms.prj;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Queries {
    private Scanner ignore = new Scanner(System.in);  // Create a Scanner object

    // Query 1
    public String q1() {
        System.out.printf("\n\nChoose MINIMM flight hours:  ");
        String Minimum = ignore.next();  // Read user input

        System.out.printf("\n\nChoose MAXIMUM flight hours:  ");
        String Maximum = ignore.next();  // Read user input

        return "SELECT TailNum, Model, CodeSize FROM AIRCRAFT WHERE AirTime >= " + Minimum +  " AND AirTime <= " + Maximum;
    }
    public void q1(ResultSet input) {
        System.out.println("\nTailNumber | Model & CodeSize");
        try {
            while(input.next() != false) {
                System.out.printf("%s\t|%s %s\n", input.getString("TailNum"), input.getString("Model"), input.getString("CodeSize"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }

        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 2
    public String q2() {
        System.out.printf("\n\nChoose a city:  ");
        String City = ignore.next();  // Read user input

        return "SELECT	P.Fname, P.MInit, P.Lname FROM PILOT P JOIN BASED_AT B ON P.SSN = B.bSSN JOIN DESTINATION D ON B.bIATA = D.IATA WHERE City = '" + City + "'";
    }
    public void q2(ResultSet input) {
        System.out.println("\nFirst Name, Middle Init, Last Name");
        try {
            while(input.next() != false) {
                System.out.printf("%s %s %s\n", input.getString("Fname"), input.getString("MInit"), input.getString("Lname"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 3
    public String q3() {
        return "SELECT Model FROM AIRCRAFT WHERE FltRange >= 3000;";
    }
    public void q3(ResultSet input) {
        System.out.println("\nModel");
        try {
            while(input.next() != false) {
                System.out.printf("%s\n", input.getString("Model"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 4
    public String q4() {
        System.out.printf("\n\nSpecify Model:  ");
        String Model = ignore.nextLine();;  // Read user input

        System.out.printf("\n\nSpecify Code/Size [if applicable]:  ");
        String CodeSize = ignore.nextLine();  // Read user input

        return "SELECT P.Fname, P.MInit, P.Lname FROM PILOT P JOIN COMMAND_ C ON P.SSN = C.cSSN JOIN AIRCRAFT A ON C.cTailNum = A.TailNum WHERE Model = '" + Model + "' AND CodeSize = '" + CodeSize + "';";
    }
    public void q4(ResultSet input) {
        System.out.println("\n[Pilot(s) Name]");
        try {
            while(input.next() != false) {
                System.out.printf("%s %s %s\n", input.getString("Fname"), input.getString("MInit"), input.getString("Lname"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 5
    public String q5() {
        System.out.printf("\n\nSpecify [M/F/U]: ");
        String Gender = ignore.nextLine();  // Read user input

        System.out.printf("\n\nSpecify Manufacturer name: ");
        String Manufacturer = ignore.nextLine();  // Read user input

        return "SELECT P.Fname, P.MInit, P.Lname FROM PILOT P JOIN COMMAND_ C ON P.SSN = C.cSSN JOIN AIRCRAFT A ON C.cTailNum = A.TailNum WHERE Gender = '" + Gender + "' AND Manufact = '" + Manufacturer + "';";
    }
    public void q5(ResultSet input) {
        System.out.println("\n[Pilot(s) Name]");
        try {
            while(input.next() != false) {
                System.out.printf("%s %s %s\n", input.getString("Fname"), input.getString("MInit"), input.getString("Lname"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 6
    public String q6() {
        System.out.printf("\n\nSpecify Depature IATA: ");
        String DepIATA = ignore.nextLine();  // Read user input

        System.out.printf("\n\nSpecify Arrival IATA: ");
        String ArrIATA = ignore.nextLine();  // Read user input

        return "SELECT P.Fname, P.MInit, P.Lname FROM PILOT P JOIN OPERATE_ O ON P.SSN = O.oSSN JOIN ROUTE_ R ON O.oFlightNo = R.FlightNo WHERE DepIATA = '" + DepIATA + "' AND ArrIATA = '" + ArrIATA + "'";
    }
    public void q6(ResultSet input) {
        System.out.println("\n[Pilot(s) Name]");
        try {
            while(input.next() != false) {
                System.out.printf("%s %s %s\n", input.getString("Fname"), input.getString("MInit"), input.getString("Lname"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 7
    public String q7() {
        System.out.printf("\n\nSpecify Ascending[A] or Descending[D] order: ");
        String o = ignore.nextLine();  // Read user input
        String order;
        
        switch(o) {
            case "A":
                order = "ASC";
                break;
            default:
                order = "DESC";
                break;
        }

        return "SELECT A.Manufact, COUNT(O.ownTailNum) AS NumAircraft FROM AIRCRAFT A JOIN OWNS_ O ON O.ownTailNum = A.TailNum GROUP BY A.Manufact HAVING COUNT(O.ownTailNum) > 0 ORDER BY NumAircraft " + order + ";";
    }
    public void q7(ResultSet input) {
        System.out.println("\nManufacturer | # of Aircraft");
        try {
            while(input.next() != false) {
                System.out.printf("%s\t%s\n", input.getString("Manufact"), input.getString("NumAircraft"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 8
    public String q8() {
        System.out.printf("\n\nSpecify Pilot's First Name: ");
        String Fname = ignore.nextLine();  // Read user input

        System.out.printf("\n\nSpecify Pilot's Last Name: ");
        String Lname = ignore.nextLine();  // Read user input

        return "SELECT A.AirlName FROM AIRLINE A JOIN WORKS_FOR W ON A.AirlID = W.wAirlID JOIN PILOT P ON P.SSN = W.wSSN WHERE Fname = '" + Fname + "' AND Lname = '" + Lname + "';";
    }
    public void q8(ResultSet input) {
        System.out.println("\n[Airline Name]");
        try {
            while(input.next() != false) {
                System.out.printf("%s\n", input.getString("AirlName"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 9
    public String q9() {
        System.out.printf("\n\nSpecify Aircraft Model: ");
        String Model = ignore.nextLine();  // Read user input

        return "SELECT A.TailNum FROM AIRCRAFT A WHERE Model = '" + Model + "';";
    }
    public void q9(ResultSet input) {
        System.out.println("\n[Aircraft Tail Number]");
        try {
            while(input.next() != false) {
                System.out.printf("%s\n", input.getString("TailNum"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query 0
    public String q0() {
        System.out.printf("\n\nSepcify an Airline: ");
        String Airline = ignore.nextLine();  // Read user input

        return "SELECT A.TailNum, A.Model, A.CodeSize FROM AIRCRAFT A JOIN OWNS_ O ON A.TailNum = O.ownTailNum JOIN AIRLINE Al ON Al.AirlID = O.ownAirlID WHERE AirlName = '" + Airline + "';";
    }
    public void q0(ResultSet input) {
        System.out.println("\nTailNumber | Model & CodeSize");
        try {
            while(input.next() != false) {
                System.out.printf("%s\t|%s %s\n", input.getString("TailNum"), input.getString("Model"), input.getString("CodeSize"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query A
    public String qA() {
        return "SELECT * FROM PILOT;";
    }
    public void qA(ResultSet input) {
        System.out.println("\n[Pilot Table]");
        System.out.printf("%-10s %-10s %-10s %-10s %-10s %-25s %-10s %-10s %-10s\n", "Fname", "MI", "Lname", "SSN", "PilotID", "Email", "Gender", "Bday", "StrtDate", "FltHours");
        try {
            while(input.next() != false) {
                System.out.printf("%-10s %-10s %-10s %-10s %-10s %-25s %-10s %-10s %-10s\n", input.getString("FName"), input.getString("MInit"), input.getString("LName"), input.getString("SSN"), input.getString("PilotID"), input.getString("Email"), input.getString("Gender"), input.getString("BDay"), input.getString("StrtDate"), input.getString("FltHours"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query B
    public String qB() {
        return "SELECT * FROM AIRCRAFT;";
    }
    public void qB(ResultSet input) {
        System.out.println("\n[Aircraft Table]");
        System.out.printf("%-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s\n", "TailNum", "SN", "AirTime", "HourTilMaint", "Manufact", "Model", "Code/Size", "FltRange", "StrtofServ");
        try {
            while(input.next() != false) {
                System.out.printf("%-10s %-10s %-10s %-20s %-10s %-10s %-10s %-10s\n", input.getString("TailNum"), input.getString("SN"), input.getString("AirTime"), input.getString("HourTilMaint"), input.getString("Manufact"), input.getString("Model"), input.getString("CodeSize"), input.getString("FltRange"), input.getString("StartOfServ"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query C
    public String qC() {
        return "SELECT * FROM DESTINATION;";
    }
    public void qC(ResultSet input) {
        System.out.println("\n[Destination Table]");
        System.out.printf("%-20s %-10s %-30s %-20s\n", "Country", "City", "APName", "IATA");
        try {
            while(input.next() != false) {
                System.out.printf("%-20s %-10s %-30s %-20s\n", input.getString("Country"), input.getString("City"), input.getString("APName"), input.getString("IATA"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query D
    public String qD() {
        return "SELECT * FROM ROUTE_;";
    }
    public void qD(ResultSet input) {
        System.out.println("\n[Route Table]");
        System.out.printf("%-15s %-10s %-10s %-10s\n", "FlightNo", "Dist", "DepIATA", "ArrIATA");
        try {
            while(input.next() != false) {
                System.out.printf("%-15s %-10s %-10s %-10s\n", input.getString("FlightNo"), input.getString("Dist"), input.getString("DepIATA"), input.getString("ArrIATA"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }

    // Query E
    public String qE() {
        return "SELECT * FROM AIRLINE;";
    }
    public void qE(ResultSet input) {
        System.out.println("\n[Airline Table]");
        System.out.printf("%-25s %-15s %-10s\n", "AirlName", "AirlID", "Country");
        try {
            while(input.next() != false) {
                System.out.printf("%-25s %-15s %-10s\n", input.getString("AirlName"), input.getString("AirlID"), input.getString("Country"));
            }
        }
        catch(SQLException e) {
            Logger.getLogger(App.class.getName()).log(Level.SEVERE, null, e);
            System.out.println("SQL Error: " + e.getMessage());
        }
        
        // Handle Ignoring state
        Scanner ignore = new Scanner(System.in);  // Create a Scanner object
        System.out.printf("\n\nPress enter to continue... ");
        String ign = ignore.nextLine();  // Read user input
        System.out.println("");
    }
}
