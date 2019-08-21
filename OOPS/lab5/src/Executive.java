public class Executive extends Manager {

    Executive(String name,String designation,String department,int salary)
    {
//        super(department,super(name,designation,salary));
        Executive.this.salary = salary;
        Executive.this.department = department;
        Executive.this.designation = designation;
        Executive.this.name = name;

    }
    public void printall()
    {
        System.out.println("Name:"+name+"\nDesignation:"+ designation+ "\nDepartment:" + department+"\nSalary;"+salary);
    }
}
