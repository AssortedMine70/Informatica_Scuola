/**
 * @author Federico Santucci
 */
public class Computer extends Dispositivo {
	private String marca;
	private int ram;
	
	Computer(String marca, int ram) {
		super();
		this.marca = marca;
		this.ram = ram;
	}
	
	public String getMarca() {
		return marca;
	}
	
	public void setMarca(String marca) {
		this.marca = marca;
	}
	public int getRam() {
		return ram;
	}
	public void setRam(int ram) {
		this.ram = ram;
	}
}
