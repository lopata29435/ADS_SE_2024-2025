#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct Section {
    double time;
    int speed;
};

int main() {
int min_distance, num_sections;
    std::cin >> min_distance >> num_sections;

    std::vector<Section> train1_schedule(num_sections);
    std::vector<Section> train2_schedule(num_sections);

    for (int i = 0; i < num_sections; ++i) {
        std::cin >> train1_schedule[i].time >> train1_schedule[i].speed;
        train2_schedule[i] = train1_schedule[i];
    }

    double current_distance = 0.0;
    int train1_section = 0;
    int train2_section = 0;
    double total_time = 0.0;

    while (current_distance < min_distance && train1_section < num_sections) {
        current_distance += train1_schedule[train1_section].time * train1_schedule[train1_section].speed;
        total_time += train1_schedule[train1_section].time;
        ++train1_section;
    }

    if (train1_section == num_sections && current_distance <= min_distance) {
        std::cout << std::fixed << std::setprecision(3) << total_time << '\n';
        return 0;
    }

    if (current_distance != min_distance) {
        --train1_section;
        double excess_distance = current_distance - min_distance;
        double adjusted_time = excess_distance / train1_schedule[train1_section].speed;
        total_time -= adjusted_time;
        train1_schedule[train1_section].time = adjusted_time;
        current_distance = min_distance;
    }

    while (train1_section < num_sections) {
        if (train1_schedule[train1_section].time <= train2_schedule[train2_section].time) {
            train2_schedule[train2_section].time -= train1_schedule[train1_section].time;
            current_distance += train1_schedule[train1_section].time * (train1_schedule[train1_section].speed - train2_schedule[train2_section].speed);

            if (current_distance < min_distance) {
                double delay_time = (min_distance - current_distance) / train2_schedule[train2_section].speed;
                total_time += delay_time;
                train2_schedule[train2_section].time += delay_time;
                current_distance = min_distance;
            }

            ++train1_section;
        } else {
            train1_schedule[train1_section].time -= train2_schedule[train2_section].time;
            current_distance += train2_schedule[train2_section].time * (train1_schedule[train1_section].speed - train2_schedule[train2_section].speed);

            if (current_distance < min_distance) {
                if (train1_schedule[train1_section].time < (min_distance - current_distance) / train1_schedule[train1_section].speed) {
                    current_distance += train1_schedule[train1_section].time * train1_schedule[train1_section].speed;
                    total_time += train1_schedule[train1_section].time;
                    train2_schedule[train2_section].time = (min_distance - current_distance) / train2_schedule[train2_section].speed;
                    total_time += train2_schedule[train2_section].time;
                    ++train1_section;
                } else {
                    total_time += (min_distance - current_distance) / train1_schedule[train1_section].speed;
                    train1_schedule[train1_section].time -= (min_distance - current_distance) / train1_schedule[train1_section].speed;
                    ++train2_section;
                }
                current_distance = min_distance;
            } else {
                ++train2_section;
            }
        }
    }

    std::cout << std::fixed << std::setprecision(3) << total_time << '\n';
    return 0;
    
    return 0;
}