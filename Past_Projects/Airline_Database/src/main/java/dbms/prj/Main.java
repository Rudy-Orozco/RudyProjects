package main.java.dbms.prj; 
import java.sql.ResultSet;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        App app = new App();
        boolean active = true;

        // Connect to DBMS
        try {
            app.Connect();
        }
        catch (Exception e){
            System.out.println("Error has occured\n");
        }
    
        // While loop for choosing queries
        while(active)
        {
            System.out.print("\033[H\033[2J");

            System.out.print("\n\n\n[Airline Management System]\n\n");
            System.out.println("1)  Gather Aircraft by FltHours between...");
            System.out.println("2)  Get pilots that are based in...");
            System.out.println("3)  Get aircraft with a minimum range of 3000 NM");
            System.out.println("4)  Get pilots that can command a 787-8.");
            System.out.println("5)  Get all pilots by gender and manufactuer...");
            System.out.println("6)  Get pilots that can fly a route from ___ to ___.");
            System.out.println("7)  List the number of aircraft by manufacturer...");
            System.out.println("8)  What airline does pilot _____ fly for?");
            System.out.println("9)  Get all tailnumbers of an aircraft model in service...");
            System.out.println("0)  Gather all aircraft is owned by the airline...\n");

            System.out.println("A)  View Pilot Table");
            System.out.println("B)  View Aircraft Table");
            System.out.println("C)  View Destination Table");
            System.out.println("D)  View Route Table");
            System.out.println("E)  View Airline Table");


            System.out.println("\nX)  Exit the program\n");
        
            Scanner myObj = new Scanner(System.in);  // Create a Scanner object
            System.out.printf("Enter choice: ");
            String input = myObj.nextLine();  // Read user input
            System.out.println("");
        
            System.out.print("\033[H\033[2J");

            Queries q = new Queries();
            ResultSet res;

            // Choices for the CLI
            switch(input) {
            case "1":
                    res = app.Execute(q.q1());
                    q.q1(res);
                    break;
                case "2":
                    res = app.Execute(q.q2());
                    q.q2(res);
                    break;  
                case "3":
                    res = app.Execute(q.q3());
                    q.q3(res);
                    break;
                case "4":
                    res = app.Execute(q.q4());
                    q.q4(res);
                    break;
                case "5":
                    res = app.Execute(q.q5());
                    q.q5(res);
                    break;
                case "6":
                    res = app.Execute(q.q6());
                    q.q6(res);
                    break;  
                case "7":
                    res = app.Execute(q.q7());
                    q.q7(res);
                    break;
                case "8":
                    res = app.Execute(q.q8());
                    q.q8(res);
                    break;
                case "9":
                    res = app.Execute(q.q9());
                    q.q9(res);
                    break;  
                case "0":
                    res = app.Execute(q.q0());
                    q.q0(res);
                    break;
                case "A":
                    res = app.Execute(q.qA());
                    q.qA(res);
                    break;          
                case "B":
                    res = app.Execute(q.qB());
                    q.qB(res);
                    break;           
                case "C":
                    res = app.Execute(q.qC());
                    q.qC(res);
                    break;  
                case "D":
                    res = app.Execute(q.qD());
                    q.qD(res);
                    break;  
                case "E":
                    res = app.Execute(q.qE());
                    q.qE(res);
                    break;  
                case "X":
                    try {
                        active = false;
                        app.Disconnect();
                    }
                    catch(Exception e) {
                        System.out.println("Error has occured\n");
                    }
                    break;
            }
        }   
        System.out.println("Program has closed\n");
    }
}
