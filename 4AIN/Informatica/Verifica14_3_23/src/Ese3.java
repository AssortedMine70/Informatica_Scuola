// Federico Santucci - 4AIN - 14/03/23

import java.io.DataInputStream;
import java.io.FileInputStream;
import java.io.IOException;

public class Ese3 {
    static void lettura() {
        try (DataInputStream dis = new DataInputStream(new FileInputStream("dati.dat"))) {
            while (dis.available() != 0) {
                System.out.println(
                        dis.readInt() + " " +
                        dis.readUTF() + " " +
                        dis.readFloat() + " " +
                        dis.readChar() + "\n"
                );
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        lettura();
    }
}
