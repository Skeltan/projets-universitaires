module Ratio {
	requires javafx.controls;
	requires javafx.base;
	requires javafx.graphics;
	requires javafx.fxml;
	
	opens controleur to javafx.graphics, javafx.fxml;
	opens modele to javafx.graphics, javafx.base,javafx.fxml;
	opens vue to javafx.graphics, javafx.fxml;
}
