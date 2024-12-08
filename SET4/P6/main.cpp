#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iomanip>

using namespace std;

double min_dist = 3e9;
pair<int, int> closestPair;

struct Point {
    int x, y, z, idx;
};

double dist(const Point& p1, const Point& p2) {
    return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

bool compareX(const Point& p1, const Point& p2) {
    if (p1.x == p2.x) {
        if (p1.y == p2.y) {
            return p1.z < p2.z;
        }
        return p1.y < p2.y;
    }
    return p1.x < p2.x;
}

bool compareY(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}

void checkBorderPoints(vector<Point>& border) {
    for (size_t i = 0; i < border.size(); ++i) {
        int max_neighbour = 12;
        for (size_t j = i + 1; j < border.size() && border[j].y - border[i].y < min_dist; ++j) {
            if (border[j].z - border[i].z < min_dist) {
                --max_neighbour;
                double d = dist(border[i], border[j]);
                if (d < min_dist) {
                    min_dist = d;
                    closestPair = {border[i].idx, border[j].idx};
                }
                if (max_neighbour == 0) {
                    break;
                }
            }
        }
    }
}

void closest_pair(vector<Point>& points, int left, int right) {
    if (right - left <= 1) {
        return;
    }

    if (right - left == 2) {
        double d = dist(points[left], points[left + 1]);
        if (d < min_dist) {
            min_dist = d;
            closestPair = {points[left].idx, points[left + 1].idx};
        }
        return;
    }

    int mid = (left + right) / 2;
    closest_pair(points, left, mid);
    closest_pair(points, mid, right);

    int mid_x = points[mid].x;
    double min_x_dist = min_dist;

    auto left_border = lower_bound(points.begin() + left, points.begin() + right, mid_x - min_x_dist, [](const Point& p, int value) {
        return p.x < value;
    });

    auto right_border = upper_bound(points.begin() + left, points.begin() + right, mid_x + min_x_dist, [](int value, const Point& p) {
        return value < p.x;
    });

    vector<Point> border(left_border, right_border);
    sort(border.begin(), border.end(), compareY);

    checkBorderPoints(border);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int n;
    cin >> n;

    vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        cin >> points[i].x >> points[i].y >> points[i].z;
        points[i].idx = i + 1;
    }

    sort(points.begin(), points.end(), compareX);

    closest_pair(points, 0, n);

    cout << fixed << setprecision(5) << min_dist << endl;
    cout << closestPair.first << " " << closestPair.second << endl;

    return 0;
}