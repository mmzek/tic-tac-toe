#include "interface.h"
#include "algorithm.h"

#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


sf::Color purple(178, 102, 255);
sf::Color pink(255, 102, 255);
sf::Color blue(204, 229, 255);

int CELL = 200;

std::string playerToStr(Player p) {
    if (p == Player::X) return "Cross";
    if (p == Player::O) return "Circle";
    return " ";
}


int countEmptyCells(const std::vector<std::vector<Player> > &board, int SIZE) {
    int count = 0;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j)
            if (board[i][j] == Player::None)
                ++count;
    return count;
}

std::vector<std::pair<int, int> > getEmptyCells(const std::vector<std::vector<Player> > &board, int SIZE) {
    std::vector<std::pair<int, int> > emptyCells;
    for (int i = 0; i < SIZE; ++i)
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == Player::None) {
                emptyCells.emplace_back(i, j);
            }
        }
    return emptyCells;
}

bool checkWin(const std::vector<std::vector<Player> > &board, Player player, int SIZE, int WIN_CONDITION) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE - WIN_CONDITION; j++) {
            if (WIN_CONDITION == 3) {
                if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player)
                    return true;
                if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player)
                    return true;
            }
            if (WIN_CONDITION == 4) {
                if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3]
                    == player)
                    return true;
                if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player && board[j + 3][i]
                    == player)
                    return true;
            }
            if (WIN_CONDITION == 5) {
                if (board[i][j] == player && board[i][j + 1] == player && board[i][j + 2] == player && board[i][j + 3]
                    == player && board[i][j + 4] == player)
                    return true;
                if (board[j][i] == player && board[j + 1][i] == player && board[j + 2][i] == player && board[j + 3][i]
                    == player && board[j + 4][i] == player)
                    return true;
            }
        }
    }
    for (int i = 0; i <= SIZE - WIN_CONDITION; i++) {
        for (int j = 0; j <= SIZE - WIN_CONDITION; j++) {
            if (WIN_CONDITION == 3) {
                if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player)
                    return true;
                if (board[i][j + 2] == player && board[i + 1][j + 1] == player && board[i + 2][j] == player)
                    return true;
            }
        }
        for (int j = 0; j <= SIZE - WIN_CONDITION; j++) {
            if (WIN_CONDITION == 4) {
                if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[
                        i + 3][j + 3] == player)
                    return true;
                if (board[i][j + 3] == player && board[i + 1][j + 2] == player && board[i + 2][j + 1] == player && board
                    [i + 3][j] == player)
                    return true;
            }
        }
        for (int j = 0; j <= SIZE - WIN_CONDITION; j++) {
            if (WIN_CONDITION == 5) {
                if (board[i][j] == player && board[i + 1][j + 1] == player && board[i + 2][j + 2] == player && board[
                        i + 3][j + 3] == player && board[i + 4][j + 4] == player)
                    return true;
                if (board[i][j + 4] == player && board[i + 1][j + 3] == player && board[i + 2][j + 2] == player && board
                    [i + 3][j + 1] == player && board[i + 4][j] == player)
                    return true;
            }
        }
    }
    countEmptyCells(board, SIZE);
    getEmptyCells(board, SIZE);
    return false;
}

bool isFull(const std::vector<std::vector<Player> > &board) {
    for (const auto &row: board)
        for (auto cell: row)
            if (cell == Player::None) return false;
    return true;
}void game(int SIZE, int WIN_CONDITION) {
    sf::RenderWindow window(sf::VideoMode(SIZE * CELL, SIZE * CELL), "Tic Tac Toe");
    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        std::cerr << "Font not found\n";
    }

    std::string tryAgainText = "Click to try again";
    std::vector<std::vector<Player>> board(SIZE, std::vector<Player>(SIZE, Player::None));
    Player currentPlayer = Player::X;
    bool gameOver = false;
    std::string resultText = "";

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int mx = event.mouseButton.x;
                int my = event.mouseButton.y;

                if (!gameOver && currentPlayer == Player::X) {
                    int x = mx / CELL;
                    int y = my / CELL;

                    if (x >= 0 && x < SIZE && y >= 0 && y < SIZE && board[y][x] == Player::None) {
                        board[y][x] = currentPlayer;
                        if (checkWin(board, currentPlayer, SIZE, WIN_CONDITION)) {
                            gameOver = true;
                            resultText = playerToStr(currentPlayer) + " wins!";
                        } else if (isFull(board)) {
                            gameOver = true;
                            resultText = "Tie!";
                        } else {
                            currentPlayer = Player::O;
                        }
                    }
                } else if (gameOver) {
                    sf::FloatRect buttonArea(50, SIZE * CELL / 3 - 50, SIZE * CELL - 100, CELL + 100);
                    if (buttonArea.contains(mx, my)) {
                        board = std::vector<std::vector<Player>>(SIZE, std::vector<Player>(SIZE, Player::None));
                        currentPlayer = Player::X;
                        gameOver = false;
                        resultText = "";
                    }
                }
            }
        }

        // RYSOWANIE PLANSZY
        window.clear(blue);

        for (int i = 1; i < SIZE + 1; ++i) {
            sf::RectangleShape lineH(sf::Vector2f(CELL * SIZE, 10));
            lineH.setPosition(0, i * CELL);
            lineH.setFillColor(sf::Color::White);
            window.draw(lineH);

            sf::RectangleShape lineV(sf::Vector2f(10, CELL * SIZE));
            lineV.setPosition(i * CELL, 0);
            lineV.setFillColor(sf::Color::White);
            window.draw(lineV);
        }

        for (int y = 0; y < SIZE; ++y) {
            for (int x = 0; x < SIZE; ++x) {
                if (board[y][x] == Player::O) {
                    sf::CircleShape circle(CELL / 2 - 30);
                    circle.setPosition(x * CELL + 30, y * CELL + 30);
                    circle.setFillColor(sf::Color::Transparent);
                    circle.setOutlineColor(pink);
                    circle.setOutlineThickness(10);
                    window.draw(circle);
                } else if (board[y][x] == Player::X) {
                    sf::RectangleShape line1(sf::Vector2f(CELL, 10));
                    line1.setRotation(45);
                    line1.setPosition(x * CELL + (CELL - CELL / 1.4) / 2, y * CELL + (CELL - CELL / 1.4) / 2);
                    line1.setFillColor(purple);
                    window.draw(line1);

                    sf::RectangleShape line2(sf::Vector2f(CELL, 10));
                    line2.setPosition(x * CELL + (CELL - CELL / 1.4) / 2, (y + 1) * CELL - (CELL - CELL / 1.4) / 2);
                    line2.setRotation(-45);
                    line2.setFillColor(purple);
                    window.draw(line2);
                }
            }
        }

        if (gameOver) {
            sf::RectangleShape button(sf::Vector2f(SIZE * CELL - 100, CELL + 100));
            button.setPosition(50, SIZE * CELL / 3 - 50);
            button.setFillColor(sf::Color::White);
            window.draw(button);

            sf::Text result(resultText, font, 60);
            if (resultText == "Cross wins!") {
                result.setFillColor(purple);
                result.setPosition(SIZE * CELL / 2 - 200, SIZE * CELL / 3 + 50);
            } else if (resultText == "Circle wins!") {
                result.setFillColor(pink);
                result.setPosition(SIZE * CELL / 2 - 200, SIZE * CELL / 3 + 50);
            } else {
                result.setFillColor(sf::Color::Black);
                result.setPosition(SIZE * CELL / 2 - 50, SIZE * CELL / 3 + 50);
            }
            window.draw(result);

            sf::Text tryAgain(tryAgainText, font, 30);
            tryAgain.setFillColor(blue);
            tryAgain.setPosition(SIZE * CELL / 2 - 150, SIZE * CELL / 3 + 150);
            window.draw(tryAgain);
        }
        window.display();
        if  (currentPlayer == Player::O && !gameOver) {
            auto [bestRow, bestCol] = findBestMove(board, SIZE, WIN_CONDITION, currentPlayer);
            if (bestRow != -1 && bestCol != -1) {
                sf::sleep(sf::milliseconds(500));
                board[bestRow][bestCol] = currentPlayer;
                if (checkWin(board, currentPlayer, SIZE, WIN_CONDITION)) {
                    gameOver = true;
                    resultText = playerToStr(currentPlayer) + " wins!";
                } else if (isFull(board)) {
                    gameOver = true;
                    resultText = "Tie!";
                } else {
                    currentPlayer = Player::X;
                }
            }
        }
    }

}
