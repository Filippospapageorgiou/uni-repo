import java.awt.*;
import javax.swing.*;
import java.awt.event.*;
import javax.swing.border.*;
import java.io.*;




public class MyFrame extends JFrame {
    JTextField name, number, address;
    JButton submitButton,nextpagebtn,returnpage;
    JPanel infopanel, mainpanel;
    JLabel Jname=new JLabel("(*)Όνομα: "),JnumbeR=new JLabel("(*)Τηλεφώνο: "),Jaddrer=new JLabel("(*)Email: ");
    public MyFrame() {
        this.setSize(500, 500);
        this.setTitle("Books Application Manager");
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);


        //-MAIN PANEL MANAGER
        mainpanel = new JPanel();
        mainpanel.setLayout(new BorderLayout());
        mainpanel.setBorder(new EmptyBorder(10, 10, 10, 10));
        //--------------------------------------------------
        // BOOKS PANEL TO 






         
        //-------------------------------------------------------
        //-INFO PANEL TO SUMBIT 
        infopanel = new JPanel();
        infopanel.setBorder(BorderFactory.createTitledBorder("Βάλε τα στοιχεία σου για να κάνεις εγγραφή :)"));
        infopanel.setLayout(new GridLayout(5,1));

        ImageIcon yes=new ImageIcon("yes.png");
        ImageIcon no=new ImageIcon("no.png");
        ImageIcon bye=new ImageIcon("exit.png");

        name = new JTextField(20);
        number = new JTextField(20);
        address = new JTextField(20);
        
        submitButton=new JButton("Εγγραφή");
        submitButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String msg1 = name.getText();
                String msg2 = number.getText();
                String msg3 = address.getText();
                if (!msg1.isEmpty() && !msg2.isEmpty() && !msg3.isEmpty()) {
                     if(saveEmailToFile(msg3)){
                      String line = "Όνομα : " + msg1 + "\n" + "Τηλεφώνο : "  +  msg2 + "\n" + "Email : " + msg3;
                      JOptionPane.showMessageDialog(null,line,"Τελέια!",0,yes);
                      dispose();
                      new mainpage();
                    }

                }
                else{
                    String line = "Πρεπει να συμπληρωσείς όλα τα στοιχεία για να κάνεις την αίτηση!!";
                    JOptionPane.showMessageDialog(null,line,"Λάθος!",0,no);
                }
            }
        });

        returnpage=new JButton("Επιστροφή στην αρχική σελίδα");
        returnpage.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                dispose();
                new Launchpage();
            }
        });

        infopanel.add(Jname);
        infopanel.add(name);
        infopanel.add(JnumbeR);
        infopanel.add(number);
        infopanel.add(Jaddrer);
        infopanel.add(address);
        infopanel.add(submitButton);
        infopanel.add(returnpage);



        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                int option = JOptionPane.showOptionDialog(null,"Θέλετε να βγείτε άπο την εφαρμογή?","",JOptionPane.YES_NO_OPTION,JOptionPane.WARNING_MESSAGE,bye,null,0);
                if (option == JOptionPane.YES_OPTION) {
                    System.exit(0);
                }
            }
        });

        mainpanel.add(infopanel, BorderLayout.CENTER);
        add(mainpanel);
        pack();
        this.setLocationRelativeTo(null);
        this.setVisible(true);
    }

   private boolean saveEmailToFile(String email) { 
    boolean flag=true;
    try {
        // Read the existing file content to check if email exists
        FileReader fileReader = new FileReader("emails.txt");
        BufferedReader bufferedReader = new BufferedReader(fileReader);
        String line;
        boolean emailExists = false;
        while ((line = bufferedReader.readLine()) != null) {
            if (line.equals(email)) {
                emailExists = true;
                break;
            }
        }
        bufferedReader.close();
        
        if (emailExists) {
            flag=false;
            JOptionPane.showMessageDialog(null, "Το email υπάρχει ήδη!", "Λάθος!", JOptionPane.ERROR_MESSAGE);
        } else {
            // Append the email to the file
            FileWriter fileWriter = new FileWriter("emails.txt", true);
            BufferedWriter bufferedWriter = new BufferedWriter(fileWriter);
            bufferedWriter.write(email);
            bufferedWriter.newLine();
            bufferedWriter.close();
            
            JOptionPane.showMessageDialog(null, "Το email αποθηκεύτηκε με επιτυχία!", "Επιτυχία!", JOptionPane.INFORMATION_MESSAGE);
        }
    } catch (IOException e) {
        e.printStackTrace();
    }
    return flag; 
}

}