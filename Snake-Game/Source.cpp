/***********************************************************************************************
Name: CanerBaba25
Date: April 24, 2019
File name: Array game
Description: There are 6 levels that user need to pass.
***********************************************************************************************/

#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include <MMSystem.h>
#include <thread>
#include <stdio.h>


using namespace std;

//Board Class
class board {
public:
	int width, height, x_board, y_board, color_board;
	// width, height of the board

	void draw_board(); // draw the board function
	void set_value(); // set value of width, height, x,y coordinate
	void print_instruction(); // show the message to instruct the game
};
//Snake Class
class snake {
public:
	int x_snake[50], y_snake[50], length = 1, speed = 150, x_tail, y_tail;
	// the value of snake's stuff
	string direction;
	// the direction of snake moving
	void move_snake();
	// change the position of snake
	void clear_snake();
	// clear snake
	void print_snake();
	//print snake
	void longer_snake();
	// add the length of snake when eat bait
	void get_direction();
	// get the input of keyboard
	void update_snake();
	// the function contain above functions
};
//Bait Class
class bait {
public:
	int number_of_bait = 0, x_bait, y_bait;
	// value of bait stuff
	void make_bait();
	// random a bait
	void eat_bait();
	// check if snake eat bait
};
//Dead Zone Class
class dead_Zone {
public:
	int  x_dead[2000], y_dead[2000], number_of_dead_point = 0;
	// the array contain dead points
	void vertical_dead_line(int start_y, int end_y, int x, int rotate_y_up = 0, int rotate_y_down = 0);
	// draw the vertical line
	void horizontal_dead_line(int start_x, int end_x, int y, int rotate_x_left = 0, int rotate_x_right = 0);
	// draw the horizontal line
};
//Time Class
class time_play {
public:
	int time_for_level[7] = { 0,35,40,50,60,90,100 };
	// time for each level
	int count_var, copy_time;
	// variable to calculate stuff
	void count_time();
	// time count
	void play_more();
	// ask user play more
};
//Level Class
class level {
public:
	int point_pass_level[7] = { 0,11,11,11,11,11,11 }, now_level = 1;
	// point need to pass a level
	boolean is_next_level = false, play_more = true;
	// the condition if user is loose
	void run_level();
	// run level
	void level_1();
	void level_2();
	void level_3();
	void level_4();
	void level_5();
	void level_6();
	void next_level();
	// tranfer to next level
	void wait_to_transfer();
	// transfer time
};
//Loose Contion Class
class is_loose {
public:
	bool loose = false;
	// LOOSING CONDITION
	void is_hit_board();
	void is_hit_dead_zone();
	void is_hit_itself();
	void is_loose_all();
	void is_end_time();
	// WIN CONDITION
	void won_condition();
};
//Score Bar Class
class score_bar {
public:
	// RESET SCORE BAR
	void reset_score_bar();
	// UPDATE SCORE BAR
	void draw_score_bar();
};



/*Declaring The Class For Each Object*/ 
board my_board;
snake my_snake;
level my_level;
dead_Zone my_dead_zone;
time_play my_time_play;
is_loose my_is_loose;
bait my_bait;
score_bar my_score_bar;



void resizeConsole(int width, int height);
void gotoxy(short x, short y);
void textcolor(int x);
int random(int min, int max);
void reset_all_value();
void play_game();
void play_music();



//Printing Animation
void print_str(int x, int y, string aa) {

	for (int i = 0; i < aa.length(); i++) {
		gotoxy(x + i, y);
		cout << aa[i];
		Sleep(1000);
	}

}
//Play Music
void play_music()
{
	/*int a; // random music song
	char b[115]; // contain name of music file
	while (my_is_loose.loose == false) {
		// play music
		a = random(0, 12);
		sprintf_s(b, "videoplayback.wav", a);
		PlaySound(b, NULL, SND_SYNC);
	}*/


}
//Start Game
void play_game()
{
	system("cls");
	reset_all_value();
	while (my_is_loose.loose == false && my_level.now_level < 7) {
		// transfer if pass level
		my_level.wait_to_transfer();
		// draw a board
		my_board.draw_board();
		// reset score bar
		my_score_bar.reset_score_bar();
		//run now level
		my_level.run_level();
		// reset pass level condition
		my_level.is_next_level = false;
		// make a bait
		my_bait.make_bait();
		while (my_is_loose.loose == false && my_level.is_next_level == false) {
			// check if pass level
			my_level.next_level();
			// make bait
			if (my_bait.number_of_bait == 0) my_bait.make_bait();
			// count play time
			my_time_play.count_time();
			// update snake
			my_snake.update_snake();
			// check loose condition
			my_is_loose.is_loose_all();
			// eat bait function
			my_bait.eat_bait();
			// Delay program
			Sleep(my_snake.speed);
		}
	}
	// check if user won
	if (my_level.now_level == 7) my_is_loose.won_condition();
	// run if user loose
	if (my_is_loose.loose == true) my_time_play.play_more();


}
//Main Function
int main() {

	// thread 1: play game
	std::thread t1(&play_game);
	// thread 2: play music
	//std::thread t2(&play_music);
	t1.join();
	//t2.detach();


}



/*DEAD ZONE*/



//Making Vertical Lines And Delacring The Dead Line For The Vertical Line
void dead_Zone::vertical_dead_line(int start_y, int end_y, int x, int rotate_y_up, int rotate_y_down) {

	for (int i = my_board.height * start_y / 24 - rotate_y_up; i < my_board.height * end_y / 24 + rotate_y_down; i++) {
		// print the dead point
		gotoxy(my_board.width*x / 24 + my_board.x_board, i + my_board.y_board);
		cout << (char)219;

		// add dead points to an array
		my_dead_zone.x_dead[my_dead_zone.number_of_dead_point] = my_board.width * x / 24 + my_board.x_board;
		my_dead_zone.y_dead[my_dead_zone.number_of_dead_point] = i + my_board.y_board;
		my_dead_zone.number_of_dead_point++;
	}
};
//Making Horizontal Lines And Delacring The Dead Line For The Horizontal Line
void dead_Zone::horizontal_dead_line(int start_x, int end_x, int y, int rotate_x_left, int rotate_x_right) {


	for (int i = my_board.width * start_x / 24 - rotate_x_left; i < my_board.width * end_x / 24 + rotate_x_right; i++) {
		// print the dead point
		gotoxy(i + my_board.x_board, my_board.height *y / 24 + my_board.y_board);
		cout << (char)254;
		// add dead points to an array
		my_dead_zone.x_dead[my_dead_zone.number_of_dead_point] = i + my_board.x_board;
		my_dead_zone.y_dead[my_dead_zone.number_of_dead_point] = (int)(my_board.height * y / 24 + my_board.y_board);
		my_dead_zone.number_of_dead_point++;
	}

};



/*END: DEAD ZONE*/



//Reset Score Bar
void score_bar::reset_score_bar() {
	// print score bar
	gotoxy(60, 35);
	for (int i = 0; i < 40; i++)
	{
		textcolor(7);
		cout << (char)219;
		textcolor(my_level.now_level);
	}

}
//Score Bar
void score_bar::draw_score_bar() {
	// update score bar
	gotoxy(60, 35);
	for (int i = 0; i < my_snake.length * 4; i++)
	{
		textcolor(2);
		cout << (char)219;
		textcolor(my_level.now_level);
	}
}
//Run Level
void level::run_level() {
	// run now level
	if (my_level.now_level == 1) level_1();
	if (my_level.now_level == 2) level_2();
	if (my_level.now_level == 3) level_3();
	if (my_level.now_level == 4) level_4();
	if (my_level.now_level == 5) level_5();
	if (my_level.now_level == 6) level_6();
};
//Level 1
void level::level_1() {
	// initialization of values for level 1
	my_snake.speed = 120;
	my_time_play.copy_time = my_time_play.time_for_level[1];
	my_snake.x_snake[0] = 50;
	my_snake.y_snake[0] = 10;
};
//Level 2
void level::level_2() {
	// initialization of values for level 2
	my_snake.speed = 120;
	my_dead_zone.number_of_dead_point = 0;
	my_dead_zone.horizontal_dead_line(6, 24, 8);
	my_dead_zone.horizontal_dead_line(0, 16, 16);
	my_time_play.copy_time = my_time_play.time_for_level[2];
	my_snake.x_snake[0] = 45;
	my_snake.y_snake[0] = 18;
	my_snake.direction = "RIGHT";


};
//Level 3
void level::level_3() {
	// initialization of values for level 3
	my_snake.speed = 120;
	my_dead_zone.number_of_dead_point = 0;
	my_time_play.copy_time = my_time_play.time_for_level[3];
	my_dead_zone.vertical_dead_line(6, 12, 18, -1);
	my_dead_zone.vertical_dead_line(6, 18, 12, 0, 1);
	my_dead_zone.vertical_dead_line(18, 24, 6, 0, 1);
	my_dead_zone.vertical_dead_line(18, 24, 18, 0, 1);

	//horizontal lines
	my_dead_zone.horizontal_dead_line(6, 18, 6, 0, 1);
	my_dead_zone.horizontal_dead_line(0, 6, 12, -1, 0);
	my_dead_zone.horizontal_dead_line(6, 12, 18, 0, 1);
	my_snake.x_snake[0] = 45;
	my_snake.y_snake[0] = 20;
	my_snake.direction = "RIGHT";
	//vertical lines

};
//Level 4
void level::level_4() {
	// initialization of values for level 4
	my_snake.speed = 120;
	my_dead_zone.number_of_dead_point = 0;
	my_time_play.copy_time = my_time_play.time_for_level[4];
	my_snake.x_snake[0] = 75;
	my_snake.y_snake[0] = 26;
	my_snake.direction = "RIGHT";
	//vertical lines

	my_dead_zone.vertical_dead_line(0, 6, 12, -1);
	my_dead_zone.vertical_dead_line(6, 12, 6);
	my_dead_zone.vertical_dead_line(12, 18, 12, -1);
	my_dead_zone.vertical_dead_line(6, 24, 18, 0, 1);
	my_dead_zone.vertical_dead_line(15, 24, 9, -1, 1);


	//horizontal lines
	my_dead_zone.horizontal_dead_line(6, 12, 6, 0, 1);
	my_dead_zone.horizontal_dead_line(6, 12, 12, 0, 1);
	my_dead_zone.horizontal_dead_line(0, 6, 18, -1);
	my_dead_zone.horizontal_dead_line(12, 18, 9);
	my_dead_zone.horizontal_dead_line(21, 24, 21);
	my_dead_zone.horizontal_dead_line(21, 24, 7);

};
//Level 5
void level::level_5() {
	// initialization of values for level 5
	my_snake.speed = 120;
	my_dead_zone.number_of_dead_point = 0;
	my_time_play.copy_time = my_time_play.time_for_level[5];
	my_snake.x_snake[0] = 68;
	my_snake.y_snake[0] = 20;
	my_snake.direction = "RIGHT";
	//vertical lines


	my_dead_zone.vertical_dead_line(5, 22, 2);
	my_dead_zone.vertical_dead_line(8, 23, 22);
	my_dead_zone.vertical_dead_line(8, 18, 4);
	my_dead_zone.vertical_dead_line(12, 19, 20);
	my_dead_zone.vertical_dead_line(12, 16, 6);
	//horizontal lines

	my_dead_zone.horizontal_dead_line(2, 24, 4);
	my_dead_zone.horizontal_dead_line(2, 22, 22);
	my_dead_zone.horizontal_dead_line(4, 22, 8);
	my_dead_zone.horizontal_dead_line(4, 20, 18);
	my_dead_zone.horizontal_dead_line(6, 20, 12);

};
//Level 6
void level::level_6() {
	// initialization of values for level 6
	my_snake.speed = 120;
	my_dead_zone.number_of_dead_point = 0;
	my_time_play.copy_time = my_time_play.time_for_level[6];
	my_snake.x_snake[0] = 50;
	my_snake.y_snake[0] = 16;
	my_snake.direction = "RIGHT";
	//vertical lines
	my_dead_zone.vertical_dead_line(1, 12, 12);
	my_dead_zone.vertical_dead_line(1, 6, 6);
	my_dead_zone.vertical_dead_line(3, 9, 9, 0, 1);
	my_dead_zone.vertical_dead_line(1, 6, 18);
	my_dead_zone.vertical_dead_line(6, 9, 21);
	my_dead_zone.vertical_dead_line(9, 12, 18);
	my_dead_zone.vertical_dead_line(3, 9, 15);
	my_dead_zone.vertical_dead_line(12, 21, 15);
	my_dead_zone.vertical_dead_line(18, 25, 18);
	my_dead_zone.vertical_dead_line(15, 18, 6);
	my_dead_zone.vertical_dead_line(15, 18, 12);
	my_dead_zone.vertical_dead_line(18, 24, 9, 0, 1);
	my_dead_zone.vertical_dead_line(19, 23, 21);
	my_dead_zone.vertical_dead_line(23, 24, 12, 0, 1);

	//horizontal lines
	my_dead_zone.horizontal_dead_line(3, 15, 12);
	my_dead_zone.horizontal_dead_line(3, 6, 6, 0, 1);
	my_dead_zone.horizontal_dead_line(0, 3, 3, -1);
	my_dead_zone.horizontal_dead_line(0, 9, 9, -1, 1);
	my_dead_zone.horizontal_dead_line(21, 24, 3, 0, 1);
	my_dead_zone.horizontal_dead_line(18, 21, 6);
	my_dead_zone.horizontal_dead_line(15, 18, 9);
	my_dead_zone.horizontal_dead_line(18, 24, 12, 0, 1);
	my_dead_zone.horizontal_dead_line(15, 21, 15, -1);
	my_dead_zone.horizontal_dead_line(0, 3, 15, -1);
	my_dead_zone.horizontal_dead_line(3, 12, 18, 0, 1);
	my_dead_zone.horizontal_dead_line(9, 12, 18);
	my_dead_zone.horizontal_dead_line(9, 12, 15, 0, 1);
	my_dead_zone.horizontal_dead_line(0, 6, 21, -1, 1);
	my_dead_zone.horizontal_dead_line(21, 24, 19, -1, 1);

};
//Next Level
void level::next_level() {
	// check if user pass level
	if (my_snake.length == my_level.point_pass_level[my_level.now_level]) {
		my_level.now_level++;
		my_time_play.copy_time = my_time_play.time_for_level[my_level.now_level];
		my_snake.length = 1;
		my_bait.number_of_bait = 0;
		my_level.is_next_level = true;
	}

}
//Transfering To Another Level
void level::wait_to_transfer() {
	// transfer if pass level
	if (my_level.now_level > 1) {
		system("cls");
		gotoxy(my_board.x_board + 10, my_board.y_board + 5);
		textcolor(2);
		cout << " Congratulation, you are one of the few people won level " << my_level.now_level - 1;
		gotoxy(my_board.x_board + 10, my_board.y_board + 6);
		textcolor(4);
		cout << "Be careful next level, try your best to win";
		textcolor(3);
		// wait for 5 seconds
		for (int i = 5; i > 0; i--) {
			gotoxy(my_board.x_board + 10, my_board.y_board + 7);
			cout << "Transfer in " << i << "...";
			Sleep(1000);
		}
	};

}
//Play More
void time_play::play_more() {
	system("cls");
	string more;
	cout << "Do you want to play more?";
	cout << "\n1. Insert 'yes' to play more";
	cout << "\n2. Insert 'no' to stop";
	while (more != "yes" && more != "no") {
		cout << "\nType your choice:";
		cin >> more;
	}
	if (more == "yes") play_game();
	if (more == "no") {
		system("cls");
		cout << "Thank you to play game, see you next time";
		Sleep(3000);
	}
}
//User Hit The Box ?
void is_loose::is_hit_board() {
	if (my_snake.x_snake[0]<my_board.x_board + 1 || my_snake.x_snake[0] > my_board.x_board + my_board.width ||
		my_snake.y_snake[0] < my_board.y_board + 1 || my_snake.y_snake[0] > my_board.y_board + my_board.height
		)
		my_is_loose.loose = true;
};
//User Hit The Walls
void is_loose::is_hit_dead_zone() {
	// dead area condition
	for (int i = 0; i < my_dead_zone.number_of_dead_point; i++) {
		if (my_snake.x_snake[0] == my_dead_zone.x_dead[i]) {
			if (my_snake.y_snake[0] == my_dead_zone.y_dead[i]) {
				loose = true;
			}
		}
	}

};
//User Hit The Snake's Tail ?
void is_loose::is_hit_itself() {
	for (int i = 1; i < my_snake.length; i++) {
		if (my_snake.x_snake[0] == my_snake.x_snake[i]) {
			if (my_snake.y_snake[0] == my_snake.y_snake[i]) my_is_loose.loose = true;
		}
	}
};
//Win Condtion
void is_loose::won_condition() {
	system("cls");
	textcolor(2);
	string message = "\nWow, surpised! You are super good player! \n Thank you for playing my game, we will update more level to play\nAcess nsnhatlong.top to see my website\n";
	for (int i = 0; i < message.length(); i++) {
		cout << message[i];
		Sleep(50);
	}
	Sleep(3000);
}
//Time End ?
void is_loose::is_end_time() {
	if (my_time_play.copy_time == 0) {
		cout << "Time is up. You lost.\n";
		Sleep(3000);
		my_is_loose.loose = true;
	}
}
//Lose ?
void is_loose::is_loose_all() {
	my_is_loose.is_hit_board();
	my_is_loose.is_hit_dead_zone();
	my_is_loose.is_hit_itself();
	my_is_loose.is_end_time();
};
//Time Counter
void time_play::count_time() {
	my_time_play.count_var += my_snake.speed;
	if (my_time_play.count_var > 1000) {
		my_time_play.copy_time--;
		my_time_play.count_var = 0;
	}
	gotoxy(105, 35);
	textcolor(6);
	cout << "Time: " << my_time_play.copy_time << "s  \t";
	textcolor(my_level.now_level);
};




/*BAIT*/


//Makes Bait
void bait::make_bait() {
	my_bait.x_bait = random(my_board.x_board + 1, my_board.x_board + my_board.width);
	my_bait.y_bait = random(my_board.y_board + 1, my_board.y_board + my_board.height);

	for (int i = 0; i < my_dead_zone.number_of_dead_point; i++) {
		if (my_bait.x_bait == my_dead_zone.x_dead[i]) {
			if (my_bait.y_bait == my_dead_zone.y_dead[i]) {
				make_bait();
			}
		}
	}
	my_bait.number_of_bait = 1;
	gotoxy(my_bait.x_bait, my_bait.y_bait);
	textcolor(3);
	cout << (char)219;
	textcolor(my_level.now_level);


};
//Eat Bait
void bait::eat_bait() {
	if (my_snake.x_snake[0] == my_bait.x_bait && my_snake.y_snake[0] == my_bait.y_bait) {
		/*Beep(350, 220);*/
		my_score_bar.draw_score_bar();
		my_snake.x_snake[my_snake.length] = my_bait.x_bait;
		my_snake.y_snake[my_snake.length] = my_bait.y_bait;
		my_snake.length++;
		my_bait.number_of_bait = 0;
		my_bait.make_bait();

	}

};



/*END-BAIT*/



//Changes Size Of The Screen
void resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
//Sets Color For Text
void textcolor(int x)
{
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}
//Gotoxy, Rows And Colums
void gotoxy(short x, short y)
{
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = { x - 1,y - 1 };
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}
//Clear Screen
void clear_screen()
{
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X = 0;
	Position.Y = 0;
	SetConsoleCursorPosition(hOut, Position);
}
//Random Number 
int random(int min, int max) {
	return rand() % (max - min) + min + 1;
}




/*BOARD*/


//Set value
void board::set_value() {
	resizeConsole(1300, 690);
	width = 81;
	height = 25;
	x_board = 38;
	y_board = 5;
	color_board = my_level.now_level;
}
//Draw Board
void board::draw_board() {
	my_board.set_value();
	// vertical 219, 254
	textcolor(my_level.now_level);
	gotoxy(x_board, y_board);
	// draw top line
	for (int i = 0; i < width + 2; i++) cout << (char)254;
	// draw middle line
	for (int i = 1; i <= height; i++) {
		gotoxy(x_board, y_board + i);
		cout << (char)219;
		for (int j = 0; j < width; j++) cout << " ";
		cout << (char)219;
	}
	// draw bottom line
	gotoxy(x_board, y_board + height + 1);
	for (int i = 0; i < width + 2; i++) cout << (char)254;

	// for (int i = 0; i < 256; i++) cout << i << (char)i << endl;
	print_instruction();
}
//Print Instruction
void board::print_instruction() {

	gotoxy(45, 3);
	textcolor(6);
	cout << "Press 'SHIFT' to boost your speed, press 'SPACE' to reset your speed";
	textcolor(my_level.now_level);
}


/*END - BOARD*/



/*SNAKE*/


//Keyboard
void snake::get_direction() {

	if (GetAsyncKeyState(VK_UP)) {

		if (direction == "DOWN" && x_snake[0] == x_snake[1]) direction = "DOWN";
		else direction = "UP";
	}
	else if (GetAsyncKeyState(VK_DOWN)) {

		if (direction == "UP" && x_snake[0] == x_snake[1]) direction = "UP";
		else direction = "DOWN";

	}
	else if (GetAsyncKeyState(VK_LEFT)) {

		if (direction == "RIGHT" && y_snake[0] == y_snake[1]) direction = "RIGHT";
		else direction = "LEFT";

	}
	else if (GetAsyncKeyState(VK_RIGHT)) {

		if (direction == "LEFT" && y_snake[0] == y_snake[1]) direction = "LEFT";
		else direction = "RIGHT";
	}

	if (GetAsyncKeyState(VK_SHIFT)) {
		my_snake.speed = 30;
	}

	if (GetAsyncKeyState(VK_SPACE)) {
		my_snake.speed = 120;
	}


};
//Clear Snake
void snake::clear_snake() {
	for (int i = 0; i < length; i++) {
		gotoxy(x_snake[i], y_snake[i]);
		textcolor(0);
		cout << (char)254;
	}

};
//Prints Snake
void snake::print_snake() {
	for (int i = 0; i < length; i++) {
		gotoxy(x_snake[i], y_snake[i]);
		textcolor(my_level.now_level + 1);
		cout << (char)254;
		textcolor(my_level.now_level);
	}
};
//Snake Movement
void snake::move_snake() {
	/*clear_snake();*/
	x_tail = x_snake[length - 1];
	y_tail = y_snake[length - 1];
	for (int i = length - 1; i > 0; i--) {
		x_snake[i] = x_snake[i - 1];
		y_snake[i] = y_snake[i - 1];
	}
	if (direction == "UP")  	y_snake[0]--;
	if (direction == "DOWN")  	y_snake[0]++;
	if (direction == "RIGHT") 	x_snake[0]++;
	if (direction == "LEFT") 	x_snake[0]--;

};
//Sanke Size
void snake::longer_snake() {
	if (my_bait.number_of_bait == 0) length++;
};
//Update Snake
void snake::update_snake() {
	// update if snake has any change.
	get_direction();
	clear_snake();
	move_snake();
	longer_snake();
	print_snake();

}


/*END SNAKE*/



/*Reset Snake Value*/
void reset_all_value() {
	// snake length
	my_snake.length = 1;
	// reset to level 1
	my_level.now_level = 1;
	// move to right
	my_snake.direction = "RIGHT";
	// no bait
	my_bait.number_of_bait = 0;
	// draw a board
	my_board.draw_board();
	// reset loose value
	my_is_loose.loose = false;
	// reset dead point array.
	my_dead_zone.number_of_dead_point = 0;
}
