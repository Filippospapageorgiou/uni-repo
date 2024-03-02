
package PROJECT;


import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.stage.Stage;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.*;


public class Main extends Application {
    @Override
    public void start(Stage stage)throws Exception{
        GridPane mygrid = new GridPane();
        String imagePath="recources/login.png";
        mygrid.setPrefSize(400, 400);
        mygrid.setHgap(10);
        mygrid.setVgap(10);
        mygrid.setAlignment(Pos.CENTER);
        mygrid.setPadding(new Insets(20));

        Label lbl0 = new Label("Συμπληρώστε τους κωδικούς για να συνδεθείτε με την Βάση");
        lbl0.setMaxSize(Double.MAX_VALUE, Double.MAX_VALUE);
        GridPane.setMargin(lbl0, new Insets(0, 0, 20, 0));

        Label lbl1 = new Label("Username");
        Label lbl2 = new Label("Password");

        Image image = new Image(getClass().getResourceAsStream(imagePath));
        TextField tf = new TextField();
        PasswordField pass = new PasswordField();

        Button bt1 = new Button();
        bt1.setGraphic(new ImageView(image));
        bt1.setPrefHeight(20);
        bt1.prefWidth(60);
        bt1.setStyle("fx-font-size: 12px");
        bt1.setOnAction(e->handleLoginButton(tf.getText(),pass.getText()));
        

        HBox buttonBox = new HBox(bt1);
        buttonBox.setAlignment(Pos.CENTER);

        mygrid.add(lbl0, 0, 0, 2, 1);
        mygrid.add(lbl1, 0, 1);
        mygrid.add(tf, 1, 1);
        mygrid.add(lbl2, 0, 2);
        mygrid.add(pass, 1, 2);
        mygrid.add(buttonBox, 0, 3, 2, 1);

        tf.setOnKeyPressed(e -> {
            if (e.getCode().equals(javafx.scene.input.KeyCode.ENTER)) {
                handleLoginButton(tf.getText(), pass.getText());
            }
        });

        pass.setOnKeyPressed(e -> {
            if (e.getCode().equals(javafx.scene.input.KeyCode.ENTER)) {
                handleLoginButton(tf.getText(), pass.getText());
            }
        });
        

        Scene myScene = new Scene(mygrid);
        stage.setScene(myScene);
        stage.setTitle("Σελίδα Σύνδεσης");
        stage.show();
    }

    private void handleLoginButton(String username, String pass) {
         if (username.isEmpty() || pass.isEmpty()){
            Image Error_image = new Image(getClass().getResourceAsStream("recources/error.png"));
            showAlert(AlertType.ERROR, "Σφάλμα", "Και τα δύο πεδία πρέπει να συμπληρωθούν.",Error_image);
         }
         else{
            DBconnect ob=new DBconnect(username,pass);
            if(ob.checkIfUserExists()){
              Image DB_iamage = new Image(getClass().getResourceAsStream("recources/database.png"));
              showAlert(AlertType.INFORMATION, "Σύνδεση", "Σύνδεση\nUsername: " + username + "\nPassword: " + pass,DB_iamage);
              newWindow newwindow = new newWindow(ob);
              newwindow.show(); 
            }
            else{
                Image Error_image = new Image(getClass().getResourceAsStream("recources/error.png"));
                showAlert(AlertType.ERROR, "Σφάλμα", "Δεν ύπαρχει αύτος ο χρήστης στην ΒΑΣΗ ΔΕΔΟΜΕΝΩΝ του συστήματος",Error_image);
            }
         }
    }
    
    private void showAlert(AlertType alertType, String title, String content,Image customImage) {
        Alert alert = new Alert(alertType);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(content);
        ImageView custoImageView = new ImageView(customImage);
        alert.getDialogPane().setGraphic(custoImageView);;
        alert.showAndWait();
    }
    public static void main(String[] args) {
        launch(args);
    }
}
