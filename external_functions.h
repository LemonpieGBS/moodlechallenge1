#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <map>
#include <algorithm>

#define array_length(x) (int) (sizeof(x) / sizeof(*x))

struct read_until_mat {
    std::string return_string = "";
    int final_position;
};

void set_color(int col) { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole,col); }

void color_reset() { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole,15); }

bool validate_option(int menu_input, int low_bound, int high_bound) { return (menu_input >= low_bound && menu_input <= high_bound); }

read_until_mat read_until_char(std::string str, int begin_position, const char char_up) {
    
    int i;
    int blessed = -1;
    read_until_mat return_mat;
    
    for(i = begin_position; i < (int) str.length(); i++) {

        if(str[i] == char_up && blessed != i) break;
        else if(str[i] == '\\') blessed = i+1;
        else return_mat.return_string += str[i];
    }
    return_mat.final_position = i-1;

    return return_mat;
}

void printc(std::string print_e) {

    std::map<std::string,int> color_keys;

    color_keys["gy"] = 8;
    color_keys["bl"] = 9;
    color_keys["gr"] = 10;
    color_keys["lb"] = 11;
    color_keys["rd"] = 12;
    color_keys["pr"] = 13;
    color_keys["yw"] = 14;
    color_keys["rs"] = 15;

    int current_pos = 0;
    read_until_mat return_mat, color_mat;

    color_reset();

    while(current_pos < (int) print_e.length()) {

        return_mat = read_until_char(print_e,current_pos,'<');
        current_pos = return_mat.final_position + 2;

        if(return_mat.return_string != "") std::cout<<return_mat.return_string;
        color_mat = read_until_char(print_e,current_pos,'>');
        current_pos = color_mat.final_position + 2;

        set_color(color_keys[color_mat.return_string]);
    }

    color_reset();
    
    // "Hi, <bl>my name <rs>is <gr>Jeremy"
}

void uppercase(std::string &string_input) {
    transform(string_input.begin(), string_input.end(), string_input.begin(), ::toupper); 
}