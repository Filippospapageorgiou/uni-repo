package online.food.delivery;

import java.awt.*;
import javax.swing.*;
import javax.swing.border.EmptyBorder;

public class MainWindow {

    private JFrame frame;
    private DatabaseConnection db;
    private JTextField emailField;
    private JPasswordField passwordField;

    public MainWindow() {
        db = new DatabaseConnection();
        createLoginWindow();
    }

    private void createLoginWindow() {
        frame = new JFrame("Online Food Order System");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 300);
        frame.setLayout(new BorderLayout());

        // Create a panel for the greeting message
        JPanel greetingPanel = new JPanel();
        greetingPanel.setBackground(new Color(70, 130, 180)); // Steel blue color
        greetingPanel.setLayout(new BoxLayout(greetingPanel, BoxLayout.Y_AXIS));
        greetingPanel.setBorder(new EmptyBorder(20, 20, 20, 20));

        JLabel welcomeLabel = new JLabel("Welcome to Online Food Order");
        welcomeLabel.setFont(new Font("Arial", Font.BOLD, 20));
        welcomeLabel.setForeground(Color.WHITE);
        welcomeLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        JLabel subLabel = new JLabel("Please login or sign up to continue");
        subLabel.setFont(new Font("Arial", Font.PLAIN, 14));
        subLabel.setForeground(Color.WHITE);
        subLabel.setAlignmentX(Component.CENTER_ALIGNMENT);

        greetingPanel.add(welcomeLabel);
        greetingPanel.add(Box.createRigidArea(new Dimension(0, 10)));
        greetingPanel.add(subLabel);

        // Create a panel for login components
        JPanel loginPanel = new JPanel();
        loginPanel.setLayout(new GridBagLayout());
        loginPanel.setBorder(new EmptyBorder(20, 20, 20, 20));
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridwidth = GridBagConstraints.REMAINDER;
        gbc.fill = GridBagConstraints.HORIZONTAL;
        gbc.insets = new Insets(5, 5, 5, 5);

        JLabel emailLabel = new JLabel("Email:");
        emailField = new JTextField(200);
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField(200);

        JButton loginButton = new JButton("Login");
        loginButton.setBackground(new Color(46, 139, 87));
        loginButton.setForeground(Color.WHITE);
        loginButton.addActionListener(e -> login());

        JButton signupButton = new JButton("Sign Up");
        signupButton.setBackground(new Color(70, 130, 180));
        signupButton.addActionListener(e -> signup());

        loginPanel.add(emailLabel, gbc);
        loginPanel.add(emailField, gbc);
        loginPanel.add(passwordLabel, gbc);
        loginPanel.add(passwordField, gbc);
        loginPanel.add(Box.createRigidArea(new Dimension(0, 10)), gbc);
        loginPanel.add(loginButton, gbc);
        loginPanel.add(signupButton, gbc);

        frame.add(greetingPanel, BorderLayout.NORTH);
        frame.add(loginPanel, BorderLayout.CENTER);

        frame.getRootPane().setDefaultButton(loginButton);
    }

    private void login() {
        String email = emailField.getText();
        String password = new String(passwordField.getPassword());
        if (email == null
                || email.isEmpty()
                || !email.matches("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+.[A-Za-z]{2,4}")
                || password == null
                || password.isEmpty()) {
            JOptionPane.showMessageDialog(
                    frame,
                    "Email and password are required.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
            return;
        }
        if (db.loginUser(email, password)) {
            int userId = db.getUserId(email);
            if (userId != -1) {
                JOptionPane.showMessageDialog(frame, "Login successful!");
                openMainApplication(userId, email);
            } else {
                JOptionPane.showMessageDialog(
                        frame,
                        "Error retrieving user information.",
                        "Error",
                        JOptionPane.ERROR_MESSAGE
                );
            }
        } else {
            JOptionPane.showMessageDialog(
                    frame,
                    "Login failed. Please try again.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
        }
    }

    private void signup() {
        String email = emailField.getText();
        String password = new String(passwordField.getPassword());
        if (email == null
                || email.isEmpty()
                || !email.matches("[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+.[A-Za-z]{2,4}")
                || password == null
                || password.isEmpty()) {
            JOptionPane.showMessageDialog(
                    frame,
                    "Email and password are required.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
            return;
        }
        if (db.signupUser(email, password)) {
            JOptionPane.showMessageDialog(
                    frame,
                    "Sign up successful! You can now log in."
            );
            int userId = db.getUserId(email);
            if (userId != -1) {
                openMainApplication(userId, email);
            } else {
                JOptionPane.showMessageDialog(
                        frame,
                        "Error retrieving user information.",
                        "Error",
                        JOptionPane.ERROR_MESSAGE
                );
            }
        } else {
            JOptionPane.showMessageDialog(
                    frame,
                    "Sign up failed. Please try again.",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
        }
    }

    private void openMainApplication(int userId, String email) {
        SwingUtilities.invokeLater(() -> {
            NewWindow newWindow = new NewWindow(userId, email, db);
            newWindow.setVisible(true);
            frame.dispose();
        });
    }

    public void show() {
        try {
            UIManager.setLookAndFeel(
                    "com.sun.java.swing.plaf.nimbus.NimbusLookAndFeel"
            ); //Nimbus look and feel.
        } catch (Exception ignored) {
        }
        frame.setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(() -> {
            MainWindow window = new MainWindow();
            window.show();
        });
    }
}
