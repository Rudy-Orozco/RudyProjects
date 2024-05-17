/* CA6 Rudy Orozco 1001864902*/

#include <stdio.h>
#include <string.h>
#define HASHTABLESIZE 10

int MyHashFunction(char HashValue[20])
{
    int Sum, Adding;

    // Alphanumeric Keys
    for(int i = 0; i < strlen(HashValue); i++)
    {
        Adding = HashValue[i]; // Adding the sum of all ASCII Values
        Sum = Sum + Adding;
    }

    return Sum % HASHTABLESIZE;
}

int main(void)
{
    char HashValue[20];
    printf("Enter value ");
    fgets(HashValue, sizeof(HashValue), stdin);

    if (HashValue[strlen(HashValue)-1] == '\n')
    {
        HashValue[strlen(HashValue)-1] = '\0';
    }

    printf("The hash value for %s is %d\n", HashValue, MyHashFunction(HashValue));

    return 0;
}