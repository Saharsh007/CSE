import java.util.Scanner;

public class q1 {

    public static void main(String[] args)
    {
        Parallelogram p = new Parallelogram();
        Rectangle r = new Rectangle();
        Square s = new Square();
        Trapezoid t = new Trapezoid();
        System.out.println("Enter coordinates!");
        Scanner in = new Scanner(System.in);
        int x1,x2,x3,x4;
        int y1,y2,y3,y4;
        x1 = in.nextInt();
        y1 = in.nextInt();
        x2 = in.nextInt();
        y2 = in.nextInt();
        x3 = in.nextInt();
        y3 = in.nextInt();
        x4 = in.nextInt();
        y4 = in.nextInt();

        p.assign(x1,x2,x3,x4,y1,y2,y3,y4);
        r.assign(x1,x2,x3,x4,y1,y2,y3,y4);
        s.assign(x1,x2,x3,x4,y1,y2,y3,y4);
        t.assign(x1,x2,x3,x4,y1,y2,y3,y4);
        p.area();
        r.area();
        s.area();
        t.area();

    }
}
