#include <iostream>
#include <stdio.h>

#include "titlePrint.h"
#include "fetch_input.h"
#include "external_functions.h"

std::string version = "INDEV";

int main() {

    // Variables for menu input
    int fu_menu_input;
    std::string fu_SN;

    set_color(10); titlePrint("MAIN_MENU"); color_reset();
    printc("<lb>- Version: " + version + ", by <gr>LemonpieGBS");
    printc("\nChallenge for Moodle & Artemis-Devs");

    // Print the starting menu
    

    return 0;
}