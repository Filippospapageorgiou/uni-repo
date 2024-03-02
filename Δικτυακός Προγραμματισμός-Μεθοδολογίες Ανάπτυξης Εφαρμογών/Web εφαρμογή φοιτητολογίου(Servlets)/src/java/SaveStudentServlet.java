

/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/JSP_Servlet/Servlet.java to edit this template
 */




import java.io.IOException;
import java.io.PrintWriter;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

/**
 *
 * @author filip
 */



@WebServlet(name = "SaveStudentServlet", urlPatterns = {"/savestudent"})
public class SaveStudentServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        Student ob = new Student();
        ob.setName(request.getParameter("firstname"));
        ob.setSurname(request.getParameter("lastname"));
        ob.setSchool(request.getParameter("school"));
        ob.setSemester(request.getParameter("semester"));
        ob.setPassed(request.getParameter("passed"));

        int status = StudentDao.save(ob);

        if (status>0) {
            out.print("<h3 style='color:blue;'>Record saved successfully!</h3>");
        } else {
            out.println("<h3 style='color:red;'>Sorry! unable to save record</h3>");
        }
        request.getRequestDispatcher("/add.html").include(request, response);
        out.close();
    }
}

