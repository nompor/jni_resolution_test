import javafx.animation.Animation;
import javafx.animation.PathTransition;
import javafx.application.Application;
import javafx.beans.value.ObservableValue;
import javafx.scene.Group;
import javafx.scene.Scene;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;
import javafx.stage.Stage;
import javafx.util.Duration;
 
 
public class Test extends Application{
 
	public static void main(String[] args) {
		launch(args);
	}
 
	//描画領域サイズ
	int w=800;
	int h=600;
 
	@Override
	public void start(Stage stg) throws Exception {
 
		//プラットフォームによって読み込み処理を変更
		String name = System.getProperty("os.name").toLowerCase();
		if ( name.contains("mac") ) {
			System.load(new java.io.File("Test.dylib").getAbsolutePath());
		} else {
			System.loadLibrary("Test");
		}
 
		//アニメーション対象である四角オブジェクト
		Rectangle rect = new Rectangle(100,100);
		rect.setFill(Color.GOLD);
 
		//背景
		Rectangle back = new Rectangle(w,h);
		back.setFill(Color.WHITE);
 
		//表示領域
		Group root = new Group(back, rect);
 
		//Sceneに表示領域セット
		Scene scene = new Scene(root, w, h);
		stg.setScene(scene);
 
		//ENTERでフルスクリーンに移行
		scene.setOnKeyReleased(e -> {
			switch(e.getCode()) {
			case ENTER:
				if ( !stg.isFullScreen() ) {
					change(w, h);
					stg.setFullScreen(true);
				}
				break;
			default:
				break;
			}
		});
 
		//ESCでフルスクリーン解除されたら、解像度も元に戻す
		stg.fullScreenProperty().addListener((ObservableValue<? extends Boolean> ob, Boolean o, Boolean n)->{
			//解除時は元の解像度に戻す
			if ( o && !n ) {
				end();
				stg.sizeToScene();
			}
		});
 
		//閉じるでアプリケーション終了
		stg.setOnCloseRequest(e ->{System.exit(0);});
		stg.show();
 
		//アニメーション処理
		PathTransition pt = new PathTransition(Duration.seconds(3), new Rectangle(50,50,w-100,h-100), rect);
		pt.setAutoReverse(true);
		pt.setCycleCount(Animation.INDEFINITE);
		pt.play();
	}
 
	public native void change(int width, int height);
	public native void end();
}