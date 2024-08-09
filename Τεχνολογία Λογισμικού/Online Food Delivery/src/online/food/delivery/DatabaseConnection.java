package online.food.delivery;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class DatabaseConnection {

    static final String MARIADB_SUB = "jdbc:mariadb:";
    static final String DB_SERVER = "//localhost:3306/";
    static final String DB_NAME = "ofd";
    static String DB_USER = "ofdUser";
    static String DB_PASS = "ofdpass";
    final String MARIADB_DRIVER = "org.mariadb.jdbc.Driver";
    static final String DB_URL = MARIADB_SUB + DB_SERVER + DB_NAME;

    public boolean checkIfUserExists() {
        try {
            Class.forName(MARIADB_DRIVER);
            Connection conn = DriverManager.getConnection(
                    DB_URL,
                    DB_USER,
                    DB_PASS
            );
            conn.close();
            return true;
        } catch (ClassNotFoundException e) {
            System.out.println(
                    "MariaDB JDBC Driver not found: " + e.getMessage()
            );
            return false;
        } catch (SQLException ex) {
            System.out.println("SQL Exception: " + ex.getMessage());
            return false;
        }
    }

    public boolean loginUser(String email, String password) {
        String query = "SELECT * FROM users WHERE email = ? AND password = ?";
        try (
                Connection conn = DriverManager.getConnection(
                        DB_URL,
                        DB_USER,
                        DB_PASS
                );
                PreparedStatement pstmt = conn.prepareStatement(query)) {
                    pstmt.setString(1, email);
                    pstmt.setString(2, password);

                    try (ResultSet rs = pstmt.executeQuery()) {
                        return rs.next();
                    }
                } catch (SQLException ex) {
                    System.out.println("SQL Exception: " + ex.getMessage());
                    return false;
                }
    }

    public boolean signupUser(String email, String password) {
        String SignUpquery
                = "INSERT INTO users (email, password) VALUES (?, ?)";
        try (
                Connection conn = DriverManager.getConnection(
                        DB_URL,
                        DB_USER,
                        DB_PASS
                );
                PreparedStatement pstmt = conn.prepareStatement(SignUpquery)) {
                    pstmt.setString(1, email);
                    pstmt.setString(2, password);

                    int affectedRows = pstmt.executeUpdate();
                    return affectedRows > 0;
                } catch (SQLException ex) {
                    System.out.println("SQL Exception: " + ex.getMessage());
                    return false;
                }
    }

    public int getUserId(String email) {
        String query = "SELECT user_id FROM users WHERE email = ?";
        try (
                Connection conn = DriverManager.getConnection(
                        DB_URL,
                        DB_USER,
                        DB_PASS
                );
                PreparedStatement pstmt = conn.prepareStatement(query)) {
                    pstmt.setString(1, email);

                    try (ResultSet rs = pstmt.executeQuery()) {
                        if (rs.next()) {
                            return rs.getInt("user_id");
                        }
                    }
                } catch (SQLException ex) {
                    System.out.println("SQL Exception: " + ex.getMessage());
                }
                return -1; // Return -1 if user not found or error occurred
    }

    public List<Product> getProducts() {
        List<Product> products = new ArrayList<>();
        String query = "SELECT * FROM products";
        try (
                Connection conn = DriverManager.getConnection(
                        DB_URL,
                        DB_USER,
                        DB_PASS
                );
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery(query)) {
                    while (rs.next()) {
                        Product product = new Product(
                                rs.getInt("product_id"),
                                rs.getString("name"),
                                rs.getString("description"),
                                rs.getDouble("price"),
                                rs.getInt("stock")
                        );
                        products.add(product);
                    }
                } catch (SQLException ex) {
                    System.out.println("SQL Exception: " + ex.getMessage());
                }
                return products;
    }

    public boolean saveOrder(
            int userId,
            Map<Product, Integer> cartItems,
            double total
    ) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);

            // Start transaction
            conn.setAutoCommit(false);

            // Insert cart items
            String cartSql
                    = "INSERT INTO cart (user_id, product_id, quantity) VALUES (?, ?, ?)";
            pstmt = conn.prepareStatement(
                    cartSql,
                    Statement.RETURN_GENERATED_KEYS
            );

            for (Map.Entry<Product, Integer> entry : cartItems.entrySet()) {
                Product product = entry.getKey();
                int quantity = entry.getValue();
                pstmt.setInt(1, userId);
                pstmt.setInt(2, product.getId());
                pstmt.setInt(3, quantity);
                pstmt.executeUpdate();

                rs = pstmt.getGeneratedKeys();
                if (!rs.next()) {
                    throw new SQLException(
                            "Creating cart failed, no ID obtained."
                    );
                }
            }

            // Get the last inserted cart_id
            String getCartIdSql
                    = "SELECT MAX(cart_id) as last_cart_id FROM cart WHERE user_id = ?";
            pstmt = conn.prepareStatement(getCartIdSql);
            pstmt.setInt(1, userId);
            rs = pstmt.executeQuery();

            int cartId = -1;
            if (rs.next()) {
                cartId = rs.getInt("last_cart_id");
            }
            if (cartId == -1) {
                throw new SQLException("Creating cart failed, no ID obtained.");
            }

            // Insert into orders table
            String orderSql
                    = "INSERT INTO orders (user_id, order_status, total, cart_id) VALUES (?, ?, ?, ?)";
            pstmt = conn.prepareStatement(orderSql);
            pstmt.setInt(1, userId);
            pstmt.setString(2, "Pending");
            pstmt.setDouble(3, total);
            pstmt.setInt(4, cartId);
            pstmt.executeUpdate();

            // Commit transaction
            conn.commit();
            return true;
        } catch (SQLException e) {
            // Roll back in case of error
            try {
                if (conn != null) {
                    conn.rollback();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
            e.printStackTrace();
            return false;
        } finally {
            // Close resources
            try {
                if (rs != null) {
                    rs.close();
                }
                if (pstmt != null) {
                    pstmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public boolean saveOrderCompletionDetails(
            int orderId,
            String addressLine1,
            String city,
            String postalCode,
            String country,
            String paymentType,
            double amount
    ) {
        Connection conn = null;
        PreparedStatement pstmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            conn.setAutoCommit(false);

            // Insert shipping address
            String shippingSQL
                    = "INSERT INTO shipping_addresses (order_id, address_line1, city, postal_code, country) VALUES (?, ?, ?, ?, ?)";
            pstmt = conn.prepareStatement(shippingSQL);
            pstmt.setInt(1, orderId);
            pstmt.setString(2, addressLine1);
            pstmt.setString(3, city);
            pstmt.setString(4, postalCode);
            pstmt.setString(5, country);
            pstmt.executeUpdate();

            // Insert payment details
            String paymentSQL
                    = "INSERT INTO payment_details (order_id, payment_type, payment_status, amount) VALUES (?, ?, ?, ?)";
            pstmt = conn.prepareStatement(paymentSQL);
            pstmt.setInt(1, orderId);
            pstmt.setString(2, paymentType);
            pstmt.setString(3, "Completed"); // Assuming payment is completed
            pstmt.setDouble(4, amount);
            pstmt.executeUpdate();

            // Update order status
            String updateOrderSQL
                    = "UPDATE orders SET order_status = 'Completed' WHERE order_id = ?";
            pstmt = conn.prepareStatement(updateOrderSQL);
            pstmt.setInt(1, orderId);
            pstmt.executeUpdate();

            conn.commit();
            return true;
        } catch (SQLException e) {
            try {
                if (conn != null) {
                    conn.rollback();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
            e.printStackTrace();
            return false;
        } finally {
            try {
                if (pstmt != null) {
                    pstmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
    }

    public int getLastOrderId(int userId) {
        Connection conn = null;
        PreparedStatement pstmt = null;
        ResultSet rs = null;

        try {
            conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASS);
            String sql
                    = "SELECT MAX(order_id) as last_order FROM orders WHERE user_id = ?";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, userId);
            rs = pstmt.executeQuery();

            if (rs.next()) {
                return rs.getInt("last_order");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            try {
                if (rs != null) {
                    rs.close();
                }
                if (pstmt != null) {
                    pstmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        }
        return -1;
    }
}
