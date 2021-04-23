#include <iostream>
#include "store.h";

int main(int argc, char** argv) {
    Store store;
     store.instruction();
    std::cout << "asdas";
    printf("\n");
    printf("\x1B[31mTexting\033[0m\t\t");
    printf("\x1B[32mTexting\033[0m\t\t");
    printf("\x1B[33mTexting\033[0m\t\t");
    printf("\x1B[34mTexting\033[0m\t\t");
    printf("\x1B[35mTexting\033[0m\n");

    printf("\x1B[36mTexting\033[0m\t\t");
    printf("\x1B[37mTexting\033[0m\t\t");
    printf("\x1B[90mTexting\033[0m\t\t");
    printf("\x1B[91mTexting\033[0m\t\t");
    printf("\x1B[92mTexting\033[0m\n");
    
    printf("\x1B[93mTexting\033[0m\t\t");
    printf("\x1B[94mTexting\033[0m\t\t");
    printf("\x1B[95mTexting\033[0m\t\t");
    printf("\x1B[96mTexting\033[0m\t\t");
    printf("\x1B[97mTexting\033[0m\n");


    return 0;
}