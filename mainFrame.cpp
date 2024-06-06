#include <iostream>
#include <stdio.h>

// Se explica solo pero es la cantidad maxima de libros
#define MAX_BOOK_AMOUNT 100
#define ISBN_ALLOWED 13
#define MIN_YEAR 1900

#include "titlePrint.h"
#include "fetch_input.h"
#include "external_functions.h"
#include "time_functions.h"

// Perdon por programar en ingles es que soy un pretencioso de mierda

// Adicionalmente, mucho de este programa esta basado en el proyecto final que estamos haciendo para el semestre
// Mas informacion aqui: https://github.com/LemonpieGBS/StockSense

// Tambien pueden ver en mi github que hice el buscaminas en C++ 

// STRUCT TIME los structs son muy bonitos los amo mwah
struct BOOK {
    std::string name;
    std::string author;
    std::string ISBN;
    int year_published;
};

// La version del programa
std::string version = "INDEV";

// FUNCIONES DEL PROGRAMA
std::string autoGenerateISBN();

// MODULOS DEL PROGRAMA
void mod_addBook(BOOK book_arr[], int &book_amount);

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
        printc("- <gr>Menu Principal de Biblioteca");

        // Menu principal
        printc("\n\n\nElija la opcion deseada:\n  <yw>1. Mostrar libros\n  2. Agregar libro\n  3. Remover libro\n  4. Editar libro\n  5. Filtrar libros (por año publicado)\n  6. \\<- Salir\n\n<rs>#: ");

        while(true) {

            fetch_input(fu_menu_input);
            if(validate_option(fu_menu_input,1,6)) break;
            else printc("<rd>!-Esa no es una opcion valida! Escriba de nuevo: ");
        }

        if(fu_menu_input == 6) break;
        switch(fu_menu_input) {
            case(1): break;
            case(2): mod_addBook(book_inventory, book_amount); break;
            default: break;
        }

    }

    return 0;
}

std::string autoGenerateISBN() {

    char characters_to_use[] = {'0','1','2','3','4','5','6','7','8','9'};
    std::string return_ISBN;

    for(int i = 0; i < ISBN_ALLOWED; i++) {

        int random_number = rand() % array_length(characters_to_use);
        return_ISBN += characters_to_use[random_number];

    }

    return return_ISBN;
}

void mod_addBook(BOOK book_arr[], int &book_amount) {
    system("cls");

    set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
    printc("- <gr>Añadir libro a Biblioteca");

    BOOK new_book;
    std::string generate_auto;

    printc("\n\n\n  <lb>$- Inserte el titulo del libro\n  <rs>#: ");
    fetch_input(new_book.name);

    printc("\n  <lb>$- Inserte el autor del libro\n  <rs>#: ");
    fetch_input(new_book.author);

    printc("\n  <yw>?- Quisiera generar el ISBN automaticamente o introducirlo manualmente? <rs>(S/N)\n  #: ");
    fetch_input_sn(generate_auto);

    uppercase(generate_auto);
    if(generate_auto == "N") {
        printc("\n  <lb>$- Introduzca el ISBN (debe ser de " + std::to_string(ISBN_ALLOWED) + " digito(s))\n  <rs>#: ");
        fetch_input_ISBN(new_book.ISBN);
    } else {
        new_book.ISBN = autoGenerateISBN();
        printc("\n  <gr>ISBN generado exitosamente: <rs>" + new_book.ISBN + "\n");
    }

    printc("\n  <lb>$- Inserte el año de publicación (debe ser no menor a 1900)\n  <rs>#: ");

    int year_container;
    while(true) {
        fetch_input(year_container);
        if(year_container < MIN_YEAR || year_container > get_current_year()) {
            printc("  <rd>!-Inserte un año valido! Escriba de nuevo: ");
        } else break;
    }
    new_book.year_published = year_container;

    book_arr[book_amount] = new_book;
    printc("\n<gr>El libro se ha creado con exito! <rs>Volviendo al menu...");
    Sleep(2000);

}