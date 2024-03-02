
import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Scanner;


public class Client {

    static final int SERVER_PORT = 9991;
    static final String SERVER_HOST = "localhost";
    static String username, password;

    public static void main(String[] args) {
        int choice, sem, passed;
        String lastname, firstname, school, check;

        try {
            Socket socket = new Socket(SERVER_HOST, SERVER_PORT);

            System.out.println("Local Socket: " + socket.getLocalSocketAddress());
            System.out.println("Remote Socket: " + socket.getRemoteSocketAddress());
            System.out.println("-------------------");

            Scanner userinput = new Scanner(System.in);
            Scanner in = new Scanner(socket.getInputStream());
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            System.out.println(in.nextLine());
            System.out.println(in.nextLine());
            System.out.println(in.nextLine());

            do {
                System.out.println(in.nextLine());
                username = userinput.nextLine();
                out.println(username);
                System.out.println(in.nextLine());
                password = userinput.nextLine();
                out.println(password);
                check = in.nextLine();
            } while (check.equals("TRUE"));

            while (true) {
                System.out.println(in.nextLine());
                System.out.println(in.nextLine());
                System.out.println(in.nextLine());
                System.out.println(in.nextLine());
                System.out.println(in.nextLine());
                System.out.println(in.nextLine());

                choice = userinput.nextInt();
                out.println(choice);
                userinput.nextLine();
                if(choice==1){
                    System.out.println(in.nextLine());
                    System.out.println(in.nextLine());
                    lastname = userinput.nextLine();
                    out.println(lastname);
                    System.out.println(in.nextLine());
                }    
 
                if(choice==2){
                   System.out.println(in.nextLine());
                   System.out.println(in.nextLine());
                   System.out.println(in.nextLine());
                   firstname = userinput.nextLine();
                   out.println(firstname);
                   System.out.println(in.nextLine());
                   lastname = userinput.nextLine();
                   out.println(lastname);
                   System.out.println(in.nextLine());
                   school = userinput.nextLine();
                   out.println(school);
                   System.out.println(in.nextLine());
                   sem = userinput.nextInt();
                   out.println(sem);
                   userinput.nextLine();
                   System.out.println(in.nextLine());
                   passed = userinput.nextInt();
                   out.println(passed);
                   userinput.nextLine();
                   System.out.println(in.nextLine());
                }
                if(choice==3)
                    break;
            }

            System.out.println("terminate connection..");
            socket.close();
            System.out.println("Connection closed");

        } catch (IOException ex) {
            System.out.println(ex);
        }
    }

}
