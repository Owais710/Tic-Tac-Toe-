#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct player {
    char name[30];
    unsigned int age;
    int score;
    int moves;
};

// The game board
char gameBoard[3][3];

// Function to initialize the game board to empty values
void initializeGameBoard() {
    // Iterate through rows and columns to set initial values to empty spaces
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = ' ';
        }
    }
}

// Function to print the current game board
void displayGameBoard() {
    // Display the tic-tac-toe board along with separators
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("| %c ", gameBoard[i][j]);
        }
        printf("|\n");
        if (i < 2) {
            printf(" -------------\n");
        }
    }
}

// Function to check if there is a winner on the board
int checkForWinner() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        // Check if a row has all the same symbols
        if (gameBoard[i][0] != ' ' && gameBoard[i][0] == gameBoard[i][1] && gameBoard[i][1] == gameBoard[i][2]) {
            return 1; // Winner found
        }

        // Check if a column has all the same symbols
        if (gameBoard[0][i] != ' ' && gameBoard[0][i] == gameBoard[1][i] && gameBoard[1][i] == gameBoard[2][i]) {
            return 1; // Winner found
        }
    }

    // Check diagonals
    // Diagonal from top-left to bottom-right
    if (gameBoard[0][0] != ' ' && gameBoard[0][0] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][2]) {
        return 1; // Winner found
    }

    // Diagonal from top-right to bottom-left
    if (gameBoard[0][2] != ' ' && gameBoard[0][2] == gameBoard[1][1] && gameBoard[1][1] == gameBoard[2][0]) {
        return 1; // Winner found
    }

    // If there are no winners, return 0
    return 0; // No winner yet
}

int main() {
    printf("Welcome to Tic Tac Toe Game!\n");

    struct player playerone;
    struct player playertwo;

    printf("\nPlayer one, enter your name: ");
    fgets(playerone.name, 30, stdin);
    playerone.name[strcspn(playerone.name, "\n")] = '\0';  // Remove trailing newline

    printf("\nPlayer two, enter your name: ");
    fgets(playertwo.name, 30, stdin);
    playertwo.name[strcspn(playertwo.name, "\n")] = '\0';  // Remove trailing newline

    printf("\n%s, enter your age: ", playerone.name);
    scanf("%u", &playerone.age);
    getchar(); // Clear the buffer after scanf to avoid issues with fgets

    printf("\n%s, enter your age: ", playertwo.name);
    scanf("%u", &playertwo.age);
    getchar(); // Clear the buffer after scanf to avoid issues with fgets

    int currentPlayer = 1; // Player 1 goes first
    int Row, Column;
    char playerSymbol;

    playerone.moves = 0;
    playertwo.moves = 0;

    initializeGameBoard(); // Initialize the game board

    while (1) {
        displayGameBoard(); // Display the current state of the board

        if (currentPlayer == 1) {
            printf("%s, enter your move (row [1-3] and column [1-3]): ", playerone.name);
            scanf("%d%d", &Row, &Column);
            playerone.moves++;
        } else {
            printf("%s, enter your move (row [1-3] and column [1-3]): ", playertwo.name);
            scanf("%d%d", &Row, &Column);
            playertwo.moves++;
        }

        // Validate the move before adjusting for 0-based index
        if (Row >= 1 && Row <= 3 && Column >= 1 && Column <= 3) {
            // Adjust for 0-based array indexing
            Row--;
            Column--;

            // Check if the entered move is valid
            if (gameBoard[Row][Column] == ' ') {
                playerSymbol = (currentPlayer == 1) ? 'X' : 'O'; // Assign 'X' or 'O' based on the player
                gameBoard[Row][Column] = playerSymbol; // Place the symbol on the board

                // Check if the current move results in a win
                if (checkForWinner()) {
                    displayGameBoard(); // Display the final state of the board
                    if (currentPlayer == 1) {
                        printf("Congratulations %s, you have won the game!\n", playerone.name);
                        playerone.score += 100;
                        printf("\nYou took a total of %d moves\n", playerone.moves);
                        printf("\nYour score was %d\n", playerone.score);
                    } else {
                        printf("Congratulations %s, you have won the game!\n", playertwo.name);
                        playertwo.score += 100;
                        printf("\nYou took a total of %d moves\n", playertwo.moves);
                        printf("\nYour score was %d\n", playertwo.score);
                    }
                    printf("Game has ended\n");
                    break; // Exit the game loop
                }

                // Switch to the other player
                currentPlayer = 3 - currentPlayer; // Switch to the other player
            } else {
                printf("Invalid move, the cell is already occupied. Try again.\n");
            }
        } else {
            printf("Invalid input, row and column should be between 1 and 3. Try again.\n");
        }
    }

    return 0; // End the program
}
