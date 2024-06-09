#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int throws, W, L, Tx, Ty;
    std::cin >> throws;
    std::cin >> W >> L >> Tx >> Ty;


    // "A" will be team A's throws and "R" will be team R's throws, first A will have all their throws, then R will have all their throws, the throws are coordinates
    std::vector<std::pair<int, int>> A(throws), R(throws);
    for (int i = 0; i < throws; i++) {
        std::cin >> A[i].first >> A[i].second;
    }
    for (int i = 0; i < throws; i++) {
        std::cin >> R[i].first >> R[i].second;
    }

    // print throws
    // for (int i = 0; i < throws; i++) {
    //     std::cout << A[i].first << " " << A[i].second << std::endl;
    // }
    


    std::vector<double> distanceA(throws);
    for (int i = 0; i < throws; i++) {
        distanceA[i] = sqrt(pow(A[i].first - Tx, 2) + pow(A[i].second - Ty, 2));
    }

    std::vector<double> distanceR(throws);
    for (int i = 0; i < throws; i++) {
        distanceR[i] = sqrt(pow(R[i].first - Tx, 2) + pow(R[i].second - Ty, 2));
    }


    // find closest distance to target
    double closestDistanceA = distanceA[0];
    for (int i = 1; i < throws; i++) {
        if (distanceA[i] < closestDistanceA) {
            closestDistanceA = distanceA[i];
        }
    }

    double closestDistanceR = distanceR[0];
    for (int i = 1; i < throws; i++) {
        if (distanceR[i] < closestDistanceR) {
            closestDistanceR = distanceR[i];
        }
    }


    int points = 0;
    if (closestDistanceA < closestDistanceR) {
        for (int i = 0; i < throws; i++) {
            if (distanceA[i] < closestDistanceR) {
                points++;
            }
        }
        std::cout << "A " << points << std::endl;
    } else {
        for (int i = 0; i < throws; i++) {
            if (distanceR[i] < closestDistanceA) {
                points++;
            }
        }
        std::cout << "R " << points << std::endl;
    }
    
}