# include <cs50.h>
# include <stdio.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("Please enter from 1 to 8: ");
    }
    while (n < 1 || n > 8);
    
    for (int i = 1; i <= n; i++)
    {
        for (int k = 1; k <= (n - i); k++)
        {
            printf(" ");
        }
        for (int s = 1; s <= i; s++)
        {
            printf("#");
        }
        printf("  ");
        for (int s = 1; s <= i; s++)
        {
            printf("#");
        }
        printf("\n"); //after done with first line, this line prints a newline character to continue the loop for subqequent lines
    }
}
