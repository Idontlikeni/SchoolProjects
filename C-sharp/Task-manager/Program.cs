using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Diagnostics;

namespace TaskManager
{
    class Program
    {
        static Process findById(int id)
        {
            foreach (Process process in Process.GetProcesses())
            {
                // выводим id и имя процесса
                if (process.Id == id) return process;
            }
            return null;
        }

        static Process findByName(string name)
        {
            foreach (Process process in Process.GetProcesses())
            {
                // выводим id и имя процесса
                if (process.ProcessName.Contains(name)) return findById(process.Id);
            }
            return null;
        }

        static void printProcesses()
        {
            foreach (Process process in Process.GetProcesses())
            {
                // выводим id и имя процесса
                Console.WriteLine($"ID: {process.Id}  Name: {process.ProcessName}");
            }
        }

        static void Main(string[] args)
        {
           
            
            Console.WriteLine("--------------------------------------------------");

            while (true)
            {
                Console.WriteLine("Доступные команды: ");
                Console.WriteLine("1 - Вывести все процессы.");
                Console.WriteLine("2 - Найти процесс по имени");
                Console.WriteLine("3 - Найти процесс по ID");
                Console.WriteLine("4 - Убить процесс (по ID)");
                Console.WriteLine("0 - Выход");
                int inp = int.Parse(Console.ReadLine());
                if (inp == 0) break;
                if (inp == 1)printProcesses();
                if (inp == 2)
                {
                    string arg = Console.ReadLine();
                    Process process = findByName(arg);
                    Console.WriteLine($"ID: {process.Id}  Name: {process.ProcessName}");
                }
                if (inp == 3)
                {
                    int arg = int.Parse(Console.ReadLine());
                    Process process = findById(arg);
                    Console.WriteLine($"ID: {process.Id}  Name: {process.ProcessName}");
                }
                if (inp == 4)
                {
                    int arg = int.Parse(Console.ReadLine());
                    Process process = findById(arg);
                    string name = process.ProcessName;
                    int pid = process.Id;
                    process.Kill();
                    Console.WriteLine($"Killed proccess {name}, ID: {pid}");
                }
                Console.WriteLine("---------------------------------------");
            }
        }
    }
}
