#include <iostream>
#include <new>

void  cleanup (int** m, int rows) {
    if (m == nullptr) {
        return;
    }
    for (int i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
    }

int main() {
    int rows = 0, cols = 0;

    if (!(std::cin >> rows >> cols) || rows <= 0 || cols <= 0) {
        return 1;
    }

    int** matrix = nullptr;
    try {
        matrix = new int*[rows];

        for (int i = 0; i < rows; ++i) {
            matrix[i] = nullptr;
         }
   
        for (int i = 0; i < rows; ++i) {
            matrix[i] = new int[cols];
        }
    }
    catch (const std::bad_alloc& e){
        cleanup(matrix, rows);
        return 2;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                cleanup(matrix, rows);
                return 1;
            }
        }
    }

    std::cout << "\n";

    for (int j = 0; j < cols; ++j) {
        for (int i = 0; i < rows; ++i) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }

    cleanup(matrix, rows);

    return 0;
}