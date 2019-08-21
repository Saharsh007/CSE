public class Trapezoid extends Quadrilateral{

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

    double temp1,temp2,height;


    public void area()
    {
        int flag = 0;

        if(angle1+ angle2 == 180)
        {
            if(flag == 1)  {System.out.println("NOT A trapezium"); return;}
            flag= 1;
            temp1 = side4;
            temp2 = side2;
            double tempside,tempangle= Math.min(angle1,angle2);
            if(tempangle == angle1)
            {
                tempside = side1;
            }
            else
                tempside = side1;
            height =  Math.sin(Math.min(angle1,angle2)*180/Math.PI)*tempside;
        }
        if(angle1+ angle3 == 180)
        {
            if(flag == 1)  {System.out.println("NOT A trapezium"); return;}
            flag= 1;
            temp1 = side1;
            temp2 = side3;
            height =  Math.sin(Math.min(angle1,angle3)*180/Math.PI)*side4;
        }
        if(angle2+ angle4 == 180)
        {
            if(flag == 1)  {System.out.println("NOT A trapezium"); return;}
            flag= 1;
            temp1 = side1;
            temp2 = side3;
            height =  Math.sin(Math.min(angle4,angle2)*180/Math.PI)*side2;
        }
        if(angle3+ angle4 == 180)
        {
            if(flag == 1)  {System.out.println("NOT A trapezium"); return;}
            flag= 1;
            temp1 = side4;
            temp2 = side2;
            height =  Math.sin(Math.min(angle3,angle4)*180/Math.PI)*side3;
        }



        if(flag == 0)
        {
            System.out.println("NOT A trapzoid");
        }
        else {
            System.out.println("Area of trapzoid is " + (temp1+temp2)*height/2);
        }
    }

    public void findarea(int d1,int d2,int height)
    {
        System.out.println("Area of trapzoid is " + (d1+d2)*height/2);
    }
}
