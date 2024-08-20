#include <iostream.h>
#include <stdio.h>
#include <conio.h>

class Str
{
private:
    char s[100];

    int getLen(char c[])
    {
        int i = 0;
        while (c[i] != '\0')
        {
            i++;
        }
        return i;
    }

public:
    void in()
    {
	cout<<"Enter the String: ";
	gets(s);
    }

    void out()
    {
	cout<< "Reversed: " << s << endl;
    }

    void reverse()
    {
	int len = getLen(s)-1;

        int i = 0;

        while (i < len)
        {
            char temp = s[i];
            s[i] = s[len];
            s[len] = temp;
            i++;
            len--;
        }
    }
};

int main()
{
    clrscr();

    Str s;
    s.in();
    s.reverse();
    s.out();

    getch();
    return 0;
}
