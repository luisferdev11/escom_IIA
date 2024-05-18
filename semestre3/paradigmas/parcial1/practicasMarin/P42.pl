%Ejercicio2
bebe(john,martini).
bebe(mary,ginebra).
bebe(susan,vodka).
bebe(john,ginebra).
bebe(fred,ginebra).
mismo(X,Y):-not(X=Y).
par(X,Y,Z):-bebe(X,Z),bebe(Y,Z), mismo(X,Y).

