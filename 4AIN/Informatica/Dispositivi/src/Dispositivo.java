/**
 * @author Federico Santucci
 */
public class Dispositivo {
	private boolean acceso;
	private boolean rotto;
	
	public Dispositivo() {
		acceso = false;
		rotto = false;
	}
	
	public void accendi() {
		if(!rotto)
			acceso = true;
	}
	
	public void spegni() {
		acceso = false;
	}

	public boolean isAcceso() {
		return acceso;
	}

	public void setAcceso(boolean acceso) {
		this.acceso = acceso;
	}

	public boolean isRotto() {
		return rotto;
	}

	public void setRotto(boolean rotto) {
		this.rotto = rotto;
	}
}
