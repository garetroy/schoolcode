import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.LinkedList;

public class Server {	
	private static final int PORT = 1235;
	private static LinkedList<Integer> Numbers = new LinkedList<Integer>();
	private static LinkedList<Integer> newNumbers = new LinkedList<Integer>();
	private static String SHUTDOWN = " ";
	
	public static void main(String[] args) {		
		System.out.println("Server started!");
		
		try {
			InetAddress localHost = InetAddress.getLocalHost();
			System.out.println("My IP address is: " + localHost);			
			
			ServerSocket serverSocket = new ServerSocket(PORT);
			boolean serverRunning = true;
			while (serverRunning) {
				Socket socket = null;
				ObjectInputStream inputStream = null;
				ObjectOutputStream outputStream = null;
				try {
					System.out.println("ServerSocket created, waiting for connection...");
		
					socket = serverSocket.accept();
		
					System.out.println("Socket connected, creating streams!");
		
					outputStream = new ObjectOutputStream(socket.getOutputStream());
					outputStream.flush();
					
					inputStream = new ObjectInputStream(socket.getInputStream());
							
					boolean running = true;
					while (running) {
						String message = inputStream.readUTF();
						try{
							if (message.equals(SHUTDOWN)){
								running = false;
								break;
							}
							int clientint = Integer.parseInt(message);
							Numbers.add(clientint);
							outputStream.writeUTF(message);
							outputStream.flush();
						} catch (NumberFormatException ex){
							outputStream.writeUTF("Can't be an string");
							outputStream.flush();
						}
					}					
				} catch (IOException ex) {
					System.out.println("Socket disconnected with: " + ex);
				} finally {
					// Close streams and sockets regardless of whether or 
					// not an exception occurred.  Make sure they were
					// initialized first, though!
					if (inputStream != null) {
						inputStream.close();
					}
					if (outputStream != null) {
						outputStream.close();
					}
					if (socket != null) {
						socket.close();
					}
					
					System.out.println("Client Sent: " + Numbers);
					for (int i: Numbers){
						if (i % 2 != 0){
							newNumbers.add(i);
						}
					}
					System.out.println("Client received: " + newNumbers);
				}
			}
		} catch (IOException ex) {
			ex.printStackTrace();
		}		
	}
}