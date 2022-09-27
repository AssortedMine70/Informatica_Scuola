/**
 * @author Federico Santucci
 */
public class Main {

	public static void main(String[] args) {
		Veicle v = new Veicle(3, 6);
		System.out.println(v);
		v.move();
		System.out.println(v);
		System.out.println(v.horn());
		v.stop();
		System.out.println(v);
		System.out.println();
		
		v = new Bicicle("City Pedals");
		System.out.println(v);
		v.move();
		System.out.println(v);
		System.out.println(v.horn());
		v.stop();
		System.out.println(v);
		System.out.println();
		
		Car c = new Car("FB1CIA", 100);
		System.out.println(c);
		c.move();
		System.out.println(c);
		c.fill(60);
		c.move();
		System.out.println(c);
		System.out.println(c.horn());
		c.stop();
		System.out.println(c);
		System.out.println();
	}

}
