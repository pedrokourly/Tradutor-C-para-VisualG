#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Celcius;
float Kelvin, Fahrein;

int main() {
    system("cls"); /* Ou 'clear' no Linux */
    printf("%s", "Celcuis Fahrenheit  Kelvi");
    printf("\n");
    for (Celcius = 1; Celcius <= 50; Celcius += 1) {
        Fahrein = Celcius * 1.800000 + 32;
        Kelvin = Celcius + 273;
        printf("%3g", (double)(Celcius));
        printf("%s", " = ");
        printf("%8.2f", (double)(Fahrein));
        printf("%s", " =    ");
        printf("%6.2f", (double)(Kelvin));
        printf("\n");
    }
    return 0;
}
