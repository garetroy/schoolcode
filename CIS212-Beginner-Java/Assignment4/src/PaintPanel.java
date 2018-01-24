import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Point;
import java.awt.Stroke;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.ArrayList;

import javax.swing.JPanel;


public class PaintPanel extends JPanel {
	private static final int POINT_SIZE = 10;
	
	private ArrayList<PaintPoint> _points;
	private Color _color;
	private int _size;
	
	public PaintPanel() {
		setPreferredSize(new Dimension(400, 400));

		_points = new ArrayList<PaintPoint>();
		_color = Color.GREEN;
		_size = POINT_SIZE;
		
		MousePaintAdapter mpa = new MousePaintAdapter();
		addMouseMotionListener(mpa);
	}
	
	public void setColor(Color color) {
		_color = color;
		repaint();
	}

	public void setSize(int size) {
		_size = size;
		repaint();
	}

	public void clearScreen() {
		_points = new ArrayList<PaintPoint>();
		repaint();
	}
	
	@Override
	public void paintComponent(Graphics graphics) {
		super.paintComponent(graphics);
		
		for (PaintPoint point : _points) {
			if ((point._c != _color) || (point._s != _size)){
			graphics.setColor(point._c);
			graphics.fillOval(point.getX(), point.getY(), point._s, point._s);
			}else{
				graphics.setColor(_color);
				graphics.fillOval(point.getX(), point.getY(), _size, _size);
			}
		}
	}
	
	private class MousePaintAdapter extends MouseAdapter {
		@Override
		public void mouseDragged(MouseEvent ev) {
			_points.add(new PaintPoint(ev.getX(), ev.getY(), _color, _size));
			repaint();
		}
	}
	
	private class PaintPoint {
		private final int _x;
		private final int _y;
		private final Color _c;
		private final int _s;
		
		public PaintPoint(int x, int y, Color c, int _size) {
			_x = x;
			_y = y;
			_c = c;
			_s = _size;
		}
		
		public int getX() { return _x; }
		public int getY() { return _y; }
	}
}