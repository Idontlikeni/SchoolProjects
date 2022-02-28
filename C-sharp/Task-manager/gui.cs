using System;
using System.Collections.Generic;
using System.Text;

namespace ConsoleApp7
{
    class gui
    {
        private int x, y, width, height;
        public gui(int x, int y, int width, int height)
        {
            this.x = x;
            this.y = y;
            this.width = width;
            this.height = height;
        }

        public void drawSymb(int x, int y, string s)
        {
            Console.SetCursorPosition(x, y);
            Console.Write(s);
        }

        public void drawRel(int x, int y, string s)
        {
            Console.SetCursorPosition(this.x + x, this.y + y);
            Console.Write(s);
        }

        public void draw()
        {
            for(int i = 0; i < width; i++)
            {
                drawSymb(x + i, y, "═");
            }
            for (int i = 0; i < width; i++)
            {
                drawSymb(x + i, y + height, "═");
            }
            for (int i = 0; i < height + 1; i++)
            {
                drawSymb(x, y + i, "║");
            }

            for (int i = 0; i < height + 1; i++)
            {
                drawSymb(x + width, y + i, "║");
            }
            drawSymb(x, y, "╔");
            drawSymb(x + width, y, "╗");
            drawSymb(x + width, y + height, "╝");
            drawSymb(x, y + height, "╚");
        }
    }
}
