import java.util.Random;

class PonteRisorsaCondivisa {
	public int portata;
	public int pesoVeicoli;
	public int maxVeicoli;
	public int nVeicoli;
	
	public PonteRisorsaCondivisa(int portata, int maxVeicoli) {
		this.portata = portata;
		this.maxVeicoli = maxVeicoli;
		pesoVeicoli = 0;
		nVeicoli = 0;
	}
	
	public void entrato(VeicoloTH v) {
		pesoVeicoli += v.peso;
		++nVeicoli;
		log(v.ID);
	}
	
	public void uscito(VeicoloTH v) {
		pesoVeicoli -= v.peso;
		--nVeicoli;
		log(v.ID);
	}
	
	public void log(int ID) {
		System.out.println("ID: " + ID);
		System.out.println("nVeicoli = " + nVeicoli);
		System.out.println("maxVeicoli = " + maxVeicoli);
		System.out.println("pesoVeicoli = " + pesoVeicoli);
		System.out.println("portata = " + portata);
	}
}

class Monitor {
	PonteRisorsaCondivisa p;
	
	public Monitor(PonteRisorsaCondivisa p) {
		this.p = p;
	}
	
	public synchronized void entra(VeicoloTH v) throws InterruptedException {
		while((p.pesoVeicoli + v.peso > p.portata) || (p.nVeicoli + 1 > p.maxVeicoli)) {
			System.out.println("Veicolo " + v.ID + " in attesa");
			wait();
		}
		p.entrato(v);
	}
	
	public synchronized void esci(VeicoloTH v) {
		p.uscito(v);
		notifyAll();
	}
}

class VeicoloTH extends Thread {
	int ID;
	int peso;
	Monitor m;
	
	public VeicoloTH(int ID, int peso, Monitor m)  {
		this.ID = ID;
		this.peso = peso;
		this.m = m;
	}
	
	@Override
	public void run() {
		try {
			System.out.println("Veicolo " + ID + " si mette in coda (Peso:" + peso + ")");
			m.entra(this);
			System.out.println("Veicolo " + ID + " entra");
			Thread.sleep(peso);
			System.out.println("Veicolo " + ID + " tenta di uscire");
			m.esci(this);
			System.out.println("Veicolo " + ID + " esce");
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}

public class Main {

	public static void main(String[] args) {
		Random r = new Random();
		int N_VEICOLI = 5;//r.nextInt(10, 20);
		PonteRisorsaCondivisa p = new PonteRisorsaCondivisa(r.nextInt(500, 1500), r.nextInt(2, 8));
		Monitor m = new Monitor(p);
		VeicoloTH veicoli[] = new VeicoloTH[N_VEICOLI];
		
		for (int i = 0; i < veicoli.length; i++) {
			veicoli[i] = new VeicoloTH(i, r.nextInt(300, 500), m);
		}
		
		for (VeicoloTH veicolo : veicoli) {
			veicolo.start();
		}
	}

}
