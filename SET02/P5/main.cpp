#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>

using namespace std;

struct Point {
    int64_t x, y;
};

double dist(const Point& p1, const Point& p2) {
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

bool compareX(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

double stripClosest(vector<Point>& strip, double d) {
    double minDist = d;
    
    sort(strip.begin(), strip.end(), compareY);

    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            double distance = dist(strip[i], strip[j]);
            if (distance < minDist) {
                minDist = distance;
            }
        }
    }
    return minDist;
}

double closestUtil(vector<Point>& pointsSortedByX, int64_t left, int64_t right) {
    if (right - left <= 3) {
        double minDist = 3e9;
        for (int64_t i = left; i < right; ++i) {
            for (int64_t j = i + 1; j <= right; ++j) {
                double distance = dist(pointsSortedByX[i], pointsSortedByX[j]);
                if (distance < minDist) {
                    minDist = distance;
                }
            }
        }
        return minDist;
    }

    int64_t mid = left + (right - left) / 2;
    Point midPoint = pointsSortedByX[mid];

    double dl = closestUtil(pointsSortedByX, left, mid);
    double dr = closestUtil(pointsSortedByX, mid + 1, right);

    double d = min(dl, dr);

    vector<Point> strip;
    for (int64_t i = left; i <= right; i++) {
        if (abs(pointsSortedByX[i].x - midPoint.x) < d) {
            strip.push_back(pointsSortedByX[i]);
        }
    }

    return min(d, stripClosest(strip, d));
}

double closestPair(vector<Point>& points) {
    sort(points.begin(), points.end(), compareX);
    return closestUtil(points, 0, points.size() - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int64_t x, y;
    vector<Point> a;
    while(cin >> x >> y) {
        a.push_back({x,y});
    }

    cout << static_cast<int64_t>(closestPair(a));
    return 0;
}