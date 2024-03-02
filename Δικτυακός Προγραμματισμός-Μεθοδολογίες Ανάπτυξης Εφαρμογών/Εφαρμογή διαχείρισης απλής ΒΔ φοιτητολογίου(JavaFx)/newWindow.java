package PROJECT;

import javafx.application.Application;
//import javafx.geometry.HPos;
//import javafx.geometry.Pos;
//import javafx.geometry.VPos;
//import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
//import javafx.scene.layout.BorderPane;
//import javafx.scene.layout.ColumnConstraints;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
//import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;




public class newWindow extends Application{
    private Label info_db,Lblastname,Lbpassed;
    private String output;
    private TextField suurname,semester,Tfsuurname2,Tfpassed,Tfsuurname3;
    private GridPane myLayout;
    private Button bt1,bt2,bt3,bt4,bt5,bt6;
    private HBox top = new HBox(10),left = new HBox(10),right = new HBox(10),buttom = new HBox(10),info=new HBox(2),buttons = new HBox(2),Hblastname = new HBox(2) , Hbpassed = new HBox(2);
    private VBox center = new VBox(10),left_info = new VBox(10);
    private TextArea textAr;
    private DBconnect ob;

    newWindow(DBconnect ob){
        this.ob=ob;
    }

    @Override
    public void start(Stage stage){
        makecontrols();
        addtoPanel();
        Scene myScene = new Scene(myLayout,650,650);
        stage.setScene(myScene);
        stage.show();
    }

    private void makecontrols(){
        bt1 = new Button("Ανακτήση ολών των εγγραφών");
        bt1.setOnAction(event->{
          output=ob.SelectAll();
          textAr.setText(output);
          output="";
        });

        bt2 = new Button("Καθαρισμός");
        bt2.setOnAction(event -> {
            output="";
            textAr.setText(output);
        });

        info_db = new Label("Δεδομένα της βασής STUDENTS της σχολής!");
       
        suurname = new TextField();
        bt3 = new Button("Δώσε επίθετο για αναζήτηση");
        bt3.setOnAction(event -> {
            output=ob.SelectbySurrname(suurname.getText());
            textAr.setText(output);
            output="";
            suurname.setText(output);
        });

        semester = new TextField();
        bt4 = new Button("Δώσε εξάμηνο για αναζήτηση");
        bt4.setOnAction(event->{
            int sem =Integer.parseInt(semester.getText());
            output=ob.SelectbySem(sem);
            textAr.setText(output);
            output="";
            semester.setText(output);
        });

        Tfsuurname2 = new TextField();
        Tfpassed = new TextField();
        Lblastname = new Label("Επώνυμο");
        Lbpassed = new Label("Μαθήματα");
        Hblastname.getChildren().addAll(Lblastname,Tfsuurname2);
        Hbpassed.getChildren().addAll(Lbpassed,Tfpassed);
        bt5 = new Button("Ενήμερωση εγγραφής βάση επωνυμού");
        bt5.setOnAction(event->{
            int x = Integer.parseInt(Tfpassed.getText());
            String y = Tfsuurname2.getText();
            output=ob.updateQuery(y, x);
            textAr.setText(output);
            output="";
            Tfpassed.setText(output);
            Tfsuurname2.setText(output);
        });

        Tfsuurname3 = new TextField();
        bt6 = new Button("Διαγραφή βάση επώνυμου");
        bt6.setOnAction(event->{
            output=ob.deleteQuery(Tfsuurname3.getText());
            textAr.setText(output);
            output="";
            Tfsuurname3.setText(output);
        });


        
        
        
        
        textAr = new TextArea();
        textAr.setPrefHeight(100);
        textAr.setPrefWidth(200);
        
        buttons.getChildren().addAll(bt1,bt2);
        info.getChildren().addAll(info_db);
        center.getChildren().addAll(buttons,info,textAr,bt6,Tfsuurname3);
        

        left_info.getChildren().addAll(bt3,suurname,bt4,semester,bt5,Hblastname,Hbpassed);
        left.getChildren().addAll(left_info);
        

        


        myLayout = new GridPane();
        myLayout.setHgap(5);
    }

    private void addtoPanel(){
        myLayout.add(center,2,400); //set center the textArea
        myLayout.add(left,0,0);

    }

    public void show(){
        Stage stage = new Stage();
        start(stage);
    }

    public static void main(String args){
        launch(args);
    }
    
}
