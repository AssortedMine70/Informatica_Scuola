
public class Bicicle extends Veicle {
	private String pedalType;
	
	public Bicicle(String pedalType) {
		super(2, 1);
		this.pedalType = pedalType;
	}
	
	@Override
	public String horn() {
		return "drin drin";
	}
	
	@Override
	public String toString() {
		return "Bicicle " + pedalType + ": " + getWheels() + " Wheels, " + getSeats() + " Seats. The Veicle " + (isMoving() ? "is" : "isn't") + " moving.";
	}
}
