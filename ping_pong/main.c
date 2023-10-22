#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define WIDTH 80
#define HEIGHT 25
#define PADDLE_SIZE 3
#define BALL_SIZE 1

// Структура для представления ракетки
typedef struct {
  int x;
  int y;
} Paddle;

// Структура для представления мяча
typedef struct {
  int x;
  int y;
  int dx;
  int dy;
} Ball;

// Инициализация библиотеки ncurses
void init_ncurses() {
  initscr();
  raw();
  keypad(stdscr, TRUE);
  noecho();
  curs_set(0);
}

// Функция отрисовки игрового поля
void draw_game(const Paddle *left_paddle, const Paddle *right_paddle,
               const Ball *ball) {
  clear();

  // Отрисовка ракеток
  for (int i = 0; i < PADDLE_SIZE; ++i) {
    mvprintw(left_paddle->y + i, left_paddle->x, "|");
    mvprintw(right_paddle->y + i, right_paddle->x, "|");
  }

  // Отрисовка мяча
  mvprintw(ball->y, ball->x, "O");

  refresh();
}

int main() {
  init_ncurses();

  // Инициализация ракеток и мяча
  Paddle left_paddle = {2, HEIGHT / 2 - PADDLE_SIZE / 2};
  Paddle right_paddle = {WIDTH - 3, HEIGHT / 2 - PADDLE_SIZE / 2};
  Ball ball = {WIDTH / 2, HEIGHT / 2, 1, 1};

  while (1) {
    draw_game(&left_paddle, &right_paddle, &ball);

    // Получение символа клавиши
    int ch = getch();
    switch (ch) {
    case 'a':
      // Движение левой ракетки вверх
      left_paddle.y -= (left_paddle.y > 0) ? 1 : 0;
      break;
    case 'z':
      // Движение левой ракетки вниз
      left_paddle.y += (left_paddle.y < HEIGHT - PADDLE_SIZE) ? 1 : 0;
      break;
    case 'k':
      // Движение правой ракетки вверх
      right_paddle.y -= (right_paddle.y > 0) ? 1 : 0;
      break;
    case 'm':
      // Движение правой ракетки вниз
      right_paddle.y += (right_paddle.y < HEIGHT - PADDLE_SIZE) ? 1 : 0;
      break;
    case ' ':
      // Пропуск действия на очередном шаге игры
      break;
    case 'q':
      // Завершение программы при нажатии 'q'
      endwin();
      exit(0);
    }

    // Обновление позиции мяча
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Отскок от верхней и нижней стенок
    if (ball.y <= 0 || ball.y >= HEIGHT - BALL_SIZE) {
      ball.dy = -ball.dy;
    }

    // Отскок от ракеток
    if ((ball.x == left_paddle.x + 1 && ball.y >= left_paddle.y &&
         ball.y < left_paddle.y + PADDLE_SIZE) ||
        (ball.x == right_paddle.x - 1 && ball.y >= right_paddle.y &&
         ball.y < right_paddle.y + PADDLE_SIZE)) {
      ball.dx = -ball.dx;
    }

    // Проверка на забитие гола
    if (ball.x <= 0 || ball.x >= WIDTH - BALL_SIZE) {
      // TODO: Обработка забития гола
      // Пока что просто сбрасываем мяч в центр поля
      ball.x = WIDTH / 2;
      ball.y = HEIGHT / 2;
    }
  }

  endwin();
  return 0;
}
