#include "final.h"
#include "sudoku.cpp"

User::User(string username, string password, int wins) {
	this->username = username;
	this->password = password;
	this->wins = wins;
};

//getters
string User::getUsername() {
	return username;
};

string User::getPassword() {
	return password;
};

int User::getWins() {
	return wins;
};

void User::winGame() {
	wins++;
	return;//adds a completed game
};

string encrypt(string line){

           //initializes encrypted string
           string encrypted = "";

           /*
           for loop that traverses the string and 
           applies encryption method, then appends the string
           to the encrypted string
           */
           for(int i = 0; i < line.length(); i++){
                      encrypted += line[i] + 20 + i;
           }

           //returns the encrypted string
           return encrypted;
}

string decrypt(string line){

           //initializes decrypted string
           string decrypted = ""; 

           /*
           for loop that traverses the string and 
           applies decryption method, then appends the string
           to the decrypted string
           */
           for(int i = 0; i < line.length(); i++){
                      decrypted += line[i] - 20 - i;
           }

           //returns the decrypted string
           return decrypted;
}

int accountVerify(vector <User> &accounts) {
	string username;
	string password;
	cout<<"Username: ";
	cin>>username;
	cout<<endl;
	cout<<"Password: ";
	cin>>password;
	cout<<endl;


	

	int j = 0;
	int index = -1;

	for (vector<User>::const_iterator i = accounts.begin(); i != accounts.end(); ++i) {
		if (username == accounts.at(j).getUsername()) {
			index = j;
			break;
		}
		j++;
	}

	if (index == -1) return -1;

	if (password == accounts.at(index).getPassword())
		return index;
	else return -1;


}

void updateFile(vector <User> &accounts) { // rewrites file to account for new completed games
	int j = 0;
	ofstream accountFile;
	string username;
	string password;
	accountFile.open("accounts.txt", std::ofstream::trunc);
	for (vector<User>::const_iterator i = accounts.begin(); i != accounts.end(); ++i) {
		//writes to file with encryption via for loop
		accountFile<<encrypt(accounts.at(j).getUsername())<<" "<<
		encrypt(accounts.at(j).getPassword())<<" "<<accounts.at(j).getWins()<<"\n";
		j++;
	}

};

bool writeToFile(string username, string password, int wins) {
	ofstream accountFile("accounts.txt", std::ios::app); //writes to the end of file 

	if (accountFile.is_open()) {
		//writes new account to a file via encryption
		accountFile <<encrypt(username)<<" "<<encrypt(password)<<" "<<wins<<"\n";
		return true;
	}
	else return false;
};

void createUsersVector(vector <User> &users) { // creates vector of previously created accounts
	string username;
	string password;
	int wins;
	ifstream accountFile("accounts.txt");

	//reads in file and decypts to get accounts
	while(accountFile >> username >> password >> wins){
		username = decrypt(username);
		password = decrypt(password);
		User user (username,password, wins);
		//adds users to vector of users
		users.push_back(user);
	}

};

bool accountOccupied(vector <User> &accounts, string userName) {//returns true if username is taken
	int j = 0;
	for (vector<User>::const_iterator i = accounts.begin(); i != accounts.end(); ++i) {
		//checks if username matches
		if (accounts.at(j).getUsername() == userName) 
			return true;
		j++;
	}

	return false;

};

bool passwordCheck (string password) {//returns true if password is good
	bool number = false;
	bool letter = false;

	if (password.length() < 6 || password.length() > 16) {
		//checks length of password
		cout<<"Password should be between 6 and 16 characters."<<endl;
		return false;
	}
	for (int i = 0; i < password.length(); i++) {
		if (password[i] == ' ') {
			cout<<"Spaces not allowed in password."<<endl;
			return false;
		}
		//checks that user input a letter and number
		if (password[i] >= '0' && password[i] <= '9') 
			number = true;
		if ((password[i] >= 'A' && password[i] <= 'Z') || (password[i] >= 'a' && password[i] <= 'z')) 
			letter = true;
	}

	if (letter && number) 
		return true;
	
	else{
		cout<<"Password must contain a letter and a number"<<endl;
		return false;
	}

}; 


bool createAccount(vector <User> &accounts) { 
	string username;
	string password;

	for (int i = 0; i < 3; i++) { //tries for correct/ unused username 3 times
		cout<<"Username (no spaces): ";
		cin>>username;
		if (accountOccupied(accounts, username)){
		cout<<"Username taken. Try again."<<endl;
			if (i == 2) {
				return false;
			}
		continue;
		}
		else break;
	}
	
	cout<<"Password (no spaces): ";
	for (int i = 0; i < 3; i++) {
		cin>>password;
		if (passwordCheck(password)) {
			break;
		}
		else {
			cout<<"Try again."<<endl;
			continue;
		}

		if (i == 2 && !passwordCheck(password)) {
			return false;
		}
	}


	//if all credentials for a new account pass, new account created
	User user (username, password, 0); 

	accounts.push_back(user);

	writeToFile(username, password, 0);

	return true;

};


int main () {

	vector <User> users;
	
	//creates vector of existing users from text file
	createUsersVector(users);

	int input;
	int indexOfAccount;
	string puzzle;
	string puzzleFile;

	cout<<"Welcome to the Ultimate Sudoku by Group 8!"<<endl;
	
	while (true) { // for loop to create a new account or log in
		cout<<"Enter a command.\n1. Log in\n2. Create new account"<<endl;
		cin>>input;

		if (input == 1) {
			//indexOfAccount tells program the index of the user in the vector
			indexOfAccount = accountVerify(users);
			if (indexOfAccount > -1) {
				cout<<"Successful login."<<endl;
				break;
			}
			else {
				cout<<"Login failed. Invalid username/password combination."<<endl;

			}
		}
		
		if (input == 2) {
			//new account creation
			if (createAccount(users)) {
				cout<<"Account creation successful. Time to play!"<<endl;
				indexOfAccount = users.size() -1;
				break;
			}	
			else {
				cout<<"Account creation not successful."<<endl;
				continue;
			}		
		}

		else { // case for bad input
			cout<<"Try a valid command."<<endl;
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	}

	while (true) {
		cout<<"Options: \n1. Play Sudoku\n2. Help/How to play \n3. View number of completed games."
		<< "\n4. Exit"<<endl;
		cin>>input;

		if (input == 1) {

			//we plan to read from a file called pn.txt, where n is a number. the file contains the board
			cout<<"Enter an int 1-10 to choose a puzzle. 1-4 for easy, 5-7 for medium, 8-10 for hard." <<endl;
			cin>>puzzle;
			puzzleFile = "p" + puzzle + ".txt";

			if (sudoku(puzzleFile) == 1) {
				users.at(indexOfAccount).winGame();
			}

		}

		if (input == 2) {
			cout<<"How to play: " <<endl
			<<"- Menu will prompt to print the board, write to it, erase a value, or quit"<<endl
		//	<<"- You can also enter \"finished\" to check if you successfully completed the puzzle"<<endl
           <<"- Treat zeroes as blanks"<<endl
           <<"- Enter row and column number"<<endl
           <<"- Enter a value 1-9 to input into the cell"<<endl
           <<"- Have each row, column, and 3x3 square have digits 1-9"<<endl
           <<"- Make sure numbers do not repeat in each row, column, and 3x3 square"<<endl
           <<"- Insert finished when you have completed the puzzle"<<endl;

		}

		if (input == 3) {
			cout<<"You've finished "<<users.at(indexOfAccount).getWins()<<" puzzles."<<endl;


		}
		if (input == 4) {
			break;
		}


		else {
			cout<<endl;
			std::cin.clear();
			std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
	}

	updateFile(users);
	cout<<"Thanks for playing!"<<endl;

	return 0; 
}
