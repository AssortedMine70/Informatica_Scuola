import java.util.Random;

class Toilette {
    private int postiLiberi = 5;
    private int nDonneWaiting = 0;

    private final Object uomini = new Object();
    private final Object donne = new Object();

    public void entra(boolean isDonna) throws InterruptedException {
        while(postiLiberi == 0 && (isDonna == false && nDonneWaiting > 0)) {
            if(isDonna) {
                ++nDonneWaiting;
                synchronized (donne) {
                    donne.wait();
                }
            } else {
                synchronized (uomini) {
                    uomini.wait();
                }
            }
        }
        if(isDonna)
            --nDonneWaiting;
        --postiLiberi;
    }

    public void esci() {
        ++postiLiberi;
        if(nDonneWaiting > 0)
            donne.notifyAll();
        else
            uomini.notifyAll();
    }
}

class Persona extends Thread {
    Toilette toilette;
    boolean isDonna;

    public Persona(Toilette toilette, boolean isDonna) {
        this.toilette = toilette;
        this.isDonna = isDonna;
    }

    @Override
    public void run() {
        try {
            toilette.entra(isDonna);
            System.out.println("un " + (isDonna ? "a Donna" : "Uomo") + " è entrat" + (isDonna ? "a" : "o") + " in bagno.");
            Thread.sleep(500);
            System.out.println("un " + (isDonna ? "a Donna" : "Uomo") + " è uscit" + (isDonna ? "a" : "o") + " dal bagno.");
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

        toilette.esci();
    }
}

public class Main {
    public static void main(String[] args) {
        Toilette toilette = new Toilette();

        for(int i = 0; i < 5; ++i) {
            new Persona(toilette, new Random().nextBoolean()).start();
        }
    }
}