import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.border.*;

public class mainpage extends JFrame{
    JPanel mainpanel=new JPanel(),leftpanel=new JPanel(),infopanel=new JPanel();
    JLabel messageLabel=new JLabel(),addres=new JLabel("Διεθυνση: "),code=new JLabel("Ταχυδρομικός κώδικας: ");
    JTextArea txt=new JTextArea();
    JButton erase=new JButton("Κάθαρισε");
    JTextField add=new JTextField(20),co=new JTextField(20);
    mainpage(){
        this.setSize(600,600);
        this.setTitle("Books Library");
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setLayout(new BorderLayout());

        mainpanel.setLayout(new BorderLayout());
        mainpanel.setBorder(new EmptyBorder(10, 10, 10, 10));
        
        ImageIcon icon=new ImageIcon("book.png");
        JLabel iconLabel = new JLabel(icon);
        JButton iconbutton=new JButton(icon);
        

        messageLabel.setHorizontalAlignment(SwingConstants.CENTER);
        messageLabel.setFont(new Font("Arial", Font.BOLD, 16));
        messageLabel.setForeground(Color.RED);
        messageLabel.setText("Νοικίασε όλα τα Βιβλία που θα χρείαστεις Για το Πανεπηστημίο Σου");

        txt.setSize(100,20);
        txt.setEditable(false);
        JScrollPane scrollPane =new JScrollPane(txt);
        mainpanel.add(txt,BorderLayout.NORTH);
        mainpanel.add(erase,BorderLayout.PAGE_END);


        leftpanel.setLayout(new GridLayout(10,1));
        String[] books = {
            "C++",
            "C",
            "JAVA",
            "Python",
            "Δίκτυα 1",
            "Δικτύα 2",
            "Μαθηματικα 1",
            "Αλγόριθμοι",
            "Λειτουργικα 1",
            "Πιθανότητες"
        };

    
        for (String book : books) {
            JButton button = new JButton(book);
            button.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    JButton source = (JButton) e.getSource();
                    String bookName = source.getText();
                    source.setEnabled(false); // Disable the button
                    txt.append(bookName+"\n");
                }
            });
            leftpanel.add(button);
        }


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

         erase.addActionListener(new ActionListener() {
                public void actionPerformed(ActionEvent e) {
                    Component[] components = leftpanel.getComponents();
                    for (Component component : components) {
                     if (component instanceof JButton) {
                        JButton button = (JButton) component;
                        button.setEnabled(true);
                        }
                    } 
                 txt.setText("");
                }
            });

        infopanel.setLayout(new GridLayout(2,2));
        infopanel.setBorder(BorderFactory.createTitledBorder("Βάλε την Διεθυνση σου για παραλάβη!! :)"));
        infopanel.add(addres);
        infopanel.add(add);
        infopanel.add(code);
        infopanel.add(co);
        mainpanel.add(infopanel,BorderLayout.CENTER);

        ImageIcon yes=new ImageIcon("yes.png");
        ImageIcon no=new ImageIcon("no.png");

        iconbutton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                String msg1 = add.getText();
                String msg2 = co.getText();
                if (!msg1.isEmpty() && !msg2.isEmpty()) {
                       String line="Τέλεια τα βιβλία θα είναι στην πόρτα σου σε 10 μέρες!";
                      JOptionPane.showMessageDialog(null,line,"Τελέια!",0,yes);
                      dispose();
                }
                else{
                    String line = "Πρεπει να συμπληρωσείς όλα τα στοιχεία για να κάνεις την αίτηση!!";
                    JOptionPane.showMessageDialog(null,line,"Λάθος!",0,no);
                }
            }
        });




         


    

        
        add(iconbutton,BorderLayout.EAST);
        add(messageLabel,BorderLayout.NORTH);
        add(mainpanel,BorderLayout.CENTER);
        add(leftpanel,BorderLayout.WEST);
        pack();
        this.setVisible(true);
    }
}