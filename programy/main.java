import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import static java.lang.Math.pow;
public class main {
    public static void main(String args[]) throws FileNotFoundException {
        for(int n=50;n<5001;n+=50) {
            final String name = "mpis"+n+".txt";
            double[] tab = new double[n];
            Funkcja f = new Funkcja();
            for (int i = 0; i < 50; i++) {
                tab[i] = f.returnn(n)*4;
            }
            //kontrola wyników w terminalu
            for (int i = 0; i < 50; i++) {
                System.out.println(tab[i]);
            }
            // zapis do pliku
        File file = new File(name);
        PrintWriter record=new PrintWriter(name);
        for(int i=0;i<50;i++) {
            record.println(tab[i]);
        }
        record.close();
        }
    }
}
