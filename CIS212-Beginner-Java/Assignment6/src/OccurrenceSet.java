import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Set;


public class OccurrenceSet<T> implements Set<T> {
	
	private HashMap<T, Integer> add_count = new HashMap<T, Integer>();
	
	
	@Override
	public boolean add(T arg0) {
		if (add_count.containsKey(arg0)) {
			Integer i = add_count.get(arg0);
			i++;
			add_count.put(arg0, i);
			return true;
		} else {
			add_count.put(arg0, new Integer(1));
			return true;
		}
	}

	@Override
	public boolean addAll(Collection<? extends T> arg0) {
		for (T obj : arg0) {
			if (add_count.containsKey(obj)) {
				Integer i = add_count.get(obj);
				add_count.put((T) obj, i++);
			} else {
				add_count.put((T) obj, new Integer(1));
			}
		}
		return true;
	}

	@Override
	public void clear() {
		this.add_count = new HashMap<T, Integer>();
		
	}

	@Override
	public boolean contains(Object arg0) {
		return add_count.containsKey(arg0);
	}

	@Override
	public boolean containsAll(Collection<?> arg0) {
		return add_count.keySet().containsAll(arg0);
	}

	@Override
	public boolean isEmpty() {
		return add_count.isEmpty();
	}

	@Override
	public Iterator<T> iterator() {
		Iterator<T> iterator = add_count.keySet().iterator();
		ArrayList<T> arr = new ArrayList<T>();
		while (iterator.hasNext()) {
			T input = iterator.next();
			arr.add(input);
		}
		return arr.iterator();
	}

	@Override
	public boolean remove(Object arg0) {
		return add_count.keySet().remove(arg0);
	}

	@Override
	public boolean removeAll(Collection<?> arg0) {
		return add_count.keySet().removeAll(arg0);
	}

	@Override
	public boolean retainAll(Collection<?> arg0) {
		return add_count.keySet().retainAll(arg0);
	}

	@Override
	public int size() {
		return add_count.size();
	}

	@Override
	public Object[] toArray() {
		return sortingvalues(add_count).toArray();
	}
	
	public String toString(){
		return sortingvalues(add_count).toString();
	}
	
	@SuppressWarnings("unchecked")
	private LinkedList sortingvalues(Map<T, Integer> map) {
		LinkedList list = new LinkedList(add_count.entrySet());
		LinkedList sorted = new LinkedList();
		Collections.sort((List<T>) list, new Comparator() {
			@Override
			public int compare(Object o1, Object o2) {
				if (((Comparable) ((Map.Entry<T, Integer>) (o1)).getValue())
						.compareTo(((Map.Entry<T, Integer>) (o2)).getValue()) > 0) {
					return -1;
				} else if (((Comparable) ((Map.Entry<T, Integer>) (o1))
						.getValue()).compareTo(((Map.Entry<T, Integer>) (o2))
						.getValue()) < 0) {
					return 1;
				} else {
					return 0;
				}
			}
		});
		for (Iterator iterate = list.iterator(); iterate.hasNext();) {
			Map.Entry entry = (Map.Entry) iterate.next();
			sorted.add(entry.getKey());
		}
		return sorted;
	}



	


	public static void main(String[] args) {
		Set<String> stringSet = new OccurrenceSet<String>();
		stringSet.add("hello");
		stringSet.add("hello");
		stringSet.add("world");
		stringSet.add("world");
		stringSet.add("world");
		stringSet.add("here");
		stringSet.add("I");
		stringSet.add("am");
		System.out.println(stringSet);

		OccurrenceSet<Integer> intSet = new OccurrenceSet<Integer>();
		intSet.add(1);
		intSet.add(3);
		intSet.add(3);
		intSet.add(3);
		intSet.add(3);
		intSet.add(5);
		intSet.add(5);
		System.out.println(intSet);
	}

	@Override
	public <T> T[] toArray(T[] a) {
		return ((T[]) sortingvalues(add_count).toArray());
	}

}
