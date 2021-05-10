/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
* Created on 4/5/21.
*
*/

#ifndef CPP_CLI_RPG_INPUTS_HXX
#define CPP_CLI_RPG_INPUTS_HXX
#include "../includes.hxx"
/**
 * Quick and dirty text wrapper
 *
 * @param input The input string
 * @param position The maximum width we can use for each step
 * @param wrap_char
 */
void text_wrap(std::string &input,unsigned int position,char wrap_char=' '){
	if(input.size() < position)
		return;
	size_t found;
	while( (found = input.find_last_of(wrap_char,position)) != std::string::npos && position < input.size()){
		//change it to a new line
		input.at(found) = '\n';
		//make the starting position be increased by the current found position
		position += found;
	}
}

/**
 * Simple print wrapper
 * @param input Input string
 * @param position position to search for
 * @param end_line call std::endl at the end or not.
 */
void print_wrap(const std::string &input, unsigned int max_width,bool end_line=false){
	std::string new_string = input;
	if(input.size() < max_width)
		std::cout << input;
	size_t found;
	size_t position = max_width;
	while((found = new_string.find_last_of(32,position)) != std::string::npos && position < input.size()){
		new_string.at(found) = '\n';
		position = max_width+found;
	}

	std::cout << new_string;

	if(end_line)
		std::cout << std::endl;
}

/**
 * Clear the text-box menu
 *
 * @param top The line at which the text menu appears
 * @param lines how many lines tall it is.
 */
void clear_textbox(unsigned short top, unsigned short lines){
	for(unsigned short i=0;i<lines;i++){
		move_cursor(top+i,2);
		std::cout << "                                                      ";
	}
}
#endif //CPP_CLI_RPG_INPUTS_HXX
