#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define UP 's'
#define DOWN 'w'
#define LEFT 'd'
#define RIGHT 'a'
#define QUIT 'q'
#define RESETGAME 'e'
#define UP_ARROW 80 // ASCII code
#define DOWN_ARROW 72
#define LEFT_ARROW 77
#define RIGHT_ARROW 75
#define NEWSHUFFLE 'n'
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define CHEATCODE 'f'

int moves = 0;

int menu();
void name_func(char *first_name, char *last_name);
void size_func(int *n);
void shuffle_puzzle(int n, int puzzle[n][n], int *zero_row, int *zero_column);
bool is_win(int n, int (*puzzle)[n]);
void swap(int *a, int *b);
void print_puzzle(int n, int puzzle[n][n], char first_name[20],
                  char last_name[20]);
void move_left(int n, int puzzle[n][n], int *zero_row, int *zero_column,
               char first_name[20], char last_name[20]);
void move_right(int n, int puzzle[n][n], int *zero_row, int *zero_column,
                char first_name[20], char last_name[20]);
void move_down(int n, int puzzle[n][n], int *zero_row, int *zero_column,
               char first_name[20], char last_name[20]);
void move_up(int n, int puzzle[n][n], int *zero_row, int *zero_column,
             char first_name[20], char last_name[20]);

int main() {
  while (1) {
    int menu_choice = menu();

    if (menu_choice == 2)
      continue;
    if (menu_choice == 3) {
      puts("See you later....");
      break;
    }

    int n;
    size_func(&n);
    char first_name[20];
    char last_name[20];
    name_func(first_name, last_name);

    int puzzle[n][n];
    int zero_row;
    int zero_column;
    srand((unsigned int)time(NULL));
    shuffle_puzzle(n, puzzle, &zero_row, &zero_column);
    int initialPuzzle[n][n];
    int initial_zero_row = zero_row;
    int initial_zero_column = zero_column;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        initialPuzzle[i][j] = puzzle[i][j];
      }
    }

    char c;
    while (!is_win(n, puzzle)) {
      print_puzzle(n, puzzle, first_name, last_name);
      c = _getch();
      if (c == DOWN || c == DOWN_ARROW) {
        move_down(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == RIGHT || c == RIGHT_ARROW) {
        move_right(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == UP || c == UP_ARROW) {
        move_up(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == LEFT || c == LEFT_ARROW) {
        move_left(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == QUIT) {
        break;
      } else if (c == RESETGAME) {
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            puzzle[i][j] = initialPuzzle[i][j];
          }
        }
        zero_row = initial_zero_row;
        zero_column = initial_zero_column;
        moves = 0;
        print_puzzle(n, puzzle, first_name, last_name);
      } else if (c == NEWSHUFFLE) {
        shuffle_puzzle(n, puzzle, &zero_row, &zero_column);
        initial_zero_row = zero_row;
        initial_zero_column = zero_column;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            initialPuzzle[i][j] = puzzle[i][j];
          }
        }
        moves = 0;
      } else if (c == CHEATCODE) {
        int trueNumber = 1;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            puzzle[i][j] = trueNumber;
            trueNumber++;
          }
        }
        puzzle[n - 1][n - 1] = 0;
      }
    }
    if (is_win(n, puzzle)) {
      print_puzzle(n, puzzle, first_name, last_name);
      puts("\nYou Win!");
    }
    moves = 0;
    if (c == QUIT) {
      continue;
    }
  }
  return 0;
}

int menu() {
  int menu_option;
  while (1) {
    printf("\nWelcome to the Ultimate Puzzle Challenge!\n"
           "Please select an option:\n"
           "1: Start Game\n"
           "2: Instructions\n"
           "3: Exit Game\n--> ");
    scanf("%d", &menu_option);
    if (menu_option >= 1 && menu_option <= 3) {
      break;
    } else {
      puts("Invalid input. Please enter a number between 1 and 3.");
    }
  }

  if (menu_option == 2) {
    system("cls");
    printf("\nINSTRUCTIONS:\n\n"
           "Welcome to the Ultimate Puzzle Challenge! In this game, you will "
           "need to arrange the numbers in the puzzle correctly.\n"
           "When the game starts, enter your name and the size of the puzzle "
           "(n).\n"
           "Your goal is to solve the puzzle by moving the empty space.\n\n"
           "Winning Condition:\n"
           "The game ends when the numbers are arranged in order from left to "
           "right "
           "and top to bottom.\nFor example:\n"
           "1 2 3\n"
           "4 5 6\n"
           "7 8\n\n"
           "Controls:\n"
           "W: Move Down\n"
           "S: Move Up\n"
           "A: Move Right\n"
           "D: Move Left\n\n"
           "GOOD LUCK!!!\n");
  }
  return menu_option;
}

void name_func(char *first_name, char *last_name) {
  printf("What is your first name brave player? ");
  scanf("%19s", first_name);
  printf("what is your last name ?");
  scanf("%19s", last_name);
}

void size_func(int *n) {
  while (1) {
    printf(
        "Enter the size of the puzzle you wish to play with (2 <= n <= 10): ");
    if (scanf("%d", n) != 1) {
      while (getchar() != '\n')
        ;
      puts("an integer between 2 and 10.");
    } else if (*n >= 2 && *n <= 10) {
      break;
    } else {
      while (getchar() != '\n')
        ;
      puts("size between 2 and 10.");
    }
  }
}

void shuffle_puzzle(int n, int puzzle[n][n], int *zero_row, int *zero_column) {
  int total = n * n;
  int used[total];
  for (int i = 0; i < total; i++) {
    used[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int random;
      do {
        random = rand() % total;
      } while (used[random]);

      used[random] = 1;
      puzzle[i][j] = random;

      if (random == 0) {
        *zero_row = i;
        *zero_column = j;
      }
    }
  }
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}

bool is_win(int n, int (*puzzle)[n]) {
  int trueNumber = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == n - 1 && j == n - 1) {
        if (puzzle[i][j] != 0) {
          return false;
        }
      } else {
        if (puzzle[i][j] != trueNumber) {
          return false;
        }
        trueNumber++;
      }
    }
  }

  return true;
}

void print_puzzle(int n, int puzzle[n][n], char first_name[20],
                  char last_name[20]) {
  system("cls");
  puts("MAGIC PUZZLE");
  printf("%s  %s\n", first_name, last_name);

  for (int j = 0; j < n; j++) {
    printf("-----");
  }
  printf("-\n");

  int trueNumber = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("|");

      // print numbers
      if (puzzle[i][j] != 0) {
        // Check if the number is in the correct position
        if (puzzle[i][j] == trueNumber) {
          printf(GREEN " %2d " RESET, puzzle[i][j]); // Print in green
        } else {
          printf(YELLOW " %2d " RESET, puzzle[i][j]); // Print in yellow
        }
      } else {
        printf("    ");
      }
      trueNumber++;
    }
    printf("|\n");

    for (int j = 0; j < n; j++) {
      printf("-----");
    }
    printf("-\n");
  }
  printf("\nMoves: %d\n", moves);
  printf("\n-> ");
}

void move_down(int n, int puzzle[n][n], int *zero_row, int *zero_column,
               char first_name[20], char last_name[20]) {
  if (*zero_row < n - 1) {
    swap(&puzzle[*zero_row][*zero_column],
         &puzzle[*zero_row + 1][*zero_column]);
    (*zero_row)++;
  } else {
    for (int i = n - 1; i > 0; i--) {
      swap(&puzzle[i][*zero_column], &puzzle[i - 1][*zero_column]);
    }
    *zero_row = 0;
  }
  moves++;
  print_puzzle(n, puzzle, first_name, last_name);
}
void move_up(int n, int puzzle[n][n], int *zero_row, int *zero_column,
             char first_name[20], char last_name[20]) {
  if (*zero_row > 0) {
    swap(&puzzle[*zero_row][*zero_column],
         &puzzle[*zero_row - 1][*zero_column]);
    (*zero_row)--;
  } else {
    for (int i = 0; i < n - 1; i++) {
      swap(&puzzle[i][*zero_column], &puzzle[i + 1][*zero_column]);
    }
    *zero_row = n - 1;
  }
  moves++;
  print_puzzle(n, puzzle, first_name, last_name);
}
void move_right(int n, int puzzle[n][n], int *zero_row, int *zero_column,
                char first_name[20], char last_name[20]) {
  if (*zero_column < n - 1) {
    swap(&puzzle[*zero_row][*zero_column],
         &puzzle[*zero_row][*zero_column + 1]);
    (*zero_column)++;
  } else {
    for (int i = n - 1; i > 0; i--) {
      swap(&puzzle[*zero_row][i], &puzzle[*zero_row][i - 1]);
    }
    *zero_column = 0;
  }
  moves++;
  print_puzzle(n, puzzle, first_name, last_name);
}
void move_left(int n, int puzzle[n][n], int *zero_row, int *zero_column,
               char first_name[20], char last_name[20]) {
  if (*zero_column > 0) {
    swap(&puzzle[*zero_row][*zero_column],
         &puzzle[*zero_row][*zero_column - 1]);
    (*zero_column)--;
  } else {
    for (int i = 0; i < n - 1; i++) {
      swap(&puzzle[*zero_row][i], &puzzle[*zero_row][i + 1]);
    }
    *zero_column = n - 1;
  }
  moves++;
  print_puzzle(n, puzzle, first_name, last_name);
}