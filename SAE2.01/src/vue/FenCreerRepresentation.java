package vue;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class FenCreerRepresentation extends Stage{
	private CtrlCreerRepresentation ctrl;
	
	public FenCreerRepresentation() throws IOException {
		this.setTitle("Création d'une représentation");
		this.setResizable(false);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}

	private Pane creerSceneGraph() throws IOException {
     	FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/creer_representation.fxml"));
        Pane root = loader.load();
        ctrl = loader.getController();
     	return root;
	}

	public CtrlCreerRepresentation getCtrl() {
		return ctrl;
	}
	
	public void effacer() {
		ctrl.effacer();
	}
}
