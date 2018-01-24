
public class Rectangle implements AreaMeasurable{
	
	public double publicside1;
	public double publicside2;
	
	public Rectangle(double side1, double side2){
		publicside1 = side1;
		publicside2 = side2;
		
	}
	
	public double getArea(){
		return(publicside1 * publicside2);
	}
}
