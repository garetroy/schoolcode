import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.List;

public class Server {

	private static final int PORT = 9993;
	private static final String SHUTDOWN = "";
	private static List<Integer> Numbers;

	public static void main(String[] args) {
		try {
			ServerSocket serverSocket = new ServerSocket(PORT);
			ObjectOutputStream outputStream = null;
			ObjectInputStream inputStream = null;
			Socket socket = null;
			boolean runServer = true;
 			while (runServer){
				socket = serverSocket.accept();
				outputStream = new ObjectOutputStream(
						socket.getOutputStream());
				outputStream.flush();
				inputStream = new ObjectInputStream(
						socket.getInputStream());
				boolean running = true;
				String message;
				while (running) {
					message = inputStream.readUTF();
					try{
					if (message.equals(SHUTDOWN)) {
						runServer = false;
						break;
					}
					try{
						int clientint = Integer.parseInt(message);
						outputStream.writeUTF(message);
					} catch (NumberFormatException ex){
						outputStream.writeUTF("Can't be an string");
					}
					outputStream.flush();
					}catch(EOFException ex){
						socket.close();
						break;
					}
				}
			}
			System.out.println("server shutting down");
			inputStream.close();
			outputStream.close();
			socket.close();
		} catch (IOException ex) {
			ex.printStackTrace();
		}
	}
}