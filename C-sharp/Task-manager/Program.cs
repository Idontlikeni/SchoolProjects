using System;
using System.IO;

namespace ConsoleApp7
{
    class Program
    {
        static void Main(string[] args)
        {
            Console.SetWindowSize(103, 40);
            string path = @"C:\"; //Directory.GetCurrentDirectory();
            gui g1 = new gui(0, 0, 50, 30);
            gui g2 = new gui(52, 0, 50, 30);
            gui g3 = new gui(0, 31, 102, 6);

            int page = 0;
            /*foreach(string s in files)
            {
                Console.WriteLine(s.Split(@"\")[^1]);
            }*/

            while (true)
            {
                g1.draw();
                g2.draw();
                g3.draw();

                var dirs = Directory.GetDirectories(path);
                var files = Directory.GetFiles(path);

                g1.drawRel(2, 0, path);
                //Console.WriteLine(dirs.Length);
                for (int i = page * 28; i < Math.Min(dirs.Length, (page + 1) * 28); i++)
                {
                    g1.drawRel(2, 1 + i - page * 28, dirs[i].Split(@"\")[^1]);
                }

                for (int i = 0; i < files.Length; i++)
                {
                    long ln = new System.IO.FileInfo(path + @"\" + files[i].Split(@"\")[^1]).Length;
                    String s = files[i].Split(@"\")[^1];
                    int leng = s.Length;
                    for(int j = 0; j < 20 - leng; j++)
                    {
                        s += " ";
                    }
                    g2.drawRel(2, 1 + i, s + "\t" + ln + " bytes.");
                }


                g3.drawRel(1, 3, "-->");
                Console.SetCursorPosition(4, 34);
                string inp = Console.ReadLine();
                string[] argv = inp.Split();

                if (argv[0] == "exit") break;
                if (argv[0] == "help") break;
                if (argv[0] == "md")Directory.CreateDirectory(path + @"\" + argv[1]);
                if (argv[0] == "mf")File.Create(path + @"\" + argv[1]);
                if (argv[0] == "") break;
                if (argv[0] == "cd") {
                    if (argv[1] == "..")
                    {
                        if(path != @"C:\")path = path.Substring(0, path.Length - path.Split(@"\")[^2].Length - 1);
                    }
                    else if (!argv[1].Contains(@"\"))
                    {
                        //Console.WriteLine("sdfsdfsfsdfsd");
                        bool f = false;
                        for (int i = 0; i < dirs.Length; i++)
                        {
                            if(dirs[i].Split(@"\")[^1] == argv[1])
                            {
                                f = true;
                                break;
                            }
                        }
                        if (f) path = path + argv[1] + @"\";
                        else {
                            if (argv[1].Contains("C:"))path = argv[1] + @"\";
                            else path = @"C:\" + argv[1] + @"\";
                        }
                    }
                    else
                    {
                        if (argv[1].Contains("C:")) path = argv[1] + @"\";
                        else path = @"C:\" + argv[1] + @"\";
                    }
                }
                if (argv[0] == "deldir") {
                    Directory.Delete(path + @"\" + argv[1]);
                }
                if (argv[0] == "delf") {
                    File.Delete(path + @"\" + argv[1]);
                }
                if (argv[0] == "next")
                {
                    page++;
                }
                if (argv[0] == "prev")
                {
                    page = Math.Max(0, page - 1);
                }
                Console.Clear();
            }
        }
    }
}
