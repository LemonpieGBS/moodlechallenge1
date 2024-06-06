#include <iostream>
#include <conio.h>
#include <string>

// Me he montado mi propio sistema de cin porque el cin es muy MUY inseguro porque al usuario le pido un entero
// y el cabron me pone, y cito "ASKDJMKODASWMNDIOWQNUJOIWQEDUJI9OWEDFNBUJIEWFBYUHJ"

// fetch_input, mi funcion, tiene varias ventajas:
// - La escritura se obtiene a tiempo real (el string siempre esta siendo actualizado en lugar de recibir datos hasta cuando el usuario presiona enter)
// - Se puede enmascarar el input del usuario, por ejemplo con '*' para una contraseña
// - Gracias a la escritura a tiempo real, se puede prevenir el uso de caracteres no deseados como letras cuando se piden enteros
// - Es muy facil de editar a conveniencia del programador

// Todas estas funciones son overloads de fetch_input original preparadas para sus necesidades

// fetch_input(string) es la mas basica de todas, deja poner cualquier letra al usuario:
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

// fetch_input(int) tiene parametros mas estrictos como el solo permitir numeros y solo poder poner un solo caracter - al principio
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

// fetch_input(float) y fetch_input(double) son casi lo mismo si no es que verdaderamente el mismo codigo, aqui los requerimentos:
// - Solo se pueden introducir numeros, '-' y '.'
// - Solo puede introducirse el punto UNA vez
// - El caracter '-' solo puede introducirse una vez y debe ser al principio

// Esto asegura que los usuarios no me maten al programa porque ya los veo
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

// Este es un ejemplo de una funcion customizada de fetch_input:
// fetch_input_sn es para cuando el usuario debe decir SI o NO (S/N)
// Solo permite un solo caracter, y debe ser 's','S','n' o 'N'
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

// otro ejemplo de como editar fetch_input, fetch_input ISBN
// solo caracteres numericos hasta 13 digitos y NO negativos
void fetch_input_ISBN(std::string &input_string, char mask = ' ') {

    const char BACKSPACE = 8;
    const char RETURN = 13;
    //const char ESCAPE = 27;

    const char allowed_characters[] = {'0','1','2','3','4','5','6','7','8','9'};
    bool is_allowed;

    unsigned char ch = 0;

    ch = getch();
    while(ch != RETURN || input_string.length() != ISBN_ALLOWED) {

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
            if(input_string.length() >= ISBN_ALLOWED) is_allowed = false;

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