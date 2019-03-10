public class Square extends Quadrilateral{

    double digonal1  =  Math.sqrt( Math.abs((x1-x4)*(x1-x4)) + Math.abs((y1-y4)*(y1-y4)) );
    double digonal2  =  Math.sqrt( Math.abs((x2-x3)*(x2-x3)) + Math.abs((y2-y3)*(y2-y3)) );

    double side1=  Math.sqrt( Math.abs((x1-x2)*(x1-x2)) + Math.abs((y1-y2)*(y1-y2)) );
    double side2=  Math.sqrt( Math.abs((x2-x4)*(x2-x4)) + Math.abs((y2-y4)*(y2-y4)) );
    double side3=  Math.sqrt( Math.abs((x4-x3)*(x4-x3)) + Math.abs((y4-y3)*(y4-y3)) );
    double side4=  Math.sqrt( Math.abs((x1-x3)*(x1-x3)) + Math.abs((y1-y3)*(y1-y3)) );

    int angle1 = (int) (Math.acos((side1*side1 + side4*side4 - digonal2*digonal2 )/(2*side1*side4) )*180/Math.PI);
    int angle2 = (int) (Math.acos((side1*side1 + side2*side2 - digonal1*digonal1 )/(2*side1*side2) )*180/Math.PI);
    int angle3 = (int) (Math.acos((side3*side3 + side4*side4 - digonal2*digonal2 )/(2*side3*side4) )*180/Math.PI);
    int angle4 = (int) (Math.acos((side3*side3 + side2*side2 - digonal1*digonal1 )/(2*side3*side2) )*180/Math.PI);




    public void area()
    {
        int flag = 0;

        if(side1-side3<1 && side1-side3>0 ) flag =0;
        if(side1 != side2) flag =0;
        if(side1 != side4) flag =0;
        if(side2 != side3) flag =0;
        if(side2 != side4) flag =0;
        if(side3 != side4) flag =0;

        if(angle1 != 90) flag =0;
        if(angle2 != 90) flag =0;
        if(angle3 != 90) flag =0;
        if(angle4 != 90) flag =0;

        if(flag == 0)
        {
            System.out.println("NOT A Square");
        }
        else {
            System.out.println("Area of square is " + side1*side1);
        }
    }

    public void findarea(int d1,int d2)
    {
        System.out.println("Area of square is " + d1*d2);
    }

}
