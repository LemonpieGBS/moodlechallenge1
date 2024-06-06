#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <string>
#include <map>
#include <algorithm>

#define array_length(x) (int) (sizeof(x) / sizeof(*x))

struct read_until_mat { // Esto lo vamos a usar en la funcion read_until_char
    std::string return_string = "";
    int final_position;
};

void set_color(int col) { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole,col); }

void color_reset() { HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); SetConsoleTextAttribute(hConsole,15); }

bool validate_option(int menu_input, int low_bound, int high_bound) { return (menu_input >= low_bound && menu_input <= high_bound); }
// ^ ^ ^ Esta funcion solo toma un numero (ejemplo: 3) y ve si esta en un rango (por ejemplo: 1-5)
// Esto lo uso para validar las opciones que por ese es el puto nombre de la funcion

read_until_mat read_until_char(std::string str, int begin_position, const char char_up) {
    
    int i;
    int blessed = -1;
    read_until_mat return_mat;

    // Esta funcion lee un string y se detiene cuando encuentra el caracter dicho por el usuario
    
    for(i = begin_position; i < (int) str.length(); i++) {

        if(str[i] == char_up && blessed != i) break;
        // El ciclo se rompe cuando se encuentra el caracter

        else if(str[i] == '\\') blessed = i+1;
        // El blessed es para que se ignoren caracteres precedidos por '\\'
        // Por ejemplo, si leemos hasta la coma de Hola, a todos, UAM! nos retornaria "Hola"
        // Sin embargo, en el caso de que el string sea "Hola\\, a todos, UAM!" nos retornaria "Hola, a todos"

        else return_mat.return_string += str[i];
        // Si el caracter no es un '\\' o el caracter indicado, se agrega al return_string
    }

    return_mat.final_position = i-1;
    // IMPORTANTE: final_position es la posicion de la ultima letra antes del caracter, NO del caracter

    // Esta funcion devuelve un struct con dos cosas, return_string es el string obtenido y final_position ps se explica
    // Un read_until_char() hasta el caracter ',' del string "Hola a todos, menos a ti" devolveria:
    // return_string = "Hola a todos"
    // final_position = 11 (se empieza a contar de 0)

    // En el caso de que el caracter este al inicio como en: ", cuando yo la vi" la funcion devuelve:
    // return_string = ""
    // final_position = -1

    // De esta manera si quieres leer partes de un string separadas por espacios por ejemplo, solo empiezas en la posicion (final_position + 2)
    // Para usar la funcion de manera efectiva declara una variable tipo read_until_mat y asignale la funcion
    
    // read_until_mat STRING_READ = read_until_char(blah blah blah);
    
    // Y despues sacas los valores asi:
    // int posicion_de_coma = STRING_READ.final_position
    // std::string string_conseguido = STRING_READ.return_string

    return return_mat;
}

void printc(std::string print_e) {

    // Empecemos con esto, esta funcion usa dos funciones ya asignadas: set_color() y color_reset();
    // La liberia windows.h deja que le pongas colores a lo que se imprime en pantalla usando numeros refiriendose a colores

    // Aqui un diagrama con cada color y su indice en hexadecimal:
    // https://blogger.googleusercontent.com/img/b/R29vZ2xl/AVvXsEinmm2pnIIbHDktGqQc1z5G6MtFEkHSLNkmYyrhYdmdHo3XTP5B1k9Xr-O-lRxDrMXy_n8UM6U8n_naXqLpZRR0vWGAoTntKbjlJCdcolqOJtP1gm4G1Bn5_nHP60hdh98tDUMz2QGfPC8e/s1600/ConsoleColor.bmp

    // Por ejemplo, el verde con fondo negro es 0A, que en decimal es 10, asi que para establecer verde usamos:
    // set_color(10);

    // El problema con esto es que siempre que se quiera volver al blanco se tiene que hacer un color_reset();
    // Esto genera muchos conflictos en donde se te olvida resetear el color
    // Adicionalmente, al querer muchos colores en una sola cadena de texto se hacía MUY engorroso, asi que me monte mi función de colorear texto
    // El texto se colorea algo parecido a como se hace en HTML, usando <cc> siendo cc el codigo del color

    std::map<std::string,int> color_keys;
    // ^ ^ ^ Esto es un mapa, basicamente lo que quiero hacer es un arreglo invertido donde le doy un string y me devuelve un numero
    // Por ejemplo, si le doy "gy" me devolvera el numero 8, que es el gris en el diagrama
    // O si le doy "pr" me devolvera ¿qué numero? exacto, entre mas me la ma

    color_keys["gy"] = 8; // Gris (gray)
    color_keys["bl"] = 9; // Azul (blue)
    color_keys["gr"] = 10; // Verde (green)
    color_keys["lb"] = 11; // Celeste (light blue)
    color_keys["rd"] = 12; // Rojo (red)
    color_keys["pr"] = 13; // Morado (purple)
    color_keys["yw"] = 14; // Amarillo (yellow)
    color_keys["rs"] = 15; // Blanco (reset) vale que blanco no se dice reset pero es para resetear el color

    int current_pos = 0;
    read_until_mat return_mat, color_mat; // Use mis funciones para hacer mis funciones, no dependo de NADIE

    color_reset();
    // ^ ^ ^ La funcion SIEMPRE empezara con texto blanco, para evitar eso, simplemente pon un color al principio

    // Aqui pueden ver una aplicacion de la funcion read_until_char asi que ojo:
    while(current_pos < (int) print_e.length()) {

        return_mat = read_until_char(print_e,current_pos,'<');
        // Leemos el string hasta la primera apertura '<'

        current_pos = return_mat.final_position + 2;
        // Como final_position es la posicion de la ultima letra antes del '<' le sumamos dos para saltarlo

        if(return_mat.return_string != "") std::cout<<return_mat.return_string;
        // Si el string no esta vacio, lo imprimimos a pantalla que creen que significa cout

        color_mat = read_until_char(print_e,current_pos,'>');
        // Leemos el string hasta encontrar el cierre, es decir '<'

        current_pos = color_mat.final_position + 2;
        // Nos saltamos el '<' para ver si hay mas texto pe

        set_color(color_keys[color_mat.return_string]);
        // return_string ahora tiene lo que iba adentro de el '<' y el '>' asi que usamos el mapa para aplicar el color correspondiente
    }

    color_reset();
    // ^ ^ ^ Resetear el color verdaderamente se explica solo
    
    // Ejemplo de uso:
    // "Hi, <bl>my name <rs>is <gr>Jeremy"
}

void uppercase(std::string &string_input) {
    transform(string_input.begin(), string_input.end(), string_input.begin(), ::toupper); 
}