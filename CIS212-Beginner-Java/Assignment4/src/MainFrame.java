
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JFrame;
import javax.swing.JPanel;


public class MainFrame extends JFrame {
	private PaintPanel _paintPanel;
	
	public MainFrame() {
		super("Hello Frame!!!");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(new BorderLayout());	
		
		_paintPanel = new PaintPanel();
		_paintPanel.setBackground(Color.WHITE);
		add(_paintPanel, BorderLayout.CENTER);

		JButton colorButton = new JButton("Color");
		colorButton.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				Color color = JColorChooser.showDialog(null,
						"Pick a color!", Color.GREEN);
				_paintPanel.setColor(color);
			}
		});
		 JButton pinkBtn = new JButton("Pink");
		 pinkBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent ev) {
				_paintPanel.setColor(Color.PINK);	
				}	
			});
		 JButton greenBtn = new JButton("Green");
		 greenBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent ev) {
				_paintPanel.setColor(Color.GREEN);	
				}	
			});
		 JButton blackBtn = new JButton("Black");
		 blackBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent ev) {
				_paintPanel.setColor(Color.BLACK);	
				}	
			});
		 JButton redBtn = new JButton("Red");
		 redBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent ev) {
				_paintPanel.setColor(Color.RED);
				}	
			});
		 JButton yellowBtn = new JButton("Yellow");
		 yellowBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setColor(Color.YELLOW);	
				}	
			});
		 JButton whiteBtn = new JButton("White");
		 whiteBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setColor(Color.WHITE);	
				}	
			});
		 JButton orangeBtn = new JButton("Orange");
		 orangeBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setColor(Color.ORANGE);	
				}	
			});
		 JButton magentaBtn = new JButton("Magenta");
		 magentaBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setColor(Color.MAGENTA);	
				}	
			});
		 JButton smallBtn = new JButton("Small");
		 smallBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(5);	
				}	
			});
		 JButton mediumBtn = new JButton("Medium");
		 mediumBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(10);	
				}	
			});
		 JButton largeBtn = new JButton("Large");
		largeBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(20);	
				}	
			});
		 JButton hugeBtn = new JButton("Huge");
		 hugeBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(40);	
				}	
			});
		 JButton crazybigBtn = new JButton("Crazy Big");
		 crazybigBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(80);	
				}	
			});
		 JButton woahthereBtn = new JButton("Woahthere");
		 woahthereBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(160);	
				}	
			});
		 JButton overboardBtn = new JButton("Overboard");
		 overboardBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.setSize(340);	
				}	
			});
		 JButton clearBtn = new JButton("Clear");
		 clearBtn.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent e) {
				_paintPanel.clearScreen();	
				}	
			});

		
		 		
		JPanel _colorsPanel = new JPanel();
		_colorsPanel.add(pinkBtn);
		_colorsPanel.add(greenBtn);
		_colorsPanel.add(blackBtn);
		_colorsPanel.add(redBtn);
		_colorsPanel.add(yellowBtn);
		_colorsPanel.add(whiteBtn);
		_colorsPanel.add(orangeBtn);
		_colorsPanel.add(magentaBtn);
		_colorsPanel.setLayout(new GridLayout(4, 1));
		add(_colorsPanel, BorderLayout.WEST);		
		
		JPanel _sizesPanel = new JPanel();
		_sizesPanel.add(smallBtn);
		_sizesPanel.add(mediumBtn);
		_sizesPanel.add(largeBtn);
		_sizesPanel.add(hugeBtn);
		_sizesPanel.add(crazybigBtn);
		_sizesPanel.add(woahthereBtn);
		_sizesPanel.add(overboardBtn);
		_sizesPanel.add(clearBtn);
		_sizesPanel.setLayout(new GridLayout(4, 1));
		add(_sizesPanel, BorderLayout.EAST);	
		
		
		pack();
	}	
}