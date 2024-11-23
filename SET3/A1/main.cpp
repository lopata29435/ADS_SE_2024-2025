#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <random>
#include <fstream>

struct Circle {
    double x, y, r;
};

bool isInIntersection(double px, double py, const Circle& c1, const Circle& c2, const Circle& c3) {
    double d1 = (px - c1.x) * (px - c1.x) + (py - c1.y) * (py - c1.y);
    double d2 = (px - c2.x) * (px - c2.x) + (py - c2.y) * (py - c2.y);
    double d3 = (px - c3.x) * (px - c3.x) + (py - c3.y) * (py - c3.y);
    return d1 <= c1.r * c1.r && d2 <= c2.r * c2.r && d3 <= c3.r * c3.r;
}

double monteCarlo(const Circle& c1, const Circle& c2, const Circle& c3, double x_min, double x_max, double y_min, double y_max, int N) {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> dist_x(x_min, x_max);
    std::uniform_real_distribution<double> dist_y(y_min, y_max);

    int countInside = 0;
    for (int i = 0; i < N; ++i) {
        double x = dist_x(rng);
        double y = dist_y(rng);
        if (isInIntersection(x, y, c1, c2, c3)) {
            countInside++;
        }
    }

    double rectangleArea = (x_max - x_min) * (y_max - y_min);
    return rectangleArea * countInside / N;
}

int main() {
    Circle c1 = {1.0, 1.0, 1.0};
    Circle c2 = {1.5, 2.0, std::sqrt(5) / 2};
    Circle c3 = {2.0, 1.5, std::sqrt(5) / 2};

    double x_min = std::min({c1.x - c1.r, c2.x - c2.r, c3.x - c3.r});
    double x_max = std::max({c1.x + c1.r, c2.x + c2.r, c3.x + c3.r});
    double y_min = std::min({c1.y - c1.r, c2.y - c2.r, c3.y - c3.r});
    double y_max = std::max({c1.y + c1.r, c2.y + c2.r, c3.y + c3.r});

    double exactArea = 0.25 * M_PI + 1.25 * asin(0.8) - 1;

    std::vector<double> scales = {1.0, 1.15, 1.30, 1.5, 2.0, 10.0};
    std::vector<int> N_values;
    for (int i = 100; i <= 100000; i += 500) {
        N_values.push_back(i);
    }
    
    std::ofstream file("results.csv");
    file << "Scale, N, Approximate Area, Relative Deviation\n";

    for (double scale : scales) {
        double x_min_scaled = x_min * scale;
        double x_max_scaled = x_max * scale;
        double y_min_scaled = y_min * scale;
        double y_max_scaled = y_max * scale;

        for (int N : N_values) {
            double approxArea = monteCarlo(c1, c2, c3, x_min_scaled, x_max_scaled, y_min_scaled, y_max_scaled, N);
            double relativeDeviation = std::abs(approxArea - exactArea) / exactArea;

            file << scale << ", " << N << ", " << approxArea << ", " << relativeDeviation << "\n";
        }
    }

    std::cout << "All results are saved!";
    file.close();

    return 0;
}
