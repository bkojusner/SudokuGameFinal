using namespace std;
#include <string>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <algorithm>
#include <fstream>
#include <valarray>

class User{
 private:
 	string username;
 	string password;
 	int wins;
 public:
 	User(string username, string password, int wins);
 	string getUsername();
 	string getPassword();
 	int getWins();
 	void winGame();
 };