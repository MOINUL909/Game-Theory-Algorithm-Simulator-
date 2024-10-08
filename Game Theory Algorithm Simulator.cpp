#include <bits/stdc++.h>
/*
UserId=Moinul
Password=Moinul909
*/
const std::string USER_ID = "Moinul";
const std::string PASSWORD = "Moinul909";

// Function to log in
bool login() {
    std::string userId, password;
    std::cout << "Enter User ID: ";
    std::cin >> userId;
    std::cout << "Enter Password: ";
    std::cin >> password;
    return (userId == USER_ID && password == PASSWORD);
}

// Display the game board
void displayBoard(const std::vector<std::vector<char>>& board) {
    std::cout << "\nCurrent Board:\n";
    for (const auto& row : board) {
        for (const auto& cell : row) {
            std::cout << cell << " ";
        }
        std::cout << "\n";
    }
    std::cout << std::endl;
}

// Check for a winner
char checkWinner(const std::vector<std::vector<char>>& board) {
    // Check rows, columns, and diagonals
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '_')
            return board[i][0];
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '_')
            return board[0][i];
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_')
        return board[0][2];

    return '_';
}

// Check if there are moves left
bool movesLeft(const std::vector<std::vector<char>>& board) {
    for (const auto& row : board) {
        for (const auto& cell : row) {
            if (cell == '_') return true;
        }
    }
    return false;
}

// Minimax algorithm
int minimax(std::vector<std::vector<char>>& board, int depth, bool isMaximizing, char player, char opponent) {
    char winner = checkWinner(board);
    if (winner == player) return 10 - depth;
    if (winner == opponent) return depth - 10;
    if (!movesLeft(board)) return 0;

    if (isMaximizing) {
        int bestScore = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '_') {
                    board[i][j] = player;
                    bestScore = std::max(bestScore, minimax(board, depth + 1, false, player, opponent));
                    board[i][j] = '_';
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == '_') {
                    board[i][j] = opponent;
                    bestScore = std::min(bestScore, minimax(board, depth + 1, true, player, opponent));
                    board[i][j] = '_';
                }
            }
        }
        return bestScore;
    }
}

// Find the best move for the computer using Minimax
std::pair<int, int> findBestMove(std::vector<std::vector<char>>& board, char player, char opponent) {
    int bestScore = std::numeric_limits<int>::min();
    std::pair<int, int> bestMove = {-1, -1};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == '_') {
                board[i][j] = player;
                int moveScore = minimax(board, 0, false, player, opponent);
                board[i][j] = '_';
                if (moveScore > bestScore) {
                    bestScore = moveScore;
                    bestMove = {i, j};
                }
            }
        }
    }
    return bestMove;
}

// Main game loop
void playGame() {
    std::vector<std::vector<char>> board(3, std::vector<char>(3, '_'));
    char player, opponent;

    std::cout << "Choose your marker (X/O): ";
    std::cin >> player;
    player = toupper(player);
    opponent = (player == 'X') ? 'O' : 'X';

    displayBoard(board);

    bool userTurn = (player == 'X');
    while (movesLeft(board) && checkWinner(board) == '_') {
        if (userTurn) {
            int row, col;
            std::cout << "Enter your move (row and column): ";
            std::cin >> row >> col;

            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '_') {
                board[row][col] = player;
                userTurn = false;
            } else {
                std::cout << "Invalid move. Try again.\n";
            }
        } else {
            std::cout << "Computer's turn...\n";
            auto [bestRow, bestCol] = findBestMove(board, opponent, player);
            board[bestRow][bestCol] = opponent;
            std::cout << "Computer placed " << opponent << " at (" << bestRow << ", " << bestCol << ").\n";
            userTurn = true;
        }
        displayBoard(board);
    }

    char winner = checkWinner(board);
    if (winner == player)
        std::cout << "Congratulations! You won!\n";
    else if (winner == opponent)
        std::cout << "Computer won. Better luck next time!\n";
    else
        std::cout << "It's a tie!\n";
}

int main() {
    if (!login()) {
        std::cout << "Login failed. Exiting...\n";
        return 1;
    }

    std::cout << "Welcome to Game Theory Algorithm Simulator!\n";
    std::cout << "1. Play Tic-Tac-Toe with Minimax\n";
    std::cout << "2. Play Tic-Tac-Toe with Alpha-Beta Pruning (Not implemented)\n";
    std::cout << "Select an option: ";
    int choice;
    std::cin >> choice;

    switch (choice) {
        case 1:
            playGame();
            break;
        case 2:
            std::cout << "Alpha-Beta Pruning is under development.\n";
            break;
        default:
            std::cout << "Invalid choice. Exiting...\n";
    }

    return 0;
}

