
import java.sql.*;

public class ServerDao {

    static final String MARIADB_SUB = "jdbc:mariadb:";
    static final String DB_SERVER = "//localhost:3306/";
    static final String DB_NAME = "askisi1_db";
    static String DB_USER;
    static String DB_PASS;
    final String MARIADB_DRIVER = "org.mariadb.jdbc.Driver";
    static final String DB_URL = MARIADB_SUB + DB_SERVER + DB_NAME;

    ServerDao(String username, String pass) {
        DB_USER = username;
        DB_PASS = pass;
        try {
            Class.forName(MARIADB_DRIVER);
        } catch (ClassNotFoundException e) {
            System.out.println("MariaDB JDBC Driver not found.");
            e.printStackTrace();
        }
    }

    public boolean checkIfUserExists() {
        try {
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            return true;
        } catch (SQLException ex) {
            System.out.println("SQL Exception: " + ex);
            return false;
        }
    }

    public String getDBname() {
        return DB_NAME;
    }

    public String SelectbySurrname(String surrname) {
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
    
    public String insertRow(String fn, String ln, String sh, int sem, int pass) {
    try {
        Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
        String query = "INSERT INTO students (firstname,lastname,school,semester,passed) VALUES ('"
                    + fn + "','"
                    + ln + "','"
                    + sh + "','"
                    + sem + "','"
                    + pass + " ')";
        
        try (PreparedStatement preparedStatement = conn.prepareStatement(query)) {
            preparedStatement.setString(1, fn);
            preparedStatement.setString(2, ln);
            preparedStatement.setString(3, sh);
            preparedStatement.setInt(4, sem);
            preparedStatement.setInt(5, pass);
            
            int rowsAffected = preparedStatement.executeUpdate();

            if (rowsAffected > 0) {
                return "Row inserted successfully.";
            } else {
                return "Failed to insert row.";
            }
        }
    } catch (SQLException ex) {
        System.out.println("SQL Exception: " + ex);
        return null;
    }
}


    

}


