#include <vector>
#include <utility>
#include <limits>
#include "interface.h"
#include "algorithm.h"

int minimax(std::vector<std::vector<Player>>& board, Player currentPlayer, int SIZE, int WIN_CONDITION) {
    if (checkWin(board, Player::X, SIZE, WIN_CONDITION))
        return +10;
    if (checkWin(board, Player::O, SIZE, WIN_CONDITION))
        return -10;
    if (isFull(board))
        return 0;

    if (currentPlayer == Player::X) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == Player::None) {
                    board[i][j] = Player::X;
                    int value = minimax(board, Player::O, SIZE, WIN_CONDITION);
                    board[i][j] = Player::None;
                    best = std::max(best, value);
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == Player::None) {
                    board[i][j] = Player::O;
                    int value = minimax(board, Player::X, SIZE, WIN_CONDITION);
                    board[i][j] = Player::None;
                    best = std::min(best, value);
                }
            }
        }
        return best;
    }
}

std::pair<int, int> findBestMove(std::vector<std::vector<Player>>& board, int SIZE, int WIN_CONDITION, Player currentPlayer) {
    int bestValue = (currentPlayer == Player::X) ? std::numeric_limits<int>::min()
                                                 : std::numeric_limits<int>::max();
    int bestRow = -1, bestCol = -1;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == Player::None) {
                board[i][j] = currentPlayer;
                int moveValue = minimax(board,
                                        (currentPlayer == Player::X ? Player::O : Player::X),
                                        SIZE, WIN_CONDITION);
                board[i][j] = Player::None;

                if ((currentPlayer == Player::X && moveValue > bestValue) ||
                    (currentPlayer == Player::O && moveValue < bestValue)) {
                    bestValue = moveValue;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    return {bestRow, bestCol};
}
