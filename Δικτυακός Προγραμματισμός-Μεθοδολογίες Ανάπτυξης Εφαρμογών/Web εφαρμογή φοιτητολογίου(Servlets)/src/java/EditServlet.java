
import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

@WebServlet(name = "EditServlet", urlPatterns = {"/edit"})
public class EditServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        out.println("<!DOCTYPE html>");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Update Employee</title>");
        out.println("</head>");
        out.println("<body>");

        out.println("<h1>Update Student</h1>");
        String fn = request.getParameter("firstname");

        Student student = StudentDao.getStudentByfn(fn);

        out.print("<form action='./edit' method='POST'>");
        out.print("<table>");
        out.print("<tr><td>Name:</td><td><input type='text' name='firstname' value='" + student.getName() + "'/></td></tr>");
        out.print("<tr><td>Lastname:</td><td><input type='text' name='lastname' value='" + student.getSurname() + "'/></td></tr>");
        out.print("<tr><td>School:</td><td><input type='text' name='school' value='" + student.getSchool() + "'/></td></tr>");
        out.print("<tr><td>Semester:</td><td><input type='number' name='semester' value='" + student.getSemester() + "'/></td></tr>");
        out.print("<tr><td>Passed:</td><td><input type='number' name='passed' value='" + student.getPassed() + "'/></td></tr>");
        out.print("</td></tr>");
        out.print("<tr><td colspan='2'><input type='submit' value='Save'/></td></tr>");
        out.print("</table>");
        out.print("</form>");
        out.println("</body>");
        out.println("</html>");

        out.close();
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        Student student = new Student();
        student.setName(request.getParameter("firstname"));
        student.setSurname(request.getParameter("lastname"));
        student.setSchool(request.getParameter("school"));
        student.setSemester(request.getParameter("semester"));
        student.setPassed(request.getParameter("passed"));

        int status = StudentDao.update(student);

        if (status > 0) {
            response.sendRedirect("./landingpage.html");
        } else {
            out.println("<h3 style='color:red;'>Sorry! unable to update record</h3>");
        }
        out.close();
    }
}
