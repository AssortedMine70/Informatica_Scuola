/**
 * @author Federico Santucci
 */
public class Bicicle extends Vehicle {
	private String pedalType;
	private String handlebarType;
	private boolean isRearing;
	
	public Bicicle(String pedalType, String handlebarType) {
		super(2, 1);
		this.pedalType = pedalType;
		this.handlebarType = handlebarType;
		isRearing = false;
	}
	

	public void wheelie() {
		isRearing = true;
	}
	

	public void stopWheelie() {
		isRearing = false;
	}
	
	public boolean isRearing() {
		return isRearing;
	}
	
	@Override
	public String horn() {
		return "drin drin";
	}
	
	public String getPedalType() {
		return pedalType;
	}


	public void setPedalType(String pedalType) {
		this.pedalType = pedalType;
	}


	public String getHandlebarType() {
		return handlebarType;
	}


	public void setHandlebarType(String handlebarType) {
		this.handlebarType = handlebarType;
	}


	public void setRearing(boolean isRearing) {
		this.isRearing = isRearing;
	}


	@Override
	public String toString() {
		return "Bicicle " + pedalType + " " + handlebarType + ": " + getWheels() + " Wheels, " + getSeats() + " Seats. The Veicle " + (isMoving() ? "is" : "isn't") + " moving. The Veicle " + (isRearing() ? "is" : "isn't") + " rearing.";
	}
}
