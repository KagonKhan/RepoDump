using System;
using System.Text;
using System.Collections.Generic;

namespace DataStructuresCS
{
    static class Program
    {
        static void Main()
        {

            System.Collections.Generic.LinkedList<int> vs;



            LinkedList<int> myList = new(new int[] { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });




            foreach (var num in myList)
                Console.WriteLine(num);

            Console.WriteLine(myList.IndexOf(5));

        }
    }
}
