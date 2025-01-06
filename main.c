#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

enum GameStatus { CONTINUE, STOP };

void display_menu(int *main_menu_option);
void ask_name_size(int *n, char (*name)[30]);
void shuffle_puzzle(int n, int (*puzzle)[n]);
bool win_check(int n, int (*puzzle)[n]);
void print_table(int n, int (*puzzle)[n], char (*name)[30], int moves);

int main() {
  enum GameStatus game;
  game = CONTINUE;
  while (game == CONTINUE) {
    int main_menu_option;
    display_menu(&main_menu_option);
    if (main_menu_option == 2) {
      continue;
    } else if (main_menu_option == 3) {
      break;
    }

    // the show start
    // taking the name and n
    int n;
    char name[30];
    ask_name_size(&n, &name);

    // creating the intial puzzle
    int puzzle[n][n];
    srand((unsigned int)time(NULL));
    shuffle_puzzle(n, puzzle);
    int initialPuzzle[n][n];
    memcpy(initialPuzzle, puzzle, (size_t)n);

    int moves = 0;
    char c;
    while (!win_check(n, puzzle)) {
      print_table(n, puzzle, &name, moves);
      c = _getch();
      if (c == 'w') {
        moves++;
      } else if (c == 'a') {
        moves++;
      } else if (c == 's') {
        moves++;
      } else if (c == 'd') {
        moves++;
      } else if (c == 'q') {
        break;
      } else if (c == 'e') {
        memcpy(puzzle, initialPuzzle, (size_t)n);
        moves = 0;
      } else {
      }
    }
    if (c == 'q') {
      continue;
    }
  }
  return 0;
}

void display_menu(int *main_menu_option) {
  while (1) {
    printf("\nWelcome to magic puzzle game\nplease choose an "
           "option\noption 1: "
           "start\noption 2: manual\noption 3: exit\n-> ");
    scanf("%d", main_menu_option);
    if (*main_menu_option == 1 || *main_menu_option == 2 ||
        *main_menu_option == 3) {
      break;
    } else {
      puts("enter a valid number between 1 and 3");
    }
  }
  if (*main_menu_option == 2) {
    puts("this is the manual");
  }
  if (*main_menu_option == 3) {
    puts("See you later....");
  }
}

void ask_name_size(int *n, char (*name)[30]) {
  printf("what should I call you: ");
  scanf("%s", name);
  while (1) {
    printf("Enter the size of puzzle you want to have (2 <= n <= 9): ");
    if (scanf("%d", n) != 1) {
      while (getchar() != '\n')
        ;
      puts("Invalid input. Please enter an integer between 2 and 9.");
    } else if (*n >= 2 && *n <= 9) {
      break;
    } else {
      while (getchar() != '\n')
        ;
    }
  }
}

void shuffle_puzzle(int n, int (*puzzle)[n]) {
  bool used[n][n];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      used[i][j] = false;
    }
  }

  // attention: the empty square has the value of 0
  for (int i = 0; i < n * n; i++) {
    int random1, random2;
    do {
      random1 = rand() % n;
      random2 = rand() % n;
    } while (used[random1][random2]);
    used[random1][random2] = true;
    puzzle[random1][random2] = i;
  }
}

bool win_check(int n, int (*puzzle)[n]) {
  int correctNumber = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (puzzle[i][j] != correctNumber && puzzle[n - 1][n - 1] != 0) {
        return false;
      }
      correctNumber++;
    }
  }
  return true;
}

void print_table(int n, int (*puzzle)[n], char (*name)[30], int moves) {
  system("cls");
  puts("MAGIC PUZZLE");
  puts(*name);
  printf("+-----+-----+-----+\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (puzzle[i][j != 0]) {
        printf("| %*d ", (5 - 1) / 2 + 1, puzzle[i][j]);
      }
    }
    printf("|\n");
    printf("+-----+-----+-----+\n");
  }
  printf("\n%d\n", moves);
  printf("\n-> ");
}
