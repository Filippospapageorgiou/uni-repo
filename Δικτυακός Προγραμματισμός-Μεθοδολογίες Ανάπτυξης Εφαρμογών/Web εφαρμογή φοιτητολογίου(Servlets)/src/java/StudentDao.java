
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
/**
 *
 * @author filip
 */
public class StudentDao {

    static final String MARIADB_SUB = "jdbc:mariadb:";
    static final String DB_SERVER = "//localhost:3306/";
    static final String DB_NAME = "askisi1_db";
    static String DB_USER;
    static String DB_PASS;
    final String MARIADB_DRIVER = "org.mariadb.jdbc.Driver";
    static final String DB_URL = MARIADB_SUB + DB_SERVER + DB_NAME;

    StudentDao(String username, String pass) {
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

    public static int save(Student student) {
        try {
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            String query = "INSERT INTO students (firstname,lastname,school,semester,passed) VALUES ('"
                    + student.getName() + "','"
                    + student.getSurname() + "','"
                    + student.getSchool() + "','"
                    + student.getSemester() + "','"
                    + student.getPassed() + " ')";
            PreparedStatement preparedStatement = conn.prepareStatement(query);
            preparedStatement.setString(1, student.getName());
            preparedStatement.setString(2, student.getSurname());
            preparedStatement.setString(3, student.getSchool());
            preparedStatement.setInt(4, student.getSemester());
            preparedStatement.setInt(5, student.getPassed());

            int rowsAffected = preparedStatement.executeUpdate();
            return rowsAffected;
        } catch (SQLException ex) {
            System.out.println("SQL Exception: " + ex);
            return 0;
        }
    }

    public static List<Student> getAllStudents() {
        List<Student> list = new ArrayList<>();
        String sql = "SELECT * FROM students";

        try {
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            PreparedStatement ps = conn.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                Student student = new Student();
                student.setName(rs.getString(1));
                student.setSurname(rs.getString(2));
                student.setSchool(rs.getString(3));
                student.setSemester(rs.getString(4));
                student.setPassed(rs.getString(5));
                list.add(student);
            }
            conn.close();
        } catch (NullPointerException | SQLException ex) {
            System.out.println(ex);
        }
        return list;
    }

    public static int delete(String fn) {
        try {
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            String query = "DELETE FROM students WHERE firstname = ?";

            try (PreparedStatement preparedStatement = conn.prepareStatement(query)) {
                preparedStatement.setString(1, fn);

                int rowsAffected = preparedStatement.executeUpdate();

                return rowsAffected;
            }
        } catch (SQLException ex) {
            System.out.println("SQL Exception: " + ex);
            return 0;
        }
    }

    public static Student getStudentByfn(String fn) {
        Student student = new Student();
        String sql = "SELECT * FROM students WHERE firstname=?";

        try {
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, fn);
            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                student.setName(rs.getString(1));
                student.setSurname(rs.getString(2));
                student.setSchool(rs.getString(3));
                student.setSemester(rs.getString(4));
                student.setPassed(rs.getString(5));
            }
            conn.close();
        } catch (SQLException ex) {
            System.out.println(ex);
        }
        return student;
    }

    public static int update(Student student) {
        int status = 0;
        String sql = "UPDATE students SET firstname=?, lastname=?, school=?, semester=? , passed=?  WHERE firstname=?";
        

        try {
            Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            PreparedStatement ps = conn.prepareStatement(sql);
            ps.setString(1, student.getName());
            ps.setString(2, student.getSurname());
            ps.setString(3, student.getSchool());
            ps.setInt(4, student.getSemester());
            ps.setInt(5, student.getPassed());
            ps.setString(6, student.getName());
            status = ps.executeUpdate();
            conn.close();
        } catch (NullPointerException | SQLException ex) {
            System.out.println(ex);
        }
        return status;
    }

}
