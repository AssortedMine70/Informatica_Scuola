// Federico Santucci - 4AIN - 14/03/23

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

public class Ese1 {
    static void scrittura() {
        try (PrintWriter pw = new PrintWriter(new FileWriter("ese1.html"))) {
            pw.print(   "<!DOCTYPE html>\n" +
                        "<html>\n" +
                        "    <head>\n" +
                        "       <title>Tabelline</title>\n" +
                        "       <style>\n" +
                        "           table, td {\n" +
                        "               border: 1px solid black;\n" +
                        "               border-collapse: collapse;\n" +
                        "               text-align: right;\n" +
                        "           }\n" +
                        "       </style>\n" +
                        "    </head>\n" +
                        "    <body>\n" +
                        "    <h1>Federico Santucci</h1>\n" +
                        "        <table>\n");

            for (int i = 1; i <= 12; ++i) {
                pw.print(   "            <tr>\n");
                for (int j = 1; j <= 12; ++j) {
                    pw.print("                <td>\n" +
                             "                    " + i * j + "\n" +
                             "                </td>\n");
                }
                pw.print(   "            </tr>\n");
            }

            pw.print(   "        </table>\n" +
                        "    </body>\n" +
                        "</html>"
                      );
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {
        scrittura();
    }
}
