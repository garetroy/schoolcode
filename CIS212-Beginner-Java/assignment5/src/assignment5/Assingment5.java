package assignment5;


import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;
import java.util.ArrayList;
import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JFrame;

//mainly used wikipedia.com
// another website I used was http://www.java2novice.com/java-sorting-algorithms/selection-sort/
// and http://www.java2novice.com/java-sorting-algorithms/merge-sort/
// Used Lab week 6 code as well

public class Assingment5 extends JFrame {

	/**
	 * 
	 */
	private static final long serialVersionUID = 4299064207294746701L;
	static ArrayList<person> data = new ArrayList<person>();

	public void assingment5() {
		readFile();

		JFrame frame = new JFrame("Sorting");
		frame.setLayout(new BorderLayout());
		Container container = frame.getContentPane();
		container.setPreferredSize(new Dimension(210, 60));
		JPanel buttonPanel = new JPanel();
		JPanel textPanel = new JPanel();
		buttonPanel.setLayout(new BoxLayout(buttonPanel, BoxLayout.Y_AXIS));
		textPanel.setLayout(new BoxLayout(textPanel, BoxLayout.Y_AXIS));
		JLabel mergeSortText = new JLabel("0.0");
		JLabel selectionSortText = new JLabel("0.0");
		JButton selectionSortButton = new JButton("Selection Sort");
		selectionSortButton.addActionListener(new ActionListener() {
			@Override
					public void actionPerformed(ActionEvent e) {
						System.out.println("Selection sort is sorting..");
						long startTime = System.nanoTime();
						ArrayList<person> sortedArrayList = selectionSort(data);
						double elapsedTime = ((System.nanoTime() - startTime) / 1000000000.0);
						System.out.println(elapsedTime);
						String timestring = Double.toString(elapsedTime);
						if (checkSort(sortedArrayList)) {
							selectionSortText.setText(timestring);
				};
			}
		});
		JButton mergeSortButton = new JButton("Merge Sort");
		mergeSortButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) { 
						System.out.println("Merge Sort is sorting...");
						long startTime = System.nanoTime();
						ArrayList<person> sortedArrayList = mergeSort(data);
						double elapsedTime = ((System.nanoTime() - startTime) / 1000000000.0);
						System.out.println(elapsedTime);
						String timestring = Double.toString(elapsedTime);
						if (checkSort(sortedArrayList)) {
							mergeSortText.setText(timestring);
						}
				}
		});

		buttonPanel.add(selectionSortButton, BorderLayout.NORTH);
		buttonPanel.add(mergeSortButton, BorderLayout.SOUTH);
		textPanel.add(selectionSortText);
		textPanel.add(mergeSortText);
		container.add(buttonPanel, BorderLayout.WEST);
		container.add(textPanel, BorderLayout.EAST);
		frame.pack();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setVisible(true);

	}
		private static void readFile(){		
		    try {
		    	URL dataSrc = new URL(
		    			"https://www.cs.uoregon.edu/Classes/14F/cis212/assignments/phonebook.txt");
		    URLConnection conn = dataSrc.openConnection();
		    	BufferedReader br = new BufferedReader(
		    			new InputStreamReader(conn.getInputStream())); 
		    	
		        String line = br.readLine();
		        while (line != null) {
		        		String[] parts=line.split(" ");
		        		parts[1] = parts[1].replace(",", "");
		        		person ent = new person(Integer.parseInt(parts[0]), parts[1], parts[2]);
		        		data.add(ent);
		            line = br.readLine();
		        }	       
		        br.close();
		    }
		    catch(Exception e){
		    	System.err.print("File reading error!");
		    	System.err.print(e.getMessage());
		    }
		    
		}
		
		public ArrayList<person> selectionSort(ArrayList<person> data){
			int n = data.size();
			ArrayList<person> newarray = data;
			int i, j, minIndex;
			for (i = 0; i < n - 1; i++) {
				minIndex = i;
				for (j = i + 1; j < n; j++) {
					if ((newarray.get(j)).getLastName().compareTo(
							newarray.get(minIndex).getLastName()) < 0) {
						minIndex = j;
					}
				}
				if (minIndex != j) {
					person temp = newarray.get(i);
					newarray.set(i, newarray.get(minIndex));
					newarray.set(minIndex, temp);
				}
			}
			for(int k = 0; k < newarray.size(); k++){
				person.print(newarray.get(k));
			}
			return newarray;
		}
		
		public ArrayList<person> mergeSort(ArrayList<person> data){
			ArrayList<person> newarray = data;
			if (data.size() > 1){
				int n = newarray.size();
				ArrayList<person> left = new ArrayList<person>();
				ArrayList<person> right = new ArrayList<person>();
				int split = n / 2;
				
				for (int i = split; i < n; i++){
					left.add(newarray.get(i));
				}
				
				for (int i = split; i < n; i++){
					right.add(newarray.get(i));
				}
				left = mergeSort(left);
				right = mergeSort(right);
				ArrayList<person> result = merge(left, right);
				newarray = result;
			}
			return newarray;
		}
			private ArrayList<person> merge(ArrayList<person> left, ArrayList<person> right){
				ArrayList<person> mergedarray = new ArrayList<person>();
				while (left.size() > 0 || right.size() > 0 ){
					int lsize = left.size(), rsize = right.size();
					
					if (lsize > 0 && rsize > 0){
						if (left.get(0).getLastName().compareTo(right.get(0).getLastName()) < 0) {
							mergedarray.add(left.get(0));
							left.remove(0);
						} else {
							mergedarray.add(right.get(0));
							right.remove(0);
						}
					} else if (lsize > 0){
						mergedarray.add(left.get(0));
						left.remove(0);
					} else if (rsize > 0){
						mergedarray.add(right.get(0));
						right.remove(0);
					}
				}
				return mergedarray;
			}
			
		public static Boolean checkSort(ArrayList<person> arraylist){
			person current_compare = arraylist.get(0);
			int n = arraylist.size();
			int i = 1;
			while(i < n){
				if (current_compare.getLastName().compareTo(arraylist.get(i).getLastName()) < 0 || current_compare.getLastName().compareTo(arraylist.get(i).getLastName()) == 0){
					current_compare = arraylist.get(i);
					i = i + 1;
				}
				return false;
			}
		return true;
		}
		
		public static void main(String[] args) {
			new Assingment5();
		}
}
