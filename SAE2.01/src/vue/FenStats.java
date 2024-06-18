package vue;

import java.io.IOException;

import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.scene.layout.Pane;
import javafx.stage.Stage;

public class FenStats extends Stage{
	private CtrlStats ctrl;
	
	public FenStats() throws IOException {
		this.setTitle("Tableau des stats");
		this.setResizable(false);
		Scene laScene = new Scene(creerSceneGraph());
		this.setScene(laScene);
	}

	private Pane creerSceneGraph() throws IOException {
     	FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("/stats.fxml"));
        Pane root = loader.load();
        ctrl = loader.getController();
     	return root;
	}

}
