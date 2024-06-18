package modele;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Random;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class Representation {
	private final Spectacle spec;
	private final SimpleStringProperty nomSpec;
	private final StringProperty debut;
	private final StringProperty fin;
	private final IntegerProperty duree;
	private final IntegerProperty nbreMaxSpect;
	private final StringProperty categorie;
	private final StringProperty genre;
	private final StringProperty date;
	private final StringProperty heure;
	private final StringProperty ventes;
	
	public Representation(Spectacle spec, Date datef, String heureString) {
		this.spec = spec;
		SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd");
        String formattedDate = sdf.format(datef);
		this.date = new SimpleStringProperty(formattedDate);
		this.heure = new SimpleStringProperty(heureString);
		this.nomSpec = new SimpleStringProperty(spec.getNom());
		this.debut = new SimpleStringProperty(spec.getDebut());
		this.fin = new SimpleStringProperty(spec.getFin());
		this.duree = new SimpleIntegerProperty(spec.getDuree());
		this.nbreMaxSpect = new SimpleIntegerProperty(spec.getNbreMaxSpect());
		this.categorie = new SimpleStringProperty(spec.getCategorie());
		this.genre = new SimpleStringProperty(spec.getGenre());
		Random rand = new Random();
		this.ventes = new SimpleStringProperty(Integer.toString(rand.nextInt(99) + 1));
	}
	
	public Representation(Spectacle spectacleA, String string, String string2, int i, int j, String string3, String string4) {
		this.spec = new Spectacle();
		this.nomSpec = new SimpleStringProperty();
		this.debut = new SimpleStringProperty();
		this.fin = new SimpleStringProperty();
		this.duree = new SimpleIntegerProperty();
		this.nbreMaxSpect = new SimpleIntegerProperty();
		this.categorie = new SimpleStringProperty();
		this.genre = new SimpleStringProperty();
		Random rand = new Random();
		this.date = new SimpleStringProperty();
		this.heure = new SimpleStringProperty();
		this.ventes = new SimpleStringProperty(Integer.toString(rand.nextInt(99) + 1));
		
	}

	// Getters
	public Spectacle getSpec() { return spec; }

    public String getNomSpec() { return nomSpec.get(); }
    public StringProperty nomSpecProperty() { return nomSpec; }

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
    
    public String getVentes() { return ventes.get(); }
    public StringProperty ventesProperty() { return ventes; }

    public String getDate() { return date.get(); }
    public StringProperty dateProperty() { return date; }
    
    public String getHeure() { return heure.get(); }
    public StringProperty heureProperty() { return heure; }
}
