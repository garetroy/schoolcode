
public class Box implements AreaMeasurable{
	
	public double publicwidth;
	public double publicheight;
	public double publiclength;
	
	public Box(double width, double height, double length){
		publicwidth = width;
		publicheight = height;
		publiclength = length;
	}
	
	public double getArea(){
		return(publicwidth * publicheight * publiclength);
	}
}
