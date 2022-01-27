#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define COUNT_OF_LETTERS 26 // eng. alphabet

void msg_show(void);
int shift_prepare(int);
void fun_fflush_stdin(void);

int main()
{
    char string[1024];
    char ciphertext[1024];
    int shift;
    int finished_shift;
    int act;

    msg_show();

    printf("\nDo you wanna encrypt/decrypt? Choose e/d: ");
    act = getchar();
    if (act == 'e')
    {
        goto encryption;
    }
    else if (act == 'd')
    {
        goto decryption;
    }
    else
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }


encryption:
    printf("\nInput a message: ");

    fun_fflush_stdin();

    if (fgets(string, sizeof (string), stdin) == NULL)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    /* make all letters uppercase */
    for (unsigned long i = 0; i < strlen(string) - 1; i++)
    {
        if (string[i] >= 65 && string[i] <= 90)
        {
            continue;
        }
        else if (string[i] >= 97 && string[i] <= 122)
        {
            string[i] = (char)((int)string[i] - 32);
        }
        else if (string[i] == ' ')
        {
            continue;
        }
        else
        {
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Now the message looks like this: %s\n", string);

    printf("Input a shift: ");
    scanf("%d", &shift);
    finished_shift = shift_prepare(shift);

    if (finished_shift < 0)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < strlen(string) - 1; i++)
    {
        if (string[i] == ' ')
        {
            ciphertext[i] = ' ';
        }
        else
        {
            ciphertext[i] = (char)((((int)string[i] - 'A' + finished_shift++) %
                                    COUNT_OF_LETTERS) + 'A');
        }
    }
    ciphertext[strlen(string) - 1] = '\0';

    printf("\nCiphertext: %s\n\n", ciphertext);
    goto end;

decryption:
    printf("\nInput a message: ");

    fun_fflush_stdin();

    if (fgets(string, sizeof (string), stdin) == NULL)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    /* make all letters uppercase */
    for (unsigned long i = 0; i < strlen(string) - 1; i++)
    {
        if (string[i] >= 65 && string[i] <= 90)
        {
            continue;
        }
        else if (string[i] >= 97 && string[i] <= 122)
        {
            string[i] = (char)((int)string[i] - 32);
        }
        else if (string[i] == ' ')
        {
            continue;
        }
        else
        {
            printf("Error\n");
            exit(EXIT_FAILURE);
        }
    }

    printf("Now the message looks like this: %s\n", string);

    printf("Input a shift: ");
    scanf("%d", &shift);
    finished_shift = shift_prepare(shift);

    if (finished_shift < 0)
    {
        printf("Error\n");
        exit(EXIT_FAILURE);
    }

    for (unsigned long i = 0; i < strlen(string) - 1; i++)
    {
        if (string[i] == ' ')
        {
            ciphertext[i] = ' ';
        }
        else
        {
            ciphertext[i] = (char)((((int)string[i] - 'A' - finished_shift++ + COUNT_OF_LETTERS) %
                                    COUNT_OF_LETTERS) + 'A');
        }
    }
    ciphertext[strlen(string) - 1] = '\0';

    printf("\nDecrypted message: %s\n\n", ciphertext);

end:

    return 0;
}


void msg_show(void)
{
    printf("#######################################\n"
           "# A program shows how modified Caesar #\n"
           "# cipher works. You input a message   #\n"
           "# which you want to encrypt/decrypt   #\n"
           "# and a shift(a number). Then program #\n"
           "# shifts each symbol of the message   #\n"
           "# to a number.                        #\n"
           "#######################################\n");
}

int shift_prepare(int key)
{
    int finished_key = 0;
    int count = 0;

    if (key < 0)
    {
        return -1;
    }
    else if (key <= COUNT_OF_LETTERS)
    {
        return key;
    }

    count = key / COUNT_OF_LETTERS;
    finished_key = key - count * COUNT_OF_LETTERS;

    return finished_key;
}

void fun_fflush_stdin(void)
{
    while( getchar() != 10)
        ;
}
