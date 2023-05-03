#include <stdio.h>

float get_points(float grades, float income) {
    float score;

    score = 10 * grades;
    if (income < 5000) {
        score += 100;
    } else if (income >= 5000 && income <= 10000) {
        score += 70;
    } else if (income > 10000) {
        score += 40;
    }

    return score;
}

void get_scolarship(float student1, float student2, float student3) {
    if (student1 > student2 && student1 > student2) {
        printf("La beca va para el alumno 1\n");
    } else if (student2 > student1 && student2 > student3) {
        printf("La beca va para el alumno 2\n");
    } else if (student3 > student1 && student3 > student1) {
        printf("La beca va para el alumno 3\n");
    }
}

int main() {
    float grad1, grad2, grad3, inc1, inc2, inc3;
    printf("Ingrese la calificación y el puntaje del primer alumno: ");
    scanf("%f, %f", &grad1, &inc1);

    printf("Ingrese la calificación y el puntaje del segundo alumno: ");
    scanf("%f, %f", &grad2, &inc2);

    printf("Ingrese la calificación y el puntaje del tercer alumno: ");
    scanf("%f, %f", &grad3, &inc3);

    float score1 = get_points(grad1, inc1);
    float score2 = get_points(grad2, inc2);
    float score3 = get_points(grad3, inc3);

    printf("%f\n", score1);
    printf("%f\n", score2);
    printf("%f\n", score3);

    get_scolarship(score1, score2, score3);

    return 0;
}
