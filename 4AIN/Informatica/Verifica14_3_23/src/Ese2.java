// Federico Santucci - 4AIN - 14/03/23

import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.Random;

public class Ese2 {
    static void scrittura(int n) {
        String[] strings = {"PUSITO", "LILUPU", "RAFUFU", "ZOFOZO", "BUNIZE", "FEPIGA", "POZIMU",
                            "RICEPA", "SABOGE", "SANURI", "TEVEVO", "CEMOSE", "BETAGE", "LOMINU",
                            "DOGIPU", "MOCODU", "TUSUPA", "PODEMA", "CEDURI", "PEPITI"};
        Random r = new Random();

        try (DataOutputStream dos = new DataOutputStream(new FileOutputStream("dati.dat"))) {
            for(int i = 0; i < n; ++i) {
                dos.writeInt(i + 1);
                dos.writeUTF(strings[r.nextInt(strings.length)]);
                dos.writeFloat(r.nextFloat());
                dos.writeChar(' ');
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        scrittura(5);
    }
}
