import java.awt.*;
import java.util.ArrayList;
import java.util.Scanner;

public class q3 {
    public static void main(String[] args )
    {
        ArrayList<AgeDatabase> passengers = new ArrayList<AgeDatabase>();
        Scanner in = new Scanner(System.in);
        while(true)
        {
            System.out.println("TO ENTER DETAILS 1\nTO CHECK FOR CHILD PASSENGERS 2\n DISPLAY 3 \nEXIT any else");

            int choice = in.nextInt();
            if(choice == 1)
            {
                AgeDatabase p = new AgeDatabase();
                p.EnterInformation();
                p.AddAge();
                passengers.add(p);
                continue;
            }
            else if(choice == 2)
            {
               for(AgeDatabase temp:passengers)
               {
                    if(temp.age <=12)
                        temp.displaychild();
               }
               continue;
            }
            else if(choice == 3)
            {
                for(Database temp:passengers)
                {
                    System.out.println("NEXT PASSENGER\n");
                        temp.display();

                }
                continue;
            }

            else{
                break;
            }
        }
    }
}
