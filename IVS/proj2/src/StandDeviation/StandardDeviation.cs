using MathLibrary;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/// <summary>
/// Contains a program for calculating standard deviation.
/// </summary>
namespace StandDeviation
{
    internal sealed class StandardDeviation
    {
        /// <summary>
        /// Function for calculating sum of numbers from list.
        /// </summary>
        /// <param name="list">List of numbers</param>
        /// <param name="power"></param>
        /// <returns>Returns the sum of power of each number.</returns>
        static double Sum(List<Number> list, int power)
        {
            double sum = 0;
            foreach (Number number in list)
            {
                sum += new PowerExp(number, new Number(power)).Evaluate();
            }
            return sum;
        }

        static List<Number> ReadNumbers()
        {
            List<Number> numbers = new List<Number>();
            string temp = Console.ReadLine();

            // Repeat until EOF is reached
            while (!string.IsNullOrEmpty(temp))
            {
                double parsed_number;
                if (double.TryParse(temp, out parsed_number))
                {
                    // add number to list
                    numbers.Add(new Number(parsed_number));
                }
                else
                {
                    Console.WriteLine("Error parsing a number.");
                    return new List<Number>(); // error, return empty
                }
                temp = Console.ReadLine();
            }
            return numbers;
        }

        static void Main(string[] args)
        {
            List<Number> numbers = ReadNumbers();
            if (numbers.Count == 0)
                return;

            //count of numbers
            int count = numbers.Count;
            //sum of numbers in list
            double sum = Sum(numbers, 1);
            //arithmetic sum
            double arithAverage = sum / count;

            //sum of numbers powered on 2 (numbers from list)
            sum = Sum(numbers, 2);

            //calculating Standart deviation
            var powerExp = new PowerExp(new Number(arithAverage), new Number(2));
            var tmpExp = new Number((sum - count * powerExp.Evaluate()) / (count - 1));
            var rootExp = new RootExp(tmpExp, new Number(2));
            double deviation = rootExp.Evaluate();

            Console.WriteLine(deviation);
        }
    }
}
