public class test {
  public static void main(String [] args) {
    System.out.println("The result is " + bar(3) + ".");


  }
  public static int bar(int n)
   {
       if(n == 1)
       {
           return 1;
       }
       else if(n == 5)
       {
           return 5;
       }
       else
       {
           return bar(n - 1) + bar(n + 1);
       }
   }


}
