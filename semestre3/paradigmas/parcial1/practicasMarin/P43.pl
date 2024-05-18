%Ejercicio3
tienevarita(harry).
jugadordequidditch(harry).
mago(X):- tieneescoba(X), tienevarita(X).
mago(ron).
mago(hermione).
asistente(chava).
tieneescoba(X) :- jugadordequidditch(X).
bruja(X):-mago(X).
