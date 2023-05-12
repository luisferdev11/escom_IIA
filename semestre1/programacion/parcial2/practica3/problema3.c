#include <stdio.h>

int main() {
    int aprobados = 0, reprobados = 0;
    float suma_grupo = 0;

    for (int i = 1; i <= 5; i++) {
        float suma = 0;
        for (int j = 1; j <= 3; j++) {
            float calificacion;
            do {
                printf("Introduce la calificacion del estudiante %d en la evaluacion %d: \n", i, j);
                scanf("%f", &calificacion);
            } while (calificacion < 0 || calificacion > 10);
            suma += calificacion;
        }
        float promedio = suma / 3;
        printf("El promedio del estudiante %d es %.2f\n", i, promedio);
        if (promedio < 6) {
            reprobados++;
        } else {
            aprobados++;
        }
        suma_grupo += promedio;
    }
    float promedio_grupo = suma_grupo / 5;
    printf("El promedio del grupo es %.2f\n", promedio_grupo);
    printf("El numero de aprobados es %d\n", aprobados);
    printf("El numero de reprobados es %d\n", reprobados);

    return 0;
}
