import java.util.concurrent.ArrayBlockingQueue;


class Consumer implements Runnable {
		private ArrayBlockingQueue<String> _queue;

		public Consumer() {
			_queue = Main.getQueue();
		}

		@Override
		public synchronized void run() {
			for (int i = 1; i != Main.SIZE + 1; ++i) {
				if(i % 1000 == 0){
					System.out.println( i + " Strings consumed");
				}
				try {
					Thread.sleep(10);
					String string = _queue.take();
					if (string.compareTo(Main.max) > 0) {
						Main.max = string;
					}
				} catch (InterruptedException e) {
					System.out.println("consumer ex");
				}
			}
			System.out.println("Max string " + Main.max);
		}
	}