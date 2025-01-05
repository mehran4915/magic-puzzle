#include <stdio.h>

enum GameStatus { CONTINUE, STOP };

int main() {
  enum GameStatus game;
  game = CONTINUE;
  while (game == CONTINUE) {
    int main_menu_option;
    while (1) {
      printf("Welcome to magic puzzle game\nplease choose an option\noption 1: "
             "start\noption 2: manual\noption 3: exit\n-> ");
      scanf("%d", &main_menu_option);
      if (main_menu_option == 1 || main_menu_option == 2 ||
          main_menu_option == 3) {
        break;
      } else {
        printf("enter a valid number between 1 and 3");
      }
    }
    if (main_menu_option == 2) {
      printf("this is the manual\n");
      continue;
    }
    if (main_menu_option == 3) {
      printf("See you later....");
      break;
    }
  }

  return 0;
}
