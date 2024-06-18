package vue;

import java.time.LocalDate;
import java.util.ArrayList;
import javafx.beans.binding.BooleanBinding;
import controleur.Main;
import modele.Donnees;
import modele.Spectacle;
import javafx.beans.binding.Bindings;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;

public class CtrlCreerSpectacle {
  	@FXML
    private TextField txtMaxSpec;
    @FXML
    private DatePicker dateFin;
    @FXML
    private TextField txtNom;
    @FXML
    private TextField txtDuree;
    @FXML
    private ChoiceBox<String> chCategorie;
    @FXML
    private TextField txtArtiste;
    @FXML
    private Button bnValider;
    @FXML
    private DatePicker dateDebut;
    @FXML
    private Button bnAnnuler;
    @FXML
    private TextField txtTarif;
    @FXML
    private ChoiceBox<String> chGenre;
    
    @FXML
    public void clicValider(ActionEvent event) {
    	String nom = txtNom.getText();
    	String artiste = txtArtiste.getText();
    	int tarif = Integer.parseInt(txtTarif.getText());
    	if(dateDebut.getValue().isAfter(dateFin.getValue())) {
    		Alert erreur = new Alert(AlertType.ERROR, "La Date de début ne peut être après la date de fin", ButtonType.OK);
    		erreur.setTitle("Date invalide");
    		erreur.showAndWait();
    	}
    	else {
        	String debut = dateDebut.getValue().toString();
        	String fin = dateFin.getValue().toString();
        	int duree = Integer.parseInt(txtDuree.getText());
        	int nbreMaxSpect = Integer.parseInt(txtMaxSpec.getText());
        	String categorie = chCategorie.getValue();
        	String genre = chGenre.getValue();
        	
        	Spectacle nvSpec = new Spectacle(nom, artiste, tarif, debut, fin, duree, nbreMaxSpect, categorie, genre);
        	Main.nvSpectacle(nvSpec);
    	}

    }
    
    public void effacer() {
    	txtNom.clear();
    	txtArtiste.clear();
    	txtDuree.clear();
    	txtTarif.clear();
    	txtMaxSpec.clear();
    	dateDebut.setValue(LocalDate.now());
    	dateFin.setValue(null);
    }
    
    @FXML
    public void tapTarif(){
    	try{
    		Integer.parseInt(txtTarif.getText());
    	}
    	catch(NumberFormatException e) {
    		Alert erreur = new Alert(AlertType.ERROR, "Le Tarif ne doit pas contenir de lettre.", ButtonType.OK);
    		erreur.setTitle("Tarif : Pas de lettres");
    		erreur.showAndWait();
    	}
    }
    
    @FXML
    public void tapMaxSpec(){
    	try{
    		Integer.parseInt(txtMaxSpec.getText());
    	}
    	catch(NumberFormatException e) {
    		Alert erreur = new Alert(AlertType.ERROR, "Le nombre maximum de  spectateur ne doit pas contenir de lettre.", ButtonType.OK);
    		erreur.setTitle("MaxSpec : Pas de lettres");
    		erreur.showAndWait();
    	}
    }
    
    @FXML
    public void tapDuree(){
    	try{
    		Integer.parseInt(txtDuree.getText());
    	}
    	catch(NumberFormatException e) {
    		Alert erreur = new Alert(AlertType.ERROR, "La duree ne doit pas contenir de lettre.", ButtonType.OK);
    		erreur.setTitle("Duree : Pas de lettres");
    		erreur.showAndWait();
    	}
    }

    @FXML
    public void clicAnnuler(ActionEvent event) {
    	Main.fermerCreerSpec();
    }
    
    @FXML 
    public void initialize() {
    	
    	BooleanBinding incomplet = Bindings.or(Bindings.or(txtNom.textProperty().isEmpty(), txtMaxSpec.textProperty().isEmpty()),Bindings.or(txtDuree.textProperty().isEmpty(),chGenre.itemsProperty().isNull()));
    	
    	bnValider.disableProperty().bind(incomplet);
    	
    	ArrayList<String> lstGenre = new ArrayList<String>();
    	lstGenre.add("Danse");
    	lstGenre.add("Opera");
    	lstGenre.add("Musique");
    	lstGenre.add("Cirque");
    	lstGenre.add("Marionette");
    	lstGenre.add("Theatre");
    	
    	ArrayList<String> lstCategorie = new ArrayList<String>();
    	lstCategorie.add("A");
    	lstCategorie.add("B");
    	lstCategorie.add("C");
    	chGenre.getItems().addAll(lstGenre);
    	chCategorie.getItems().addAll(lstCategorie);
 
    }
    
        
}
