#include <stdio.h>

enum GameStatus { CONTINUE, STOP };

int main() {
  enum GameStatus game;
  game = CONTINUE;
  while (game == CONTINUE) {
    // main menu
    int main_menu_option;
    while (1) {
      printf(
          "\nWelcome to magic puzzle game\nplease choose an option\noption 1: "
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
    scanf("%d", name);
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
  }

  return 0;
}
