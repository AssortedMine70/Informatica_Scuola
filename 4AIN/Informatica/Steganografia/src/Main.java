import java.io.*;
import java.util.Arrays;

class Steganografia {
    public void codifica(String str) throws IOException {
        byte[] bytes = str.getBytes();
        try (DataInputStream r = new DataInputStream(new FileInputStream("./assets/immagine.bmp"))) {
            try (DataOutputStream w = new DataOutputStream(new FileOutputStream("./assets/immagine-codificata.bmp"))) {
                // copy the first bytes until the bytes containing the offset
                w.write(r.readNBytes(11));
                // reads the offset and proceeds to copy the rest of the header
                int offset = r.readInt();
                System.out.println(offset);
                w.writeInt(offset);
                w.write(r.readNBytes(offset));
                // starts codifying the string in the image data
                System.out.println(Arrays.toString(bytes));
                for (byte b : bytes) {
                    System.out.println(b);
                    for (int i = 0; i < 8; ++i) {
                        byte imgByte = r.readByte();
                        if ((b & 1) == 0) {
                            imgByte &= ~1;
                        } else {
                            imgByte |= 1;
                        }
                        w.write(imgByte);
                        b >>= 1;
                    }
                }
                while(r.available() != 0) {
                    w.write(r.read());
                }
            }
        }
    }
    public String decodifica() {
        return new String();
    }
}

public class Main {
    public static void main(String[] args) throws IOException {
        new Steganografia().codifica("ciao");
    }
}