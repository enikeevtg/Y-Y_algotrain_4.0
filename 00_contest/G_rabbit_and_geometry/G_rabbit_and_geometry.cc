#include <iostream>

const int carrot = 1;

class CarrotField {
 public:
  CarrotField() {}
  CarrotField(int rows, int cols) : rows_(rows), cols_(cols) {
    array_2D_ = new int*[rows];
    for (int i = 0; i < rows_; ++i) {
      array_2D_[i] = new int[cols_];
    }
  }
  ~CarrotField() {
    for (int i = 0; i < rows_; ++i) {
      delete[] array_2D_[i];
    }
    delete array_2D_;
  }

  void Fill() {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        std::cin >> array_2D_[i][j];
      }
    }
  }

  void Print() {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        std::cout << array_2D_[i][j] << ' ';
      }
      std::cout << std::endl;
    }
  }

  int FindMaxFilledSquare() {
    int max_square_size = 0;
    CarrotField square_sizes{rows_, cols_};
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        if (i == 0 || j == 0) {
          square_sizes.array_2D_[i][j] = array_2D_[i][j];
          continue;
        }

        if (array_2D_[i][j] == carrot) {
          int min = square_sizes.array_2D_[i - 1][j - 1];
          if (square_sizes.array_2D_[i - 1][j] < min) {
            min = square_sizes.array_2D_[i - 1][j];
          }
          if (square_sizes.array_2D_[i][j - 1] < min) {
            min = square_sizes.array_2D_[i][j - 1];
          }

          square_sizes.array_2D_[i][j] = min + 1;
          if (max_square_size < square_sizes.array_2D_[i][j]) {
            max_square_size = square_sizes.array_2D_[i][j];
          }
        }
      }
    }
    return max_square_size;
  }

 private:
  int rows_{0};
  int cols_{0};
  int** array_2D_{nullptr};
};

int main() {
  int rows = 0;
  int cols = 0;
  std::cin >> rows >> cols;
  CarrotField field{rows, cols};
  field.Fill();
  std::cout << field.FindMaxFilledSquare();
  return 0;
}
