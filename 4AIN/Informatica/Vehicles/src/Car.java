/**
 * @author Federico Santucci
 */
public class Car extends Vehicle {
	private String licensePlate;
	private int capacity;
	public String getLicensePlate() {
		return licensePlate;
	}

	public void setLicensePlate(String licensePlate) {
		this.licensePlate = licensePlate;
	}

	public int getCapacity() {
		return capacity;
	}

	public void setCapacity(int capacity) {
		this.capacity = capacity;
	}

	public int getFuelTank() {
		return fuelTank;
	}

	public void setFuelTank(int fuelTank) {
		this.fuelTank = fuelTank;
	}

	private int fuelTank;
	
	public Car(String licensePlate, int capacity) {
		super(4, 5);
		this.licensePlate = licensePlate;
		this.capacity = capacity;
		fuelTank = 0;
	}
	
	@Override
	public void move() {
		if(fuelTank > 0) {
			super.move();
			--fuelTank;
		}
	}
	
	public void fill(int fuel) {
		if(fuel > 0 && (fuelTank + fuel) < capacity)
			fuelTank += fuel;
	}
	
	@Override
	public String horn() {
		return "beep beep";
	}
	
	@Override
	public String toString() {
		return "Car " + licensePlate + ": " + getWheels() + " Wheels, " + getSeats() + " Seats. The Veicle " + (isMoving() ? "is" : "isn't") + " moving.";
	}
}
