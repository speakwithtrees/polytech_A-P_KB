#include <new>
#include <cstddef>
#include <limits>

void  cleanup (int** m, size_t rows) {
    if (m == nullptr) {
        return;
    }
    for (size_t i = 0; i < rows; ++i) {
        delete[] m[i];
    }
    delete[] m;
}

int** concat_rows(
    const int* const* lhs, size_t n1, size_t m1,
    const int* const* rhs, size_t n2, size_t m2
) { 
    int n;
    if (n1 > n2) {
        n = n1;
    } else {
        n = n2;
    }

    int** result = nullptr;

    try {
        result = new int*[n];

        for (size_t i = 0; i < n; ++i) {
            result[i] = nullptr;
        }

        for (size_t i = 0; i < n; ++i) {
            bool has_lhs = i < n1;
            bool has_rhs = i < n2;

            size_t len = 0;

            if (has_lhs) {
                len = m1;
            }

            if (has_rhs) {
                if (m2 > std::numeric_limits<size_t>::max() - len) {
                    cleanup(result, n);
                    return nullptr;
                }

                len += m2;
            }

            result[i] = new int[len];

            size_t k = 0;

            if (has_lhs) {
                for (size_t j = 0; j < m1; ++j) {
                    result[i][k] = lhs[i][j];
                    k++;
                }
            }

            if (has_rhs) {
                for (size_t j = 0; j < m2; ++j) {
                    result[i][k] = rhs[i][j];
                    k++;
                }
            }
        }
    }

    catch (const std::bad_alloc& e) {
        cleanup(result, n);
        return nullptr;
    }
    
    return result;
}
