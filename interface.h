//
// Created by maja on 20.06.25.
//

#ifndef INTERFACE_H
#define INTERFACE_H
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

extern sf::Color purple;
extern sf::Color pink;
extern sf::Color blue;

enum class Player { None, X, O };

std::string playerToStr(Player p);
bool checkWin(const std::vector<std::vector<Player>>& board, Player player, int SIZE, int WIN_CONDITION );
bool isFull(const std::vector<std::vector<Player>>& board);
void game(int SIZE, int WIN_CONDITION);
#endif //INTERFACE_H
