#include <iostream>
#include <cstdlib>

using namespace std;




int** matr_2_2(int a, int b, int c, int d)
{
    int strr = 2;
    int stol = 2;


    int** matr = (int**)calloc(strr, sizeof(int*));
    for (int i = 0; i < strr; i++) {
        matr[i] = (int*)calloc(stol, sizeof(int));
    }


    matr[0][0] = a;
    matr[0][1] = b;
    matr[1][0] = c;
    matr[1][1] = d;
    while (matr[0][0] < 0)
    {
        cout << "Число А отрицательное. Повторите ввод" << endl;
        cin >> matr[0][0];
    }while (matr[0][1] < 0)
    {
        cout << "Число А отрицательное. Повторите ввод" << endl;
        cin >> matr[0][1];
    }
    return matr;
}
void rassh(int*** matrix, int oldRows, int* oldCols, int newRows, int newCols) {
    *matrix = (int**)realloc(*matrix, newRows * sizeof(int*));
    for (int i = 0; i < oldRows; i++) {
        (*matrix)[i] = (int*)realloc((*matrix)[i], newCols * sizeof(int));
        for (int j = *oldCols; j < newCols; j++) {
            (*matrix)[i][j] = 0.0;
        }
    }
    for (int i = oldRows; i < newRows; i++) {
        (*matrix)[i] = (int*)calloc(newCols, sizeof(int));
    }
}
void zap(int** matr, int rowww, int colll)
{

    for (int i = 0; i < rowww; i++) {
        for (int j = 2; j < colll; j++) {
            matr[i][j] = (i - 1) * matr[1][0] + (j - 1) * matr[1][1];
        }
    }

    for (int i = 2; i < rowww; i++)
    {
        for (int j = 0; j < colll; j++)
        {
            matr[i][j] = (i - 1) * matr[1][0] + (j - 1) * matr[1][1];
        }
    }

}


int* nulevie_stolb(int** matr, int strr, int stoll, int& zeroCount) {
    bool* zeroStoll = (bool*)calloc(stoll, sizeof(bool));
    zeroCount = 0;

    for (int j = 0; j < stoll; j++) {
        bool hasZero = false;
        for (int i = 0; i < strr; i++) {
            if (matr[i][j] == 0) {
                hasZero = true;
                break;
            }
        }
        if (hasZero) {
            zeroStoll[j] = true;
            zeroCount += 1;
        }
    }


    int* zeroStol = (int*)malloc(zeroCount * sizeof(int));
    int index = 0;
    for (int j = 0; j < stoll; j++) {
        if (zeroStoll[j]) {
            zeroStol[index++] = j;

        }
    }

    free(zeroStoll);
    return zeroStol;
}


int** del_Stoll(int** matr, int strr, int& stoll, int* udal_stoll, int count) {//удаляем столбцы
    if (count == 0) return matr;

    int newStoll = stoll - count;
    int** newMatr = (int**)calloc(strr, sizeof(int*));

    for (int i = 0; i < strr; i++) {
        newMatr[i] = (int*)calloc(newStoll, sizeof(int));
        int newJ = 0;
        for (int j = 0; j < stoll; j++) {
            bool skip = false;
            for (int k = 0; k < count; k++) {
                if (j == udal_stoll[k]) {
                    skip = true;
                    break;
                }
            }
            if (!skip) {
                newMatr[i][newJ++] = matr[i][j];
            }
        }
    }

    for (int i = 0; i < strr; i++) {
        free(matr[i]);
    }
    free(matr);

    stoll = newStoll;
    return newMatr;
}


void printMatr(int** matr, int strr, int stoll) {
    for (int i = 0; i < strr; i++) {
        for (int j = 0; j < stoll; j++) {
            cout << matr[i][j] << "\t";
        }
        cout << endl;
    }
}

void freeMatrix(int** matr, int strr) {
    for (int i = 0; i < strr; i++) {
        free(matr[i]);
    }
    free(matr);
}

int main() {
    int ro = 2;
    int co = 2;
    setlocale(LC_ALL, "Russian");
    int a, b;
    cout << "Введите а" << endl;
    cin >> a;
    cout << "Введите b" << endl;
    cin >> b;
    cout << "Введите c: ";
    int c;
    cin >> c;

    cout << "Введите d: ";
    int d;
    cin >> d;

    int rows = 2 + a;
    int cols = 2 + b;
    int** matrix = matr_2_2(a, b, c, d);

    cout << "Исходная расширенная матрица:" << endl;
    printMatr(matrix, ro, co);

    rassh(&matrix, ro, &co, rows, cols);
    zap(matrix, rows, cols);
    cout << "РАсширенная матрица" << endl;
    printMatr(matrix, rows, cols);
    int zeroCount;
    int* zeroColumns = nulevie_stolb(matrix, rows, cols, zeroCount); // функция ищет стобцы в которых есть 0 и передает их количество в zeroCount

    if (zeroCount > 0) { //выводим номера столбцов в которых есть нули
        cout << "Найдены нулевые значения в столбцах: ";
        for (int i = 0; i < zeroCount; i++) {
            cout << zeroColumns[i] + 1 << " ";
        }
        cout << endl;


        matrix = del_Stoll(matrix, rows, cols, zeroColumns, zeroCount); // удаляем столбцы с нулями

        cout << "Матрица после удаления столбцов:" << endl;
        printMatr(matrix, rows, cols);
    }
    else {
        cout << "Нулевых значений нет" << endl;
    }


    free(zeroColumns);
    freeMatrix(matrix, rows);

    //ПУНКТ 2
    double aa, ba;
    cout << "Введите а и b" << endl;
    cin >> aa;
    cin >> ba;
    double* ptr_a = new double(aa);
    double* ptr_b = new double(ba);
    *ptr_a *= 3;
    double i = *ptr_a;
    *ptr_a = *ptr_b;
    *ptr_b = i;
    aa = *ptr_a;
    ba = *ptr_b;
    cout << "После всех операций a = " << aa << ",b = " << ba << endl;
    delete ptr_a;
    delete ptr_b;
}
