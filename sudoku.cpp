//declaring variables
const int size = 9;
const int empty = 0;

//method creating empty board
//sets size for the game
void createBoard(vector < vector<int> >& board){
    
    //for loop creating row
    for(int i = 0; i < size; i++){
        
        //for loop creating column
        for(int j = 0; j < size; j++){
            board[i][j] = empty;
        }
    }
}

//method importing board
//lets sudoku game load a board for play
void importBoard(vector< vector<int> >& board, string filename) {
    //declaring variables
    ifstream infile(filename.c_str());
    int cell;
    string line;

    //checking if file is good
    if(infile.good()){
        
        //for loop creating row
        for(int i = 0; i < size; i++){
            
            //for loop creating column
            for(int j = 0; j< size; j++){
                infile >> cell;
                board[i][j] = cell;
            }
        }
    }
   
    //error handling
    else {
        cout << "Invalid input file" << "\n";
    }
}

//method printing board
//prints board with values
void printBoard(vector < vector<int> >& board){
    //for loop initializing display
    for(int i=0; i < size; i++){
        //if statement for layout
        if(i % 3 == 0){
            cout << "------+-------+------" << "\n";
        }
        
        //for loop for layout
        for(int j = 0; j < size; j++){
            if((j%9) != 0 && (j %9) % 3 == 0){
                cout << " |";
            }
            if(j > 0){
                cout << " ";
           }
            cout << board[i][j];
        }
        cout << "\n";
    }
}

//method checking for fixed values
//avoids confusion during game
bool fixedValues(vector <vector <int> >& board, int row, int column){
    //if statement checking fixed values
    if (board[(row - 1)][(column - 1)] == empty){
        return false;
    }
    else{
        cout<<"Invalid placement"<<"\n";
        return true;
    }
}

//method checking row values
//prevents similarity on rows
bool rowCheck(vector <vector <int> >& board, int row, int number){
    //declaring variable
    int n;

    //for loop checking row similarity
    for(int j = 0; j < size; j++){
        n = board[(row - 1)][j];
        if(n == number){
            cout << "Error: Same number in row." << "\n";
            return true;
        }
    }
    return false;
}


//method checking column values
//prevents similarity on columns
bool colCheck(vector < vector<int> >& board, int column, int number){
    //declaring variable
    int n;

    //for loop checking for column similarity
    for(int i = 0; i < size; i++){
        n = board[i][(column - 1)];
        if(n == number){
           cout << "Error: Same number in column." << "\n";
            return true;
        }
    }
    return false;
}


//method checking 3x3 box values
//prevents similarity on 3x3 box
bool boxCheck(vector< vector<int> >& board, int row, int column, int number){
    int boxRow;
    int boxColumn;

    //sequence of if statements that determine which 3x3 box to traverse
    if(row <= 3 && row >= 1){
        if(column <= 3 && column >= 1){
            boxRow = 0;
            boxColumn = 0;
        }
        if(column <= 6 && column >= 4){
             boxRow = 0;
            boxColumn = 3;
        }
        if(column <= 9 && column >= 7){
             boxRow = 0;
            boxColumn = 6;
        }
    }

    if(row <= 6 && row >= 4){
        if(column <= 3 && column >= 1){
             boxRow = 3;
            boxColumn = 0;
        }
        if(column <= 6 && column >= 4){
             boxRow = 3;
            boxColumn = 3;
        }
        if(column <= 9 && column >= 7){
             boxRow = 3;
            boxColumn = 6;
        }
    }

    if(row <= 9 && row >= 7){
        if(column <= 3 && column >= 1){
             boxRow = 6;
            boxColumn = 0;
        }
        if(column <= 6 && column >= 4){
             boxRow = 6;
            boxColumn = 3;
        }
        if(column <= 9 && column >= 7){
             boxRow = 6;
            boxColumn = 6;
        }
    }
    
    //loops through specified 3x3 box to see if the number already exists
    for(int i = boxRow; i < (boxRow+3); i++){
        for(int j = boxColumn; j < (boxColumn+3); j++){
            if(board[i][j] == number){
                cout << "Error: Same number in 3x3 box." << "\n";
                return true;
            }
        }
    }
    return false;
}

//method to erase numbers
//lets player insert their numbers
bool erase(vector< vector<int> >& originalBoard, int row, int column){
    //if statement to erase numbers
    if(originalBoard[(row-1)][(column-1)] == empty){
        return false;
    }
    else{
        return true;
    }
}

//sudoku method
//lets player play sudoku
int sudoku(string filename) {
    //declaring variables
    int row,column,number;
    
    vector< vector<int> > theBoard(size,vector<int>(size));
    vector< vector<int> > originalBoard(size,vector<int>(size));
    
    //calling forth the createBoard and importBoard methods
    //lets boards begin to initialize
    createBoard(theBoard);
    importBoard(theBoard,filename);
    createBoard(originalBoard);
    importBoard(originalBoard,filename);
    
    //greeting message
    cout << "You're now playing sudoku!" << "\n";
    
    //declaring variables
    string userChoice = " ";
    bool close = true;
    bool finished = false;
    
    //printing menu to begin playing uno
    do{
        //menu declaration message
        cout << "Insert action (print, write, erase, quit, finished): ";
        cin >> userChoice;
        
        //if print is chosen
        if(userChoice == "print"){
            printBoard(theBoard);
            continue;
        }

        //if write is chosen
        if(userChoice == "write"){
            
            //makes player input row
            //checks for number parameters
            cout << "Input Row: " << "\n";
            cin >> row;
            if ((row < 0 || row > 9)) {
                cout<<"Bad number"<<"\n";
                continue;
            }
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout<<"Try a number."<<"\n";
                continue;

            }

            //makes player input column
            //checks for number parameters
            cout<< "Input Column: " << "\n";
            cin >> column;
            if ((column < 0 || column > 9)) {
                cout<<"Bad number"<<"\n";
                continue;
            }
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout<<"Try a number."<<"\n";
                continue;
            }

            //makes player input number
            //checks for number parameters
            cout << "Input Number: " << "\n";
            cin >> number;
            if ((number < 0 || number > 9)) {
                cout<<"Bad number"<<"\n";
                continue;
            }
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout<<"Try a number."<<"\n";
                continue;
            }

            //if statement making sure play is legal
            //checks number with row, col, and box check methods
            if((fixedValues(theBoard, row, column) == false) && 
                (rowCheck(theBoard, row, number) == false) && 
                (colCheck(theBoard, column, number) == false)&&
                (boxCheck(theBoard, row, column, number) == false)){
                theBoard[(row -1)][(column-1)] = number;
                printBoard(theBoard);
            }
            else{
                cout << "" << "\n";
            }
            continue;
        }
        
        //if erase is chosen
        if(userChoice == "erase"){
            cout << "Input Row: " << "\n";
            cin >> row;
            cout << "Input Column" << "\n";
            cin >> column;
            
            if(erase(originalBoard, row, column) == false){
                theBoard[(row-1)][(column-1)] = empty;
                printBoard(theBoard);
            }
            else{
                cout << "Error: That is a fixed number" << "\n";
            }
            continue;
        }
        
        //if quit is chosen
        if(userChoice == "quit"){
            close = false;
        } 

        //if finished is chosen
        if (userChoice == "finished") {
            finished = true;
            for (int i = 0; i < size; i++) {
                for (int j = 0; j < size; j++) {
                    if (theBoard[i][j] == 0) {
                        finished = false;
                        cout<<"Puzzle not finished"<<"\n";
                        break;
                    }
                 }
                 if (!finished) {
                    break;
                 }
            }

            if (finished) {
                cout<<"Successfully completed the puzzle! Good job :)"<<"\n";
                close = false;
            }
        }
    } 
    while(close);

    //if finished was typed
    //game is finished
    if (finished) {
        return 1;
    }
    else return 0;  
}

