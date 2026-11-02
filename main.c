#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void part1();
void part2();
double f(double x);
void printTable(double x_arr[], double y_arr[], unsigned int size);
void pressEnterToContinue();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    double *x_arr = NULL;
    double *y_arr = NULL;
    bool *is_gap = NULL;
    unsigned int n = 0;

    while(true)
    {
        system("cls");

        printf("Лотоцький Назар РС-зп61\n");
        printf("Лабораторна робота №3\n\n");

        int t = 0;

        printf("Оберіть варіант введення початкових данних\n"
               "1 - початкове, кінцеве значення та кількість точок в таблиці (за умовчанням)\n"
               "2 - початкове, кінцеве значення та крок зміни аргументу\n"
               ": ");
        scanf("%u", &t);

        double delta = 0;

        //Введення меж аргументу

        double x1, x2;
        printf("Початкове значення аргументу: ");
        scanf("%lf", &x1);

        while(true)
        {
            printf("Кінцеве значення аргументу: ");
            scanf("%lf", &x2);

            if(x2 > x1)break;
            printf("Неправильне кінцеве значення\n");
        }


        if(t == 1)
        {
            while(true)
            {
                printf("Кількість точок у таблиці: ");
                scanf("%u", &n);

                if(n >= 2)break;
                printf("Неправильне введене значення (>=2)\n");
            }
            delta = (x2 - x1) / (n - 1);
        }
        else
        {
            while(true)
            {
                printf("Крок зміни аргументу: ");
                scanf("%lf", &delta);

                if(delta > 0)break;
                printf("Неправильний крок зміни аргументу\n");
            }
            n = (unsigned int)floor((x2 - x1) / delta) + 1;
        }

        free(x_arr);
        free(y_arr);
        free(is_gap);
        x_arr = malloc(n * sizeof(double));
        y_arr = malloc(n * sizeof(double));
        is_gap = malloc(n * sizeof(bool));
        if(x_arr == NULL || y_arr == NULL || is_gap == NULL)
        {
            printf("Помилка виділення пам'яті");
            exit(0);
        }
        bool gap_found = false;
        for(unsigned int i = 0; i < n; i++)
        {
            x_arr[i] = x1 + delta*i;
            y_arr[i] = f(x_arr[i]);
            is_gap[i] = false;
        }
        for(unsigned int i = 0; i < n; i++)
        {
            if(i != (n - 1))
            {
                is_gap[i] = y_arr[i] * y_arr[i+1] < 0;
                gap_found |= is_gap[i];
            }
        }

        printTable(x_arr, y_arr, n);

        if(gap_found) break;

        printf("Не знайдено проміжок ізоляції\n");

        pressEnterToContinue();

    }
    printf("Знайдено проміжок(ки) ізоляції:\n"
           "Номер|Проміжок\n");
    unsigned int count = 0;
    unsigned int choise;
    for(unsigned int i = 0; i < n; i++)
    {
        if((i != (n - 1)) && is_gap[i])
        {
            choise = i;
            count++;
            printf("%-5u-[%.2lf, %.2lf]\n", i, x_arr[i], x_arr[i+1]);
        }
    }
    while(true)
    {
        if(count == 1) break;
        printf("Оберіть номер проміжку для обчислень: ");
        unsigned int a;
        scanf("%u", a);
        if(a < n && is_gap[a])
        {
            choise = a;
            break;
        }
        printf("Невірний номер проміжку");
    }

    printf("Обраний проміжок: [%.2lf, %.2lf]\n", x_arr[choise], x_arr[choise+1]);

    double isol_gap[2] = { x_arr[choise], x_arr[choise + 1] };

    pressEnterToContinue();

    system("cls");

    printf("Обраний проміжок: [%.2lf, %.2lf]\n", x_arr[choise], x_arr[choise+1]);

    int t1 = 0;

    while(true)
    {
        printf("Оберіть варіант ітеративного розв'язання нелінійних рівняння\n"
           "1 - методом хорд\n"
           "2 - методом половинного ділення\n"
           ": ");
        scanf("%u", &t1);
        if(t1 >= 1 && t1 <= 2) break;
        else printf("Невірно введене значення!\n");
    }


    double max_err;
    unsigned int max_iter;

    while(true)
    {
        printf("Введіть максимальну похибку): ");
        scanf("%lf", &max_err);
        if(max_err > 0) break;
        else printf("Невірно введене значення!\n");
    }

    while(true)
    {
        printf("Введіть кількість ітерацій(>0): ");
        scanf("%d", &max_iter);
        if(max_iter > 0) break;
        else printf("Невірно введене значення!\n");
    }

    bool verbose = false;

    while(true)
    {
        char buffer[2];
        printf("Виводити ітерації?(y/n):");
        scanf("%1s", &buffer);
        if(buffer[0] == 'y')
        {
            verbose = true;
            break;
        }
        else if (buffer[0] == 'n')
        {
            verbose = false;
            break;
        }
        else printf("Невірно введене значення!\n");
    }

    /*printf("[%.2lf, %.2lf]\n max_err = %.2lf\n max_iter = %u\n verbose = %s\n",
           isol_gap[0],
           isol_gap[1],
           max_err,
           max_iter,
           verbose ? "Y" : "N");*/

    double result = 0.0 / 0.0; // NAN

    switch(t1)
    {
    case 1:
        /*
        Аналітично знайдено f''(x) = 5*x^3 + 48*(x+20)^2
        f''(x) < 0 при x < -9.6, що також знайдено аналітичним шляхом
        */
        double sign = 1;
        if(isol_gap[0] < -9.6) sign = -1;

        if(f(isol_gap[0]) == 0)
        {
            if(verbose) printf("Знайдено відповідь на рівняння.\n");
            result = isol_gap[0];
        }
        else if (f(isol_gap[1]) == 0)
        {
            if(verbose) printf("Знайдено відповідь на рівняння.\n");
            result = isol_gap[1];
        }
        else if (sign * f(isol_gap[0]) > 0)
        {
            double old_x = isol_gap[1];
            double a = isol_gap[0];
            for(unsigned int i = 0; i < max_iter; i++)
            {
                double x = old_x - f(old_x)/(f(old_x) - f(a))*(old_x - a);
                if(verbose) printf("Ітерація №%u:\n"
                                   "\tx    = %.2lf\n"
                                   "\tf(x) = %.2lf\n",
                                   i,
                                   x,
                                   f(x));
                if(fabs(f(x)) <= max_err)
                {
                    if(verbose) printf("Значення x задовільнило максимальну похибку.\n");
                    result = x;
                    break;
                }
                old_x = x;
            }
        }
        else
        {
            double old_x = isol_gap[0];
            double b = isol_gap[1];
            for(unsigned int i = 0; i < max_iter; i++)
            {
                double x = old_x - f(old_x)/(f(b) - f(old_x)) * (b - old_x);
                if(verbose) printf("Ітерація №%u:\n"
                                   "\tx    = %.2lf\n"
                                   "\tf(x) = %.2lf\n",
                                   i,
                                   x,
                                   f(x));
                if(fabs(f(x)) <= max_err)
                {
                    if(verbose) printf("Значення x задовільнило максимальну похибку.\n");
                    result = x;
                    break;
                }
                old_x = x;
            }
        }
        break;
    case 2:
        if(f(isol_gap[0]) == 0)
            result = isol_gap[0];
        else if (f(isol_gap[1]) == 0)
            result = isol_gap[1];
        else
        {
            double interval[2] = {isol_gap[0], isol_gap[1]};
            for(unsigned int i = 0; i < max_iter; i++)
            {
                double delta = (interval[1] - interval[0]) / 2;
                double x = interval[0] + delta;
                if(x == 0)
                {
                    if(verbose) printf("Знайдено відповідь на рівняння.\n");
                    result = x;
                    break;
                }
                if(verbose) printf("Ітерація №%u:\n"
                                   "\tПроміжок: [%lf, %lf]\n"
                                   "\t x посередині проміжку = %lf\n"
                                   "\tf(x)посередині проміжку = %lf\n",
                                   i,
                                   interval[0], interval[1],
                                   x,
                                   f(x));
                if(fabs(f(x)) <= max_err)
                {
                    if(verbose) printf("Значення x задовільнило максимальну похибку.\n");
                    result = x;
                    break;
                }
                if(f(interval[0]) * f(x) < 0) interval[1] = x;
                else interval[0] = x;
            }
        }
        break;

    }

    if(result != result)
    {
        printf("Роз'вязок, що задовільнив би умову не знайдено\n");

        pressEnterToContinue();
        return 0;
    }
    printf("Знайдено розв'язок що задовільнив допустиму похибку:\n"
           "\tпохибка = %e\n"
           "\tx   = %lf\n"
           "\tf(x)= %e\n",
           max_err,
           result,
           f(result));

    pressEnterToContinue();
    return 0;
}

//Функція залежності y від x за умовою варіанту 2
double f(double x){
    return 0.25*pow(x, 5) + 4.0 * pow(x + 20.0, 4) - 2.0 * x;
}

//Виведення таблиці на екран
void printTable(double x_arr[], double y_arr[], unsigned int size){

    if(size == 0) return;
    printf("╔═══════════════════════╤═══════════════════════╗\n");
    printf("║           x           │           y           ║\n");
    printf("╠═══════════════════════╪═══════════════════════╣\n");
    for(unsigned int i = 0; i < size; i++){
        printf("║%23.8lf│%23.8lf║\n", x_arr[i], y_arr[i]);
        if(i == size - 1)
            printf("╚═══════════════════════╧═══════════════════════╝\n");
        else
            printf("╟───────────────────────┼───────────────────────╢\n");
    }
}

//Очікує Enter від користувача щоб продовжити
void pressEnterToContinue() {
    printf("\nНатисніть Enter щоб продовжити...");

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    getchar();
}
