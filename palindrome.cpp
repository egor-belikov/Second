#include <iostream>
#include <string>
#include <math.h>
#define MAXN 1000
using namespace std;

int palSubSeq(int** dynamic, string s, int left, int right) //ленивая динамика. динамика lr-типа. длина максимального подпалиндрома на куске строки с l по r.
{
    if (dynamic[left][right] == -1)
    {
        if (s[left] == s[right])
            dynamic[left][right] = palSubSeq(dynamic, s, left + 1, right - 1) + 2;
        else
            dynamic[left][right] = max(palSubSeq(dynamic, s, left + 1, right), palSubSeq(dynamic, s, left, right - 1));
    }
    return dynamic[left][right];
}

void palChars(int** dynamic, string s, int left, int right, int palLeft, int palRight, char* palindrome)//восстановление ответа очевидно
{
    while (left <= right)
    {
        if ((left == right) && (dynamic[left][right] == 1))
            palindrome[palLeft++] = s[left++];
        else
            if (s[left] == s[right])
            {
                palindrome[palLeft++] = s[left++];
                palindrome[palRight--] = s[right--];
            }
            else
                if (dynamic[left + 1][right] > dynamic[left][right - 1])
                    left++;
                else
                    right--;
    }
}
int main()
{
    int** dynamic; //двумерный массив для динамики.
    dynamic = (int**) malloc(sizeof(int*) * MAXN);
    for (int i = 0; i < MAXN; i++)
        dynamic[i] = (int*) malloc(sizeof(int) * MAXN); // маллочим память
    for (int i = 0; i < MAXN; i++) //инициализация динамики
        for (int j = 0; j < MAXN; j++)
            if (i == j)
                dynamic[i][j] = 1;
            else
                if (i > j)
                    dynamic[i][j] = 0;
                else
                    dynamic[i][j] = -1;
    string s;//вводимая строка
    cin >> s;
    int n = (int)s.length();//длина строки
    int left = 0, right = n - 1;
    palSubSeq(dynamic, s, left, right); //запуск динамики
    char* palindrome;
    palindrome = (char*) malloc(sizeof(char) * MAXN);
    int palLeft = 0, palRight = dynamic[0][n - 1] - 1;
    left = 0;
    right = n - 1;
    palChars(dynamic, s, left, right, palLeft, palRight, palindrome); //запуск восстановления ответа
    for (int i = 0; i <= dynamic[0][n - 1] - 1; i++)
        cout << palindrome[i];
    cout << endl;
    return 0;
}

