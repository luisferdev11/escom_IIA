#include <iostream>
#include <vector>
#include <string>

int main() {
    int size;
    std::cin >> size;

    std::vector<std::string> board(size);
    for (int i = 0; i < size; i++) {
        std::cin >> board[i];
    }

    int maxTiles = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < board[i].size() - 1; j++) {
            if (board[i][j] == 'N' && board[i][j + 1] == 'N') {
                maxTiles++;
                j++;
            }
        }
    }

    std::cout << maxTiles << std::endl;

    return 0;
}

