#include <iostream>
#include <fstream> // Esto para manejar ficheros pq no soy masoquista y uso funciones de C
#include <direct.h> // Para usar _mkdir y crear carpetas

// Se explica solo pero es la cantidad maxima de libros
#define MAX_BOOK_AMOUNT 100
#define ISBN_ALLOWED 13
#define MIN_YEAR 1900
#define CONSIDERED_RECENT 5

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
    std::string name = "";
    std::string author = "";
    std::string ISBN = "";
    int year_published = -1;
};

// La version del programa
std::string version = "v1.1.0";

// Estamos obteniendo la dirección de %APPDATA% para evitar problemas al abrir ficheros
std::string appdata_path = getenv("APPDATA");

// Agregamos la dirección dentro de APPDATA
std::string savefile_path = appdata_path + "\\moodlechallenge1\\savefile.dat";

// FUNCIONES DEL PROGRAMA
std::string autoGenerateISBN();
bool checkISBNavailability(BOOK book_arr[], int book_amount, std::string ISBN_INPUT);
void showBooks(BOOK book_arr[], int book_amount, int minimum_year = 0);

// FUNCIONES DE SAVE/LOAD
bool SL_loadBooks(BOOK book_arr[], int &book_amount);
void SL_saveBooks(BOOK book_arr[], int book_amount);

// MODULOS DEL PROGRAMA
void mod_addBook(BOOK book_arr[], int &book_amount);
void mod_showBooks(BOOK book_arr[], int book_amount);
void mod_removeBook(BOOK book_arr[], int &book_amount);
void mod_showRecentBooks(BOOK book_arr[], int book_amount);

int main() {

    srand(time(0)); // Semilla aleatoria
    system("cls"); // Se que es mala practica usar system pero no me pueden forzar a usar otra cosa

    // Imprimimos el titulo del programa
    set_color(10); titlePrint("MAIN_MENU"); color_reset();

    // Variables para el menu
    int fu_menu_input;
    std::string fu_SN;

    // Arreglo de libros
    BOOK book_inventory[MAX_BOOK_AMOUNT];
    int book_amount = 0;

    printc("- <gr>Cargando libros...");

    // Creamos la carpeta en %appdata% si no existe

    // Como _mkdir solo acepta un arreglo de caracteres y no un string, usamos c_str()
    // c_str() convierte un dato tipo string en un arreglo de caracteres
    _mkdir((appdata_path + "\\moodlechallenge1").c_str());

    // Cargamos los libros y avisamos al usuario si se pudieron cargar
    if(SL_loadBooks(book_inventory,book_amount)) {
        printc("\n\n\n<rd>!-No se pudo encontrar savefile.dat! <rs>Es posible que la biblioteca este vacia...");
    } else printc("\n\n\n<lb>Libros cargados con exito!");

    // Esperamos 2 segundos antes de entrar oficialmente al programa
    Sleep(2000);

    system("cls");

    // Si eso de <lb> <gr> te parece raro es una funcion que me he montado para imprimir en colores
    set_color(10); titlePrint("MAIN_MENU"); color_reset();

    // Lo de los colores esta mejor explicado en el header file "external_functions.h"
    printc("<lb>- Version: <gr>" + version + " <lb>por <gr>LemonpieGBS");
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

        // Imprimimos el titulo e indicamos que estamos en el menu de añadir libro
        set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
        printc("- <gr>Menu Principal de Biblioteca");

        // Menu principal
        printc("\n\n\nElija la opcion deseada:\n  <yw>1. Mostrar libros\n  2. Agregar libro\n  3. Remover libro\n  4. Mostrar libros recientes\n  5. \\<- Salir\n\n<rs>#: ");

        while(true) {

            // Si la opcion se valida rompemos el loop, sino, seguimos pidiendo al usuario
            fetch_input(fu_menu_input);

            if(validate_option(fu_menu_input,1,5)) break;
            else printc("<rd>!-Esa no es una opcion valida! <rs>Escriba de nuevo: ");
        }

        // Si el usuario pide salir, salimos
        if(fu_menu_input == 5) break;

        // Un switch para determinar que modulo llamar
        switch(fu_menu_input) {
            case(1): mod_showBooks(book_inventory, book_amount); break;
            case(2): mod_addBook(book_inventory, book_amount); break;
            case(3): mod_removeBook(book_inventory, book_amount); break;
            case(4): mod_showRecentBooks(book_inventory, book_amount); break;
            default: break;
        }

    }

    return 0;
}

std::string autoGenerateISBN() {

    // Los caracteres que vamos a usar
    char characters_to_use[] = {'0','1','2','3','4','5','6','7','8','9'};
    std::string return_ISBN;

    // Repetimos este bucle las veces que indique los digitos del ISBN
    for(int i = 0; i < ISBN_ALLOWED; i++) {

        // Generamos un numero aleatorio del 0 al 9 para acceder al arreglo
        int random_number = rand() % array_length(characters_to_use);

        // Añadimos el número generado al azar al ISBN
        return_ISBN += characters_to_use[random_number];
    }

    return return_ISBN;
}

std::string parseBOOK(BOOK book_input) {
    // Esta función se usa para parsear un libro a string, y asi poder guardarlo a savefile
    std::string return_string = "";
    return_string += "name:" + book_input.name + ">";
    return_string += "author:" + book_input.author + ">";
    return_string += "ISBN:" + book_input.ISBN + ">";
    return_string += "year_published:" + std::to_string(book_input.year_published) + ">";
    // Por ejemplo, el libro Pedro Paramo de Juan Rulfo, publicado en 1955 con un ISBN 0001112223334 sera:
    // name:Pedro Paramo>author:Juan Rulfo>ISBN:0001112223334>year_published:1955>

    return return_string;
}

BOOK unparseBOOK(std::string string_input) {
    // Esta función toma un string de libro parseado y lo desparsea a un struct de libro
    BOOK return_book;
    int current_position = 0;

    // Aqui usaremos la funcion read_until_char para determinar que parte es el valor que queremos
    while(current_position <= (int) string_input.length()) {

        read_until_mat parameter_mat; // Este mat contendra el nombre del parametro
        read_until_mat value_mat; // Este mat contendra el valor del parametro

        // Leemos hasta donde diga el ':' para saber que parametro estamos tratando
        parameter_mat = read_until_char(string_input,current_position,':');
        // Saltamos el ':' la proxima leida sumando 2
        current_position = parameter_mat.final_position + 2;

        // Leemos lo que hay entre el ultimo ':' y el siguiente '>'
        value_mat = read_until_char(string_input,current_position,'>');
        // Saltamos el '>' la proxima leida sumando 2
        current_position = value_mat.final_position + 2;

        // Dependiendo de lo que leyó parameter_mat, asignamos al libro el value_mat
        if(parameter_mat.return_string == "name") return_book.name = value_mat.return_string;
        else if(parameter_mat.return_string == "author") return_book.author = value_mat.return_string;
        else if(parameter_mat.return_string == "ISBN") return_book.ISBN = value_mat.return_string;
        else if(parameter_mat.return_string == "year_published") return_book.year_published = stoi(value_mat.return_string);
    }

    return return_book;
}

bool checkISBNavailability(BOOK book_arr[], int book_amount, std::string ISBN_INPUT) {

    // Funcion para revisar disponibilidad de un ISBN
    for(int i = 0; i < book_amount; i++) {
        if(ISBN_INPUT == book_arr[i].ISBN) { return false; }
        // ^ ^ ^ Ciclamos el arreglo y si encontramos un ISBN igual regresamos false
    }

    return true;
    // Si la funcion no ha retornado significa que no se encontro ninguna coincidencia
}

void showBooks(BOOK book_arr[], int book_amount, int minimum_year) {

    // Ciclamos por el arreglo entero de libros
    for(int i = 0; i < book_amount; i++) {
        
        // Si el año del libro es menor al año mínimo, saltarlo
        if(book_arr[i].year_published < minimum_year) continue;

        // Este es el formato con el que se mostraran los libros
        printc("\n  <gr>" + book_arr[i].name + "<rs> de <gr>" + book_arr[i].author);
        printc("\n  - Publicado en: <lb>" + std::to_string(book_arr[i].year_published) + "<rs>, ISBN: <lb>" + book_arr[i].ISBN + "\n");
    }

}

bool SL_loadBooks(BOOK book_arr[], int &book_amount) {

    // Esta función retorna 'true' si no se pudo cargar el inventario, para que el programador (yo) lo maneje

    // Declaramos un ifstream, es decir, input fstream
    std::ifstream SAVE_FILE;

    // Abrimos el file en nuestro savefile_path en el modo out, equivalente a "r" en fopen()
    SAVE_FILE.open(savefile_path, std::ios::in);

    if(SAVE_FILE.is_open()) {

        // En esta variable vamos guardando cada linea
        std::string save_line;

        // Mientras getline de 1 (es decir, que no es ha encontrado el final del archivo) sacamos lineas y las
        // guardamos en save_line
        while(std::getline(SAVE_FILE,save_line)) {

            // Desencriptamos save_line y lo guardamos al arreglo
            book_arr[book_amount] = unparseBOOK(save_line);
            book_amount++;

        }

    } else { return true; }

    return false;
    
}

void SL_saveBooks(BOOK book_arr[], int book_amount) {

    // Declaramos un ofstream, es decir, output fstream
    std::ofstream SAVE_FILE;

    // Abrimos el file en nuestro savefile_path en el modo out, equivalente a "w" en fopen()
    SAVE_FILE.open(savefile_path, std::ios::out);

    for(int i = 0; i < book_amount; i++) {
        // Para escribir a un fichero en fstream se hace como cout
        SAVE_FILE<<parseBOOK(book_arr[i])<<"\n";
    }

    // Cerramos el fichero cuando dejamos de manipularlo
    SAVE_FILE.close();
}

void mod_showBooks(BOOK book_arr[], int book_amount) {

    system("cls");

    // Imprimimos el titulo e indicamos que estamos en el menu de añadir libro
    set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
    printc("- <gr>Inventario de Biblioteca <lb>(Use 'ESC' para salir)");

    printc("\n\n\n======================================================\n");

    // Detectar si hay libros sabes
    if(book_amount > 0) {

        // Llamamos a la funcion de mostrar libros sin restriccion de año
        showBooks(book_arr,book_amount);

    } else {

        // Si no hay libros, imprimimos lo mismo
        printc("\n  <rd>!: No hay libros en biblioteca!\n");

    }

    printc("\n======================================================");

    // Bucle infinito mientras no se presione enter
    while(!(GetAsyncKeyState(VK_ESCAPE) < 0)) {}
}

void mod_addBook(BOOK book_arr[], int &book_amount) {
    
    system("cls");

    // Imprimimos el titulo e indicamos que estamos en el menu de añadir libro
    set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
    printc("- <gr>Añadir libro a Biblioteca");

    // Limite de libros que se pueden añadir
    if(book_amount >= MAX_BOOK_AMOUNT) {

        // Informamos al usuario que ha alcanzado el maximo de libros
        printc("\n\n\n<rd>!: Se ha llegado al maximo de libros: <gr>" + std::to_string(MAX_BOOK_AMOUNT));
        printc("\n<rs>Volviendo al menu inicial...");

        Sleep(2000); // Esperamos 2 segundos a salir
        return; // con return nos salimos de la funcion
    }

    // Variables que usaremos luego
    BOOK new_book;
    std::string generate_auto;

    // Pedimos al usuario que nos de el titulo del libro
    printc("\n\n\n  <lb>$-Inserte el titulo del libro\n  <rs>#: ");
    fetch_input(new_book.name);

    // Pedimos al usuario que nos de el autor del libro
    printc("\n  <lb>$-Inserte el autor del libro\n  <rs>#: ");
    fetch_input(new_book.author);

    // Damos la opcion al usuario de autogenerar el ISBN o introducirlo manualmente
    printc("\n  <yw>?-Quisiera generar el ISBN automaticamente? <rs>(S/N)\n  #: ");
    fetch_input_sn(generate_auto);

    // Si el usuario indica que no quiere generar el ISBN damos a escribirlo
    uppercase(generate_auto);
    if(generate_auto == "N") {

        // Pedimos al usuario que nos de el ISBN
        printc("\n  <lb>$-Introduzca el ISBN (debe ser de " + std::to_string(ISBN_ALLOWED) + " digitos)\n  <rs>#: ");

        while(true) {
            fetch_input_ISBN(new_book.ISBN);

            // Si el ISBN no esta disponible lo decimos y reiniciamos
            if(!checkISBNavailability(book_arr,book_amount,new_book.ISBN)) { printc("  <rd>!: Este ISBN ya esta en uso! <rs>Escriba de nuevo: "); }
            else break;
        }

    } else {

        while(true) {
            new_book.ISBN = autoGenerateISBN();

            // Bucle hasta que el ISBN generado este disponible
            if(checkISBNavailability(book_arr,book_amount,new_book.ISBN)) break;
        }

        // Imprimir el ISBN generado de cortesía
        printc("\n  <gr>ISBN generado exitosamente: <rs>" + new_book.ISBN + "\n");
    }

    // Pedimos al usuario que nos de el año de publicación
    printc("\n  <lb>$-Inserte el año de publicacion (debe ser no menor a 1900)\n  <rs>#: ");

    // Creamos un contenedor para el año
    int year_container;
    while(true) {

        fetch_input(year_container);
        // Si el año es menor al año minimo o mayor al año actual, es invalido
        if(year_container < MIN_YEAR || year_container > get_current_year()) {
            printc("  <rd>!-Inserte un año valido! <rs>Escriba de nuevo: ");
        } else break;
    }
    new_book.year_published = year_container;

    // Es mejor tener una variable de contenedor en lugar de editar el arreglo en tiempo real
    book_arr[book_amount] = new_book;
    book_amount++;

    // Salvar los cambios a savefile.dat
    SL_saveBooks(book_arr,book_amount);

    // Si el programa no se murio poniendo el nuevo libro, es exitoso!
    printc("\n\n<gr>El libro se ha creado con exito! <rs>Volviendo al menu...");

    // Esperar 2 segundos para volver al menu
    Sleep(2000);

}

void mod_removeBook(BOOK book_arr[], int &book_amount) {

    system("cls");

    // Imprimimos el titulo e indicamos que estamos en el menu de añadir libro
    set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
    printc("- <gr>Remover libro de biblioteca <rd>(Proceder con cuidado!)");

    printc("\n\n\n======================================================\n");

    // Detectar si hay libros sabes
    if(book_amount > 0) {

        // Llamamos a la funcion de mostrar libros sin restriccion de año
        showBooks(book_arr,book_amount);

    } else {

        // Si no hay libros, imprimimos lo mismo
        printc("\n  <rd>!: No hay libros en biblioteca!\n");

    }

    printc("\n======================================================");

    // Si no hay libros, esperamos un poco y volvemos al programa inicial
    if(book_amount == 0) {
        Sleep(2000);
        return;
    }

    // Variables que vamos a usar yay
    std::string ISBN_input, current_confirmation;
    int book_to_remove = -1;

    // Pedimos al usuario el ISBN del libro a eliminar
    printc("\n\n\n<lb>$-Inserte el ISBN del libro que desea eliminar\n<rs>#: ");

    // Bucle infinito jjijiijijiji
    while(true) {

        // Recolectamos el ISBN a eliminar
        fetch_input_ISBN(ISBN_input);

        // Revisamos si existe el ISBN
        for(int i = 0; i < book_amount; i++) {
            
            // Si si existe, guardamos su indice y rompemos el for
            if(ISBN_input == book_arr[i].ISBN) {
                book_to_remove = i;
                break;
            }

        }

        // Si no se encontro el libro, hacer lo siguiente:
        if(book_to_remove == -1) {

            // Pedir al usuario si quiere intentar de nuevo
            printc("\n<rd>!-No se pudo encontrar el libro! Desea intentar de nuevo? <rs>(S/N)\n#: ");
            fetch_input_sn(current_confirmation);

            uppercase(current_confirmation);

            // Si el resultado es no, salimos de la funcion
            if(current_confirmation == "N") return;
            else {
                printc("\n<lb>$-Inserte el ISBN del libro que desea eliminar\n<rs>#: ");
            }
        } else break;
    }

    system("cls");

    // Imprimimos el titulo e indicamos que estamos en el menu de añadir libro
    set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
    printc("- <gr>Remover libro de biblioteca <rd>(Proceder con cuidado!)");

    // Se encontro el libro entonces preguntamos al usuario si esta seguro
    printc("\n\n\nEl libro se ha encontrado: <gr>" + book_arr[book_to_remove].name + "<rs>, Esta seguro de quererlo eliminar? (S/N)\n#: ");
    fetch_input_sn(current_confirmation);

    uppercase(current_confirmation);

    if(current_confirmation == "N") return;

    // Preguntar si estan muy muy seguros
    printc("\n<rd>!: ULTIMO AVISO, DESEA ELIMINAR EL LIBRO? <rs>(S/N)\n#: ");
    fetch_input_sn(current_confirmation);

    uppercase(current_confirmation);

    if(current_confirmation == "N") return;

    // ELIMINAMOS EL LIBRO
    book_amount--;

    // Empezamos en el libro que vamos a vaporizar asi es reemplazado
    for(int i = book_to_remove; i < book_amount; i++) {
        // Reemplazamos el libro actual con el siguiente
        book_arr[i] = book_arr[i+1];
    }

    // Salvar los cambios a savefile.dat
    SL_saveBooks(book_arr,book_amount);

    // Decir que se ha logrado
    printc("\n\n<gr>El libro se ha eliminado exitosamente! <rs>Volviendo al menu principal...");
    Sleep(2000);
}

void mod_showRecentBooks(BOOK book_arr[], int book_amount) {

    system("cls");

    // Imprimimos el titulo e indicamos que estamos en el menu de añadir libro
    set_color(10); titlePrint("LIBRARY_TITLE"); color_reset();
    printc("- <gr>Libros recientes en Biblioteca (no mas de " + std::to_string(CONSIDERED_RECENT) + " años) <lb>(Use 'ESC' para salir)");

    printc("\n\n\n======================================================\n");

    int books_eligible = 0; // Vamos a contar los libros que son elegibles
    for(int i = 0; i < book_amount; i++) { if(book_arr[i].year_published >= get_current_year() - CONSIDERED_RECENT) books_eligible++; }
    // get_current_year() - CONSIDERED RECENT, el año actual menos los 5 años para que un libro siga siendo reciente

    // Detectar si hay libros sabes
    if(books_eligible > 0) {

        // Llamamos a la funcion de mostrar libros sin restriccion de año
        showBooks(book_arr,book_amount,get_current_year() - CONSIDERED_RECENT);
        // get_current_year() - CONSIDERED RECENT, el año actual menos los 5 años para que un libro siga siendo reciente

    } else {

        // Si no hay libros elegibles, imprimimos lo mismo
        printc("\n  <rd>!: No hay libros recientes en biblioteca!\n");

    }

    printc("\n======================================================");

    // Bucle infinito mientras no se presione enter
    while(!(GetAsyncKeyState(VK_ESCAPE) < 0)) {}
}