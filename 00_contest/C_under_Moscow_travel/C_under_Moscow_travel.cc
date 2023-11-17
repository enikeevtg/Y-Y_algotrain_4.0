#include <cmath>
#include <iostream>

class Point {
 public:
  Point() {}
  Point(int x, int y) : x_(x), y_(y), r_(std::sqrt(x_ * x_ + y_ * y_)) {
    if (r_ != 0) fi_ = std::asin(std::fabs((double)y_) / r_);
    if (y_ >= 0 && x_ < 0) {
      fi_ = M_PI - fi_;
    } else if (y_ < 0 && x_ >= 0) {
      fi_ = 2 * M_PI - fi_;
    } else if (y_ < 0 && x_ < 0) {
      fi_ = M_PI + fi_;
    }
  }
  ~Point() {}

  long double get_r() const { return r_; }
  double get_fi() const { return fi_; }

  double NormalDistance(const Point& other) const {
    return std::fabs(r_ - other.r_);
  }

  double TangentialDistance(const Point& other) const {
    double delta_fi = std::fabs(other.fi_ - fi_);
    if (delta_fi > M_PI) delta_fi = 2 * M_PI - delta_fi;
    double r_min = r_;
    if (r_min > other.r_) r_min = other.r_;
    double distance = delta_fi * r_min;
    return distance;
  }

 private:
  long int x_{0};
  long int y_{0};
  double r_{0};
  double fi_{0};
};

int main() {
  int x_a, y_a, x_b, y_b;
  std::cin >> x_a >> y_a >> x_b >> y_b;

  Point A{x_a, y_a};
  Point B{x_b, y_b};

  if (A.get_r() == 0 || B.get_r() == 0) {
    std::cout << std::fixed << A.NormalDistance(B) << std::endl;
  } else {
    double radial_path = A.get_r() + B.get_r();
    double mixed_path = A.NormalDistance(B) + A.TangentialDistance(B);
    if (radial_path > mixed_path) {
      std::cout << std::fixed << mixed_path << std::endl;
    } else {
      std::cout << std::fixed << radial_path << std::endl;
    }
  }

  return 0;
}
