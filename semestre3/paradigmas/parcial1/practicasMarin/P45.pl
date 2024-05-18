%Ejercicio5
palabra(articulo, una).
palabra(articulo, cada).
palabra(sustantivo, criminal).
palabra(sustantivo, 'gran hamburguesa kahuna').
palabra(verbo, comer).
palabra(verbo, gustar).
oración(Palabra1, Palabra2, Palabra3, Palabra4, Palabra5) :-
palabra(articulo,Palabra1),
palabra(sustantivo, Palabra2),
palabra(verbo, Palabra3),
palabra(articulo,Palabra4),
palabra(sustantivo, Palabra5).

