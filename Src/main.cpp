// main.cpp
// Aswin van Woudenberg

#include <iostream>
#include <string>
#include <regex>

#include "game.h"
#include "ansi.h"

void help();
void setOptions(Game &game);

int main()
{
    Game game;
    std::cout << Color(ColorValue::GREEN) << "Welcome to HEX!" << Color() << std::endl << std::endl;
   
    std::cout << game << std::endl;

    bool halt = false;
    while (!halt) {
        if (game.getPlayerType(game.getCurrentPlayer()) == PlayerType::HUMAN || game.isGameOver()) {
            std::cout << "Enter a move or command (h for help): ";
            std::string input;
            std::getline(std::cin, input);
            if (std::regex_match(input, std::regex("[A-Za-z]+[[:digit:]]+"))) {
                Move m;
                std::stringstream ss(input);
                ss >> m;
                try {
                    game.doMove(m);
                    std::cout << game << std::endl;
                } catch (const char *e) {
                    std::cerr << Color(ColorValue::RED) << e << Color() << std::endl;
                }
            } else if (std::regex_match(input, std::regex("[hopnuqHOPNUQ]"))) {
                char c;
                std::stringstream ss(input);
                ss >> c;
                switch (c) {
                    case 'h': case 'H':
                        help(); break;
                    case 'o': case 'O':
                        setOptions(game); break;
                    case 'p': case 'P':
                        try {
                            game.applyPieRule(); break;
                        } catch (const char *e) {
                            std::cerr << Color(ColorValue::RED) << e << Color() << std::endl;
                        }
                        break; 
                    case 'n': case 'N':
                        game.newGame(); 
                        std::cout << game << std::endl;
                        break;
                    case 'u': case 'U':
                        if (game.canUndo()) {
                            game.undoMove();
                            if (game.getPlayerType(game.getCurrentPlayer()) == PlayerType::COMPUTER)
                                game.undoMove();
                            std::cout << game << std::endl;
                        } else
                            std::cerr << Color(ColorValue::RED) << "There are no moves to undo!" << Color() << std::endl;
                        break;
                    case 'q': case 'Q':
                        halt = true; break;
                    default:
                        std::cerr << Color(ColorValue::RED) << "Invalid command!" << Color() << std::endl;
                }             
            } else {
                std::cerr << Color(ColorValue::RED) << "Invalid command!" << Color() << std::endl;
            }
        } else if (game.getPlayerType(game.getCurrentPlayer()) == PlayerType::COMPUTER && !game.isGameOver()) {
            game.doComputerMove();
            std::cout << game << std::endl;
        }
    }
    std::cout << Color(ColorValue::GREEN) << "Bye." << Color() << std::endl;
 
    return 0;
}

void help()
{
    std::cout << Color(ColorValue::GREEN) << "Help:" << Color() << std::endl << std::endl
              << Color(ColorValue::DEFAULT, ColorWeight::BOLD) << "  Commands" << Color() << std::endl
              << "   h   print this help menu" << std::endl
              << "   o   set options" << std::endl
              << "   p   apply the pie rule" << std::endl
              << "   n   start a new game" << std::endl
              << "   u   undo a move" << std::endl
              << "   q   quit HEX" << std::endl << std::endl
              << "Or enter a move such as " 
              << Color(ColorValue::DEFAULT, ColorWeight::BOLD) 
              << "F5" << Color() 
              << " to place a token in column F row 5." << std::endl << std::endl; 
}

void setOptions(Game &game)
{
    std::string input;
    int size = game.getSize();
    Player firstPlayer = game.getFirstPlayer();

    std::cout << "What size (1-40) do you want the board to be? [" << size << "]: ";
    std::getline(std::cin, input);
    if (std::regex_match(input, std::regex("[[:digit:]]+"))) {
        size = std::stoi(input);
        if (size < 1 || size > 40)
            size = game.getSize();
    }
    std::cout << "Who should go first? Red or blue? [" 
              << (game.getFirstPlayer() == Player::RED ? "Rb" : "rB") << "]: ";
    std::getline(std::cin, input);
    if (std::regex_match(input, std::regex("[Rr]")))
        firstPlayer = Player::RED;
    else if (std::regex_match(input, std::regex("[Bb]")))
        firstPlayer = Player::BLUE;

    std::cout << "Is red a human or the computer? ["
              << (game.getPlayerType(Player::RED) == PlayerType::HUMAN ? "Hc" : "hC") << "]: ";
    std::getline(std::cin, input);
    if (std::regex_match(input, std::regex("[Hh]")))
        game.setPlayerType(Player::RED, PlayerType::HUMAN);
    else if (std::regex_match(input, std::regex("[Cc]")))
        game.setPlayerType(Player::RED, PlayerType::COMPUTER);

    std::cout << "Is blue a human or the computer? ["
              << (game.getPlayerType(Player::BLUE) == PlayerType::HUMAN ? "Hc" : "hC") << "]: ";
    std::getline(std::cin, input);
    if (std::regex_match(input, std::regex("[Hh]")))
        game.setPlayerType(Player::BLUE, PlayerType::HUMAN);
    else if (std::regex_match(input, std::regex("[Cc]")))
        game.setPlayerType(Player::BLUE, PlayerType::COMPUTER);

    std::cout << "Is the pie rule allowed? ["
              << (game.isPieRuleAllowed() ? "Yn" : "yN") << "]: ";
    std::getline(std::cin, input);
    if (std::regex_match(input, std::regex("[Yy]")))
        game.setPieRuleAllowed(true);
    else if (std::regex_match(input, std::regex("[Nn]")))
        game.setPieRuleAllowed(false);

    if (game.getPlayerType(Player::RED) == PlayerType::COMPUTER ||
        game.getPlayerType(Player::BLUE) == PlayerType::COMPUTER) {
        int plies = game.getPlies();
        std::cout << "How many plies (1-30) should the computer think ahead? [" << plies << "]: ";
        std::getline(std::cin, input);
        if (std::regex_match(input, std::regex("[[:digit:]]+"))) {
            plies = std::stoi(input);
            if (plies < 1 || plies > 30)
                plies = game.getPlies();
            game.setPlies(plies);
        }

        int trials = game.getTrials();
        std::cout << "How many Monte Carlo trials (1-10000) are to be done during each evaluation? [" << trials << "]: ";
        std::getline(std::cin, input);
        if (std::regex_match(input, std::regex("[[:digit:]]+"))) {
            trials = std::stoi(input);
            if (trials < 1 || trials > 10000)
                trials = game.getTrials();
            game.setTrials(trials);
        }
    }

    if (size != game.getSize() || firstPlayer != game.getFirstPlayer()) {
        game.newGame(size, firstPlayer);
    }
    std::cout << game << std::endl;
}

