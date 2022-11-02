import java.util.Random;

/**
 * A Java class that takes care of Polynomials.
 * @author Federico Santucci
 */
public class Poly {
    private float[] poly;

    /**
     * Creates an empty Poly.
     */
    public Poly() {
        poly = new float[0]; // preferred for reducing null pointer exceptions.
    }

    /**
     * Takes an Array and converts it into a Poly.
     * @param poly Array of Integer Values that will become Poly numeral Parts.
     */
    public Poly(float[] poly) {
        int zeros = 0;
        for(int i = poly.length-1; i >= 0; --i)
            if(poly[i] == 0) ++zeros;
            else break;
        float[] newPoly = new float[poly.length - zeros];
        System.arraycopy(poly, 0, newPoly, 0, newPoly.length);
        this.poly = newPoly;
    }

    /**
     * Generates a Poly of a certain grade and numeral parts between -10 and 10.
     * @param i The grade of the Poly that will be generated.
     * @return The Poly that as been generated.
     */
    public static Poly genera(int i) {
        float[] random = new float[i+1];
        Random r = new Random();
        for(int j = 0; j < random.length; ++j)
            random[j] = r.nextFloat(-10, 10);
        while(random[i]==0)
            random[i] = r.nextFloat(-10, 10);
        return new Poly(random);
    }

    /**
     * Adds a Poly p to the one contained in the Object itself.
     * @param p The Poly to add to the one contained in the Object itself.
     * @return A Poly that is the sum between the one contained in the Object itself and the parameter p.
     */
    public Poly add(Poly p) {
        float[] sum;
        if (poly.length > p.poly.length) {
            sum = poly.clone();
            for(int i = 0; i<p.poly.length; ++i)
                sum[i] += p.poly[i];
        } else {
            sum = p.poly.clone();
            for (int i = 0; i < poly.length; ++i)
                sum[i] += poly[i];
        }
        return new Poly(sum);
    }

    /**
     * Subtracts a Poly p to the one contained in the Object itself.
     * @param p The Poly to subtract to the one contained in the Object itself.
     * @return A Poly that is the subtraction between the one contained in the Object itself and the parameter p.
     */
    public Poly sub(Poly p) {
        return add(p.neg());
    }

    /**
     * Multiplies a Poly p to the one contained in the Object itself.
     * @param p The Poly to multiply the one contained in the Object itself.
     * @return A Poly that is the multiplication between the one contained in the Object itself and the parameter p.
     */
    public Poly mul(Poly p) {
        float[] result = new float[poly.length + p.poly.length];
        for(int i=0; i < poly.length; ++i)
            for(int j=0; j < p.poly.length; ++j)
                result[i+j] += poly[i] * p.poly[j];
        return new Poly(result);
    }

    /**
     * Divides a Poly p to the one contained in the Object itself.
     * @param p The Poly to divide the one contained in the Object itself.
     * @return A Poly that is the division between the one contained in the Object itself and the parameter p.
     */
    public Poly div(Poly p) {
        Poly q = new Poly(poly.clone());
        Poly result = new Poly();
        if(p.poly.length != 0 && poly.length-1>=p.poly.length-1) {
            while(q.poly.length >= p.poly.length) {
                if(p.poly[p.poly.length-1] != 0) {
                    float[] temp = new float[q.poly.length];
                    temp[q.poly.length - p.poly.length] = q.poly[q.poly.length-1] / p.poly[p.poly.length-1];
                    q = q.sub(p.mul(new Poly(temp)));
                    result = result.add(new Poly(temp));
                }
            }
            return result;
        }
        else if(p.poly.length != 0)
            return new Poly();
        return null;
    }

    /**
     * Divides a Poly p to the one contained in the Object itself and returns the module.
     * @param p The Poly to divide the one contained in the Object itself.
     * @return A Poly that is the module between the one contained in the Object itself and the parameter p.
     */
    public Poly mod(Poly p) {
        Poly q = new Poly(poly.clone());
        float[] result = new float[q.poly.length];
        if(p.poly.length != 0 && poly.length-1>=p.poly.length-1) {
            while(q.poly.length >= p.poly.length) {
                if(p.poly[p.poly.length-1] != 0) {
                    float[] temp = new float[q.poly.length];
                    temp[q.poly.length - p.poly.length] = q.poly[q.poly.length-1] / p.poly[p.poly.length-1];
                    q = q.sub(p.mul(new Poly(temp)));
                }
            }
            return q;
        }
        else if(p.poly.length != 0)
            return new Poly();
        return null;
    }

    /**
     * Negates the Poly that is contained in the Object itself.
     * @return The Poly that is the negation of the Poly that is contained in the Object itself.
     */
    public Poly neg() {
        float[] neg = new float[poly.length];
        for (int i = 0; i < poly.length; ++i)
            neg[i] = -poly[i];
        return new Poly(neg);
    }

    /**
     * Generates a String that represents the Poly contained in the Object.
     * @return A String that represents the Poly contained in the Object.
     */
    @Override
    public String toString() {
        if(poly.length > 0) {
            StringBuilder str = new StringBuilder();
            for (int i = poly.length-1; i >= 0; --i) {
                if(poly[i]!=0) {
                    if(i!=poly.length-1) {
                        if (poly[i] >= 0) {
                            str.append(" + ");
                        } else {
                            str.append(" - ");
                        }
                    }
                    str.append((String.format("%.2f", poly[i] >= 0 ? poly[i] : -poly[i])) + (i!=0? "x^" + i : ""));
                }
            }
            return str.toString();
        }
        return "Polinomio Nullo";
    }
}