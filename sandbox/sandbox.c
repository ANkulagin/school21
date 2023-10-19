#include <stdio.h>

#define TEST

#define cube(x) ((x) * (x))

#define SWAP(x, y)    \
    do                \
    {                 \
        int temp = x; \
        x = y;        \
        y = temp;     \
    } while (0)

int main()
{
    int count = 2, n = 2;

    // Вывод результата выражения 27/cube(count+1)
    printf("%d\n", 27 / cube(count + 1));

    // Вызов макроса cube с аргументом ++n
    cube(++n);

    // Условный оператор
    if (count > 0)
    {
        printf("%d\n", n);
    }

// Условная компиляция
#ifdef TEST
    printf("test print 1\n");
#endif

    int a = 5, b = 7;

    // Условный оператор с вызовом макроса SWAP
    if (count > 0)
    {
        SWAP(n, b);
    }
    else
    {
        // else пустой, так как ничего не делаем
    }

    // Вывод значений переменных n и b
    printf("n=%d b=%d\n", n, b);

// Условная компиляция с выводом номера строки и имени функции
#ifdef TEST
    printf("test print 2 line=%d function=%s\n", __LINE__, __func__);
#endif

    return 0;
}
