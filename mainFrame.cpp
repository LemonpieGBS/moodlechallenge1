#include <iostream>
#include <stdio.h>

#include "titlePrint.h"
#include "fetch_input.h"
#include "external_functions.h"

// Perdon por programar en ingles es que soy un pretencioso de mierda

// Adicionalmente, mucho de este programa esta basado en el proyecto final que estamos haciendo para el semestre
// Mas informacion aqui: https://github.com/LemonpieGBS/StockSense

// Tambien pueden ver en mi github que hice el buscaminas en C++ 

// Se explica solo pero es la cantidad maxima de libros
#define MAX_BOOK_AMOUNT 100

// STRUCT TIME los structs son muy bonitos los amo mwah
struct BOOK {
    std::string name;
    std::string author;
    std::string ISBN;
    int year_published;
};

// La version del programa
std::string version = "INDEV";

int main() {

    system("cls"); // Se que es mala practica usar system pero no me pueden forzar a usar otra cosa

    // Variables para el menu
    int fu_menu_input;
    std::string fu_SN;

    // Arreglo de libros
    BOOK book_inventory[MAX_BOOK_AMOUNT];
    int book_amount = 0;

    // Si eso de <lb> <gr> te parece raro es una funcion que me he montado para imprimir en colores
    set_color(10); titlePrint("MAIN_MENU"); color_reset();

    // Lo de los colores esta mejor explicado en el header file "external_functions.h"
    printc("<lb>- Version: " + version + ", por <gr>LemonpieGBS");
    printc("\nReto para <gr>Moodle <rs>y <gr>Artemis-Devs");

    // Imprimamos el menu inicial
    printc("\n\nElija la opcion deseada:\n  <yw>1. Acceder a biblioteca\n  2. \\<- Salir\n\n<rs>#: ");

    while(true) { // while(true) pq es un loop que voy a romper cuando yo quiera

        fetch_input(fu_menu_input); // Esto de fetch_input es otra funcion que me he montado, ver "fetch_input.h"
        if(validate_option(fu_menu_input,1,2)) break;
        else printc("<rd>!-Esa no es una opcion valida! Escriba de nuevo: ");
    }

    // Si el usuario eligio la opcion 1 lo vamos a poner en un bucle WOOoo
    if(fu_menu_input == 1) while(true) {

        system("cls");
        
        set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
        printc("- Menu Principal de Biblioteca");

        // Menu principal
        printc("\n\n\nElija la opcion deseada:\n  <yw>1. Mostrar libros\n  2. Agregar libro\n  3. Remover libro\n  4. Editar libro\n  5. Filtrar libros (por año publicado)\n  6. \\<- Salir\n\n<rs>#: ");

        while(true) {

            fetch_input(fu_menu_input);
            if(validate_option(fu_menu_input,1,6)) break;
            else printc("<rd>!-Esa no es una opcion valida! Escriba de nuevo: ");
        }

        if(fu_menu_input == 6) break;

    }

    return 0;
}