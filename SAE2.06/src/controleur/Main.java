package controleur;

import java.util.ArrayList;
import javafx.application.Application;
import javafx.stage.Modality;
import javafx.stage.Stage;
import modele.Donnees;
import modele.Representation;
import modele.Spectacle;
import vue.CtrlCreerRepresentation;
import vue.FenAccueil;
import vue.FenCreerRepresentation;
import vue.FenCreerSpectacle;
import vue.FenStats;
public class Main extends Application {
	static private FenAccueil fAccueil;
	static private FenCreerRepresentation fCreerRep;
	static private FenCreerSpectacle fCreerSpec;
	static private FenStats fStats;


	@Override
	public void start(Stage primaryStage) throws Exception {
		fAccueil = new FenAccueil();
		fCreerRep = new FenCreerRepresentation();
		fCreerSpec = new FenCreerSpectacle();
		fStats = new FenStats();
		fCreerRep.initModality(Modality.APPLICATION_MODAL);
		fCreerSpec.initModality(Modality.APPLICATION_MODAL);
		fStats.initModality(Modality.APPLICATION_MODAL);
		Donnees.chargementDonnees();
		fAccueil.show();
	}
	
	//////////////////////////////////////////////////////////
	// Gestion des fenêtres
	//////////////////////////////////////////////////////////
	static public void ouvrirCreerRep() {
		fCreerRep.effacer();
		fCreerRep.getCtrl().updateSpectacleList();
		fCreerRep.show();
	}
	
	static public void ouvrirCreerSpec() {
		fCreerSpec.effacer();
		fCreerSpec.show();
	}
	
	static public void ouvrirStats() {
		fStats.show();
	}
	
	static public void fermerCreerRep() {
		fCreerRep.close();
	}
	
	static public void fermerCreerSpec() {
		fCreerSpec.close();
	}
	
	static public void fermerStats() {
		fStats.close();
	}
	
	static public void fermerAppli() {
		System.exit(0);
	}

	public static ArrayList<String> getListSpectacle() {
		return Donnees.getlesSpectacle() ;
	}

	public static void nvRep(Representation rep) {
		Donnees.ajouterRep(rep);
		fCreerRep.close();
	}
	
	public static void main(String[] args) {
		Application.launch(args);

	}

	public static void nvSpectacle(Spectacle nvSpec) {
		Donnees.ajouterSpect(nvSpec);
		fCreerSpec.close();
		
	}
	
	public static CtrlCreerRepresentation getCreerRepresentationController() {
	    return fCreerRep.getCtrl();
	}
}
