import javax.swing.*;
import java.awt.*;
import java.io.*;
import java.awt.event.*;

public class Launchpage extends JFrame {
    private JTextField emailTextField;
    private JButton signInButton;
    private JButton enterPageButton;
    private JLabel messageLabel;

    public Launchpage() {
        // Set up the JFrame
        setTitle("Επισήμη σελίδα Βιβλιοθήκης");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setLocationRelativeTo(null);

        // Create the email text field
        emailTextField = new JTextField(20);

        // Create the sign-in button
        signInButton = new JButton("Εγγραφή");
         signInButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
                new MyFrame();
            }
        });

        

        // Create the enter page button
        enterPageButton = new JButton("Σύνδεση");
         enterPageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String enteredEmail = emailTextField.getText();
                if (emailExists(enteredEmail)) {
                    JOptionPane.showMessageDialog(null, "Επιτυχής σύνδεση!", "Επιτυχία!", JOptionPane.INFORMATION_MESSAGE);
                    // Code to proceed to the next page or perform necessary actions
                    dispose();
                    new mainpage();
                } else {
                    JOptionPane.showMessageDialog(null, "Μη έγκυρο email. Παρακαλώ ελέγξτε το email σας.", "Λάθος!", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        //create the mesasge lbl
        messageLabel = new JLabel();
        messageLabel.setHorizontalAlignment(SwingConstants.CENTER);
        messageLabel.setFont(new Font("Arial", Font.BOLD, 16));
        messageLabel.setForeground(Color.RED);
        messageLabel.setText("Συνδέσου με το email Ή κάνε εγγραφη για να προλάβεις όλα τα βιβλια!");

        //
        JPanel messagepanel=new JPanel();
        messagepanel.setLayout(new FlowLayout());
        messagepanel.add(messageLabel);


        // Create panels to hold the components
        JPanel inputPanel = new JPanel(new FlowLayout());
        inputPanel.add(new JLabel("Email:"));
        inputPanel.add(emailTextField);

        JPanel buttonPanel = new JPanel(new FlowLayout());
        buttonPanel.add(signInButton);
        buttonPanel.add(enterPageButton);

        // Add the panels and label to the JFrame
        add(messagepanel,BorderLayout.NORTH);
        add(inputPanel, BorderLayout.CENTER);
        add(buttonPanel, BorderLayout.PAGE_END);

        ImageIcon bye=new ImageIcon("exit.png");

        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                int option = JOptionPane.showOptionDialog(null,"Θέλετε να βγείτε άπο την εφαρμογή?","",JOptionPane.YES_NO_OPTION,JOptionPane.WARNING_MESSAGE,bye,null,0);
                if (option == JOptionPane.YES_OPTION) {
                    System.exit(0);
                }
            }
        });

        // Pack and display the JFrame
        pack();
        setVisible(true);
    }


     private boolean emailExists(String email) {
        try {
            FileReader fileReader = new FileReader("emails.txt");
            BufferedReader bufferedReader = new BufferedReader(fileReader);
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                if (line.equals(email)) {
                    bufferedReader.close();
                    return true;
                }
            }
            bufferedReader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return false;
    }
}
