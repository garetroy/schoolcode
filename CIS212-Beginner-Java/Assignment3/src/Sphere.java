
public class Sphere implements AreaMeasurable{
	
	public double publicradius;
	
	public Sphere(double radius){
		publicradius = radius;
	}
	
	public double getArea(){
		return(4 * Math.pow(publicradius, 2) * Math.PI);
	}
}
