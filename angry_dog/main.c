#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

int main()
{
    char mas[10][21]; // Создаем двумерный массив для представления игрового поля 10x20.
    int i;
    int x = 10, y = 5; // Начальные координаты игрока.
    char key;
    int ox, oy;
    int apllex = 5, aplley = 3; // Начальные координаты апельсина.
    int score = 0;  // Счётчик очков.
    srand(56);

    do
    {
        // Отрисовываем стены
        sprintf(mas[0], "####################");
        for (i = 1; i < 9; i++)
        {
            sprintf(mas[i], "#                  #");
        }
        sprintf(mas[9], "####################");

        mas[y][x] = '@';           // Рисуем игрока
        mas[aplley][apllex] = '*'; // Рисуем апельсин

        system("cls"); // Очищаем консоль.

        // Выводим игровое поле
        for (i = 0; i < 10; i++)
        {
            printf("%s\n", mas[i]);
        }
        // Вывод счёта.
        printf("Score: %d\n", score);

        key = getch(); // Получаем символ клавиши.

        ox = x;
        oy = y;

        // Обработка клавиш управления
        if (key == 'w')
        {
            y--;
        }
        if (key == 's')
        {
            y++;
        }
        if (key == 'a')
        {
            x--;
        }
        if (key == 'd')
        {
            x++;
        }

        // Проверка на столкновение с стеной
        if (mas[y][x] == '#')
        {
            x = ox;
            y = oy;
        }

        // Обработка подбора апельсина
        if ((x == apllex) && (y == aplley))
        {
            apllex = rand() * 1.0 / RAND_MAX * 18 + 1;
            aplley = rand() * 1.0 / RAND_MAX * 8 + 1;
            score +=5;
        }

    } while (key != 'e'); // Выход из цикла при нажатии 'e'.

    return 0;
}
