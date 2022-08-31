#include <glib.h>

int main(int argc, char **argv){
    int x;
    x = g_random_int_range(0, INT_MAX);
    g_print("%d %d\n", x % 2, x);
    return 0;
}