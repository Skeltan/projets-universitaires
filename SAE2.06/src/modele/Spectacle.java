package modele;
import java.time.LocalDate;
import java.time.chrono.ChronoLocalDate;
import java.util.Date;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Spectacle {
	private final StringProperty nom;
	private final StringProperty artiste;
	private final IntegerProperty tarif;
	private final StringProperty debut;
	private final StringProperty fin;
	private final IntegerProperty duree;
	private final IntegerProperty nbreMaxSpect;
	private final StringProperty categorie;
	private final StringProperty genre;

	public Spectacle() {
		this.nom = new SimpleStringProperty();
		this.artiste = new SimpleStringProperty();
		this.tarif = new SimpleIntegerProperty();
		this.debut = new SimpleStringProperty();
		this.fin = new SimpleStringProperty();
		this.duree = new SimpleIntegerProperty();
		this.nbreMaxSpect = new SimpleIntegerProperty();
		this.categorie = new SimpleStringProperty();
		this.genre = new SimpleStringProperty();
	}
	
	public Spectacle(String nom, String artiste, int tarif, String debut, String fin, int duree, int nbreMaxSpect, String categorie, String genre) {
		this.nom = new SimpleStringProperty(nom);
		this.artiste = new SimpleStringProperty(artiste);
		this.tarif = new SimpleIntegerProperty(tarif);
		this.debut = new SimpleStringProperty(debut);
		this.fin = new SimpleStringProperty(fin);
		this.duree = new SimpleIntegerProperty(duree);
		this.nbreMaxSpect = new SimpleIntegerProperty(nbreMaxSpect);
		this.categorie = new SimpleStringProperty(categorie);
		this.genre = new SimpleStringProperty(genre);

	}
	
	

	// Getters
    public String getNom() { return nom.get(); }
    public StringProperty nomProperty() { return nom; }

    public String getArtiste() { return artiste.get(); }
    public StringProperty artisteProperty() { return artiste; }

    public int getTarif() { return tarif.get(); }
    public IntegerProperty tarifProperty() { return tarif; }

    public String getDebut() { return debut.get(); }
    public StringProperty debutProperty() { return debut; }

    public String getFin() { return fin.get(); }
    public StringProperty finProperty() { return fin; }

    public int getDuree() { return duree.get(); }
    public IntegerProperty dureeProperty() { return duree; }

    public int getNbreMaxSpect() { return nbreMaxSpect.get(); }
    public IntegerProperty nbreMaxSpectProperty() { return nbreMaxSpect; }

    public String getCategorie() { return categorie.get(); }
    public StringProperty categorieProperty() { return categorie; }

    public String getGenre() { return genre.get(); }
    public StringProperty genreProperty() { return genre; }
    
	public LocalDate getDateDeb() {
    	LocalDate d;
    	d = LocalDate.parse(getDebut());
    	return d;
    }
	public LocalDate getDateFin() {
    	LocalDate d;
    	d = LocalDate.parse(getFin());
    	return d;
    }


}
