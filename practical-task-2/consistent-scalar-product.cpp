#include <cstdio>
#include <cmath>

#define VECTOR_PART_SIZE 1000
#define PARTS_COUNT 10

// Инициализация части вектора
void init_vector_part(int vector_id, int part_number, 
                      int part_size, double* vector) {
    for (int i = 0; i < part_size; i++) {
        if (vector_id == 0)
            vector[i] = part_number * part_size + i;
        else
            vector[i] = (part_number * part_size + i) * 0.1;
    }
}

// Скалярное произведение части векторов
double smulv2_part(const double* x, const double* y, int part_size) {
    double result = 0;
    for (int i = 0; i < part_size; i++)
        result += x[i] * y[i];
    return result;
}

// Вывод результата
void print_result(double n) {
    printf("Result: %lf\n", sqrt(n));
}

// Суммирование массива (редукция)
double reduce_sum(double* arr, int begin, int end) {
    if (end - begin == 1) {
        return arr[begin];
    }
    if (end - begin > 1) {
        int mid = begin + (end - begin) / 2;
        double tmp1 = reduce_sum(arr, begin, mid);
        double tmp2 = reduce_sum(arr, mid, end);
        return tmp1 + tmp2;
    }
    return 0;
}

// Умножение векторов по частям
void mulv(double** x, double** y, double* z) {
    for (int i = 0; i < PARTS_COUNT; i++) {
        z[i] = smulv2_part(x[i], y[i], VECTOR_PART_SIZE);
    }
}

int main() {
    // Выделяем память для частей векторов
    double** x = new double*[PARTS_COUNT];
    double** y = new double*[PARTS_COUNT];
    double* z = new double[PARTS_COUNT];
    
    // Инициализируем части векторов x и y
    for (int i = 0; i < PARTS_COUNT; i++) {
        x[i] = new double[VECTOR_PART_SIZE];
        y[i] = new double[VECTOR_PART_SIZE];
        
        init_vector_part(0, i, VECTOR_PART_SIZE, x[i]);
        init_vector_part(1, i, VECTOR_PART_SIZE, y[i]);
    }
    
    // Вычисляем скалярное произведение по частям
    mulv(x, y, z);
    
    // Суммируем частичные результаты
    double result = reduce_sum(z, 0, PARTS_COUNT);
    
    // Выводим результат
    print_result(result);
    
    // Освобождаем память
    for (int i = 0; i < PARTS_COUNT; i++) {
        delete[] x[i];
        delete[] y[i];
    }
    delete[] x;
    delete[] y;
    delete[] z;
    
    return 0;
}