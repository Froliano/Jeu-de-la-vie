#include <SFML/Graphics.hpp>
#include <iostream>

const int SQUARE_SIZE = 100;
const int WIDTH = 700;
const int HEIGHT = 400;


class Game
{
    private:
        std::vector<std::vector<bool>> board;
        sf::RenderWindow window;

        void drawBoard() {
            for (int x = 0; x < WIDTH/SQUARE_SIZE; ++x)
            {
                for (int y = 0; y < HEIGHT/SQUARE_SIZE; ++y)
                {
                    if (board[x][y]) {
                        fillBlack(x, y);
                    }
                    else
                    {
                        fillWhite(x, y);
                    }
                }
            }

            sf::RectangleShape line(sf::Vector2f(1, HEIGHT));
            line.setFillColor(sf::Color(70, 70, 70));
            for (int i = 0; i <= WIDTH; i += SQUARE_SIZE)
            {
                line.setPosition(i, 0);
                window.draw(line);
            }

            line.setSize(sf::Vector2f(WIDTH, 1));
            for (int i = 0; i <= HEIGHT; i += SQUARE_SIZE)
            {
                line.setPosition(0, i);
                window.draw(line);
            }

        }

        void fillWhite(int x, int y)
        {
            sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            rect.setFillColor(sf::Color::White);
            rect.setPosition(x*SQUARE_SIZE, y*SQUARE_SIZE);
            window.draw(rect);
        }
        
        void fillBlack(int x, int y)
        {
            sf::RectangleShape rect(sf::Vector2f(SQUARE_SIZE, SQUARE_SIZE));
            rect.setFillColor(sf::Color::Black);
            rect.setPosition(x * SQUARE_SIZE, y * SQUARE_SIZE);
            window.draw(rect);
        }

        void nextGeneration()
        {
            std::vector<std::vector<bool>> newBoard = std::vector<std::vector<bool>>(WIDTH / SQUARE_SIZE, std::vector<bool>(HEIGHT / SQUARE_SIZE, false));

            for (int x = 0; x < WIDTH / SQUARE_SIZE; ++x)
            {
                for (int y = 0; y < HEIGHT / SQUARE_SIZE; ++y)
                {
                    int nbCellulesAliveNear = 0;

                    for (int i = std::max(0, x - 1); i < std::min(WIDTH / SQUARE_SIZE, x + 2); i++)
                    {
                        for (int j = std::max(0, y - 1); j < std::min(HEIGHT / SQUARE_SIZE, y + 2); j++)
                        {
                            if (board[i][j] and (i != x or j != y))
                            {
                                nbCellulesAliveNear++;
                            }
                        }
                    }

                    if (board[x][y])
                    {
                        if (nbCellulesAliveNear == 2 or nbCellulesAliveNear == 3)
                        {
                            newBoard[x][y] = true;
                        }
                    }

                    else
                    {
                        if (nbCellulesAliveNear == 3)
                        {
                            newBoard[x][y] = true;
                        }
                    }
                }
            }
            board = newBoard;
        }

    public:
        Game() : window(sf::VideoMode(WIDTH+1, HEIGHT+1), "Le Jeu de la Vie") {
            board = std::vector<std::vector<bool>>(WIDTH/SQUARE_SIZE, std::vector<bool>(HEIGHT/SQUARE_SIZE, false));
            board[2][1] = true;
            board[2][2] = true;
            board[2][3] = true;
        }

        void run()
        {
            while (window.isOpen())
            {
                sf::Event event;
                while(window.pollEvent(event)) 
                {
                    if(event.type == sf::Event::Closed)
                        window.close();
                    else if (event.type == sf::Event::KeyPressed)
                    {
                        if (event.key.code == sf::Keyboard::Enter)
                        {
                            nextGeneration();
                        }
                    }
                    /*else if (event.type == sf::Event::MouseButtonPressed)
                        handleClick(event.mouseButton.x, event.mouseButton.y);*/
                }

                window.clear(sf::Color::White);
                drawBoard();
                window.display();
            }
        }
};

int main() {

    Game game;

    game.run();

    return 0;
}