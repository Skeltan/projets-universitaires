package vue;

import controleur.Main;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import modele.Donnees;
import modele.Representation;
import modele.Spectacle;

public class CtrlAccueil {

    @FXML
    private TableColumn<Representation, String> repDebutColumn;

    @FXML
    private Button bnFermerSpec;

    @FXML
    private Button bnAjouterRep;

    @FXML
    private TableColumn<Spectacle, String> maxSpecColumn;

    @FXML
    private TableColumn<Representation, String> repMaxSpecColumn;

    @FXML
    private Button bnAjouterSpec;

    @FXML
    private TableColumn<Representation, String> repGenreColumn;

    @FXML
    private TableColumn<Spectacle, String> tarifColumn;

    @FXML
    private TableColumn<Spectacle, String> finColumn;

    @FXML
    private TableColumn<Representation, String> repCategorieColumn;

    @FXML
    private TableColumn<Spectacle, String> cateColumn;

    @FXML
    private TableColumn<Spectacle, String> artisteColumn;

    @FXML
    private TableColumn<Spectacle, String> debutColumn;

    @FXML
    private Button bnAfficherStats;

    @FXML
    private TableView<Spectacle> tabSpec;

    @FXML
    private TableColumn<Spectacle, String> nomColumn;

    @FXML
    private TableColumn<Spectacle, String> dureeColumn;

    @FXML
    private Button bnFermerRep;

    @FXML
    private TableColumn<Representation, String> repNomColumn;

    @FXML
    private TableColumn<Spectacle, String> genreColumn;

    @FXML
    private TableColumn<Representation, String> repDureeColumn;

    @FXML
    private TableView<Representation> tabRep;

    @FXML
    private TableColumn<Representation, String> repFinColumn;
    
    @FXML
    private TableColumn<Representation, String> repHeureColumn;
    
    @FXML
    void ouvrirCreerSpec(ActionEvent event) {
    	controleur.Main.ouvrirCreerSpec();
    }

    @FXML
    void fermerAccueil(ActionEvent event) {
    	controleur.Main.fermerAppli();
    }

    @FXML
    void ouvrirCreerRep(ActionEvent event) {
    	Main.getCreerRepresentationController().updateSpectacleList(); // Met à jour la liste des spectacles dans la fenêtre de création de représentation
    	controleur.Main.ouvrirCreerRep();
    }

    @FXML
    void ouvrirStats(ActionEvent event) {
    	controleur.Main.ouvrirStats();
    }
    
    
    @FXML 
    public void initialize() {
    	nomColumn.setCellValueFactory(new PropertyValueFactory<>("nom"));
    	artisteColumn.setCellValueFactory(new PropertyValueFactory<>("artiste"));
    	tarifColumn.setCellValueFactory(new PropertyValueFactory<>("tarif"));
    	debutColumn.setCellValueFactory(new PropertyValueFactory<>("debut"));
    	finColumn.setCellValueFactory(new PropertyValueFactory<>("fin"));
    	dureeColumn.setCellValueFactory(new PropertyValueFactory<>("duree"));
    	maxSpecColumn.setCellValueFactory(new PropertyValueFactory<>("nbreMaxSpect"));
    	cateColumn.setCellValueFactory(new PropertyValueFactory<>("categorie"));
    	genreColumn.setCellValueFactory(new PropertyValueFactory<>("genre"));
    	tabSpec.setItems(Donnees.getLesSpectacle());
    	
    	repNomColumn.setCellValueFactory(new PropertyValueFactory<>("nomSpec"));
    	repHeureColumn.setCellValueFactory(new PropertyValueFactory<>("heure"));
    	repDebutColumn.setCellValueFactory(new PropertyValueFactory<>("debut"));
        repFinColumn.setCellValueFactory(new PropertyValueFactory<>("fin"));
        repDureeColumn.setCellValueFactory(new PropertyValueFactory<>("duree"));
        repMaxSpecColumn.setCellValueFactory(new PropertyValueFactory<>("nbreMaxSpect"));
        repCategorieColumn.setCellValueFactory(new PropertyValueFactory<>("categorie"));
        repGenreColumn.setCellValueFactory(new PropertyValueFactory<>("genre"));
        tabRep.setItems(Donnees.getLesRep());
    }

}