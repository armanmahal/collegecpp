#include <iostream.h>
#include <stdio.h>
#include <conio.h>

class Names
{
private:
    char names[10][100];

    int getLen(char a[])
    {
	int i = 0;
		while (a[i] != '\0')
	{
	    i++;
	}
	return i;
    }
    char lowerCase(char x)
    {
	int i = (int)x;

	if(i>=65 && i<=90)
	{
	    return x-32;
	}

	return x;
    }
    int compare(char a[], char b[])
    {
	int aLen = getLen(a);
	int bLen = getLen(b);

	int i = 0;
	int j = 0;
	
	while(i<aLen && j<bLen)
	{
	    if ((int)(lowerCase(a[i])) == (int)(lowerCase(b[j])))
	    {
	    	i++;
	    	j++;
		continue;
	    }
	    else if(a[i] == ' ')
	    {
	    	i++;
		continue;
	    }
	    else if(b[j] == ' ')
	    {
	    	j++;
		continue;
	    }
	    else if ((int)(lowerCase(a[i])) > (int)(lowerCase(b[j])))
	    {
		return 1;
	    }
	    else
	    {
		return 0;
	    }
	}

	if (aLen > bLen)
	{
	    return 1;
	}

	return 0;
    }
    void swap(char a[], char b[])
    {
	char temp[100];

	int aLen = getLen(a);
	int bLen = getLen(b);
	int i = 0;
	for (i = 0; i <= aLen; i++)
	{
	    temp[i] = a[i];
	}

	for (i = 0; i <= bLen; i++)
	{
	    a[i] = b[i];
	}

	for (i = 0; i <= aLen; i++)
	{
	    b[i] = temp[i];
	}
    }

public:
    void in()
    {
	cout << "Enter the Names: " << endl;
	for (int i = 0; i < 10; i++)
	{
	    cout<<"Enter the "<<i+1<<" name: ";
	    gets(names[i]);
	}
    }

    void out()
    {
	cout << "Sorted: " << endl;
	for (int i = 0; i < 10; i++)
	{
	    cout << names[i] << endl;
	}
    }

    void sort()
    {
	int j = 1;
	while (j < 10)
	{
	    for (int i = 0; i < 10 - j; i++)
	    {
		if (compare(names[i], names[i + 1]) == 1)
		{
		    swap(names[i], names[i + 1]);
		}
	    }
	    j++;
	}
    }
};

int main()
{
    clrscr();

    Names n;
    n.in();
    n.sort();
    n.out();

    getch();
    return 0;
}

