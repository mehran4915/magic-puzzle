#include <conio.h>   // __getch()
#include <stdbool.h> // bool
#include <stdio.h>
#include <stdlib.h> // srand(), rand(), system()
#include <time.h>   // (unsigned int)time(NULL)

// جایگزین برای آن مقادیر
// برای داشتن درک بیشتر از آن مقادیر
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
// ریست کردن ترمینال و چاپ کردن با رنگ عادی
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define CHEATCODE 'f'

// متغیر گلوبال
//  قابل دسترسی در تمام جای برنامه
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
  // تمام برنامه در داخل حلقه وایل قرار دارد
  while (1) {
    // مقداری که منو بازگشت میدهد در متغیر قرار میگیرد
    int menu_choice = menu();

    // عدم اجرای بقیه برنامه و بازگشت دوباره به اول
    if (menu_choice == 2)
      continue;
    if (menu_choice == 3) {
      puts("See you later....");
      break;
    }

    int n;
    // پارامتر چون که عدد صحیح است و با پوینتر داده شده نیاز به علامت آدرس دارد
    size_func(&n);
    char first_name[20];
    char last_name[20];
    // بر خلاف بالایی پارامتر چون آرایه است نیاز به علامت آدرس ندارد
    name_func(first_name, last_name);

    int puzzle[n][n];
    // سطر و ستونی که که عدد صفر در آن قرار دارد
    int zero_row;
    int zero_column;
    // تولید کردن عدد رندوم متفاوت در هر بار
    srand((unsigned int)time(NULL));
    shuffle_puzzle(n, puzzle, &zero_row, &zero_column);
    // کپی و ذخیره کردن پازل اولیه
    int initialPuzzle[n][n];
    int initial_zero_row = zero_row;
    int initial_zero_column = zero_column;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        initialPuzzle[i][j] = puzzle[i][j];
      }
    }

    char c;
    // تا زمانی که که پازل حل نشده بتوانیم حرکت کنیم
    while (!is_win(n, puzzle)) {
      print_puzzle(n, puzzle, first_name, last_name);
      // فقط با زدن دکمه مورد نظر ورودی را بگیرد
      c = _getch();
      // انجام حرکات
      if (c == DOWN || c == DOWN_ARROW) {
        move_down(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == RIGHT || c == RIGHT_ARROW) {
        move_right(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == UP || c == UP_ARROW) {
        move_up(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      } else if (c == LEFT || c == LEFT_ARROW) {
        move_left(n, puzzle, &zero_row, &zero_column, first_name, last_name);
      }
      // خارج شدن از حلقه وایل
      else if (c == QUIT) {
        break;
      } else if (c == RESETGAME) {
        // بازگرداندن پازل به حالت اولیه
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            puzzle[i][j] = initialPuzzle[i][j];
          }
        }
        // بازگرداندن سطر و ستون صفر به حالت اولیه
        zero_row = initial_zero_row;
        zero_column = initial_zero_column;
        moves = 0;
        print_puzzle(n, puzzle, first_name, last_name);
      } else if (c == NEWSHUFFLE) {
        // شافل کردن همان پازل و داشتن پازل جدید
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
        // cheat
        // برابر قرار دادن هر جای پازل به مقدار درستش
        int trueNumber = 1;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < n; j++) {
            puzzle[i][j] = trueNumber;
            trueNumber++;
          }
        }
        // برابر قرار دادن آخرین خانه به صفر
        puzzle[n - 1][n - 1] = 0;
      }
    }
    // اگر پازل شده باشد و از وایل خارج شده باشد.
    if (is_win(n, puzzle)) {
      print_puzzle(n, puzzle, first_name, last_name);
      puts("\nYou Win!");
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
    // گرفتن مقدار ورودی از کاربر
    scanf("%d", &menu_option);
    //  در صورتی که مقدار ورودی بین 1 تا 3 باشد و در غیر این صورت
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
  // برکرداندن مقداری که کاربر میدهد
  return menu_option;
}

void name_func(char *first_name, char *last_name) {
  printf("What is your first name brave player? ");
  // عدد نوزده به این معنی است که نوزده کراکتر اول را بگیرد
  // به این دلیل 20 نیست چون در اخر اتوماتیک بک اسلش صفر(0\) را می گیرد
  scanf("%19s", first_name);
  printf("what is your last name ?");
  scanf("%19s", last_name);
}

void size_func(int *n) {
  while (1) {
    printf(
        "Enter the size of the puzzle you wish to play with (2 <= n <= 10): ");
    /*
    اسکن اف در صورتی که ورودی بگیرد که دیتای آن درست نباشد
    (برای نمونه در این مورد عدد صحیح نباشد)
    عدد صفر را بر میگرداند و در غیر این صورت 1
    */
    if (scanf("%d", n) != 1) {
      // پاک کردن ورودی
      while (getchar() != '\n')
        ;
      puts("an integer between 2 and 10.");
    } else if (*n >= 2 && *n <= 10) {
      // اگر ورودی بین 2 و 10 باشد
      break;
    } else {
      // اگر ورودی بین 2 و 10 نباشد
      while (getchar() != '\n')
        ;
      puts("size between 2 and 10.");
    }
  }
}

void shuffle_puzzle(int n, int puzzle[n][n], int *zero_row, int *zero_column) {
  /*
    از خانه اول پازل شروع کرده و خانه به خانه یک عدد
     رندوم که قبلا انتخاب نشده را در آن قرار میدهد
  */
  int total = n * n;
  // اعدادی که قبلا انتخاب شده اند
  int used[total];
  for (int i = 0; i < total; i++) {
    used[i] = 0;
  }

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int random;
      // انتخاب عددی که قبلا انتخاب نشده
      do {
        // عددی رندوم بین 0 تا n^2 - 1
        random = rand() % total;
      } while (used[random]);

      used[random] = 1;
      puzzle[i][j] = random;

      if (random == 0) {
        // سطر و ستونی که صفر در آن قرار دارد
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
        // برای خانه اخر اگر برابر ضفر نبود
        if (puzzle[i][j] != 0) {
          return false;
        }
      } else {
        // برای خانه های دیگر اگر برابر عدد مورد نظر نباشند
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

  // چاپ خط بالایی برای هر خانه
  for (int j = 0; j < n; j++) {
    printf("-----");
  }
  printf("-\n");

  int trueNumber = 1;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      printf("|"); // خط کناری برای هر خانه

      // چاپ اعداد
      if (puzzle[i][j] != 0) {
        // اگر عدد در جای درست باشد
        if (puzzle[i][j] == trueNumber) {
          printf(GREEN " %2d " RESET, puzzle[i][j]);
        } else {
          printf(YELLOW " %2d " RESET, puzzle[i][j]);
        }
      } else {
        // در خانه صفر به جای خود صفر خانه خالی چاپ میکنیم
        printf("    ");
      }
      trueNumber++;
    }
    // چاپ اخرین دیوار سمت راست
    printf("|\n");

    // چاپ دیوار پایینی برای هر خانه
    for (int j = 0; j < n; j++) {
      printf("-----");
    }
    // رفتن به سطر جدید
    printf("-\n");
  }
  printf("\nMoves: %d\n", moves);
  printf("\n-> ");
}

void move_down(int n, int puzzle[n][n], int *zero_row, int *zero_column,
               char first_name[20], char last_name[20]) {
  // اگر حرکت در گوشه نباشد
  if (*zero_row < n - 1) {
    swap(&puzzle[*zero_row][*zero_column],
         &puzzle[*zero_row + 1][*zero_column]); // سطر به علاوه 1
    (*zero_row)++;
  } else {
    // اگر صفر با پایین رسیده باشد
    // بالا بردن صفر از اخرین خانه به ترتیب به بالاترین خانه
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
         &puzzle[*zero_row - 1][*zero_column]); // سطر - 1
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
         &puzzle[*zero_row][*zero_column + 1]); // ستون + 1
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
         &puzzle[*zero_row][*zero_column - 1]); // ستون - 1
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
