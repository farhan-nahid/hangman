#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

#define RED "\033[0;31m"
#define BOLD_RED "\033[1;31m"
#define GREEN "\033[0;32m"
#define BOLD_GREEN "\033[1;32m"
#define YELLOW "\033[0;33m"
#define BOLD_YELLOW "\033[1;33m"
#define BLUE "\033[0;34m"
#define BOLD_BLUE "\033[1;34m"
#define MAGENTA "\033[0;35m"
#define BOLD_MAGENTA "\033[1;35m"
#define CYAN "\033[0;36m"
#define BOLD_CYAN "\033[1;36m"
#define RESET "\033[0m"

void welcome();
int get_word(char *, int);
int run_game(char *, int);
void put_into_string(char, char *);
int is_blank_available(char *);
void ascii_art_hangman(int);

int main(int argc, char const *argv[])
{
    welcome();

    // Setting up variables
    char game_word[256];
    int difficulty = 1;
    int check_ok;
    int word_len;

    // Choosing difficulty in Game
    if (argc != 1)
    {
        switch (argv[1][1])
        {
        case 'e':
            difficulty = 1;
            break;
        case 'm':
            difficulty = 2;
            break;
        case 'h':
            difficulty = 3;
            break;
        default:
            puts(MAGENTA "Wrong argument(s) were passed." RESET);
            puts(YELLOW "  run \"./hangman -e\" for easy difficulty" RESET);
            puts(YELLOW "  run \"./hangman -m\" for medium difficulty" RESET);
            puts(YELLOW "  run \"./hangman -h\" for hard difficulty" RESET);
            printf("\n\n");
            puts(BLUE "Starting game in medium difficulty" RESET);
            break;
        }
    }
    else
    {
        puts(MAGENTA "No argument(s) were passed." RESET);
        puts(YELLOW "  run \"./hangman -e\" for easy difficulty" RESET);
        puts(YELLOW "  run \"./hangman -m\" for medium difficulty" RESET);
        puts(YELLOW "  run \"./hangman -h\" for hard difficulty" RESET);
        printf("\n\n");
        puts(BLUE "Starting game in medium difficulty" RESET);
    }

    // Getting a Random Word For Hangman
    check_ok = get_word(game_word, difficulty);
    if (!check_ok)
    {
        puts(RED "ERROR: Unable to get word. Exiting..." RESET);
        sleep(1);
    }
    word_len = (int)strlen(game_word);

    // Run the game and Get if the user got the word
    check_ok = run_game(game_word, word_len);
    if (check_ok)
    {
        printf(BOLD_YELLOW "WORD: %s\n" RESET, game_word);
        puts(BOLD_GREEN "You've won the game. Run it to play again." RESET);
        sleep(3);
        system("clear");
    }
    else
    {
        printf(BOLD_MAGENTA);
        ascii_art_hangman(0);
        printf(RESET);
        puts(BOLD_MAGENTA "You've lost the game. Try again." RESET);
        printf(BOLD_YELLOW "Correct WORD: %s\n" RESET, game_word);
        sleep(3);
        system("clear");
    }

    return 0;
}

void ascii_art_hangman(int ll)
{
    if (ll == 0)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |    (_)");
        puts("      |    \\|/");
        puts("      |     |");
        puts("      |    / \\");
        puts("      |");
        puts("    _ | ___");
    }
    if (ll == 1)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |    (_)");
        puts("      |    \\|/");
        puts("      |     |");
        puts("      |    /");
        puts("      |");
        puts("    _ | ___");
    }
    if (ll == 2)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |    (_)");
        puts("      |    \\|/");
        puts("      |     |");
        puts("      |");
        puts("      |");
        puts("    _ | ___");
    }
    if (ll == 3)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |    (_)");
        puts("      |     |/");
        puts("      |     |");
        puts("      |");
        puts("      |");
        puts("    _ | ___");
    }
    if (ll == 4)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |    (_)");
        puts("      |     | ");
        puts("      |     |");
        puts("      |");
        puts("      |");
        puts("    _ | ___");
    }
    if (ll == 5)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |    (_)");
        puts("      |");
        puts("      |");
        puts("      |");
        puts("      |");
        puts("    _ | ___");
    }
    if (ll == 6)
    {
        puts("      _______");
        puts("      |/    |");
        puts("      |");
        puts("      |");
        puts("      |");
        puts("      |");
        puts("      |");
        puts("    _ | ___");
    }
}

void welcome()
{
    system("clear");
    puts(BOLD_YELLOW "▬▬▬▬▬▬▬▬▬▬▬▬▬▬ஜ۩۞۩ஜ▬▬▬▬▬▬▬▬▬▬▬▬▬▬" RESET);
    puts(BOLD_GREEN " Welcome to the game of Hangman " RESET);
    puts(BOLD_YELLOW "▬▬▬▬▬▬▬▬▬▬▬▬▬▬ஜ۩۞۩ஜ▬▬▬▬▬▬▬▬▬▬▬▬▬▬" RESET);
    sleep(1);
}

int get_word(char game_word[], int d)
{
    FILE *file;
    int n_words, i = 0, random_n;
    char line[256];
    switch (d)
    {
    case 1:
        file = fopen("easy.txt", "r");
        break;
    case 2:
        file = fopen("medium.txt", "r");
        break;
    case 3:
        file = fopen("hard.txt", "r");
        break;
    default:
        file = fopen("medium.txt", "r");
        break;
    }
    if (file == NULL)
    {
        puts(RED "Cannot Open Dictionary. Game is Exiting." RESET);
        return 0;
    }
    while (fgets(line, 255, file))
    {
        if (i == 0)
        {
            sscanf(line, "%d", &n_words);
            srand((unsigned)time(NULL));
            random_n = (rand() % n_words) + 1;
            i++;
        }
        else
        {
            if (i == random_n)
            {
                sscanf(line, "%s", game_word);
                break;
            }
            i++;
        }
    }
    fclose(file);
    return 1;
}

int run_game(char game_word[], int l)
{
    char word_guessed[60];
    int life_left = 6;
    int correct_guess;
    char input_c, char_flush;
    char blanks[l];

    for (int i = 0; i < l; i++)
    {
        blanks[i] = '_';
    }
    blanks[l] = '\0';
    word_guessed[0] = '\0';

    while (life_left != 0 && is_blank_available(blanks))
    {
        correct_guess = 0;
        printf(MAGENTA "\n\n");
        ascii_art_hangman(life_left);
        printf(RESET);
        puts(CYAN "Enter a character, Try to guess the word." RESET);
        printf(YELLOW "So far you've guessed: %s\n" RESET, word_guessed);
        printf("WORD: %s\n", blanks);
        printf("INPUT: ");
        scanf("%c", &input_c);
        scanf("%c", &char_flush);
        put_into_string(input_c, word_guessed);
        for (int i = 0; i < l; i++)
        {
            if (game_word[i] == input_c && blanks[i] == '_')
            {
                blanks[i] = input_c;
                correct_guess = 1;
            }
        }
        if (!correct_guess)
        {
            puts(MAGENTA "You've guessed wrong." RESET);
            life_left--;
            printf("LIFE LEFT: %d\n\n", life_left);
        }
        else
        {
            printf(GREEN "You've guessed correctly.\n\n" RESET);
        }
    }
    if (life_left == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void put_into_string(char c, char word[])
{
    int i = strlen(word);
    word[i] = toupper(c);
    word[i + 1] = ',';
    word[i + 2] = '\0';
    return;
}

int is_blank_available(char word[])
{
    int a_blank_available = 0;
    int l = strlen(word);
    for (int i = 0; i < l; i++)
    {
        if (word[i] == '_')
        {
            a_blank_available = 1;
        }
    }
    return a_blank_available;
}
