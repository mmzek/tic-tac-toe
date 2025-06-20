
#ifndef ALGORITHM_H
#define ALGORITHM_H
#include "interface.h"
int minimax(std::vector<std::vector<Player>>& board, int depth, int SIZE, int WIN_CONDITION, Player currentPlayer, int alpha, int beta, int maxDepth);
std::pair<int, int> findBestMove(std::vector<std::vector<Player>>& board, int SIZE, int WIN_CONDITION, Player currentPlayer);
int heuristicEvaluation(const std::vector<std::vector<Player>>& board, int SIZE, int WIN_CONDITION) ;
#endif //ALGORITHM_H
