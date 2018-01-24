import java.util.concurrent.ArrayBlockingQueue;
import java.util.List;
import java.util.ArrayList;
import java.util.Collections;
import java.util.concurrent.Executors;
import java.util.concurrent.ExecutorService;


public class Main {

	public final static int SIZE = 10000;
	public static boolean FINISHED = false;
	static private ArrayBlockingQueue<String> queue;
	static String max = "0";
	static List<String> synchedArrayList = Collections.synchronizedList(new ArrayList<String>());

	public static void main(String[] args) {
		queue = new ArrayBlockingQueue<String>(100000);
		Producer producer = new Producer();
		Consumer consumer = new Consumer();

		ExecutorService execService = Executors.newCachedThreadPool();
		execService.execute(producer);
		execService.execute(consumer);
		execService.shutdown();
		
	}

	public static ArrayBlockingQueue<String> getQueue() {
		return queue;
	}
}