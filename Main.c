// To compile, run gcc $(pkg-config --cflags gtk4) -o main main.c $(pkg-config --libs gtk4)
// To compile for windows, check README.txt for windows

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <gtk/gtk.h>

#define X -1 // defines X to allow change of turn
#define O -2 // defines O to allow change of turn

#define CHAR_LIM 50 // max characters user can input

int turn = X; // sets your first turn to O

int board[] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // shows the numbers on board placement

int output = 0; // shows number of possible moves available

int difficulty; // 1 to 5 (only for PVE)

int mode; // 1 for PVP 2 for PVE

GtkWidget *window; // Main window used for UI

void delay(int number_of_seconds);
void curBoard(int from[], int to[]);
// int getl(char s[], int lim);
int bufferToNum(char buffer[]);
char boardToChar(int i);
// void printBoard();
void altTurn();
int draw(int l_board[]);
int win(int l_board[]);
int putInBoard(int l_board[], int pos, int newVal);
int gameState(int l_board[]);
void legalMoves(int l_board[], int output[]);
int max(int a, int b);
int min(int a, int b);
int minimax(int l_board[], int depth, int maximising);
int largemin(int l_board[], int depth, int maximising);
int ai(int l_board[], int depth);
int badai(int l_board[], int depth);
void gameLogic(int board[], int mode);
void boxOnClick(GtkButton *button, gpointer data);
void returnOnClick(GtkButton *button, gpointer data);
void tictactoeWindow(int board[], int turn, char state);
void difficultyOnClick(GtkButton *button, gpointer data);
void difficultySelectWindow();
void oneplayerpressed(GtkWidget *widget, gpointer data);
void twoplayerpressed(GtkWidget *widget, gpointer data);
void mainWindow();
static void activate(GtkApplication *app, gpointer user_data);
int main(int argc, char **argv);

void delay(int number_of_seconds)
{
    // Converting time into milli_seconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // looping till required time is not achieved
    while (clock() < start_time + milli_seconds);
}

void curBoard(int from[], int to[])
{ // saves current board state
    for (int i = 0; i < 9; i++)
    {
        to[i] = from[i];
    }
}

// gets line WITHOUT \n
int getl(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        s[i] = c;

    s[i] = '\0';
    return i;
}

// converts char[] to int to allow for > and < operands to work
int bufferToNum(char buffer[])
{
    int n = 0;
    for (int i = 0; buffer[i] != '\0'; i++)
    {
        n = 10 * n + buffer[i] - '0';
    }
    return n;
}

// converts the board numbers to char to display
char boardToChar(int i)
{
    int a = board[i];
    if (a == X)
    {
        return 'X';
    }
    else if (a == O)
    {
        return 'O';
    }
    else
    {
        return a + '0';
    }
}

// prints board
void printBoard()
{
    printf("=============\n"
           "| %c | %c | %c |\n"
           "-------------\n"
           "| %c | %c | %c |\n"
           "-------------\n"
           "| %c | %c | %c |\n"
           "=============\n", //
           boardToChar(0), boardToChar(1), boardToChar(2),
           boardToChar(3), boardToChar(4), boardToChar(5),
           boardToChar(6), boardToChar(7), boardToChar(8));
}

// alternates turn
void altTurn()
{
    if (turn == O)
    {
        turn = X;
    }
    else if (turn == X)
    {
        turn = O;
    }
}

// returns 1 if draw, return 0 if not a draw
int draw(int l_board[])
{
    for (int i = 0; i < 9; i++)
    {
        if (l_board[i] == i + 1)
        {
            return 0;
        }
    }
    return 1;
}

// returns X if X won and O if O won and 0 if draw
int win(int l_board[])
{
    // Rows
    for (int i = 0; i < 3; i++)
    {
        if (l_board[3 * i] == l_board[3 * i + 1] && l_board[3 * i + 1] == l_board[3 * i + 2])
        {
            return l_board[3 * i];
        }
    }

    // Columns
    for (int j = 0; j < 3; j++)
    {
        if (l_board[j] == l_board[3 + j] && l_board[3 + j] == l_board[6 + j])
        {
            return l_board[j];
        }
    }

    // Diagonal Top Left to Bottom Right
    if (l_board[0] == l_board[4] && l_board[0] == l_board[8])
    {
        return l_board[0];
    }

    // Diagonal Top Right to bottom Left
    if (l_board[2] == l_board[4] && l_board[2] == l_board[6])
    {
        return l_board[2];
    }

    return 0;
}

// 1 if no board placement and 0 if there is board placement
int putInBoard(int l_board[], int pos, int newVal)
{
    if (l_board[pos] == pos + 1)
    {
        l_board[pos] = newVal;
        return 1;
    }
    else
    {
        return 0;
    }
}

// X if X win, O if O win, 0 if draw, 1 if nothing
int gameState(int l_board[])
{
    int wc = win(l_board);
    if (wc == X)
    {
        return X;
    }
    else if (wc == O)
    {
        return O;
    }
    else
    {
        if (draw(l_board))
        {
            return 0;
        }
    }
    return 1;
}

// shows allowed moves to be taken within the range of 1-9, array 0-8
void legalMoves(int l_board[], int output[])
{
    for (int i = 0; i < 9; i++)
    {
        if (l_board[i] == i + 1)
        {
            output[i] = 1;
        }
        else
        {
            output[i] = 0;
        }
    }
}

// best possible move possible
int max(int a, int b)
{
    return a > b ? a : b;
}

// worst possible move possible
int min(int a, int b)
{
    return a < b ? a : b;
}

// X is computer
int minimax(int l_board[], int depth, int maximising)
{
    int gs = gameState(l_board); // goes through every single move possible from both sides
    output++;                    // totals number of possible move that can be made
    if (gs == X)
    { // best move that can be made
        return 10;
    }
    else if (gs == O)
    { // worst move that can be made
        return -10;
    }
    else if (gs == 0)
    { // no possible move
        return 0;
    }
    if (depth == 0)
    { // no further board states available
        return 0;
    }
    if (maximising)
    {
        // X's Turn so it has to maximise
        int val = -100;                     // works together with gs to show how effective all moves will be
        int legalMovesArr[9];               // prevents illegal moves <1 || >9
        legalMoves(l_board, legalMovesArr); // finds the legal moves available with current boardstate
        for (int i = 0; i < 9; i++)
        {
            if (legalMovesArr[i])
            {
                int tempBoard[9];
                curBoard(l_board, tempBoard);
                putInBoard(tempBoard, i, X);
                val = max(minimax(tempBoard, depth - 1, 0), val);
            }
        }
        return val;
    }
    else
    {
        // for minimising to try to find the worst possible moves for opponent
        int val = 100;
        int legalMovesArr[9];
        legalMoves(l_board, legalMovesArr);
        for (int i = 0; i < 9; i++)
        {
            if (legalMovesArr[i])
            {
                int tempBoard[9];
                curBoard(l_board, tempBoard);
                putInBoard(tempBoard, i, O);
                val = min(minimax(tempBoard, depth - 1, 1), val);
            }
        }
        return val;
    }
}

int largemin(int l_board[], int depth, int maximising)
{
    int gs = gameState(l_board); // goes through every single move possible from both sides
    output++;                    // totals number of possible move that can be made
    if (gs == O)
    { // best move that can be made
        return 10;
    }
    else if (gs == X)
    { // worst move that can be made
        return -10;
    }
    else if (gs == 0)
    { // no possible move
        return 0;
    }
    if (depth == 0)
    { // no further board states available
        return 0;
    }
    if (maximising)
    {
        // X's Turn so it has to maximise
        int val = -100;                     // works together with gs to show how effective all moves will be
        int legalMovesArr[9];               // prevents illegal moves <1 || >9
        legalMoves(l_board, legalMovesArr); // finds the legal moves available with current boardstate
        for (int i = 0; i < 9; i++)
        {
            if (legalMovesArr[i])
            {
                int tempBoard[9];
                curBoard(l_board, tempBoard);
                putInBoard(tempBoard, i, X);
                val = max(largemin(tempBoard, depth - 1, 0), val);
            }
        }
        return val;
    }
    else
    {
        // for minimising to try to find the worst possible moves for opponent
        int val = 100;
        int legalMovesArr[9];
        legalMoves(l_board, legalMovesArr);
        for (int i = 0; i < 9; i++)
        {
            if (legalMovesArr[i])
            {
                int tempBoard[9];
                curBoard(l_board, tempBoard);
                putInBoard(tempBoard, i, O);
                val = min(largemin(tempBoard, depth - 1, 1), val);
            }
        }
        return val;
    }
}

int ai(int l_board[], int depth)
{ // uses current boardstate to find the best possible moves
    int legalMovesArr[9];
    legalMoves(board, legalMovesArr);
    int val = -100;
    int best_move = 0;
    for (int i = 0; i < 9; i++)
    {
        if (legalMovesArr[i])
        {
            int tempBoard[9];
            curBoard(l_board, tempBoard);
            putInBoard(tempBoard, i, X);
            int temp = minimax(tempBoard, depth - 1, 0);
            if (val <= temp)
            {
                val = temp;
                best_move = i;
            }
        }
    }
    return best_move; // the closer val is to 0, the better the move
}

int badai(int l_board[], int depth)
{ // uses current boardstate to find the best possible moves
    int legalMovesArr[9];                                           //uses current boardstate to find the best possible moves
    legalMoves(board, legalMovesArr);                               //creates an array to correspond if the spot in the board is empty or filled
    int val = -100;                                                 //fills the legalmovesarray with 1 or 0's and checks with the current board state whether if it is already filled or not
    int worst_move = 0;                                             //set the initial best move to -100
    for (int i = 0; i < 9; i++)                                     //set local value to 0 to avoid garbage values
    {
        if (legalMovesArr[i])                                       //checks if theres any moves left
        {
            int tempBoard[9];                                       //creates a temporary board for the local function
            curBoard(l_board, tempBoard);                           //fill this temp board to be what the current board state is
            putInBoard(tempBoard, i, X);                            //update the board state to the next with an 'X'
            int temp = largemin(tempBoard, depth - 1, 0);           //pass in a 0 so maximizing is false and we always return the minimum minimizing
            if (val <= temp)                                        //val will always be <= temp because largemin returns value -10 (minimum minimizing value)
            {               
                val = temp;                                         //set temp value into val
                worst_move = i;                                     //puts in the board[] array on the 0th index to 8th index
            }
        }
    }
    return worst_move; // the closer val is to -10, the worst the move
}

// Function for checking for a winner, switching player turns and running the AI
// Called after each player/AI move and at the start of a game
void gameLogic(int board[], int mode)
{
    // Checking if a winner
    int gs = gameState(board);

    // if there is a winner tictactoeWindow() is called
    if (gs == X)
    {
        tictactoeWindow(board, turn, 'X'); // X is the winner
        printf("X won! \n");
    }
    else if (gs == O)
    {
        tictactoeWindow(board, turn, 'O'); // O is the winner
        printf("O won! \n");
    }
    else if (gs == 0)
    {
        tictactoeWindow(board, turn, 'D'); // It is a draw
        printf("It is a draw!");
    }
    // There is no winner therefore the game continues
    else
    {
        // if Player vs Player
        if (mode == 1)
        {
            altTurn();                         // Switch player turns
            tictactoeWindow(board, turn, ' '); // Display the board
        }

        // else Player vs AI
        else
        {
            altTurn(); // Switch player turns
            printf("%d's Turn\n", turn);

            // if the current player is the user
            if (turn == O)
            {
                tictactoeWindow(board, turn, ' ');
            }

            // else the current player is the AI
            else
            {
                int random = rand() % difficulty; // sets difficulty level by user input
                printf("random = %d \n", random);
                printf("Computer is thinking...\n");
                delay(1);
                if (difficulty == 6)
                {
                    putInBoard(board, ai(board, 5), X);
                    printf("Calculated %d types of outputs\n", output);
                    output = 0;
                    gameLogic(board, mode);
                }
                else if (difficulty == 2)
                { // lvl 1
                    putInBoard(board, badai(board, 4), X);
                    gameLogic(board, mode);
                }

                else if (difficulty == 3)
                { // lvl 2
                    putInBoard(board, badai(board, 1), X);
                    printf("Calculated %d types of outputs\n", output);
                    output = 0;
                    gameLogic(board, mode);
                }
                else
                { // lvl 3 and lvl 4
                    if (random != 1)
                    { // makes all non-1 values be the smart move
                        putInBoard(board, ai(board, 4), X);
                        printf("Calculated %d types of outputs\n", output);
                        output = 0;
                    }
                    else
                    {
                        putInBoard(board, badai(board, 3), X);
                    }
                    gameLogic(board, mode);
                }
            } // Else if the player is an AI
        }
    }
}

// Event listener for tictactoe box click
void boxOnClick(GtkButton *button, gpointer data)
{
    gchar *text = gtk_widget_get_name(button); // Recieves the name of the box
    int num = bufferToNum(text);
    printf("Grid box: %d\n", num);
    if (putInBoard(board, num - 1, turn))
    { // Ensures that the move is valid and is made
        gameLogic(board, mode);
    }
}

// Event listener for "Return" button
// Triggered from tictactoeWindow() when the user clicks "Retun" after game ends
void returnOnClick(GtkButton *button, gpointer data)
{
    // Resets the starting player turn to default
    turn = X;

    // Clears the board
    for (int i = 1; i <= 9; i++)
    {
        board[i - 1] = i;
    }
    // Returns the player back to the menu screen
    mainWindow();
}

// Function for displaying the tic-tac-toe box
// Called from gameLogic() after a move is made
void tictactoeWindow(int board[], int turn, char state)
{   // state is for determining winner (' ','X','O','D')
    // Declaring widgets within the window
    GtkWidget *button;
    GtkWidget *grid;
    GtkWidget *label;

    // Creating the grid, setting it as the widget in the window
    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER); // Alligning the grid in the window

    // Creating the individual tiactactoe boxes within the grid
    // Using buttons to represent each box of the grid
    for (int i = 0; i < 9; i++)
    {
        char str[2] = {boardToChar(i)};

        // if the board number i is 'X' or 'O' display as such
        if (boardToChar(i) == 'X' || boardToChar(i) == 'O')
        {
            button = gtk_button_new_with_label(str); // Sets the button text as 'X' or 'O'
            gtk_widget_set_name(button, str);        // Assigns the name of the button
            gtk_widget_set_sensitive(button, FALSE); // Disables the button
        }

        // else the box is set as blank
        else
        {
            button = gtk_button_new_with_label(" "); // Sets the button text as ' '
            gtk_widget_set_name(button, str);        // Assigns the name of the button
            gtk_widget_set_sensitive(button, TRUE);  // Enables the button
        }

        // Assigns the event listener to the button
        g_signal_connect(button, "clicked", G_CALLBACK(boxOnClick), NULL);

        // Disables the buttons if the game is over
        if (state != ' ')                            // Checks if the current game is over
            gtk_widget_set_sensitive(button, FALSE); // Disables the button

        // Calculating the button position and then attaching it to the grid
        int x = i % 3; // Determins the x axis
        int y;         // Determining the y axis
        if (i < 9)
            y = 2;
        if (i < 6)
            y = 1;
        if (i < 3)
            y = 0;

        // Attaching the button to the grid
        gtk_grid_attach(GTK_GRID(grid), button, x, y, 1, 1); // Attaching the button
    }

    // Sets the message to display at the bottom of the grid
    char message[20];
    if (state == ' ')                                                // Checks if the current game is still ongoing
        sprintf(message, "Player %c's turn", turn == X ? 'X' : 'O'); // Sets the message as the current player's turn
    else
    {
        if (state == 'D')                     // checks if the game resulted in a draw
            sprintf(message, "It's a Draw!"); // Sets the message as a draw
        else
            sprintf(message, "Player %c Won!", state); // Sets the message as a win

        // Shows the "Return" button below the message
        button = gtk_button_new_with_label("Return");
        g_signal_connect(button, "clicked", G_CALLBACK(returnOnClick), NULL);
        gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 3, 1);
    }

    // Displays the message at the bottom of the grid
    label = gtk_label_new(message);
    gtk_grid_attach(GTK_GRID(grid), label, 0, 3, 3, 1);

    gtk_widget_show(window);
}

// Event listener for difficulty select buttons
// Triggered from difficultySelectWindow() when the user clicks on a difficulty option
void difficultyOnClick(GtkButton *button, gpointer data)
{
    // Recieves the name of the button
    gchar *text = gtk_button_get_label(button);
    difficulty = bufferToNum(text) + 1; // Sets the difficulty level +1 based on the button clicked
    printf("Difficulty: %d\n", difficulty);
    gameLogic(board, mode); // Starts the game
}

// Function for displaying the difficulty select screen when the user chooses "Player vs AI"
void difficultySelectWindow()
{
    // Declaring widgets within the window
    GtkWidget *button;
    GtkWidget *grid;
    GtkWidget *label;

    // Creating the grid, setting it as the widget in the window
    grid = gtk_grid_new();
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);

    // Setting a label to instruct the user to select a difficulty
    label = gtk_label_new("Choose a difficulty");
    gtk_grid_attach(GTK_GRID(grid), label, 0, 0, 5, 1); // Attaching the label to the top of the grid and span 5 columns

    // Creating the difficulty select buttons within the grid
    for (int i = 1; i < 6; i++)
    {
        char str[2];
        sprintf(str, "%d", i);
        button = gtk_button_new_with_label(str);                                  // Sets the button text as the difficulty level
        g_signal_connect(button, "clicked", G_CALLBACK(difficultyOnClick), NULL); // Assigns the event listener to the button
        gtk_grid_attach(GTK_GRID(grid), button, i - 1, 1, 1, 1);                  // Attaching the button to the grid
    }

    gtk_widget_show(window);
}

void oneplayerpressed(GtkWidget *widget, gpointer data)
{
    mode = 2;
    g_print("Single player mode chosen\n");
    difficultySelectWindow();
}

void twoplayerpressed(GtkWidget *widget, gpointer data)
{
    mode = 1;
    g_print("Two player mode chosen\n");
    gameLogic(board, mode);
}

void mainWindow()
{
    GtkWidget *grid;
    GtkWidget *oneplayer;
    GtkWidget *twoplayer;
    // construct the container that is going pack our buttons//
    grid = gtk_grid_new();

    // Pack the container in the window//
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_widget_set_halign(grid, GTK_ALIGN_CENTER);

    // oneplayer button//
    /*gtk_grid_attach: horizontal,vertical,size_horizontal,size_vertical*/
    oneplayer = gtk_button_new_with_label("Player vs AI");
    g_signal_connect(oneplayer, "clicked", G_CALLBACK(oneplayerpressed), NULL);
    gtk_grid_attach(GTK_GRID(grid), oneplayer, 0, 0, 1, 1);

    // twoplayer button//
    /*gtk_grid_attach: horizontal,vertical,size_horizontal,size_vertical*/
    twoplayer = gtk_button_new_with_label("Player vs Player");
    g_signal_connect(twoplayer, "clicked", G_CALLBACK(twoplayerpressed), NULL);
    gtk_grid_attach(GTK_GRID(grid), twoplayer, 0, 1, 1, 1);
}

static void activate(GtkApplication *app, gpointer user_data)
{
    // new window with title//
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Tic Tac Toe");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 150);
    gtk_widget_show(window);
    mainWindow();
}

int main(int argc, char **argv)
{
    // UI elements for opening window
    GtkApplication *app;
    int status;
    app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}