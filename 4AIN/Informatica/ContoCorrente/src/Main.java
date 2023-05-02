import java.util.Random;
import java.util.concurrent.Semaphore;

class ContoCorrente {
	Semaphore s = new Semaphore(1);
	int conto = 0;
	
	public synchronized void preleva(int n, int x) {
		try {
			s.acquire();
			if(n <= conto && n <= 1000) {
				conto -= n;
				System.out.println("Prelievo effettuato dal Thread" + x);
			} else {
				System.out.println("Prelievo negato al Thread" + x);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			s.release();
		}
	}
	
	public synchronized void deposita(int n, int x) {
		try {
			s.acquire();
			System.out.println("Conto = " +  conto);
			if(n <= 1500) {
				conto += n;
				System.out.println("Deposito effettuato dal Thread " + x);
			} else {
				System.out.println("Deposito negato al Thread " + x);
			}
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} finally {
			System.out.println("Conto = " + conto);
			s.release();
		}
	}
}

class Cliente extends Thread {
	int n;
	ContoCorrente c;
	Random r;
	
	public Cliente(int n, ContoCorrente c) {
		this.n = n;
		this.c = c;
		r = new Random();
	}
	
	@Override
	public void run() {
		while(true) {
			int k = r.nextInt(50, 2000);
			if(r.nextBoolean()) {
				System.out.println("Il Thread " + n + " tenta di prelevare " + k);
				c.preleva(k, n);
			} else {
				System.out.println("Il Thread " + n + " tenta di depositare " + k);
				c.deposita(k, n);
			}
			
			try {
				System.out.println("Il Thread " + n + " riposa");
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
}

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		ContoCorrente c = new ContoCorrente();
		Cliente[] clienti = new Cliente[5];
		
		for (int i = 0; i < clienti.length; i++) {
			clienti[i] = new Cliente(i, c);
		}
		
		for (Cliente cliente : clienti) {
			cliente.start();
		}
	}

}
