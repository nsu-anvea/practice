#include <cstdio>
#include <cmath>

#define MATRIX_SIZE 1000        // Размер матрицы (n×n)
#define PARTS_COUNT 10          // Количество частей (подматриц)
#define PART_ROWS (MATRIX_SIZE / PARTS_COUNT)  // Строк в каждой подматрице

// Инициализация части матрицы (подматрицы)
void init_matrix_part(int part_number, int rows, int cols, double* matrix_part) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            // Формула для инициализации: можно изменить по желанию
            int global_row = part_number * rows + i;
            matrix_part[i * cols + j] = global_row + j * 0.1;
        }
    }
}

// Инициализация вектора
void init_vector(int size, double* vector) {
    for (int i = 0; i < size; i++) {
        vector[i] = i * 0.5;  // Формула для инициализации
    }
}

// Умножение подматрицы на вектор
void matrix_vector_mult_part(const double* matrix_part, 
                              const double* vector,
                              double* result,
                              int rows,      // количество строк в подматрице
                              int cols) {    // размер вектора (и столбцов матрицы)
    for (int i = 0; i < rows; i++) {
        result[i] = 0;
        for (int j = 0; j < cols; j++) {
            result[i] += matrix_part[i * cols + j] * vector[j];
        }
    }
}

// Вывод части результирующего вектора
void print_result_part(int part_number, const double* result_part, int size) {
    printf("Result part %d:\n", part_number);
    for (int i = 0; i < size && i < 5; i++) {  // Выводим первые 5 элементов
        printf("  [%d] = %lf\n", part_number * size + i, result_part[i]);
    }
    if (size > 5) {
        printf("  ...\n");
    }
}

// Вывод полного результата
void print_full_result(double** result_parts, int parts_count, int part_size) {
    printf("\nFull result vector (first 10 elements):\n");
    int count = 0;
    for (int i = 0; i < parts_count && count < 10; i++) {
        for (int j = 0; j < part_size && count < 10; j++) {
            printf("  [%d] = %lf\n", count, result_parts[i][j]);
            count++;
        }
    }
}

// Умножение всей матрицы на вектор по частям
void multiply_matrix_vector(double** matrix_parts, 
                            double* vector,
                            double** result_parts) {
    for (int i = 0; i < PARTS_COUNT; i++) {
        matrix_vector_mult_part(matrix_parts[i], 
                               vector, 
                               result_parts[i],
                               PART_ROWS, 
                               MATRIX_SIZE);
    }
}

int main() {
    printf("Matrix-Vector multiplication\n");
    printf("Matrix size: %d×%d\n", MATRIX_SIZE, MATRIX_SIZE);
    printf("Number of parts: %d\n", PARTS_COUNT);
    printf("Rows per part: %d\n\n", PART_ROWS);
    
    // Выделяем память для подматриц
    double** matrix_parts = new double*[PARTS_COUNT];
    for (int i = 0; i < PARTS_COUNT; i++) {
        matrix_parts[i] = new double[PART_ROWS * MATRIX_SIZE];
    }
    
    // Выделяем память для вектора
    double* vector = new double[MATRIX_SIZE];
    
    // Выделяем память для частей результирующего вектора
    double** result_parts = new double*[PARTS_COUNT];
    for (int i = 0; i < PARTS_COUNT; i++) {
        result_parts[i] = new double[PART_ROWS];
    }
    
    // Инициализируем подматрицы
    printf("Initializing matrix parts...\n");
    for (int i = 0; i < PARTS_COUNT; i++) {
        init_matrix_part(i, PART_ROWS, MATRIX_SIZE, matrix_parts[i]);
    }
    
    // Инициализируем вектор
    printf("Initializing vector...\n");
    init_vector(MATRIX_SIZE, vector);
    
    // Выполняем умножение матрицы на вектор
    printf("Multiplying matrix by vector...\n\n");
    multiply_matrix_vector(matrix_parts, vector, result_parts);
    
    // Выводим результаты по частям
    for (int i = 0; i < PARTS_COUNT; i++) {
        print_result_part(i, result_parts[i], PART_ROWS);
    }
    
    // Выводим полный результат (первые 10 элементов)
    print_full_result(result_parts, PARTS_COUNT, PART_ROWS);
    
    // Освобождаем память
    for (int i = 0; i < PARTS_COUNT; i++) {
        delete[] matrix_parts[i];
        delete[] result_parts[i];
    }
    delete[] matrix_parts;
    delete[] result_parts;
    delete[] vector;
    
    return 0;
}