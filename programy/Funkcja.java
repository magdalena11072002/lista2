import static java.lang.Math.pow;
import static java.lang.Math.sin;
public class Funkcja {
    private double oblicz(double x){
        //return pow(x,(1.0/3.0));
        //return sin(x);
        //return (4*x)*pow((1-x),3);
        return Math.PI*x*x;
    }
    double returnn(int n) {
            int counter = 0;
            Random random = new Random();
            for (int i = 1; i <= n; i++) {
                double x = random.nextDouble();
                double y = random.nextDouble();
                double xi = 2*x;
                double yi = 2*y;
                if (yi <= oblicz(xi)) {
                    counter++;
                }
            }
            return (1.0 * counter) / n;
        }
}
