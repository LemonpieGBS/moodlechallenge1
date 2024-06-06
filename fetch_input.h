#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <string>

void fetch_input(std::string &input_string, char mask = ' ') {

    const char BACKSPACE = 8;
    const char RETURN = 13;
    //const char ESCAPE = 27;

    input_string = "";
    const char allowed_characters[] = {' '};
    bool is_allowed;

    unsigned char ch = 0;

    ch = getch();
    while( ch != RETURN) {

        if(ch == BACKSPACE) {

            if(input_string.length() != 0) {

                std::cout<<"\b \b";
                input_string.resize(input_string.length()-1);

            }

        } else if(ch==0 || ch==224) {

            getch();
            continue;

        } else {

            if(allowed_characters[0] != ' ') {

                is_allowed = false;
                for(int i = 0; i < (int) (sizeof(allowed_characters) / sizeof(allowed_characters[0])); i++) { if(ch == allowed_characters[i]) { is_allowed = true; break; }}

            } else is_allowed = true;

            if(is_allowed) {

                input_string += ch;

                if(input_string.length() != 0) {
                    if(mask == ' ') std::cout<<input_string[input_string.length()-1];
                    else std::cout<<mask;
                }

            }

        }

        ch = getch();

    }
    std::cout<<"\n";

}

void fetch_input(int &target, char mask = ' ') {

    const char BACKSPACE = 8;
    const char RETURN = 13;
    //const char ESCAPE = 27;

    const char allowed_characters[] = {'0','1','2','3','4','5','6','7','8','9','-'};
    bool is_allowed;

    std::string input_string;

    unsigned char ch = 0;

    ch = getch();
    while( ch != RETURN) {

        if(ch == BACKSPACE) {

            if(input_string.length() != 0) {

                std::cout<<"\b \b";
                input_string.resize(input_string.length()-1);

            }

        } else if(ch==0 || ch==224) {

            getch();
            continue;

        } else {

            is_allowed = false;
            for(int i = 0; i < (int) (sizeof(allowed_characters) / sizeof(allowed_characters[0])); i++) { if(ch == allowed_characters[i]) { is_allowed = true; break; }}
            if(ch == '-' && input_string.length() != 0) is_allowed = false;

            if(is_allowed) {

                input_string += ch;

                if(input_string.length() != 0) {
                    if(mask == ' ') std::cout<<input_string[input_string.length()-1];
                    else std::cout<<mask;
                }

            }

        }

        ch = getch();

    }

    target = (input_string == "") ? 0 : stof(input_string);
    std::cout<<"\n";

}

void fetch_input(float &target, char mask = ' ') {

    const char BACKSPACE = 8;
    const char RETURN = 13;
    //const char ESCAPE = 27;

    const char allowed_characters[] = {'0','1','2','3','4','5','6','7','8','9','-','.'};
    bool is_allowed;
    bool point_placed = false;

    std::string input_string;

    unsigned char ch = 0;

    ch = getch();
    while( ch != RETURN) {

        if(ch == BACKSPACE) {

            if(input_string.length() != 0) {
                
                if(input_string[input_string.length()-1] == '.') point_placed = false;
                std::cout<<"\b \b";
                input_string.resize(input_string.length()-1);

            }

        } else if(ch==0 || ch==224) {

            getch();
            continue;

        } else {

            is_allowed = false;
            for(int i = 0; i < (int) (sizeof(allowed_characters) / sizeof(allowed_characters[0])); i++) { if(ch == allowed_characters[i]) { is_allowed = true; break; }}
            if(ch == '-' && input_string.length() != 0) is_allowed = false;
            if(ch == '.' && point_placed) is_allowed = false;

            if(is_allowed) {

                input_string += ch;
                if(ch == '.') point_placed = true;

                if(input_string.length() != 0) {
                    if(mask == ' ') std::cout<<input_string[input_string.length()-1];
                    else std::cout<<mask;
                }

            }

        }

        ch = getch();

    }

    target = (input_string == "") ? 0 : stof(input_string);
    std::cout<<"\n";

}

void fetch_input(double &target, char mask = ' ') {

    const char BACKSPACE = 8;
    const char RETURN = 13;
    //const char ESCAPE = 27;

    const char allowed_characters[] = {'0','1','2','3','4','5','6','7','8','9','-','.'};
    bool is_allowed;
    bool point_placed = false;

    std::string input_string;

    unsigned char ch = 0;

    ch = getch();
    while( ch != RETURN ) {

        if(ch == BACKSPACE) {

            if(input_string.length() != 0) {
                
                if(input_string[input_string.length()-1] == '.') point_placed = false;
                std::cout<<"\b \b";
                input_string.resize(input_string.length()-1);

            }

        } else if(ch==0 || ch==224) {

            getch();
            continue;

        } else {

            is_allowed = false;
            for(int i = 0; i < (int) (sizeof(allowed_characters) / sizeof(allowed_characters[0])); i++) { if(ch == allowed_characters[i]) { is_allowed = true; break; }}
            if(ch == '-' && input_string.length() != 0) is_allowed = false;
            if(ch == '.' && point_placed) is_allowed = false;

            if(is_allowed) {

                input_string += ch;
                if(ch == '.') point_placed = true;

                if(input_string.length() != 0) {
                    if(mask == ' ') std::cout<<input_string[input_string.length()-1];
                    else std::cout<<mask;
                }

            }

        }

        ch = getch();

    }
    std::cout<<"\n";

    target = (input_string == "") ? 0 : stod(input_string);

}

void fetch_input_sn(std::string &input_string, char mask = ' ') {

    const char BACKSPACE = 8;
    const char RETURN = 13;
    //const char ESCAPE = 27;

    input_string = "";
    const char allowed_characters[] = {'s','S','n','N'};
    bool is_allowed;
    int max_length = 1;

    unsigned char ch = 0;

    ch = getch();
    while(ch != RETURN || input_string.length() <= 0) {

        if(ch == BACKSPACE) {

            if(input_string.length() != 0) {

                std::cout<<"\b \b";
                input_string.resize(input_string.length()-1);

            }

        } else if(ch==0 || ch==224) {

            getch();
            continue;

        } else {

            if(allowed_characters[0] != ' ') {

                is_allowed = false;
                for(int i = 0; i < (int) (sizeof(allowed_characters) / sizeof(allowed_characters[0])); i++) { if(ch == allowed_characters[i]) { is_allowed = true; break; }}

            } else is_allowed = true;
            if((int) input_string.length() >= max_length) is_allowed = false;

            if(is_allowed) {

                input_string += ch;

                if(input_string.length() != 0) {
                    if(mask == ' ') std::cout<<input_string[input_string.length()-1];
                    else std::cout<<mask;
                }

            }

        }

        ch = getch();

    }
    std::cout<<"\n";

}