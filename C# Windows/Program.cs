using System;
using System.Collections.Generic;
using RGiesecke.DllExport;
using System.Runtime.InteropServices;

namespace TestDLL
{
    class Program
    {
        public static List<int> superCalculation()
        {
            //Actual name of the function should be: "dateNowToIntegerList"

            List<int> result = new List<int>();
            string dateString = DateTime.Now.ToString();
            for(int i = 0;i<dateString.Length;i++)
            {
                if (Char.IsNumber(dateString[i]) == false) continue;
                result.Add(Int32.Parse( dateString[i].ToString() ));
            }

            return result;
        }

        [DllImport("./Kazelib.so", EntryPoint = "storeResults")]
        public extern static void storeResults(System.UInt64 container, int value);
        
        [DllExport("process", CallingConvention = CallingConvention.Cdecl)]
        public static void process(System.UInt64 container)
        {
            List<int> results = superCalculation();
            for (int i = 0; i < results.Count; i++)
            {
                storeResults(container, results[i]);
            }
        }
    }
}
