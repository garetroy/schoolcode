package assignment5;

public class person {
	
	private int phonenumber;
	private String last_name;
	private String first_name;
	
	public person (int phone, String last_name, String first_name){
		phonenumber = phone;
		this.last_name = last_name;
		this.first_name = first_name;
	}
	
	public static void print(person ent){
		System.out.println(ent.phonenumber + " " + ent.last_name + " " + ent.first_name);
	}
	
	public String getLastName(){
		return last_name;
	}
	
	public String getFirstName(){
		return first_name;
	}
	
	public int getPhone(){
		return phonenumber;
	}
	
}
