#include <stdio.h>
#include <cs50.h>


int main(void)
{
    //Prompts users' name using get_string which is then used when printing hello. 
    string name = get_string("What is your name?\n");
    printf("Hello, %s\n", name);
}