
public class Square implements AreaMeasurable {
	
	public double publicside;
	
	public Square(double side){
		publicside = side;
	}

	public double getArea(){
		return(Math.pow(publicside, 2));
	}
}
