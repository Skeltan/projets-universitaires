package vue;

import java.io.IOException;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;
import javafx.fxml.FXMLLoader;

public class FenAccueil extends Stage {
		
	private CtrlAccueil ctrl;
	
	public FenAccueil() throws IOException {
		this.setTitle("Accueil");
		this.setResizable(false);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}

	private Pane creerSceneGraph() throws IOException {
     	FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/accueilfix.fxml"));
        Pane root = loader.load();
        ctrl = loader.getController();
     	return root;
	}
}
