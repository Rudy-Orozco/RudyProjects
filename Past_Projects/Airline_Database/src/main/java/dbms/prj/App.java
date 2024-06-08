package main.java.dbms.prj;     
import java.sql.*;

public class App {
    Statement sqlSt;

    //Connecting to the DBMS
    public void Connect() throws Exception {
        try {
            Class.forName("com.mysql.jdbc.Driver");

            String dbURL = "jdbc:mysql://127.0.0.1:3306/airline_manager";
            String Password = "Tennis5656";
            String User = "root";

            Connection dbConn = DriverManager.getConnection(dbURL, User, Password);

            sqlSt = dbConn.createStatement();
        }
        catch(ClassNotFoundException e) {
            System.out.println("Class not found, JAR ERROR");
        }
        catch(SQLException e) {
            System.out.println("SQL: " + e.getMessage());
        }
    }

    //Disconnecting to the DBMS
    public void Disconnect() throws Exception{
        try {
            sqlSt.close();
        }
        catch(SQLException e) {
            System.out.println("SQL: " + e.getMessage());
        }
    }

    //Executing the statement in the DBMS
    public ResultSet Execute(String SQL) {
        ResultSet res = null;

        try {
            res = sqlSt.executeQuery(SQL);
        }
        catch(SQLException e) {
            System.out.println("SQL: " + e.getMessage());
        }

        return res;
    }
}


