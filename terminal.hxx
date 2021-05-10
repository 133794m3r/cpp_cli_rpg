/*
* Basic Terminal Setup stuff && Input Validation
* By Macarthur Inbody <admin-contact@transcendental.us> 2020
* Licensed AGPLv3
*/
#ifndef TERMINAL_SETUP_
#define TERMINAL_SETUP_
#include <limits>

/**
 * Moves cursor to specified line(up from current) and clears it all.
 * @param lines_up How many lines to go up.
 */
void move_and_clear_up(unsigned int lines_up){
	printf("\x1b[%dF\x1b[0J", lines_up);
}

/**
 * Moves and clears all lines from this specific one down.
 * @param line The line to move to.
 */
void move_and_clear(unsigned short line){
	printf("\x1b[%dH\x1b[0J",line);
}

void clear_current_line(){
	printf("\x1b[2K");
}
void clear_lines(unsigned short start_line, unsigned short lines){
	printf("\x1b[%d;1H",start_line);
	for(unsigned short i=0;i<=lines;i++){
		fputs("\x1b[2K",stdout);
		fputs("\x1b[1B",stdout);
	}
	printf("\x1b[%d;1H",start_line);
}

#ifdef _WIN32
//what do you know more BS windows garbage.
#include <windows.h>
		//windows has the system pause command.
		void pause(){
			system("pause");
			move_and_clear_up(1);
		}
		//complained that I wasn't capturing the output. So this is just here 
		// for that. Also WINBOOL isn't a type anymore. Still only going to be
		// 1 byte of pointless space and 1 global.
		bool __unused_test = SetConsoleMode(GetStdHandle(static_cast<DWORD>(-11)), 7);

#else
	//all other devices I have use to the crappy get() version but it works.
	int pause(){
		//clear the rest of cin.
		std::cout << "press enter/return key to continue... ";
		std::cin.sync();
		//this wasn't needed
//		std::cin.get(tmp,2,'\n');
		//get a single character
		std::cin.get();
		//ignore the next one
//		std::cin.ignore(1);
		//clear it
		std::cin.clear();
		//move the terminal up a line.
		move_and_clear_up(1);
		return 0;
	}
#endif //_WIN32

#include <limits>
#include <cstdio>

//text styles.
enum TEXT_STYLES{RESET ,BOLD,DIM,ITALIC,UNDERLINE,REVERSED,DOUBLE_UNDERLINE=21,UN_BOLD=22,UN_DIM=22,UN_ITALIC,UN_UNDERLINE,UN_REVERSED=27};
//the colors.
enum TEXT_COLORS{RESET_COLOR,
	//foreground colors.
	BLACK_TXT = 30,RED_TXT,GREEN_TXT,YELLOW_TXT,BLUE_TXT,MAGENTA_TXT,CYAN_TXT,WHITE_TXT,
	//"bright" variants
	GRAY_TXT=90,BRIGHT_RED_TXT, BRIGHT_GREEN_TXT, BRIGHT_YELLOW_TXT, BRIGHT_BLUE_TXT, BRIGHT_MAGENTA_TXT, BRIGHT_CYAN_TXT, BRIGHT_WHITE_TXT,
	//background colors.
	BLACK_BG = 40,RED_BG,GREEN_BG,YELLOW_BG,BLUE_BG,MAGENTA_BG,CYAN_BG,WHITE_BG,
	//"bright" variants
	GRAY_BG = 100, BRIGHT_RED_BG, BRIGHT_GREEN_BG, BRIGHT_YELLOW_BG, BRIGHT_BLUE_BG, BRIGHT_MAGENTA_BG, BRIGHT_CYAN_BG, BRIGHT_WHITE_BG
};

//move terminal cursor to the top of the screen and clear it
void clear_and_move_top(){
	printf("\x1b[1H\x1b[0J");
}

//move the cursor to the specified row and column.
void move_cursor(unsigned int row, unsigned int column=1){
	printf("\x1b[%d;%dH",row,column);
}

#ifdef __cplusplus
//to make it still work as a C style header. I'll have a version for C eventually.
template <typename T> int proper_input(T &variable, std::string prefix){
	/* I'm checking to see if the return code is set to anything.
	* if it fails to coerce the input into the type that's passed
	* then I'll negate the response code so that it'll loop forever.
	* So if it can't convert the input into the type that's needed it'll fail
	* thus it'll continue the loop.
	*/
	while(true){
		//try to put it into the variable
		std::cin >> variable;
		//check that we didn't just get an EOF
		if(std::cin.eof()){
			//if we did construct a default type
			variable = T();
			//clear cin
			std::cin.clear();
			//return status of -1
			return -1;
		}
		//if we had an error
		else if(std::cin.fail()){
			//tell them that the input is invalid.
			std::cout << "You have entered invalid input please try again." << std::endl;
			//make sure to clear the thing
			std::cin.clear();
			//ignore everything
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			//clear it again just in case
			std::cin.clear();
			//prompt them to press enter not using the pause function 
			// since I can't rely on it to work here.
			std::cout << "press enter/return key to continue... ";
			//get a single character
			std::getchar();
			//clear the buffer
			std::cin.clear();
			//move the lines up
			move_and_clear_up(3);
			//show the message again
			std::cout << "\x1b[1m" << prefix << "\x1b[22m: ";
		}
		else{
			//we succeeded tim to leave it
			break;
		}
	}
	//ignore whatever else in the buffer.
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	//we finished it properly.
	return 0;
}

/**
 * Checks that hte user's input is a valid one within the options.
 *
 * @param min Lowest possible
 * @param max Highest possible
 * @param prefix Prefix message to show before player input.
 * @return The option that they chose.
 */
unsigned int valid_option(unsigned int min=1,unsigned int max=1,const std::string&& prefix="Selection"){
	unsigned int option;
	//infinite loop is best way to enforce the options.
	int res;
	//this way it can be called with a single argument
	if(max < min)
		std::swap(min,max);
	//infinite loop until it's good
	while(true) {
		res = proper_input(option,prefix);
		//-1 means EOF was noticed
		if(res == -1)
			//so die
			exit(1);
		//if their option is valid
		if(option >= min && option <= max)
			break;
		//otherwise tell them the valid range
		std::cout << "Enter valid option from " << min << " to " << max << std::endl;
		//make sure they know this
		pause();
		move_and_clear_up(2);
		//show the prefix message
		std::cout << "\x1b[1m" << prefix << "\x1b[22m: ";
	}
	return option;
}

#else
//this'll be the C version of the function sometime in the future.
#endif //__cplusplus
#endif //TERMINAL_SETUP_
