import java.util.Random;

class Bacchetta {
    private boolean isUp;
    private int n;

    public Bacchetta(int n) {
        isUp = false;
        this.n = n;
    }
    public synchronized void up() {
        while (isUp) {
            try {
                wait();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }
        isUp = true;
    }
    public synchronized void down() {
        isUp = false;
        notifyAll();
    }

    @Override
    public String toString() {
        return "Bacchetta{" +
                "n=" + n +
                ", isUp=" + isUp +
                '}';
    }
}

class Filosofo extends Thread {
    private static Object lock = new Object();
    private Bacchetta sx, dx;
    private int n;
    public Filosofo(int n, Bacchetta sx, Bacchetta dx) {
        this.n = n;
        this.sx = sx;
        this.dx = dx;
    }
    @Override
    public void run() {
        while(true) {
            synchronized (lock) {
                sx.up();
                System.out.println(n + " ha alzato una bacchetta: " + sx);
                dx.up();
                System.out.println(n + " ha alzato una bacchetta: " + dx);
            }
            /*try {
                sleep(new Random().nextInt(3) * 1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }*/
            System.out.println(n + " ha mangiato");
            //synchronized (lock) {
            sx.down();
            System.out.println(n + " ha abbassato una bacchetta: " + sx);
            dx.down();
            System.out.println(n + " ha abbassato una bacchetta: " + dx);
            //}
            /*try {
                sleep(new Random().nextInt(3) * 1000);
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }*/
            System.out.println(n + " ha pensato");
        }
    }
}

public class Main {
    public static void main(String[] args) {
        Filosofo[] f = new Filosofo[5];
        Bacchetta[] b = new Bacchetta[5];

        for (int i = 0; i < f.length; i++) {
            b[i] = new Bacchetta(i);
        }

        for (int i = 0; i < f.length; i++) {
            f[i] = new Filosofo(i, b[i], b[(i + 1)%b.length]);
        }

        for (Filosofo filosofo : f) {
            filosofo.start();
        }
    }
}