import java.util.*;

public class main {

    static ArrayList<books> listOfBooks = new ArrayList<>();
    static ArrayList<student> listOfStudents = new ArrayList<>();
    static ArrayList<teacher> listOfTeachers = new ArrayList<>();
    static Scanner in;
    static Date date;
    static Date today = new Date();

    public static void main(String[] args) {
         in = new Scanner(System.in);


         date = new Date();
        addSomeBooks();

        while(true) {
            //date work
//            System.out.println("Enter number of days passed\n");
//            int x = in.nextInt();
//            in.nextLine();
//
//            if(x < 0){
//                System.out.println("WRONG INPUT!! PASSED DAYS CAN'T BE NEAGTIVE\n");
//                continue;
//            }
            int x = 1;
            long currdate = date.getTime();
            currdate += x*24*60*60*1000;
            date.setTime(currdate);
            System.out.println("Current date is " + date+ "\n");
            //date work done

            //asking for type of user
            System.out.println("Teacher:1\tStudent:2\tLibrarian:3\tQuit any else\n");
            int type = in.nextInt();
            in.nextLine();

            if(type == 1) {loginedAsTeacher();}
            else if(type == 2) {loginedAsStudent();}
            else if(type == 3) {loginedAsLibrarian();}
            else  break;

        }
    }

    private static void loginedAsTeacher() {

        teacher currTeacher = new teacher();
        boolean flag =false;
        System.out.println("ENTER YOUR NAME");
        String userName = in.nextLine();
        for(teacher allTeacher : listOfTeachers)
        {
            if(allTeacher.name.equals(userName)){
                currTeacher = allTeacher;
                flag = true;
                break;
            }
        }
        if(!flag){
            System.out.println("SORRY YOUR NAME ISN'T IN DATABASE\nBUT NO WORRIES WE'LL CREATE A ENTRY FOR YOU , NOW\n");
            teacher newTeacher = new teacher();
            System.out.println("ENTER NAME\n");
            newTeacher.name = in.nextLine();
            listOfTeachers.add(newTeacher);
            System.out.println("CONGRATS , YOU ARE NOW OFFICIAL MEMBER OF LIBRARY !!!\n PLEASE COME SOON AGAIN\n");
            return;
        }

        System.out.println("View Most Recent Book Added:1\tIssue any book:2\tSubmit Any Book:3\tCome on, I am comps student , I don't read books : any else\n");
        int choice  = in.nextInt();
        in.nextLine();

        if(choice == 1) {  viewRecentBook(currTeacher); }
        else if(choice ==2 ) {  currTeacher =  issueBook(currTeacher); }
        else if(choice == 3) {  currTeacher =  submitBook(currTeacher); }
        else System.out.println("WRONG INPUT!&*#%^!(*#%*&@(&!\n");
    }



    private static void loginedAsStudent() {

        student currStudent = new student();
        boolean flag =false;
        System.out.println("ENTER YOUR NAME");
        String userName = in.nextLine();
        for(student allStudent : listOfStudents)
        {
            if(allStudent.name.equals(userName)){
                currStudent = allStudent;
                flag = true;
                break;
            }
        }
        if(!flag){
                System.out.println("SORRY YOUR NAME ISN'T IN DATABASE\nBUT NO WORRIES WE'LL CREATE A ENTRY FOR YOU , NOW\n");
                student newStudent = new student();
                System.out.println("ENTER NAME\n");
                newStudent.name = in.nextLine();
                listOfStudents.add(newStudent);
                System.out.println("CONGRATS , YOU ARE NOW OFFICIAL MEMBER OF LIBRARY !!!\n PLEASE COME SOON AGAIN\n");
                return;
        }

        System.out.println("View Most Recent Book Added:1\tIssue any book:2\tSubmit Any Book:3\tCome on, I am comps student , I don't read books : any else\n");
        int choice  = in.nextInt();
        in.nextLine();

        if(choice == 1) {  viewRecentBook(currStudent); }
        else if(choice ==2 ) { currStudent = issueBook(currStudent); }
        else if(choice == 3) { currStudent = submitBook(currStudent); }
        else System.out.println("WRONG INPUT!&*#%^!(*#%*&@(&!\n");
    }



    private static void loginedAsLibrarian() {

        System.out.println("Add Book : 1\tDelete Book : 2\tView book : 3\tView Issued Book : 4\t" +
                            "Show all Delayed books : 5\tSearch books : 6\tNothing!! I am going home : any other\n");
        int choice = in.nextInt();
        in.nextLine();

        if(choice == 6) { searchBooks(); }
        else if(choice == 1) { addBook();}
        else if(choice == 2) { deleteBook();}
        else if(choice == 3) { viewAllBooks();}
        else if(choice == 4) { viewIssuedBooks();}
        else if(choice == 5) { showDelayedBooks();}
        else return;



    }





    ///////////////////////////////////////////////////////////LIBRARIAN'S CODE
    private static void showDelayedBooks() {
        boolean booksbool = false;

        for (books allBooks : listOfBooks){
            if(allBooks.getIssue())
            {
                if(allBooks.issuedBy) {
                    long delaytime = date.getTime() - allBooks.issueDate.getTime();
                    delaytime = delaytime / 24 * 60 * 60 * 1000;
                    if (delaytime > 15){
                        printBookDetails(allBooks);
                    booksbool = true;
                     }
                }
                else{
                    long delaytime  =   date.getTime() - allBooks.issueDate.getTime();
                    delaytime =delaytime/24*60*60*1000;
                    if (delaytime > 30){
                        printBookDetails(allBooks);
                        booksbool = true;
                    }
                }
            }
        }

        if(booksbool == false) System.out.println("NO DELAYED BOOKS\n");
    }


    private static void viewIssuedBooks() {
        if(listOfBooks.size() == 0){
            System.out.println("NO BOOKS EXIST DAMN IT!!\nADD SOME BOOKS\n");
            return;
        }
        for (books allBooks : listOfBooks){
            if(allBooks.getIssue()) printBookDetails(allBooks);
        }
    }


    private static void viewAllBooks() {
        if(listOfBooks.size() > 0)   System.out.println("LIST OF BOOKS COMING RIGHT UP!!");
        else{
            System.out.println("NO BOOKS EXIST DAMN IT!!\nADD SOME BOOKS\n");
            return;
        }
        for (books allBooks : listOfBooks) printBookDetails(allBooks);

    }


    private static void deleteBook() {
        boolean flag = false;
        System.out.println("Enter name of book to be deleted\n");
        String nameEntered = in.nextLine();
        for(books allBooks : listOfBooks){
            if(allBooks.name.equals(nameEntered)) {
                listOfBooks.remove(allBooks);
                flag= true;
                System.out.println("BOOK SUCCESSFULLY REMOVED FROM LIBRARY!\n");
                break;
            }
        }
        if(flag == false) System.out.println("BOOK NOT FOUND!!\n");
    }

    private static void addBook() {
        books newBook = new books();
        System.out.println("Enter name of book\n");
        newBook.name = in.nextLine();
        newBook.dateAdded = date;

        System.out.println("Enter Author name\n");
        newBook.author = in.nextLine();

        System.out.println("ENTER PUBLISHER NAME\n");
        newBook.publisher = in.nextLine();
        listOfBooks.add(newBook);
    }

    private static void searchBooks() {
        System.out.println("SEARCH BY NAME:1\tAUTHOR:2\tPUBLISHER:3");
        int choice = in.nextInt();
        in.nextLine();

        in.nextLine();
        if(choice == 1){

            boolean flag = false;
            System.out.println("ENTER NAME OF BOOK\n");
            String bookName = in.nextLine();
            for(books allbooks : listOfBooks){
                if(allbooks.name.equals(bookName) ){
                    flag = true;
                    printBookDetails(allbooks);
                }
            }

            if(flag == false) {
                System.out.println("BOOK NOT FOUND@\n");
                return;
            }
        }
        else if(choice == 2){
            boolean flag = false;
            System.out.println("ENTER NAME OF AUTHOR\n");
            String authorName = in.nextLine();
            for(books allbooks : listOfBooks){
                if(allbooks.author.equals(authorName) ){
                    flag = true;
                    printBookDetails(allbooks);
                }
            }

            if(flag == false) {
                System.out.println("BOOK NOT FOUND@\n");
                return;
            }
        }
        else if(choice == 3){
            boolean flag = false;
            System.out.println("ENTER NAME OF PUBLISHER\n");
            String publisherName = in.nextLine();
            for(books allbooks : listOfBooks){
                if(allbooks.publisher.equals(publisherName) ){
                    flag = true;
                    printBookDetails(allbooks);
                }
            }

            if(flag == false) {
                System.out.println("BOOK NOT FOUND@\n");
                return;
            }
        }
        else {
            System.out.println("WRONG CHOICE!!\n");
        }
    }

    private static void printBookDetails(books allbooks){
        if(!allbooks.issue)
            System.out.println("Name: " + allbooks.name + "\tAuthor: " + allbooks.author + "\tDate added: " + allbooks.dateAdded + "\n");
        else
            System.out.println("Name: " + allbooks.name + "\tAuthor: " + allbooks.author + "\tDate added: " + allbooks.dateAdded + "Issue date: " + allbooks.issueDate +"\n");

    }
    ///////////////////////////////////////////////////////////LIBRARIAN'S CODE


    //////////////////////////////////////////////////////////////STUDENT'S CODE
    private static student submitBook(student user) {
        boolean flag = true;
        System.out.println("ENTER NAME OF BOOK TO SUBMIT\n");
        String nameOfBook = in.nextLine();
        for(Map<String,Date>  m : user.listOfIssuedBooks){
            if(m.containsKey(nameOfBook)){
                m.remove(nameOfBook);
                flag = false;
                System.out.println("BOOK SUCCESSFULLY REMOVED");
            }
        }
        if(flag == true) System.out.println("BOOK NOT FOUND");

        return user;

    }


    private static student issueBook(student user) {
        boolean flag = true;
        System.out.println("ENTER NAME OF BOOK TO ISSUE\n");
        String nameOfBook = in.nextLine();
        for(books allbooks : listOfBooks){
            if(allbooks.name.equals(nameOfBook) ){
                if(allbooks.issue){
                    System.out.println("ALREADY ISSUED\n");
                    return user;
                }
                flag = false;
                System.out.println("BOOK SUCCESSFULLY ISSUED");
                allbooks.issuedBy = false;//means student
                allbooks.issue = true;
                allbooks.issueDate = date;
                Map<String,Date> m = new HashMap<>();
                m.put(nameOfBook,date);
                user.listOfIssuedBooks.add(m);
            }
        }
        if(flag == true) System.out.println("BOOK NOT FOUND");
        return user;

    }


    private static void viewRecentBook(student user) {
        books booktoDisplay;
        if(listOfBooks.size() == 0) {
            System.out.println("NO BOOK IN LIBRARY\n");
            return;
        }
        booktoDisplay = listOfBooks.get(0);
        for(books allbooks : listOfBooks){
            if(allbooks.dateAdded.after(booktoDisplay.dateAdded) ){
                booktoDisplay = allbooks;
            }
        }

        printBookDetails(booktoDisplay);
    }

    //////////////////////////////////////////////////////////////STUDENT'S CODE




    //////////////////////////////////////////////////////////////TEACHER'S CODE
    private static teacher submitBook(teacher user) {
        boolean flag = true;
        System.out.println("ENTER NAME OF BOOK TO SUBMIT\n");
        String nameOfBook = in.nextLine();
        for(Map<String,Date>  m : user.listOfIssuedBooks){
            if(m.containsKey(nameOfBook)){
                m.remove(nameOfBook);
                flag = false;
                System.out.println("BOOK SUCCESSFULLY REMOVED");
            }
        }
        if(flag == true) System.out.println("BOOK NOT FOUND");

        return user;

    }

    private static void viewRecentBook(teacher user) {

        books booktoDisplay;
        if(listOfBooks.size() == 0) {
            System.out.println("NO BOOK IN LIBRARY\n");
            return;
        }
        booktoDisplay = listOfBooks.get(0);
        for(books allbooks : listOfBooks){
            if(allbooks.dateAdded.after(booktoDisplay.dateAdded) ){
                booktoDisplay = allbooks;
            }
        }

        printBookDetails(booktoDisplay);
    }

    private static teacher issueBook(teacher user) {
        boolean flag = true;
        System.out.println("ENTER NAME OF BOOK TO ISSUE\n");
        String nameOfBook = in.nextLine();
        for(books allbooks : listOfBooks){
            if(allbooks.name.equals(nameOfBook) ){
                if(allbooks.issue){
                    System.out.println("ALREADY ISSUED\n");
                    return user;
                }
                flag = false;
                System.out.println("BOOK SUCCESSFULLY ISSUED");
                allbooks.issuedBy = false;//means student
                allbooks.issue = true;
                allbooks.issueDate = date;
                Map<String,Date> m = new HashMap<>();
                m.put(nameOfBook,date);
                user.listOfIssuedBooks.add(m);
            }
        }
        if(flag == true) System.out.println("BOOK NOT FOUND");
        return user;

    }

    //////////////////////////////////////////////////////////////TEACHER'S CODE


     private static void addSomeBooks(){
        books newBook = new books();
        newBook.name = "physic concepts";
        newBook.author = "Aditiya";
        newBook.publisher = "PHYSICS LAB";
        newBook.dateAdded = date;
        listOfBooks.add(newBook);

         books newBook1 = new books();
         newBook1.name = "OOPS CONCEPTS";
         newBook1.author = "saharsh";
         newBook1.publisher = "OOPS LAB";
         newBook1.dateAdded = date;
         listOfBooks.add(newBook1);


         books newBook2 = new books();
         newBook2.name = "chemisty concepts";
         newBook2.author = "rahul";
         newBook2.publisher = "CHEMISTRY LAB";
         newBook2.dateAdded = date;
         listOfBooks.add(newBook2);

         books newBook3 = new books();
         newBook3.name = "OS concepts";
         newBook3.author = "GD";
         newBook3.publisher = "OS LAB";
         newBook3.dateAdded = date;
         listOfBooks.add(newBook3);

         books newBook4 = new books();
         newBook4.name = "SE concepts";
         newBook4.author = "mari";
         newBook4.publisher = "SE LAB";
         newBook4.dateAdded = date;
         listOfBooks.add(newBook4);
     }
}
