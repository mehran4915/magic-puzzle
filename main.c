#include <conio.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int moves = 0;

void display_menu(int *main_menu_option);
void ask_name_size(int *n, char (*name)[30]);
void shuffle_puzzle(int n, int (*puzzle)[n], int *empty_row,
                    int *empty_coloumn);
bool win_check(int n, int (*puzzle)[n]);
void print_table(int n, int (*puzzle)[n], char (*name)[30], int moves);
void swap(int *a, int *b);

int main() {
  while (1) {
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
    int empty_row;
    int empty_coloumn;
    srand((unsigned int)time(NULL));
    shuffle_puzzle(n, puzzle, &empty_row, &empty_coloumn);
    int initialPuzzle[n][n];
    int initial_empty_row = empty_row;
    int initial_empty_column = empty_coloumn;
    memcpy(initialPuzzle, puzzle, sizeof(puzzle));

    char c;
    while (!win_check(n, puzzle)) {
      print_table(n, puzzle, &name, moves);
      c = _getch();
      if (c == 'w') { // move down
        if (empty_row < n - 1) {
          swap(&puzzle[empty_row][empty_coloumn],
               &puzzle[empty_row++][empty_coloumn]);
        } else {
          for (int i = n - 1; i > 0;) {
            swap(&puzzle[i][empty_coloumn], &puzzle[i--][empty_coloumn]);
          }
          empty_row = 0;
        }
        moves++;
        print_table(n, puzzle, &name, moves);
      } else if (c == 'a') { // right
        if (empty_coloumn < n - 1) {
          swap(&puzzle[empty_row][empty_coloumn],
               &puzzle[empty_row][empty_coloumn++]);
        } else {
          for (int i = n - 1; i > 0;) {
            swap(&puzzle[empty_row][i], &puzzle[empty_row][i--]);
          }
          empty_coloumn = 0;
        }
        moves++;
        print_table(n, puzzle, &name, moves);
      } else if (c == 's') { // up
        if (empty_row != 0) {
          swap(&puzzle[empty_row][empty_coloumn],
               &puzzle[empty_row--][empty_coloumn]);
        } else {
          for (int i = 0; i < n - 1;) {
            swap(&puzzle[i][empty_coloumn], &puzzle[i++][empty_coloumn]);
          }
          empty_row = n - 1;
        }
        moves++;
        print_table(n, puzzle, &name, moves);
      } else if (c == 'd') { // left
        if (empty_coloumn != 0) {
          swap(&puzzle[empty_row][empty_coloumn],
               &puzzle[empty_row][empty_coloumn--]);
        } else {
          for (int i = 0; i < n - 1;) {
            swap(&puzzle[empty_row][i], &puzzle[empty_row][i++]);
          }
          empty_coloumn = n - 1;
        }
        moves++;
        print_table(n, puzzle, &name, moves);
      } else if (c == 'q') {
        break;
      } else if (c == 'e') {
        memcpy(puzzle, initialPuzzle, sizeof(puzzle));
        empty_row = initial_empty_row;
        empty_coloumn = initial_empty_column;
        moves = 0;
        print_table(n, puzzle, &name, moves);
      } else {
      }
    }
    if (win_check(n, puzzle)) {
      print_table(n, puzzle, &name, moves);
      puts("\nYou Win!");
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

void shuffle_puzzle(int n, int (*puzzle)[n], int *empty_row,
                    int *empty_coloumn) {
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
    if (i == 0) {
      *empty_coloumn = random2;
      *empty_row = random1;
    }
  }
}

bool win_check(int n, int (*puzzle)[n]) {
  int correctNumber = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (i == n - 1 && j == n - 1) {
        if (puzzle[i][j] != 0) {
          return false;
        }
      } else {
        if (puzzle[i][j] != correctNumber) {
          return false;
        }
        correctNumber++;
      }
    }
  }
  return true;
}

void print_table(int n, int (*puzzle)[n], char (*name)[30], int moves) {
  system("cls");
  puts("MAGIC PUZZLE");
  puts(*name);
  printf("+");
  for (int k = 0; k < n; k++) {
    printf("-----+");
  }
  printf("\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (puzzle[i][j] != 0) {
        printf("| %*d ", (5 - 1) / 2 + 1, puzzle[i][j]);
      } else {
        printf("|     ");
      }
    }
    printf("|\n");
    printf("+");
    for (int k = 0; k < n; k++) {
      printf("-----+");
    }
    printf("\n");
  }
  printf("\nMoves: %d\n", moves);
  printf("\n-> ");
}

void swap(int *a, int *b) {
  *a = *a ^ *b;
  *b = *a ^ *b;
  *a = *a ^ *b;
}
