// Vivek Patel
// Lab 10, CECS 130 Section 2, Date: 04/01/2018
// 3D Tic Tac Toe as Required

#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
using namespace std;

class game{
	public:
		int irand,userCount,compCount; //random integer for selection
		char box[3][3];  //2D array to store Values of Each Box
		void initializeGameBoard(); //Initialize Game
		void gameBoard();               //Display Game Board
		void checkWin();                //Check if Wins
		int playMove();                 //Ask User to input integer for Move
};
class _3dgame : public game{
	//inherited class
	public:
		int ibox,winner; //counters
		char box1[3][3]; //second layer of box (array)
		char box2[3][3]; //third layer of box (array)
		bool stopGame,player,computer,bAllUsed; //Variable to check
		void initialize3DGameBoard(); //3d initialize 
		void _3dgameBoard(); //3d view of board
		void AskBox(); // ask the box number
		bool moveUsed(int); //check move used
		void userTurn(); //user turn Function
		void compTurn(); //computer turn function
		void check3DWin(); //check if it wins
		bool allUsed();                 //check if all boxes are used
		void randomSelection();         //Random selection who goes first
};
void game::initializeGameBoard(){
	//Initialize Game Board Matrix With Default Values
	box[0][0]='1'; box[0][1]='2'; box[0][2]='3';
	box[1][0]='4'; box[1][1]='5'; box[1][2]='6';
	box[2][0]='7'; box[2][1]='8'; box[2][2]='9';
}
void game::gameBoard(){
	system("CLS"); //clear screen and Output of first box in the clean Format
	cout<<"\n\t\t3D Tic-Tac-Toe\n";
	cout<<"\n-----------------------------------------------------\n";
	cout<<"\n\n\tBox1->  ";
			cout<<"    |     |   "<<endl<<"\t\t";
			cout<<" "<<box[0][0]<<"  |  "<<box[0][1]<<"  |  "<<box[0][2]<<endl<<"\t\t";
			cout<<"____|_____|____"<<endl<<"\t\t";
			cout<<"    |     |   "<<endl<<"\t\t";
			cout<<" "<<box[1][0]<<"  |  "<<box[1][1]<<"  |  "<<box[1][2]<<endl<<"\t\t";
			cout<<"____|_____|____"<<endl<<"\t\t";
			cout<<"    |     |   "<<endl<<"\t\t";
			cout<<" "<<box[2][0]<<"  |  "<<box[2][1]<<"  |  "<<box[2][2]<<endl<<"\t\t";
			cout<<"    |     |   "<<endl<<"\t\t";
}
int game::playMove(){
	int iu; //flag and integer to store the move
	bool done=false;
	string str="Invalid Move"; //if user enter the string
	do{
		try{
			cout<<"\nEnter the number:";  //Asking user for the move
			cin>>iu;
			if(!cin) 
				throw str; //something wrong with cin then throw string
			if(iu<1 || iu>9) /* Checking if User entered right move*/
				throw iu; //out of range then throw number
			done=true;
		}
		catch(int){
			cout<<"\nError 100: Out of Range\n";
			cout<<"Try Again\n"; //string error
		}
		catch(string str1){
			cout<<"\nError 101: "<<str<<endl;
			cout<<"Try Again\n"; //out of range error
			cin.clear();
			cin.ignore(100, '\n');
		}
	}while(!done);
	return iu; //return the entered number for box
}
void game::checkWin(){
	//this function checks the first box wins.
	int i=0, j=0;
	//userCount=0; //set the user score counter to zero
	//compCount=0; //set the computer score counter to zero
	for(i=0; i<3; i++){
		if(box[i][0]==box[i][1] && box[i][1]==box[i][2]){ //checking all the horizontal rows
			if(box[i][0]=='X')
				userCount++; //if user wins increment the score
			if(box[i][0]=='O')
				compCount++; //if computer wins increment the score
		}
	}
	for(i=0; i<3; i++){
		if(box[0][i]==box[1][i] && box[1][i]==box[2][i]){ //checking all the vertical coloumns 
			if(box[0][i]=='X')
				userCount++; //if user wins increment the score
			if(box[0][i]=='O')
				compCount++; //if computer wins increment the score
		}
	}
	if((box[0][0]==box[1][1] && box[1][1]==box[2][2])){
		if(box[0][0]=='X')
			userCount++; //if user wins increment the score
		if(box[0][0]=='O')
			compCount++; //if computer wins increment the score
	}
	if((box[0][2]==box[1][1] && box[1][1]==box[2][0])){
		if(box[0][2]=='X')
			userCount++; //if computer wins increment the score
		if(box[0][2]=='O')
			compCount++; //if computer wins increment the score
	}
}
void _3dgame::userTurn(){
	int i=0, j=0, x; //counter and integers to store moves
	bool bu=false; //default checking values
	player=true; computer=false; //set the values such that next turn will be computer
	_3dgame::AskBox();  //calling function to enter the box number
	x=game::playMove(); //calling function to Enter the move
	while(!bu){
		bu=_3dgame::moveUsed(x); //calling the function to play the move
		if(bu==0){ //if place is used then do it again
			_3dgame::_3dgameBoard();
			cout<<"\nAlready Used ! Select Different Box\n";
			_3dgame::AskBox();
			cout<<"\nEnter the Number:";
			cin>>x;
		}
	}
	userCount=0; compCount=0;
	_3dgame::check3DWin(); //check if User Wins
	_3dgame::_3dgameBoard();
	bAllUsed=_3dgame::allUsed(); // check if all boxes Used
	if(bAllUsed==1){ /* If all boxes used then game is tie*/
		stopGame=true; //if everything used then stop game
		player=false; computer=false; //reset the turn so game stops
		//Display the final results
		if(winner==1) cout<<"\n\nYou Won!\n";
		if(winner==-1) cout<<"\n\nComputer won!\n";
		if(winner==2) cout<<"\n\nGame Tie!\n";
	}
}
void _3dgame::compTurn(){
	irand=(rand()%9)+1; //storing random number to play move
	int i=0, j=0, count=1, irbox; //counter and integer for loops
	irbox=(rand()%3)+1; //rand number for box
	ibox=irbox;
	bool bfound=false, win=false, bu=false; //Default values for checking
	computer=true; player=false;  //set the values such that next turn will be User
	while(!bu){
		bu=_3dgame::moveUsed(irand); //using the irand to play 
		if(!bu){//if not played then call it again
			irbox=(rand()%3)+1;//set new random parameters
			ibox=irbox;
			irand=(rand()%9)+1;
		}
	}
	userCount=0; compCount=0;
	_3dgame::check3DWin(); //check if User Wins
	_3dgame::_3dgameBoard();
	bAllUsed=_3dgame::allUsed(); // check if all boxes Used
	if(bAllUsed==1){ /* If all boxes used then game is tie*/
		stopGame=true;//if all used then stop game
		player=false; computer=false; //set the flags so the game exits
		_3dgame::_3dgameBoard(); //display final results
		if(winner==1) cout<<"\n\nYou Won!\n";
		if(winner==-1) cout<<"\n\nComputer won!\n";
		if(winner==2) cout<<"\n\nGame Tie!\n";
	}
}
bool _3dgame::allUsed(){
	int i=0, j=0;
	bool used; //flag for used boxes
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if((box[i][j]=='X' || box[i][j]=='O') &&
				(box1[i][j]=='X' || box1[i][j]=='O') &&
				(box2[i][j]=='X' || box2[i][j]=='O')){ //checking all the boxes are used or not
				 used=true;
			}
			else{
				used=false; //if not then return false
				return false;
			}
		}
	}
	if(userCount>compCount){
		winner=1; //set the user as winner
	}
	else if(compCount>userCount){
		winner=-1; //set the computer as winner
	}
	else{
		winner=2; //set the value for tie
	}
	return used; //if boxes are used return true
}
void _3dgame::randomSelection(){
	int r1;
	srand(time(0));
	r1=rand()%2; //seeking random number 1 or 2
	if(r1==0){ //if 0 then user goes first
		player=false; computer=true;  //setting the values such that user turn first
		cout<<"\nYou go first!\n";
	}
	else{//if 1 then computer goes first
		player=true; computer=false;  //setting the values such that computer goes first
		cout<<"\nComputer goes first!\n";
	}
	system("pause");
}
void _3dgame::initialize3DGameBoard(){
	game::initializeGameBoard(); //use the base class function
	//Initialize Game Board 2 Matrix With Default Values
	box1[0][0]='1'; box1[0][1]='2'; box1[0][2]='3';
	box1[1][0]='4'; box1[1][1]='5'; box1[1][2]='6';
	box1[2][0]='7'; box1[2][1]='8'; box1[2][2]='9';
	
	//Initialize Game Board 1 Matrix With Default Values
	box2[0][0]='1'; box2[0][1]='2'; box2[0][2]='3';
	box2[1][0]='4'; box2[1][1]='5'; box2[1][2]='6';
	box2[2][0]='7'; box2[2][1]='8'; box2[2][2]='9';
	
	userCount=0; compCount=0; // set the score to zero
	stopGame=false; //set the game to play
	winner=0;       //set the winner flag off
}
void _3dgame::_3dgameBoard(){
	game::gameBoard(); //calling the base function to print first box then printing rest
	cout<<"\n\t\tBox2->  ";
	        cout<<"    |     |   "<<endl<<"\t\t\t";
			cout<<" "<<box1[0][0]<<"  |  "<<box1[0][1]<<"  |  "<<box1[0][2]<<endl<<"\t\t\t";
			cout<<"____|_____|____"<<endl<<"\t\t\t";
			cout<<"    |     |   "<<endl<<"\t\t\t";
			cout<<" "<<box1[1][0]<<"  |  "<<box1[1][1]<<"  |  "<<box1[1][2]<<endl<<"\t\t\t";
			cout<<"____|_____|____"<<endl<<"\t\t\t";
			cout<<"    |     |   "<<endl<<"\t\t\t";
			cout<<" "<<box1[2][0]<<"  |  "<<box1[2][1]<<"  |  "<<box1[2][2]<<endl<<"\t\t\t";
			cout<<"    |     |   "<<endl<<"\t\t\t";
	cout<<"\n\t\t\tBox3->  ";
			cout<<"    |     |   "<<endl<<"\t\t\t\t";
			cout<<" "<<box2[0][0]<<"  |  "<<box2[0][1]<<"  |  "<<box2[0][2]<<endl<<"\t\t\t\t";
			cout<<"____|_____|____"<<endl<<"\t\t\t\t";
			cout<<"    |     |    "<<endl<<"\t\t\t\t";
			cout<<" "<<box2[1][0]<<"  |  "<<box2[1][1]<<"  |  "<<box2[1][2]<<endl<<"\t\t\t\t";
			cout<<"____|_____|____"<<endl<<"\t\t\t\t";
			cout<<"    |     |    "<<endl<<"\t\t\t\t";
			cout<<" "<<box2[2][0]<<"  |  "<<box2[2][1]<<"  |  "<<box2[2][2]<<endl<<"\t\t\t\t";
			cout<<"    |     |    "<<endl<<"\t\t\t\t";
	cout<<"\n\n";
	cout<<"\nPlayer Points: "<<userCount<<"\tComputer Points: "<<compCount<<endl; //Score Board
}
void _3dgame::AskBox(){
	bool done=false;
	string str1="Invalid Input";
	do{
		//same rules of try catch as in the playmove function 
		//string error and range error
		try{
			cout<<"\nEnter the Box Number:";
			cin>>ibox; //update the box number to play in that box
			if(!cin)
				throw str1; //throw string if wrong with cin
			if(ibox<1 || ibox>3)
				throw ibox; //throw number if out of range
			done=true;
		}
		catch(int){
			cout<<"\nError 100: Out of Range\n";
			cout<<"Try Again\n";
		}
		catch(string str1){
			cout<<"\nError 101: "<<str1<<endl;
			cout<<"Try Again\n";
			cin.clear();
			cin.ignore(100, '\n');
		}
	}while(!done);
}
bool _3dgame::moveUsed(int x){
	int i=0, j=0, count=1;
	bool bu=true; //flag for move played
		for(i=0; i<3; i++){
			for(j=0; j<3; j++){
				if(count==x){ /* If box found then switch to appropriate box number*/
					switch(ibox){
						case 1:
							if(box[i][j]=='X' || box[i][j]=='O'){
								bu=false; //if used return false
							}
							else{
								if(player==true && computer==false){
									box[i][j]='X'; //playing the user Move
									return true; //set checking value true to exit loop
								}
								if(player==false && computer==true){
									box[i][j]='O'; //playing the computer Move
									return true; //set checking value true to exit loop
								}
							}
							break;
						case 2:
							if(box1[i][j]=='X' || box1[i][j]=='O'){
								bu=false; //if used return false
							}
							else{
								if(player==true && computer==false){
									box1[i][j]='X'; //playing the user Move
									return true; //set checking value true to exit loop
								}
								if(player==false && computer==true){
									box1[i][j]='O'; //playing the computer Move
									return true; //set checking value true to exit loop
								}
							}
							break;
						case 3:
							if(box2[i][j]=='X' || box2[i][j]=='O'){
								bu=false; //if used return false
							}
							else{
								if(player==true && computer==false){
									box2[i][j]='X'; //playing the user Move
									return true; //set checking value true to exit loop
								}
								if(player==false && computer==true){
									box2[i][j]='O'; //playing the computer Move
									return true; //set checking value true to exit loop
								}
							}
							break;
					}
				}
				count++;
			}
		}
	return bu;
}
void _3dgame::check3DWin(){
	int i=0, j=0;
	game::checkWin(); // use of inheritance calling the base class function to check first box 
	//then checking all the conditions for 2d and 3d wins and incrementing appropriate counter
	
	//checking the second box
	for(i=0; i<3; i++){
		if(box1[i][0]==box1[i][1] && box1[i][1]==box1[i][2]){ //checking all the horizontal rows
			if(box1[i][0]=='X')
				userCount++;
			if(box1[i][0]=='O')
				compCount++;
		}
	}
	for(i=0; i<3; i++){
		if(box1[0][i]==box1[1][i] && box1[1][i]==box1[2][i]){ //checking all vertical coloumn
			if(box1[0][i]=='X')
				userCount++; 
			if(box1[0][i]=='O')
				compCount++;
		}
	}
	if((box1[0][0]==box1[1][1] && box1[1][1]==box1[2][2])){ //checkng diagonal
			if(box1[0][0]=='X')
				userCount++; 
			if(box1[0][0]=='O')
				compCount++;
	}
	if((box1[0][2]==box1[1][1] && box1[1][1]==box1[2][0])){ //checking diagonal
			if(box1[0][2]=='X')
				userCount++; 
			if(box1[0][2]=='O')
				compCount++; 
	}
	
	//checking the third box
	for(i=0; i<3; i++){
		if(box2[i][0]==box2[i][1] && box2[i][1]==box2[i][2]){ //checking all the horizontal rows
			if(box2[i][0]=='X')
				userCount++; 
			if(box2[i][0]=='O')
				compCount++;
		}
	}
	for(i=0; i<3; i++){
		if(box2[0][i]==box2[1][i] && box2[1][i]==box2[2][i]){ //checking all the vertical coloumns 
			if(box2[0][i]=='X')
				userCount++; 
			if(box2[0][i]=='O')
				compCount++;
		}
	}
	if((box2[0][0]==box2[1][1] && box2[1][1]==box2[2][2])){ //checking diagonal
			if(box2[0][0]=='X')
				userCount++; 
			if(box2[0][0]=='O')
				compCount++;
	}
	if((box2[0][2]==box2[1][1] && box2[1][1]==box2[2][0])){ //checking diagonal
			if(box2[0][2]=='X')
				userCount++; 
			if(box2[0][2]=='O')
				compCount++; 
	}
	//checking all the vertial 3D coloumn
	for(i=0; i<3; i++){
		for(j=0; j<3; j++){
			if((box[i][j]=='X' || box[i][j]=='O') && 
				(box[i][j]==box1[i][j] && box1[i][j]==box2[i][j])){
				if(box[i][j]=='X')
					userCount++; 
				if(box[i][j]=='O')
					compCount++;
			}
		}
		//checking all the 3D Diagonal
		if(box[0][i]==box1[1][i] && box1[1][i]==box2[2][i]){
			if(box[0][i]=='X')
				userCount++; 
			if(box[0][i]=='O')
				compCount++;
		}
		if(box[2][i]==box1[1][i] && box1[1][i]==box2[0][i]){
			if(box[2][i]=='X')
				userCount++; 
			if(box[2][i]=='O')
				compCount++;
		}
		if(box[i][0]==box1[i][1] && box1[i][1]==box2[i][2]){
			if(box[i][0]=='X')
				userCount++; 
			if(box[i][0]=='O')
				compCount++;
		}
		if(box[i][2]==box1[i][1] && box1[i][1]==box2[i][0]){
			if(box[i][2]=='X')
				userCount++; 
			if(box[i][2]=='O')
				compCount++;
		}
	}
	//checking all the 3D Cross Diagonals
	if((box[0][0]==box1[1][1] && box1[1][1]==box2[2][2])){
			if(box[0][0]=='X')
				userCount++; 
			if(box[0][0]=='O')
				compCount++;
		}
	if((box[0][2]==box1[1][1] && box1[1][1]==box2[2][0])){
			if(box[0][2]=='X')
				userCount++; 
			if(box[0][2]=='O')
				compCount++;
		}
	if((box[2][0]==box1[1][1] && box1[1][1]==box2[0][2])){
			if(box[2][0]=='X')
				userCount++; 
			if(box[2][0]=='O')
				compCount++;
	}
	if((box[2][2]==box1[1][1] && box1[1][1]==box2[0][0])){
			if(box[2][2]=='X')
				userCount++; 
			if(box[2][2]=='O')
				compCount++;
		}
}
int main(){
	_3dgame g; //making an object
	g.initialize3DGameBoard(); //initializing game
	//clean output format for Game Rules and Instructions
	cout<<"\n\n**********************************WELCOME TO 3D TIC-TAC-TOE**********************************\n";
	cout<<"******************************************GAME RULES******************************************\n";
	cout<<"\n\t1. Point System (Winner if scores more points)\n";
	cout<<"\t2. Randomly Descision Made Who go First\n";
	cout<<"\t3. First select the Box Number then select the corresponding number to play your Move\n";
	cout<<"\t4. Imagine that each box is the layer on top of each other\n";
	cout<<"\t5. Player(X)\t\tComputer(O)\n";
	cout<<"Ready for Game!! \n";
	system("pause");
	g._3dgameBoard(); //display the board
	g.randomSelection(); //random selection who goes first
	g._3dgameBoard(); //display the board then start game
	while(!g.stopGame){
		//play until all box used up
		if(g.player==false && g.computer==true){
			//checking if user turn condition met then play user turn
			g.userTurn();
		}
		if(g.player==true && g.computer==false){
			//checking if computer turn condition met then play computer turn
			g.compTurn();
		}
	}
	return 0;
}
