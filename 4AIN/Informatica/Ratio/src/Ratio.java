/**
 * @author Federico Santucci
 */
public class Ratio {
	private int n;
	private int d;
	
	public Ratio(int n, int d) {
		if(d < 0) {
			n = -n;
			d = -d;
		}
		
		int mcd = mcd(n, d);
		this.n = n / mcd;
		this.d = d / mcd;
	}
	
	// Sum
	public Ratio add(Ratio r) {
		return new Ratio(n * r.d + r.n * d, d * r.d);
	}
	
	public static Ratio add(Ratio r, Ratio s) {
		return new Ratio(s.n * r.d + r.n * s.d, s.d * r.d);
	}
	
	// Product
	
	
	// toString
	@Override
	public String toString() {
		return n + "/" + d;
	}
	
	// MCD
	private int mcd(int a, int b) {
		int t;
		while (b != 0) {
			t = b;
		 	b = a % b;
		 	a = t;
		}
		return a;
	}
}
