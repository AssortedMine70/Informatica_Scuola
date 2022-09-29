/**
 * @author Federico Santucci
 */
public class Main {

	public static void main(String[] args) {
		Vehicle v = new Vehicle(3, 6);
		System.out.println(v);
		v.move();
		System.out.println(v);
		v.stop();
		System.out.println(v);
		System.out.println();
		
		Bicicle b = new Bicicle("City Pedals", "City Handle");
		System.out.println(b);
		b.move();
		System.out.println(b);
		b.wheelie();
		System.out.println(b);
		b.stopWheelie();
		System.out.println(b.horn());
		b.stop();
		System.out.println(b);
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
