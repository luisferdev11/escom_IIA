/*
Pseudocodigo:

Entrada: Entero dia_nacimiento, mes_nacimiento, año_nacimiento, dia_actual, mes_actual, año_actual
Salida: Entero edad_en_años, edad_en_meses, edad_en_dias

Imprimir "Ingrese su fecha de nacimiento (día mes año): "
Leer dia_nacimiento, mes_nacimiento, año_nacimiento

Imprimir "Ingrese la fecha actual (día mes año): "
Leer dia_actual, mes_actual, año_actual

edad_en_años = año_actual - año_nacimiento

Si (mes_actual < mes_nacimiento o (mes_actual == mes_nacimiento y dia_actual < dia_nacimiento)) entonces
    edad_en_años--
finSi

Si (edad_en_años == 0) entonces
    edad_en_meses = mes_actual - mes_nacimiento
    edad_en_dias = dia_actual - dia_nacimiento

    Si (edad_en_dias < 0) entonces
        edad_en_meses--
        edad_en_dias += 30 // asumimos que un mes tiene 30 días
    finSi

    Imprimir "La edad es: " concatenar edad_en_meses concatenar " meses y " concatenar edad_en_dias concatenar " días"

sino
    Imprimir "La edad es: " concatenar edad_en_años concatenar " años"
finSi
*/

#include <stdio.h>

int main() {
    int birth_day, birth_month, birth_year;
    int current_day, current_month, current_year;
    int age_years, age_months, age_days;

    printf("Ingrese su fecha de nacimiento (día mes año): ");
    scanf("%d %d %d", &birth_day, &birth_month, &birth_year);

    printf("Ingrese la fecha actual (día mes año): ");
    scanf("%d %d %d", &current_day, &current_month, &current_year);

    // Calcula la edad en años
    age_years = current_year - birth_year;

    // Verifica si la fecha actual está antes del cumpleaños
    if (current_month < birth_month || (current_month == birth_month && current_day < birth_day)) {
        age_years--;
    }

    // Calcula la edad en meses y días si la persona es un bebé
    if (age_years == 0) {
        age_months = current_month - birth_month;
        age_days = current_day - birth_day;

        if (age_days < 0) {
            age_months--;
            age_days += 30;
        }

        printf("La edad es: %d meses y %d días\n", age_months, age_days);
    } else {
        printf("La edad es: %d años\n", age_years);
    }

    return 0;
}