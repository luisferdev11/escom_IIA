#ifndef PELOTA_H
#define PELOTA_H

struct Pelota {
    int alto;
    int ancho;
    char color[20];
};

// Prototipos de funciones
void crearPelota(struct Pelota **p, int *n);
void destruirPelota(struct Pelota **p, int *n, int index);
void leerPelotas(struct Pelota *p, int n);
void menuOperaciones(struct Pelota **p, int *n);

#endif // PELOTA_H

