
public class Circle implements AreaMeasurable{
	
	public double publicradius;
	
	public Circle(double radius){
		publicradius = radius;
	}
	
	public double getArea(){
		return Math.pow(publicradius, 2) * Math.PI;
	}
}
