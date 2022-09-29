/**
 * @author Federico Santucci
 */
public class Vehicle {
	private int nWheels;
	private int nSeats;
	private boolean moving;
	
	public Vehicle(int nWheels, int nDoors) {
		moving = false;
		this.nWheels = nWheels;
		this.nSeats = nDoors;
	}
	
	public boolean isMoving() {
		return moving;
	}
	
	public int getWheels() {
		return nWheels;
	}
	
	public int getSeats() {
		return nSeats;
	}
	
	public void move() {
		moving = true;
	}
	
	public void stop() {
		moving = false;
	}
	
	public String horn() {
		return "the horn is playing.";
	}
	
	@Override
	public String toString() {
		return "Veicle: " + nWheels + " Wheels, " + nSeats + " Seats. The Veicle " + (moving ? "is" : "isn't") + " moving.";
	}
}
