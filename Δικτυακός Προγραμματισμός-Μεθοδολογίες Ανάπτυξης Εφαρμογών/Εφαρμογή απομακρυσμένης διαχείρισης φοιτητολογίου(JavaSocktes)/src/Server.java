
import java.io.IOException;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {

    static final int SERVER_PORT = 9991;

    public static void main(String[] args) {
        try {
            ServerSocket serverSocket = new ServerSocket(SERVER_PORT);
            System.out.println("SERVER IS RUNNING...");

            while (true) {
                System.out.println("----------------------");
                System.out.println("Waiting for a client...");

                Socket socket = serverSocket.accept();
                System.out.println("Client accepted");

                // Create a new thread for each client
                Thread clientHandler = new Thread(new ClientHandler(socket));
                clientHandler.start();
            }
        } catch (IOException ex) {
            System.out.println(ex);
        }
    }
}

class ClientHandler implements Runnable {

    private final Socket clientSocket;

    public ClientHandler(Socket socket) {
        this.clientSocket = socket;
    }

    @Override
    public void run() {
        try {
            Scanner in = new Scanner(clientSocket.getInputStream());
            PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);

            System.out.println("-----start serving-------");
            out.println("Welcome to DatabaseServer!");
            out.println("Connect to the database client!");
            out.println("GIVE USERNAME AND PASSWORD!");

            String username, password;
            ServerDao db;

            do {
                out.println("username:");
                username = in.nextLine();
                out.println("password:");
                password = in.nextLine();
                db = new ServerDao(username, password);
                if (db.checkIfUserExists()) {
                    out.println("TRUE");
                }
                System.out.println("Client gave:");
                System.out.println("username:" + username);
                System.out.println("password:" + password);
            } while (!db.checkIfUserExists());

            String lastname, firstname, school;
            int semester, passed;
            String result;

            while (true) {
                out.println("--------------------------");
                out.println("MENU BAR!!");
                out.println("1.Look with lastname");
                out.println("2.Register new student in Database");
                out.println("3.EXIT");
                out.println("Choice:");
                int choice = in.nextInt();
                in.nextLine();

                if (choice == 1) {
                    out.println("--------------------------");
                    out.println("Give lastname to search");
                    lastname = in.nextLine();
                    result = db.SelectbySurrname(lastname);
                    if (result != null) {
                        out.println("RESULT : " + result);
                    } else {
                        out.println("Lastname : " + lastname + " Not in database");
                    }
                } else if (choice == 2) {
                    out.println("--------------------------");
                    out.println("Give the data to register");
                    out.println("Firstname:");
                    firstname = in.nextLine();
                    out.println("Lastname:");
                    lastname = in.nextLine();
                    out.println("School:");
                    school = in.nextLine();
                    out.println("semester:");
                    semester = in.nextInt();
                    out.println("Passed:");
                    passed = in.nextInt();
                    out.println(db.insertRow(firstname, lastname, school, semester, passed));
                } else if (choice == 3) {
                    break;
                }
            }
        } catch (IOException ex) {
            System.out.println("Error handling client: " + ex);
        } finally {
            try {
                clientSocket.close();
            } catch (IOException ex) {
                System.out.println("Error closing client socket: " + ex);
            }
        }
    }
}
