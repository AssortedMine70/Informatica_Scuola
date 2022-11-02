public class Complex {
    private float a;
    private float b;

    public Complex(float a, float b) {
        this.a = a;
        this.b = b;
    }

    public Complex sum(Complex c) {
        return new Complex(a + c.a, b + c.b);
    }

    public Complex sub(Complex c) {
        return sum(new Complex(-c.a, -c.b));
    }

    public Complex mul(Complex c) {
        return new Complex(a*c.a - b*c.b, a*c.b + b*c.a);
    }

    public Complex div(Complex c) {
        return new Complex((a * c.a + b*c.b)/(c.a*c.a + c.b*c.b), (b*c.a - a*c.b)/(c.a*c.a + c.b*c.b));
    }

    public Complex pow(int i) {
        switch (i%4){
            case 1:
                return new Complex((float)Math.pow(a,i), (float)Math.pow(b,i));
            case 2:
                return new Complex((float)(Math.pow(a,i) - Math.pow(b,i)),0);
            case 3:
                return new Complex((float) Math.pow(a, i), (float) -Math.pow(b, i));
            default:
                return new Complex((float)(Math.pow(a,i) + Math.pow(b,i)),0);
        }
    }

    public Complex reciprocal() {
        return new Complex(1,0).div(Complex.this);
    }

    @Override
    public String toString() {
        return a + b != 0? (" + i" + b) : "";
    }
}
