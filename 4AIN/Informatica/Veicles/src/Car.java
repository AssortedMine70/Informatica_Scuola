
public class Car extends Veicle {
	private String licensePlate;
	private int capacity;
	private int fuelTank = 0;
	
	public Car(String licensePlate, int capacity) {
		super(4, 5);
		this.licensePlate = licensePlate;
		this.capacity = capacity;
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
