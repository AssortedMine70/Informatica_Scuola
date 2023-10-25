import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.Socket;

public class Client {

	public static void main(String[] args) {
		final String serverAddress = "localhost";
		final int serverPort = 50000;
		
		try (Socket socket = new Socket(serverAddress, serverPort);
			 BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {
			
			String greeting = in.readLine();
			System.out.println("Messaggio dal Server: " + greeting);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
