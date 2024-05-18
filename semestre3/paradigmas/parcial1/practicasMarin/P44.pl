%Ejercicio4
elfodomestico(dobby).
bruja(hermione).
bruja('McGonagall').
bruja(ritaskeeter).
bruja(house_elf).
bruja(mago).
mago(harry).
magia(X) :- elfodomestico(X).
magia(X) :- mago(X).
magia(X) :- bruja(X).
