/**
 * @author Federico Santucci
 */
public class Main {
	
	/**
	 * main
	 */
	public static void main(String[] args) {
		NumeroIntero ni;
		for(int i = 0; i < 10; ++i) {
			ni = new NumeroIntero(i);
			System.out.println(i + ": " + ni.isEven());
		}
	}

}