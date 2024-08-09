package online.food.delivery;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;

public class OrderCompletionWindow extends JFrame {

    private DatabaseConnection db;
    private int orderId;
    private double orderAmount;

    // Shipping address fields
    private JTextField addressLine1Field;
    private JTextField cityField;
    private JTextField postalCodeField;
    private JTextField countryField;

    // Payment details fields
    private JComboBox<String> paymentTypeComboBox;
    private JLabel amountLabel;

    public OrderCompletionWindow(
        DatabaseConnection db,
        int orderId,
        double orderAmount
    ) {
        this.db = db;
        this.orderId = orderId;
        this.orderAmount = orderAmount;

        setTitle("Complete Order #" + orderId);
        setSize(400, 300);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLayout(new BorderLayout());

        JPanel mainPanel = new JPanel(new GridLayout(0, 2, 10, 10));
        mainPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        // Shipping address fields
        mainPanel.add(new JLabel("Address Line 1:"));
        addressLine1Field = new JTextField(20);
        mainPanel.add(addressLine1Field);

        mainPanel.add(new JLabel("City:"));
        cityField = new JTextField(20);
        mainPanel.add(cityField);

        mainPanel.add(new JLabel("Postal Code:"));
        postalCodeField = new JTextField(20);
        mainPanel.add(postalCodeField);

        mainPanel.add(new JLabel("Country:"));
        countryField = new JTextField(20);
        mainPanel.add(countryField);

        // Payment details fields
        mainPanel.add(new JLabel("Payment Type:"));
        paymentTypeComboBox = new JComboBox<>(
            new String[] { "Credit Card", "PayPal", "Bank Transfer" }
        );
        mainPanel.add(paymentTypeComboBox);

        mainPanel.add(new JLabel("Amount:"));
        amountLabel = new JLabel(String.format("$%.2f", orderAmount));
        mainPanel.add(amountLabel);

        add(mainPanel, BorderLayout.CENTER);

        JButton submitButton = new JButton("Submit");
        submitButton.addActionListener(
            new ActionListener() {
                @Override
                public void actionPerformed(ActionEvent e) {
                    saveOrderDetails();
                }
            }
        );
        add(submitButton, BorderLayout.SOUTH);
    }

    private void saveOrderDetails() {
        String addressLine1 = addressLine1Field.getText();
        String city = cityField.getText();
        String postalCode = postalCodeField.getText();
        String country = countryField.getText();
        String paymentType = (String) paymentTypeComboBox.getSelectedItem();
        //check if null or empty
        if (
            addressLine1 == null ||
            addressLine1.isEmpty() ||
            city == null ||
            city.isEmpty() ||
            postalCode == null ||
            postalCode.isEmpty() ||
            country == null ||
            country.isEmpty()
        ) {
            JOptionPane.showMessageDialog(
                this,
                "Data are required to be filled in all fields.",
                "Error",
                JOptionPane.ERROR_MESSAGE
            );
            return;
        }

        boolean success = db.saveOrderCompletionDetails(
            orderId,
            addressLine1,
            city,
            postalCode,
            country,
            paymentType,
            orderAmount
        );
        if (success) {
            JOptionPane.showMessageDialog(
                this,
                "Order details saved successfully",
                "Success",
                JOptionPane.INFORMATION_MESSAGE
            );
            this.dispose();
        } else {
            JOptionPane.showMessageDialog(
                this,
                "Error saving order details",
                "Error",
                JOptionPane.ERROR_MESSAGE
            );
        }
    }
}
