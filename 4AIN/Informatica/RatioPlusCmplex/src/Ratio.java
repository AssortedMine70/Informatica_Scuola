/**
 * @author Federico Santucci
 */

public class Ratio {
    private int num;
    private int den;

    public Ratio(int num, int den) {
        int mcd = gcd(num,den);
        this.num = num/mcd;
        this.den = den/mcd;
    }

    public Ratio add(Ratio r) {
        return new Ratio(this.num*r.den+r.num*this.den,this.den*r.den);
    }

    public Ratio sub(Ratio r) {
        return add(new Ratio(-r.num, r.den));
    }

    public Ratio mul(Ratio r) {
        return new Ratio(this.num*r.num, this.den*r.den);
    }

    public Ratio div(Ratio r) {
        return mul(new Ratio(r.den, r.num));
    }

    public Ratio pow(int i) {
        return new Ratio((int)Math.pow(num, i), (int)Math.pow(den, i));
    }

    public Ratio reciprocal() {
        return new Ratio(den, num);
    }

    public int gcd() {
        return gcd(num, den);
    }

    private static int gcd(int a, int b) {
        if (b==0) return a;
        return gcd(b,a%b);
    }

    @Override
    public String toString() {
        return num+"/"+den;
    }
}
