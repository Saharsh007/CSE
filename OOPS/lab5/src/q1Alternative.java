import java.util.Scanner;

public class q1Alternative {
    public static void main(String[] args )
    {
        int choice;
        Scanner in = new Scanner(System.in);
        System.out.println("Square:1\nRectangle:2\nParallelogram:3\nTrapzoid:4");
        choice = in.nextInt();


        if(choice == 1)
        {
            Square s = new Square();
            System.out.println("Enter sides!");

            int d1 =in.nextInt();
            int d2 =in.nextInt();
            s.findarea(d1,d2);
        }
        else if(choice == 2)
        {
            Rectangle r = new Rectangle();

            System.out.println("Enter sides!");

            int d1 =in.nextInt();
            int d2 =in.nextInt();
            r.findarea(d1,d2);

        }
        else if(choice ==3)
        {
            Parallelogram p = new Parallelogram();
            System.out.println("Enter digonals!");

            int d1 =in.nextInt();
            int d2 =in.nextInt();
            p.findarea(d1,d2);

        }
        else if(choice ==4)
        {
            Trapezoid t = new Trapezoid();

            System.out.println("Enter parallel sides and height!");

            int d1 =in.nextInt();
            int d2 =in.nextInt();
            int h = in.nextInt();
            t.findarea(d1,d2,h);
        }
        else
        {
            System.out.println("WRONG INPUT \nTERMINATING...");
        }

    }

}
