// // #include <stdio.h>

// // int main() {
// //     char s[9];           // Массив для 8 цифр + завершающий ноль
// //     int pos1, pos2;
// //     int d1, d2, product;

// //     // 1. Вводим число как строку
// //     printf("Введите 8-значное число: ");
// //     scanf("%8s", s);

// //     // 2. Спрашиваем позиции (например, 2 и 5)
// //     printf("Введите две позиции для перемножения (от 1 до 8): ");
// //     scanf("%d %d", &pos1, &pos2);

// //     // 3. Достаем цифры
// //     d1 = s[pos1 - 1] - '0';
// //     d2 = s[pos2 - 1] - '0';

// //     // 4. Считаем произведение
// //     product = d1 * d2;

// //     // 5. Выводим результат
// //     printf("Цифра на позиции %d: %d\n", pos1, d1);
// //     printf("Цифра на позиции %d: %d\n", pos2, d2);
// //     printf("Произведение: %d\n", product);

// //     return 0;
// // }


// #include <stdio.h>
// int main ()
// {
//     int res;
//     scanf("%d", &res)
    
//     switch (res)
//     {
//         case 1:
//         printf("Variable %d", res);
//         break;
//         case 245:
//         printf("Variable 245");
//         break;
//         default:
//         printf("some other charge");

//     }
//     printf("\n")
//     return 0;
// }


#include <stdio.h>
#include <stddef.h>
#include <locale.h>



int *find_min(int *begin, int *end);
int *find_max(int *begin, int *end);
long long sum_between(const int *first, const int *second);
size_t find_longest_increasing(int *begin, int *end, int **sequence_begin);
void reverse_range(int *begin, int *end);
void print_array(const int *begin, const int *end);




void print_array(const int *begin, const int *end)
{
    const int *p = begin;
    while (p < end) {
        printf("%d ", *p);
        p++;
    }
    printf("\n");
}

int *find_min(int *begin, int *end)
{
    int *min_ptr = begin;
    int *p = begin + 1;
    while (p < end) {
        if (*p < *min_ptr) {
            min_ptr = p;
        }
        p++;
    }
    return min_ptr;
}

int *find_max(int *begin, int *end)
{
    int *max_ptr = begin;
    int *p = begin + 1;
    while (p < end) {
        if (*p > *max_ptr) {
            max_ptr = p;
        }
        p++;
    }
    return max_ptr;
}

long long sum_between(const int *first, const int *second)
{
    const int *left  = (first < second) ? first  : second;
    const int *right = (first < second) ? second : first;

    long long sum = 0;
    const int *p = left + 1;
    while (p < right) {
        sum += *p;
        p++;
    }
    return sum;
}

void reverse_range(int *begin, int *end)
{
    int *left  = begin;
    int *right = end - 1;
    while (left < right) {
        int temp = *left;
        *left = *right;
        *right = temp;
        left++;
        right--;
    }
}

size_t find_longest_increasing(int *begin, int *end, int **sequence_begin)
{
    if (begin >= end) {
        *sequence_begin = begin;
        return 0;
    }

    int *best_start = begin;
    size_t best_len = 1;

    int *cur_start = begin;
    size_t cur_len = 1;

    int *p = begin + 1;
    while (p < end) {
        if (*p > *(p - 1)) {
            cur_len++;
        } else {
            if (cur_len > best_len) {
                best_len = cur_len;
                best_start = cur_start;
            }
            cur_start = p;
            cur_len = 1;
        }
        p++;
    }

    if (cur_len > best_len) {
        best_len = cur_len;
        best_start = cur_start;
    }

    *sequence_begin = best_start;
    return best_len;
}




int main(void)
{
    int n;
    setlocale(LC_ALL, "ru");

    printf("Введите количество элементов N (2-1000): ");
    if (scanf("%d", &n) != 1 || n < 2 || n > 1000) {
        printf("Ошибка: N должно быть от 2 до 1000.\n");
        return 1;
    }

    int arr[1000];
    printf("Введите %d целых чисел:\n", n);
    for (int i = 0; i < n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("Ошибка ввода.\n");
            return 1;
        }
    }

    int *begin = arr;
    int *end = arr + n;

    printf("\nИсходный массив:\n");
    print_array(begin, end);

    int *min_ptr = find_min(begin, end);
    int *max_ptr = find_max(begin, end);

    printf("\nМинимум: %d\n", *min_ptr);
    printf("Позиция минимума: %ld\n", min_ptr - begin);
    printf("Максимум: %d\n", *max_ptr);
    printf("Позиция максимума: %ld\n", max_ptr - begin);

    long long dist = (max_ptr - min_ptr);
    if (dist < 0) dist = -dist;
    printf("Расстояние между минимумом и максимумом: %lld\n", dist);

    printf("Сумма элементов между минимумом и максимумом: %lld\n",
           sum_between(min_ptr, max_ptr));

    int *seq_begin = NULL;
    size_t seq_len = find_longest_increasing(begin, end, &seq_begin);

    printf("\nСамый длинный возрастающий участок:\n");
    print_array(seq_begin, seq_begin + seq_len);
    printf("Длина: %zu\n", seq_len);

    reverse_range(seq_begin, seq_begin + seq_len);

    printf("\nМассив после разворота выбранного участка:\n");
    print_array(begin, end);

    return 0;
}

