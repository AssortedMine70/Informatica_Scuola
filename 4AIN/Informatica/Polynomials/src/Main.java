/**
 * @author Federico Santucci
 */
public class Main {
    public static void main(String[] args) {
        Poly p = Poly.genera(5);
        Poly q = Poly.genera(3);
        System.out.println("Polinomio p:        " + p);
        System.out.println("Polinomio q:        " + q);
        System.out.println();
        System.out.println("Addizione:          " + p.add(q));
        System.out.println("Sottrazione:        " + p.sub(q));
        System.out.println("Moltiplicazione:    " + p.mul(q));
        System.out.println("Divisione:          " + p.div(q));
        System.out.println("Modulo:             " + p.mod(q));
    }
}
