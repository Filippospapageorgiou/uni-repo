package PROJECT;

import java.sql.*;


public class DBconnect {

    static final String MARIADB_SUB="jdbc:mariadb:";
    static final  String DB_SERVER="//localhost:3306/";
    static final String DB_NAME="askisi1_db";
    static String DB_USER;
    static String DB_PASS;
    final String MARIADB_DRIVER="org.mariadb.jdbc.Driver";
    static final String DB_URL=MARIADB_SUB + DB_SERVER +DB_NAME; 
        DBconnect(String username,String pass){
            DB_USER=username;
            DB_PASS=pass;
        }

        public boolean checkIfUserExists(){
            try{
                Connection conn = DriverManager.getConnection(DB_URL,DB_USER,DB_PASS);
                return true;
            }catch(SQLException ex){
                System.out.println("SQL Exception: " + ex);
                return false;
            }
        }
        
        public String SelectAll() {
            try {
                String returnString;
                Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
                Statement st = conn.createStatement();
                ResultSet rs = st.executeQuery("SELECT * FROM students");
    
                StringBuilder output = new StringBuilder();
        
                while (rs.next()) {
                    output.append("|").append(rs.getString(1)).append("|")
                          .append(rs.getString(2)).append("|")
                          .append(rs.getString(3)).append("|")
                          .append(rs.getString(4)).append("|")
                          .append(rs.getString(5)).append("|\n");
                }
                returnString = output.toString();
                return returnString;
            } catch (SQLException ex) {
                System.out.println("SQL Exception: " + ex);
                return null;
            }
        }
        
        public String SelectbySurrname(String surrname){
            try {
                String returnString;
                Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
                Statement st = conn.createStatement();
                ResultSet rs = st.executeQuery("SELECT * FROM students WHERE lastname = '" + surrname + "'");
    
                StringBuilder output = new StringBuilder();
        
                while (rs.next()) {
                    output.append("|").append(rs.getString(1)).append("|")
                          .append(rs.getString(2)).append("|")
                          .append(rs.getString(3)).append("|")
                          .append(rs.getString(4)).append("|")
                          .append(rs.getString(5)).append("|\n");
                }
                returnString = output.toString();
                return returnString;
            } catch (SQLException ex) {
                System.out.println("SQL Exception: " + ex);
                return null;
            }
        }


        public String SelectbySem(int sem){
            try {
                String returnString;
                Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
                Statement st = conn.createStatement();
                ResultSet rs = st.executeQuery("SELECT * FROM students WHERE semester IN(" + sem + ")");
                StringBuilder output = new StringBuilder();
                while (rs.next()) {
                    output.append("|").append(rs.getString(1)).append("|")
                          .append(rs.getString(2)).append("|")
                          .append(rs.getString(3)).append("|")
                          .append(rs.getString(4)).append("|")
                          .append(rs.getString(5)).append("|\n");
                }
                returnString = output.toString();
                return returnString;
            } catch (SQLException ex) {
                System.out.println("SQL Exception: " + ex);
                return null;
            }
        }


        public String updateQuery(String surname, int passed) {
            try {
                Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
                Statement st = conn.createStatement();
        
                // Use executeUpdate for UPDATE queries
                int rowsAffected = st.executeUpdate("UPDATE students SET passed = " + passed + " WHERE lastname = '" + surname + "'");
        
                // Optionally, you can return the number of rows affected
                return "SUCCES rows affected " + rowsAffected;
            } catch (SQLException ex) { 
                return "SQL Exception: " + ex; // Indicate an error using a negative value, or handle it differently based on your needs
            }
        }

        public String deleteQuery(String surname) {
            try {
                Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
                Statement st = conn.createStatement();
        
                // Use executeUpdate for DELETE queries
                int rowsAffected = st.executeUpdate("DELETE FROM students WHERE lastname = '" + surname + "'");
        
                // Optionally, you can return the number of rows affected
                return "SUCCES rows affected" + rowsAffected;
            } catch (SQLException ex) {
                System.out.println("SQL Exception: " + ex);
                return null; // Indicate an error using a negative value, or handle it differently based on your needs
            }
        }
        

}
