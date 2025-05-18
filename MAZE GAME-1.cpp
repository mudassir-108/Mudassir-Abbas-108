#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>

using namespace std;

// Define maximum maze size
const int MAX_MAZE_SIZE = 20;

enum Difficulty { LOW = 5, MEDIUM = 7, HIGH = 9 };

class MazeGame {
private:
    char maze[MAX_MAZE_SIZE][MAX_MAZE_SIZE];
    int playerRow, playerCol;
    int exitRow, exitCol;
    int mazeSize;
    int playerLives;
    int currentLevel;

public:
    MazeGame(Difficulty difficulty) {
        mazeSize = static_cast<int>(difficulty);
        playerLives = 3;
        currentLevel = 1;
        
        initializeMaze();
    }

    void initializeMaze() {
        // Clear the maze
        for (int i = 0; i < mazeSize; i++) {
            for (int j = 0; j < mazeSize; j++) {
                maze[i][j] = '.';
            }
        }
        
        // Add walls randomly
        for (int i = 1; i < mazeSize - 1; i++) {
            for (int j = 1; j < mazeSize - 1; j++) {
                if (rand() % 5 == 0) {
                    maze[i][j] = '#';  // Wall
                } else if (rand() % 20 == 0) {
                    maze[i][j] = '?';  // Bonus
                }
            }
        }
        
        // Set player position
        playerRow = 0;
        playerCol = 0;
        maze[playerRow][playerCol] = 'P';
        
        // Set exit position
        exitRow = mazeSize - 1;
        exitCol = mazeSize - 1;
        maze[exitRow][exitCol] = 'E';
    }

    void displayMaze() {
        // Clear screen
        system("cls");
        
        // Print game header
        cout << "\n   *** MAZE GAME ***\n\n";
        cout << "   Lives: " << playerLives << " | Level: " << currentLevel << "\n\n";
        
        // Print the maze
        for (int i = 0; i < mazeSize; i++) {
            cout << "   ";
            for (int j = 0; j < mazeSize; j++) {
                cout << maze[i][j] << " ";
            }
            cout << endl;
        }
        
        cout << "\n   Legend: P = Player, E = Exit, # = Wall, ? = Bonus\n";
        cout << "   Controls: W = Up, S = Down, A = Left, D = Right, Q = Quit\n\n";
    }

    bool makeMove(char direction) {
        int newRow = playerRow;
        int newCol = playerCol;
        
        // Calculate new position based on direction
        switch (direction) {
            case 'W': case 'w': newRow--; break;
            case 'S': case 's': newRow++; break;
            case 'A': case 'a': newCol--; break;
            case 'D': case 'd': newCol++; break;
            case 'Q': case 'q': return false;
            default: return true;  // Invalid move, no change
        }
        
        // Check if the move is valid
        if (newRow < 0 || newRow >= mazeSize || newCol < 0 || newCol >= mazeSize || maze[newRow][newCol] == '#') {
            cout << "\n   Invalid move! Try again.\n";
            system("pause");
            return true;
        }
        
        // Check for bonus
        if (maze[newRow][newCol] == '?') {
            playerLives++;
            cout << "\n   You found a bonus! +1 Life\n";
            system("pause");
        }
        
        // Check for exit
        if (newRow == exitRow && newCol == exitCol) {
            currentLevel++;
            cout << "\n   Level complete! Moving to level " << currentLevel << "\n";
            system("pause");
            
            // Update maze size for next level (max 20)
            mazeSize = min(mazeSize + 1, MAX_MAZE_SIZE);
            initializeMaze();
            return true;
        }
        
        // Update player position
        maze[playerRow][playerCol] = '.';
        playerRow = newRow;
        playerCol = newCol;
        maze[playerRow][playerCol] = 'P';
        
        return true;
    }
    
    bool isGameOver() {
        return playerLives <= 0;
    }
    
    void loseLife() {
        playerLives--;
        if (playerLives <= 0) {
            cout << "\n   Game Over! You're out of lives.\n";
            system("pause");
        } else {
            cout << "\n   You lost a life! Lives remaining: " << playerLives << "\n";
            system("pause");
        }
    }
};

Difficulty chooseDifficulty() {
    int choice;
    cout << "\n   Choose difficulty:\n";
    cout << "   1. Easy\n";
    cout << "   2. Medium\n";
    cout << "   3. Hard\n";
    cout << "   Your choice (1-3): ";
    cin >> choice;
    
    switch (choice) {
        case 1: return LOW;
        case 2: return MEDIUM;
        case 3: return HIGH;
        default: return LOW;
    }
}

int main() {
    // Seed random number generator
    srand(time(NULL));
    
    char playAgain;
    
    do {
        // Display welcome message
        system("cls");
        cout << "\n   *** WELCOME TO THE MAZE GAME ***\n\n";
        
        // Get player name
        string playerName;
        cout << "   Enter your name: ";
        cin.ignore();
        getline(cin, playerName);
        cout << "\n   Hello, " << playerName << "! Let's begin.\n";
        
        // Choose difficulty
        Difficulty difficulty = chooseDifficulty();
        
        // Create game
        MazeGame game(difficulty);
        bool gameRunning = true;
        
        // Game loop
        while (gameRunning && !game.isGameOver()) {
            game.displayMaze();
            
            cout << "   Enter move (W/A/S/D) or Q to quit: ";
            char move = getch();  // Get single character without pressing Enter
            
            gameRunning = game.makeMove(move);
        }
        
        // Ask to play again
        cout << "\n   Play again? (Y/N): ";
        cin >> playAgain;
        
    } while (playAgain == 'Y' || playAgain == 'y');
    
    cout << "\n   Thanks for playing!\n";
    system("pause");
    return 0;
}
