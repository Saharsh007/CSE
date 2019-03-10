
import java.util.Scanner;

public  class Database{
    String name,placevisited;
    int travelStart,returndate;

    Scanner in = new Scanner(System.in);
    public void EnterInformation()
    {
        System.out.println("Enter name,place visited,travel start date,return date");
        this.name = in.nextLine();
        this.placevisited = in.nextLine();
        this.travelStart = in.nextInt();
        this.returndate = in.nextInt();


    }

    public void display()
    {
        System.out.println("Name:" + this.name +"\nPlace visited:" + this.placevisited +"\nTravel start:"+ this.travelStart+"\nReturn date:"+ this.returndate);
    }
}
