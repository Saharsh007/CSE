import java.util.Scanner;

public class AgeDatabase extends Database {

    Scanner in = new Scanner(System.in);
    int age;
    public void AddAge()
    {
        System.out.println("Enter Age");
        this.age = in.nextInt();
    }

    public void displaychild()
    {
        System.out.println("Name:" + this.name +"\nAge:"+this.age +"\nPlace visited:" + this.placevisited +"\nTravel start:"+ this.travelStart+"\nReturn date:"+ this.returndate);
    }

}
