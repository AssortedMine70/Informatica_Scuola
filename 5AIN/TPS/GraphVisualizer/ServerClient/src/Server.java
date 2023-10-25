import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {

	public static void main(String[] args) {
		final int port = 50000;
		
		try (ServerSocket serverSocket = new ServerSocket(port)) {
			System.out.println("Server in ascolto sulla porta " + port);
			while(true) {
				Socket clientSocket = serverSocket.accept(); // bloccante
				System.out.println("Client connesso da " + clientSocket.getInetAddress());
				PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
				out.println("Benvenuto sul server!");
				clientSocket.close();
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

}
