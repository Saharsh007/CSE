import java.util.Scanner;

public class q2 {
    public static void  main(String[] args)
    {
        String name,designation,department;
        int salary;
        Scanner in = new Scanner(System.in);
        System.out.println("Enter name");
        name = in.nextLine();
        System.out.println("Enter designation");
        designation = in.nextLine();
        System.out.println("Enter department");
        department = in.nextLine();
        System.out.println("Enter salary");
        salary = in.nextInt();

        Executive e =new Executive(name,designation,department,salary);
        e.printall();



    }
}
