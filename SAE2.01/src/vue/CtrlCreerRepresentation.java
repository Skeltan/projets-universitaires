package vue;

import java.time.Instant;
import java.time.LocalDate;
import java.time.ZoneId;
import java.util.Date;

import controleur.Main;
import javafx.beans.binding.BooleanBinding;
import javafx.beans.binding.Bindings;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.scene.control.Tooltip;
import javafx.scene.input.KeyEvent;
import modele.Donnees;
import modele.Representation;
import modele.Spectacle;

public class CtrlCreerRepresentation {
    @FXML
    private Button ferm;
    @FXML
    private ChoiceBox<String> nom_spectacle;
    @FXML
    private DatePicker textDate;
    @FXML
    private TextField txtHeur;
    @FXML
    private Button valid;


    @FXML
    void clicFermer(ActionEvent event) {
        if (event.getSource() == ferm) {
            Main.fermerCreerRep();
        }
    }
    
    public void effacer() {
    	txtHeur.clear();
    	textDate.setValue(LocalDate.now());
    }
    
    @FXML
    void clicValider(ActionEvent event) {
        if (event.getSource() == valid) {
        	boolean possible = true;
        	try {
        		String heureString = txtHeur.getText();
        		Float f = Float.parseFloat(heureString);
        	}catch(NumberFormatException er) {
        		Alert error = new Alert(AlertType.ERROR, "L'heure doit être au format HH.MM.", ButtonType.OK);
        		error.setTitle("Code postal : format incorrect");
        		error.showAndWait();
        		possible = false;
        		
        	}
        	if(possible) {
        		Spectacle spec = null;
                LocalDate date = textDate.getValue();
                String heureString = txtHeur.getText();
                Instant instant = date.atStartOfDay(ZoneId.systemDefault()).toInstant();
                Date datef = Date.from(instant);
                for (int i = 0; i < Donnees.getlesSpectacle().size();i++) {
                	if (Donnees.getlesSpectacle().get(i) == nom_spectacle.getValue()) {
                		spec = Donnees.getSpec().get(i);
                	}
                }
                if(textDate.getValue().isBefore(spec.getDateDeb())){
            		Alert erreur = new Alert(AlertType.ERROR, "\r\n" + "La Date doit être comprise entre le : \n" + spec.getDebut() + " et le : "  + spec.getFin() + " " , ButtonType.OK);
            		erreur.setTitle("Date incorrect");
            		erreur.showAndWait();
                }
                else if(textDate.getValue().isAfter(spec.getDateFin())){
                	Alert erreur = new Alert(AlertType.ERROR, "\r\n" + "La Date doit être comprise entre le : \n" + spec.getDebut() + " et le : "  + spec.getFin() + " ", ButtonType.OK);
            		erreur.setTitle("Date incorrect");
            		erreur.showAndWait();
                }
                else {
                    Representation rep = new Representation(spec, datef, heureString);
                    Main.nvRep(rep);
                }

        	}

        }
    }
    @FXML
    void tape(KeyEvent e) {
    	if (txtHeur.getText().length() >= 5) {
    		e.consume();
    		Alert erreur = new Alert(AlertType.ERROR, "\r\n" + "La longueur ne doit pas dépasser 5 caractères \n et doit être au format HH.MM.", ButtonType.OK);
    		erreur.setTitle("Heure : format incorrect");
    		erreur.showAndWait();
    		}
    	if (txtHeur.getText().startsWith("3") || txtHeur.getText().startsWith("4") || txtHeur.getText().startsWith("5") || txtHeur.getText().startsWith("6") || txtHeur.getText().startsWith("7") || txtHeur.getText().startsWith("8") || txtHeur.getText().startsWith("9") ) {
    		e.consume();
    		Alert erreur = new Alert(AlertType.ERROR, "\r\n" + "L'Heure doit être comprit entre 00h et 24h .", ButtonType.OK);
    		erreur.setTitle("Heure : format incorrect");
    		erreur.showAndWait();
    		}
    	if (txtHeur.getText().startsWith("25") || txtHeur.getText().startsWith("26") || txtHeur.getText().startsWith("27") || txtHeur.getText().startsWith("28") || txtHeur.getText().startsWith("29") ) {
    		e.consume();
    		Alert erreur = new Alert(AlertType.ERROR, "\r\n" + "L'Heure doit être comprit entre 00h et 24h .", ButtonType.OK);
    		erreur.setTitle("Heure : format incorrect");
    		erreur.showAndWait();
    		}
    	if (txtHeur.getText().startsWith("-")) {
    		e.consume();
    		Alert erreur = new Alert(AlertType.ERROR, "\r\n" + "L'Heure doit être comprit entre 00h et 24h .", ButtonType.OK);
    		erreur.setTitle("Heure : format incorrect");
    		erreur.showAndWait();
    		}
    }

    @FXML
    public void initialize() {
        valid.setDefaultButton(true);
        ferm.setCancelButton(true);
        nom_spectacle.getItems().clear();
        txtHeur.setTooltip(new Tooltip("ex: 15.30"));


        nom_spectacle.getItems().addAll(Main.getListSpectacle());


        BooleanBinding manque = Bindings.createBooleanBinding(() -> 
            textDate.getValue() == null || 
            txtHeur.getText().isEmpty() || 
            nom_spectacle.getSelectionModel().isEmpty(),
            textDate.valueProperty(), 
            txtHeur.textProperty(), 
            nom_spectacle.getSelectionModel().selectedItemProperty());
        
        valid.disableProperty().bind(manque);
    }



    public void updateSpectacleList() {
        nom_spectacle.getItems().clear();
        nom_spectacle.getItems().addAll(Main.getListSpectacle());
    }
}
