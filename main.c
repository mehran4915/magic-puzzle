#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


enum GameStatus { CONTINUE, STOP };

void shufflePuzzle(int n, int (*puzzle)[n]);

int main() {
  enum GameStatus game;
  game = CONTINUE;
  while (game == CONTINUE) {
    // main menu
    int main_menu_option;
    while (1) {
      printf("\nWelcome to magic puzzle game\nplease choose an "
             "option\noption 1: "
             "start\noption 2: manual\noption 3: exit\n-> ");
      scanf("%d", &main_menu_option);
      if (main_menu_option == 1 || main_menu_option == 2 ||
          main_menu_option == 3) {
        break;
      } else {
        puts("enter a valid number between 1 and 3");
      }
    }
    if (main_menu_option == 2) {
      puts("this is the manual");
      continue;
    }
    if (main_menu_option == 3) {
      puts("See you later....");
      break;
    }

    // the show start
    // taking the name and n
    char name[30];
    printf("what should I call you: ");
    scanf("%s", name);
    int n;
    while (1) {
      printf("Enter the size of puzzle you want to have (2 <= n <= 9): ");
      if (scanf("%d", &n) != 1) {
        while (getchar() != '\n')
          ;
        puts("Invalid input. Please enter an integer between 2 and 9.");
      } else if (n >= 2 && n <= 9) {
        break;
      } else {
        while (getchar() != '\n')
          ;
      }
    }

    // creating the intial puzzle
    int puzzle[n][n];
    srand((unsigned int)time(NULL));
    shufflePuzzle(n, puzzle);

    return 0;
  }
}

void shufflePuzzle(int n, int (*puzzle)[n]) {
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
