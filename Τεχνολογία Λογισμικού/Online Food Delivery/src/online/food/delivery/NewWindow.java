package online.food.delivery;

import java.awt.*;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import javax.swing.*;

public class NewWindow extends JFrame {

    private DatabaseConnection db;
    private int currentUserId;
    private JPanel cartPanel;
    private Map<Product, Integer> cartItems = new HashMap<>();
    private String userEmail;
    private double total = 0;

    public NewWindow(int userId, String email, DatabaseConnection db) {
        this.currentUserId = userId;
        this.userEmail = email;
        this.db = db;

        setTitle("Online Food Order System");
        setSize(1000, 600);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());

        // Top panel for user info and nav bar
        JPanel topPanel = createTopPanel();
        add(topPanel, BorderLayout.NORTH);

        // Main content panel
        JPanel contentPanel = new JPanel(new BorderLayout());

        JPanel productsPanel = createProductsPanel();
        JScrollPane scrollPane = new JScrollPane(productsPanel);
        scrollPane.setHorizontalScrollBarPolicy(
                JScrollPane.HORIZONTAL_SCROLLBAR_NEVER
        );
        scrollPane.setVerticalScrollBarPolicy(
                JScrollPane.VERTICAL_SCROLLBAR_AS_NEEDED
        );
        contentPanel.add(scrollPane, BorderLayout.CENTER);

        // Cart area on the right
        JPanel cartPanel = createCartPanel();
        contentPanel.add(cartPanel, BorderLayout.EAST);

        add(contentPanel, BorderLayout.CENTER);
    }

    private JPanel createTopPanel() {
        JPanel topPanel = new JPanel(new BorderLayout());

        // User info on the left
        JPanel userPanel = createUserPanel();
        topPanel.add(userPanel, BorderLayout.WEST);

        // Nav bar on the right
        JPanel navBar = createNavBar();
        topPanel.add(navBar, BorderLayout.EAST);

        return topPanel;
    }

    private JPanel createUserPanel() {
        JPanel userPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
        userPanel.add(new JLabel("User: " + userEmail));
        return userPanel;
    }

    private JPanel createNavBar() {
        JPanel navBar = new JPanel(new FlowLayout(FlowLayout.RIGHT));
        JButton logoutButton = new JButton("Logout");
        JButton exitButton = new JButton("Exit");

        logoutButton.addActionListener(e -> logout());
        exitButton.addActionListener(e -> System.exit(0));

        navBar.add(logoutButton);
        navBar.add(exitButton);
        return navBar;
    }

    private JPanel createProductsPanel() {
        JPanel productsPanel = new JPanel(new GridBagLayout());
        GridBagConstraints gbc = new GridBagConstraints();
        gbc.gridx = 0;
        gbc.gridy = 0;
        gbc.insets = new Insets(5, 5, 5, 5);
        gbc.anchor = GridBagConstraints.NORTHWEST;

        List<Product> products = db.getProducts();

        for (Product product : products) {
            JPanel productPanel = new JPanel();
            productPanel.setLayout(
                    new BoxLayout(productPanel, BoxLayout.Y_AXIS)
            );
            productPanel.setBorder(BorderFactory.createEtchedBorder());
            productPanel.setPreferredSize(new Dimension(220, 100));

            productPanel.add(new JLabel(product.getName()));
            productPanel.add(new JLabel("$" + product.getPrice()));
            productPanel.add(new JLabel(product.getDescription()));
            JButton addToCartButton = new JButton("Add to Cart");
            addToCartButton.addActionListener(e -> addToCart(product));
            productPanel.add(addToCartButton);

            productsPanel.add(productPanel, gbc);

            gbc.gridx++;
            if (gbc.gridx > 2) {
                gbc.gridx = 0;
                gbc.gridy++;
            }
        }

        gbc.gridx = 0;
        gbc.gridy++;
        gbc.weightx = 1;
        gbc.weighty = 1;
        gbc.fill = GridBagConstraints.BOTH;
        productsPanel.add(Box.createGlue(), gbc);

        return productsPanel;
    }

    private JPanel createCartPanel() {
        JPanel panel = new JPanel();
        panel.setLayout(new BorderLayout());
        panel.setBorder(BorderFactory.createTitledBorder("Cart"));

        cartPanel = new JPanel();
        cartPanel.setLayout(new BoxLayout(cartPanel, BoxLayout.Y_AXIS));
        JScrollPane scrollPane = new JScrollPane(cartPanel);
        panel.add(scrollPane, BorderLayout.CENTER);

        JPanel buttonPanel = new JPanel(
                new FlowLayout(FlowLayout.CENTER, 10, 10)
        );
        JButton completeOrderButton = new JButton("Complete Order");
        completeOrderButton.addActionListener(e -> completeOrder());
        JButton clearCartButton = new JButton("Clear Cart");
        clearCartButton.addActionListener(e -> clearCart());
        buttonPanel.add(completeOrderButton);
        buttonPanel.add(clearCartButton);
        panel.add(buttonPanel, BorderLayout.SOUTH);

        return panel;
    }

    private void addToCart(Product product) {
        cartItems.put(product, cartItems.getOrDefault(product, 0) + 1);
        updateCartDisplay();
    }

    private void updateCartDisplay() {
        cartPanel.removeAll();
        for (Map.Entry<Product, Integer> entry : cartItems.entrySet()) {
            Product item = entry.getKey();
            int quantity = entry.getValue();
            JPanel itemPanel = new JPanel();
            itemPanel.setLayout(new BoxLayout(itemPanel, BoxLayout.X_AXIS));
            itemPanel.setBorder(BorderFactory.createEmptyBorder(5, 5, 5, 5));

            JLabel itemName = new JLabel(
                    item.getName()
                    + " x"
                    + quantity
                    + " - $"
                    + String.format("%.2f", item.getPrice() * quantity)
            );
            itemPanel.add(itemName);

            total = total + item.getPrice();

            cartPanel.add(itemPanel);
        }

        JLabel totalLabel = new JLabel("Total: $" + String.format("%.2f", total));
        totalLabel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));
        cartPanel.add(totalLabel);

        cartPanel.revalidate();
        cartPanel.repaint();
    }

    private void completeOrder() {
        if (cartItems.isEmpty()) {
            JOptionPane.showMessageDialog(
                    this,
                    "Your cart is empty!",
                    "Error",
                    JOptionPane.ERROR_MESSAGE
            );
            return;
        }

        StringBuilder orderDetails = new StringBuilder("Order Details:\n");
        for (Map.Entry<Product, Integer> entry : cartItems.entrySet()) {
            Product product = entry.getKey();
            int quantity = entry.getValue();
            double itemTotal = product.getPrice() * quantity;

            orderDetails
                    .append(product.getName())
                    .append(" x")
                    .append(quantity)
                    .append(" - $")
                    .append(String.format("%.2f", itemTotal))
                    .append("\n");
        }

        orderDetails.append("\nTotal: $").append(String.format("%.2f", total));

        int choice = JOptionPane.showConfirmDialog(
                this,
                orderDetails.toString() + "\n\nConfirm your order?",
                "Order Confirmation",
                JOptionPane.YES_NO_OPTION
        );

        if (choice == JOptionPane.YES_OPTION) {
            if (db.saveOrder(currentUserId, cartItems, total)) {
            } else {
                JOptionPane.showMessageDialog(
                        this,
                        "Error saving order. Please try again.",
                        "Error",
                        JOptionPane.ERROR_MESSAGE
                );
            }
        }

        if (choice == JOptionPane.YES_OPTION) {
            if (db.saveOrder(currentUserId, cartItems, total)) {
                int orderId = db.getLastOrderId(currentUserId);
                if (orderId != -1) {
                    SwingUtilities.invokeLater(() -> {
                        OrderCompletionWindow completionWindow
                                = new OrderCompletionWindow(db, orderId, total);
                        completionWindow.setVisible(true);
                    });
                }
            } else {
                JOptionPane.showMessageDialog(
                        this,
                        "Error saving order. Please try again.",
                        "Error",
                        JOptionPane.ERROR_MESSAGE
                );
            }
        }
    }

    private void clearCart() {
        total = 0;
        cartItems.clear();
        updateCartDisplay();
    }

    private void logout() {
        this.dispose();
        new MainWindow().show();
    }
}
