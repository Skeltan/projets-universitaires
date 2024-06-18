package modele;

import java.util.ArrayList;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

public class Donnees {

	static private ObservableList<Spectacle> 	lesSpectacle = FXCollections.observableArrayList();
	static private ObservableList<Representation> 		lesRep	= FXCollections.observableArrayList();

	static public void chargementDonnees() { 
//		Spectacle spectacleA = new Spectacle("Spectacle A", "Artiste A", 50, "2023-06-01", "2023-06-02", 120, 100, "Catégorie A", "Genre A");
//        Spectacle spectacleB = new Spectacle("Spectacle B", "Artiste B", 60, "2023-07-01", "2023-07-02", 90, 150, "Catégorie B", "Genre B");
//		lesSpectacle.add(spectacleA);
//		lesSpectacle.add(spectacleB);
//		
//		lesRep.add(new Representation(spectacleA, "2023-06-01 20:00", "2023-06-01 22:00", 120, 100, "Catégorie A", "Genre A"));
//		lesRep.add(new Representation(spectacleB, "2023-07-01 19:00", "2023-07-01 21:00", 120, 150, "Catégorie B", "Genre B"));
	}


	static public ArrayList<String> getlesSpectacle() {
		ArrayList<String> lesDepPossibles = new ArrayList<String>();
		for(int i=0 ; i<lesSpectacle.size() ; i++) {
			lesDepPossibles.add(lesSpectacle.get(i).getNom());
		}
		return lesDepPossibles;
	}
	static public ArrayList<Spectacle> getSpec(){
		ArrayList<Spectacle> speclist = new ArrayList<Spectacle>();
		for(int i=0 ; i<lesSpectacle.size() ; i++) {
			speclist.add(lesSpectacle.get(i));
		}
		return speclist;
	}
	
	
	public static ObservableList<Spectacle> getLesSpectacle() {
		return lesSpectacle;
	}

	public static ObservableList<Representation> getLesRep() {
		return lesRep;
	}

	static public void ajouterRep(Representation rep) {
		lesRep.add(rep);
	}
	
	static public void ajouterSpect(Spectacle spec) {
		lesSpectacle.add(spec);
	}
	

}

