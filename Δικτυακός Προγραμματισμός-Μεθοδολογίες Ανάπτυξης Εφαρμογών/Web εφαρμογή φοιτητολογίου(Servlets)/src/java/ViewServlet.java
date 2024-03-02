
import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.util.*;

/**
 *
 */

@WebServlet(name = "ViewServlet", urlPatterns = {"/view"})
public class ViewServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<DOCTYPE hmlt>");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>View Students</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>view all students in databse</h1>");

        List<Student> list = StudentDao.getAllStudents();
        out.print("<table border='1' width='100%'");
        out.print("<tr><th>Name</th><th>Last</th><th>School</th><th>semester</th><th>passed</th><th>Edit</th><th>Delete</th></tr>");
        for (Student s : list) {
            out.print("<tr>"
                    + "<td>" + s.getName() + "</td>"
                    + "<td>" + s.getSurname() + "</td>"
                    + "<td>" + s.getSchool() + "</td>"
                    + "<td>" + s.getSemester() + "</td>"
                    + "<td>" + s.getPassed() + "</td>"
                     + "<td><a href='./edit?firstname=" + s.getName()+ "'>edit</a></td>"
                    + "<td><a href='./delete?firtsname=" + s.getName() + "'>delete</a></td>"
                    + "</tr>");
        }
        out.print("</table>");

        out.println("</body>");
        out.println("</html>");

        out.close();
    }

}
