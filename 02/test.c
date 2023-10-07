//Igec -arch 1386 -00 challenge.c 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void print_msg1(int c) {
    printf("Msg1 has been called: %d\n", c);
}
void print_msg2(int c) {
    printf("Msg2 has been called: %d\n", c);
}
int get_input(void) {
    int c;
    char buf [50];
    fgets(buf, sizeof (buf), stdin);
    c = atoi(buf);  
    return c;
}
void handle_input(int c) {
    void (*handler) (int);
    int o = 0;
    switch (c) {
    case 1:
        o = 2;
        handler = print_msg1;
        break;
    case 2:
        o = 12;
        handler = print_msg2;
        break;
    }
    handler(o);
}
int main(int argc, char const *argv[]) {
    int input = get_input();
    handle_input(input);
    return 0;
}
