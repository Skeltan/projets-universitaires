package vue;

import java.util.ArrayList;
import java.util.List;
import java.util.stream.Collectors;

import javafx.collections.FXCollections;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.ChoiceBox;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.KeyEvent;
import modele.Donnees;
import modele.Representation;
import javafx.scene.control.TableView;

public class CtrlStats {
	
	@FXML
    private TableView<Representation> tvStats;
	
	@FXML
    private TableColumn<Representation, String> nomSpecColumn;
	
	@FXML
    private TableColumn<Representation, String> dateColumn;
	
	@FXML
    private TableColumn<Representation, String> heureColumn;
	
	@FXML
    private TableColumn<Representation, String> ventesColumn;
	
    @FXML
    private TextField annee;

    @FXML
    private Button bnFermer;

    @FXML
    private ChoiceBox<String> choiceBoxFiltre;

    @FXML
    private TextField textFieldFiltre;

    @FXML
    private TextField totalPlace;

    
    @FXML
    void fermerStats(ActionEvent event) {
    	controleur.Main.fermerStats();
    }
    
    @FXML
    void onKeyTyped(KeyEvent event) {
        String input = textFieldFiltre.getText().trim();
        String mode = choiceBoxFiltre.getValue();

        if (mode == null || input.isEmpty()) {
            // Si le mode ou l'entrée est vide, afficher toutes les représentations
            tvStats.setItems(Donnees.getLesRep());
        } else {
            List<Representation> filteredRepresentations = new ArrayList<>();

            if (mode.equals("Nom")) {
                // Filtrer par nom de spectacle
                filteredRepresentations = Donnees.getLesRep().stream().filter(rep -> rep.getNomSpec().toLowerCase().contains(input.toLowerCase())).collect(Collectors.toList());
            } else if (mode.equals("Date")) {
                // Filtrer par date (supposant que vous filtrez par la représentation de la date, ajustez si nécessaire)
                filteredRepresentations = Donnees.getLesRep().stream().filter(rep -> rep.getDate().toLowerCase().contains(input.toLowerCase())).collect(Collectors.toList());
            }

            // Mettre à jour la TableView avec les représentations filtrées
            tvStats.setItems(FXCollections.observableArrayList(filteredRepresentations));
        }
    }
    
    
    @FXML 
    public void initialize() {
    	ArrayList<String> lstFiltre = new ArrayList<String>();
    	lstFiltre.add("Nom");
    	lstFiltre.add("Date");
    	
    	choiceBoxFiltre.getItems().addAll(lstFiltre);
    	annee.setText("2024");
    	
    	nomSpecColumn.setCellValueFactory(new PropertyValueFactory<>("nomSpec"));
    	dateColumn.setCellValueFactory(new PropertyValueFactory<>("date"));
    	heureColumn.setCellValueFactory(new PropertyValueFactory<>("heure"));
    	ventesColumn.setCellValueFactory(new PropertyValueFactory<>("ventes"));
    	
    	// Configurer le mode de sélection à une seule ligne
        tvStats.getSelectionModel().setSelectionMode(SelectionMode.SINGLE);
    	
    	// Écouter les changements dans la sélection de la TableView
        tvStats.getSelectionModel().selectedItemProperty().addListener((observable, oldValue, newValue) -> {
            if (newValue != null) {
                updateTotalVentes(newValue.getNomSpec());
            } else {
                totalPlace.clear();
            }
        });
    	
    	tvStats.setItems(Donnees.getLesRep());
    }
    
    private void updateTotalVentes(String nomSpec) {
        List<Representation> representations = Donnees.getLesRep().stream().filter(rep -> rep.getNomSpec().equals(nomSpec)).collect(Collectors.toList());

        int totalVentes = representations.stream().mapToInt(rep -> Integer.parseInt(rep.getVentes())).sum();

        totalPlace.setText(String.valueOf(totalVentes));
    }

}
