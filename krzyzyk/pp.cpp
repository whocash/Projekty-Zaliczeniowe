#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Klasa reprezentująca planszę do gry w kółko i krzyżyk
class TicTacToe {
public:
    enum class Player { NONE, X, O };
    std::vector<std::vector<Player>> board;

    TicTacToe() : board(3, std::vector<Player>(3, Player::NONE)) {}

    // Metoda do wyświetlania planszy
    void displayBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                char symbol = ' ';
                if (board[i][j] == Player::X) {
                    symbol = 'X';
                } else if (board[i][j] == Player::O) {
                    symbol = 'O';
                }
                std::cout << symbol;
                if (j < 2) std::cout << " | ";
            }
            std::cout << std::endl;
            if (i < 2) std::cout << "---------" << std::endl;
        }
        std::cout << std::endl;
    }

    
    bool makeMove(int row, int col, Player player) {
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == Player::NONE) {
            board[row][col] = player;
            return true;
        }
        return false;
    }

    
    bool isGameOver() {
       
        for (int i = 0; i < 3; i++) {
            if (board[i][0] != Player::NONE && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
                return true;
            }
            if (board[0][i] != Player::NONE && board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
                return true;
            }
        }
        if (board[0][0] != Player::NONE && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
            return true;
        }
        if (board[0][2] != Player::NONE && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
            return true;
        }

        // Sprawdzanie remisu
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == Player::NONE) {
                    return false; // Gra nadal trwa
                }
            }
        }

        return true; // Remis
    }
};

// Funkcja do wykonania ruchu komputera (losowy wybór wolnego miejsca)
void computerMove(TicTacToe& game, TicTacToe::Player computerPlayer) {
    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (game.board[i][j] == TicTacToe::Player::NONE) {
                emptyCells.push_back(std::make_pair(i, j));
            }
        }
    }

    if (!emptyCells.empty()) {
        int randomIndex = rand() % emptyCells.size();
        int row = emptyCells[randomIndex].first;
        int col = emptyCells[randomIndex].second;
        game.makeMove(row, col, computerPlayer);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inicjalizacja generatora liczb losowych

    TicTacToe game;
    TicTacToe::Player currentPlayer = TicTacToe::Player::X;

    while (true) {
        game.displayBoard();

        if (currentPlayer == TicTacToe::Player::X || currentPlayer == TicTacToe::Player::O) {
            std::cout << "Ruch gracza " << (currentPlayer == TicTacToe::Player::X ? 'X' : 'O') << std::endl;
            int row, col;
            std::cout << "Podaj wiersz (0-2): ";
            std::cin >> row;
            std::cout << "Podaj kolumnę (0-2): ";
            std::cin >> col;
            if (game.makeMove(row, col, currentPlayer)) {
                if (game.isGameOver()) {
                    game.displayBoard();
                    std::cout << "Koniec gry.\n";
                    break;
                }
                currentPlayer = (currentPlayer == TicTacToe::Player::X) ? TicTacToe::Player::O : TicTacToe::Player::X;
            } else {
                std::cout << "Nieprawidłowy ruch. Spróbuj jeszcze raz.\n";
            }
        }
        else { 
            std::cout << "Ruch komputera (gracz O)...\n";
            computerMove(game, TicTacToe::Player::O);
            if (game.isGameOver()) {
                game.displayBoard();
                std::cout << "Koniec gry.\n";
                break;
            }
            currentPlayer = TicTacToe::Player::X;
        }
    }

    return 0;
}
