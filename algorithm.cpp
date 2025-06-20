#include "algorithm.h"
#include "interface.h"
#include <vector>#include <vector>
#include <algorithm>

int heuristicEvaluation(const std::vector<std::vector<Player>>& board, int SIZE, int WIN_CONDITION) {

}

int minimax(std::vector<std::vector<Player>>& board, int depth, int SIZE, int WIN_CONDITION,
            Player currentPlayer, int alpha, int beta, int maxDepth) {

    if (checkWin(board, Player::X, SIZE, WIN_CONDITION))
        return 10 - depth;
    if (checkWin(board, Player::O, SIZE, WIN_CONDITION))
        return depth - 10;
    if (SIZE>3) {
        if (SIZE==WIN_CONDITION) {

        }
    }
    if (isFull(board) || depth == maxDepth)
        return heuristicEvaluation(board, SIZE, WIN_CONDITION);

    if (currentPlayer == Player::X) {
        int maxEval = -10000;
        Player nextPlayer = Player::O;

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == Player::None) {
                    board[i][j] = currentPlayer;
                    int eval = minimax(board, depth + 1, SIZE, WIN_CONDITION, nextPlayer, alpha, beta, maxDepth);
                    board[i][j] = Player::None;
                    maxEval = std::max(maxEval, eval);
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha)
                        return maxEval;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = 10000;
        Player nextPlayer = Player::X;

        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (board[i][j] == Player::None) {
                    board[i][j] = currentPlayer;
                    int eval = minimax(board, depth + 1, SIZE, WIN_CONDITION, nextPlayer, alpha, beta, maxDepth);
                    board[i][j] = Player::None;
                    minEval = std::min(minEval, eval);
                    beta = std::min(beta, eval);
                    if (beta <= alpha)
                        return minEval;
                }
            }
        }
        return minEval;
    }
}

std::pair<int, int> findBestMove(std::vector<std::vector<Player>>& board, int SIZE, int WIN_CONDITION, Player currentPlayer) {
    int bestVal = -10000;
    int bestRow = -1, bestCol = -1;
    int maxDepth = 3;

    Player nextPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == Player::None) {
                board[i][j] = currentPlayer;
                int moveVal = minimax(board, 0, SIZE, WIN_CONDITION, nextPlayer, -10000, 10000, maxDepth);
                board[i][j] = Player::None;

                if (moveVal > bestVal) {
                    bestVal = moveVal;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
    }

    return {bestRow, bestCol};
}
