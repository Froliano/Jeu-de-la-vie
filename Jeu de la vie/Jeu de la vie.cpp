#include <SFML/Graphics.hpp>
#include <iostream>

const int WIDTH = 300;
const int HEIGHT = 300;
const int ROWS = 3;
const int COLS = 3;

enum class Player { None, X, O };

class TicTacToe {
public:
    TicTacToe() : currentPlayer(Player::X), window(sf::VideoMode(WIDTH, HEIGHT), "Tic Tac Toe") {
        board = std::vector<std::vector<Player>>(ROWS, std::vector<Player>(COLS, Player::None));
    }

    void run() {
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                else if (event.type == sf::Event::MouseButtonPressed)
                    handleClick(event.mouseButton.x, event.mouseButton.y);
            }

            window.clear(sf::Color::White); // Efface la fenêtre avec une couleur blanche
            drawBoard();
            window.display(); // Affiche le contenu de la fenêtre
        }
    }

private:
    Player currentPlayer;
    std::vector<std::vector<Player>> board;
    sf::RenderWindow window;

    void drawBoard() {
        sf::RectangleShape line(sf::Vector2f(10, HEIGHT));
        line.setFillColor(sf::Color::Black);
        line.setPosition(WIDTH / 3 - 5, 0);
        window.draw(line);
        line.setPosition(2 * WIDTH / 3 - 5, 0);
        window.draw(line);
        line.setSize(sf::Vector2f(WIDTH, 10));
        line.setRotation(90);
        line.setPosition(0, HEIGHT / 3 - 5);
        window.draw(line);
        line.setPosition(0, 2 * HEIGHT / 3 - 5);
        window.draw(line);

        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == Player::X) {
                    drawX(i, j);
                }
                else if (board[i][j] == Player::O) {
                    drawO(i, j);
                }
            }
        }
    }

    void drawX(int row, int col) {
        sf::RectangleShape line1(sf::Vector2f(WIDTH / 3 - 20, 5));
        line1.setFillColor(sf::Color::Black);
        line1.rotate(45);
        line1.setPosition(col * WIDTH / 3 + 10, row * HEIGHT / 3 + 10);
        window.draw(line1);

        sf::RectangleShape line2(sf::Vector2f(WIDTH / 3 - 20, 5));
        line2.setFillColor(sf::Color::Black);
        line2.rotate(-45);
        line2.setPosition(col * WIDTH / 3 + 10, (row + 1) * HEIGHT / 3 - 10);
        window.draw(line2);
    }

    void drawO(int row, int col) {
        sf::CircleShape circle(WIDTH / 6 - 10);
        circle.setFillColor(sf::Color::Transparent);
        circle.setOutlineThickness(5);
        circle.setOutlineColor(sf::Color::Black);
        circle.setPosition(col * WIDTH / 3 + 10, row * HEIGHT / 3 + 10);
        window.draw(circle);
    }

    void handleClick(int x, int y) {
        int row = y / (HEIGHT / 3);
        int col = x / (WIDTH / 3);

        if (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] == Player::None) {
            board[row][col] = currentPlayer;
            if (checkWin(currentPlayer)) {
                std::cout << "Player " << (currentPlayer == Player::X ? 'X' : 'O') << " wins!" << std::endl;
                window.close();
            }
            else if (checkDraw()) {
                std::cout << "It's a draw!" << std::endl;
                window.close();
            }
            else {
                currentPlayer = (currentPlayer == Player::X) ? Player::O : Player::X;
            }
        }
    }

    bool checkWin(Player player) {
        // Check rows and columns
        for (int i = 0; i < ROWS; ++i) {
            if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
                return true;
            if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
                return true;
        }

        // Check diagonals
        if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
            return true;
        if (board[0][2] == player && board[1][1] == player && board[2][0] == player)
            return true;

        return false;
    }

    bool checkDraw() {
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                if (board[i][j] == Player::None)
                    return false;
            }
        }
        return true;
    }
};

int main() {
    TicTacToe game;
    game.run();

    return 0;
}
