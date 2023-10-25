import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class IntegerClient {

	public static void main(String[] args) {
		final String serverAddress = "localhost";
		final int serverPort = 50000;
		
		try (Socket socket = new Socket(serverAddress, serverPort);
			 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			 PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
			 BufferedReader userInput = new BufferedReader(new InputStreamReader(socket.getInputStream()));
				 ) {
			
	} catch (Exception e) {
			e.printStackTrace();
		}
	}

}

