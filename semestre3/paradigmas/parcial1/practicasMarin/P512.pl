%Ejercicio 1.2
%Hechos
persona(aleman).
persona(britanico).
persona(sueco).
casa(verde).
casa(blanca).
casa(azul).
bebida(cafe).
bebida(agua).
bebida(te).
mascota(gato).
mascota(pez).
mascota(perro).

%validacion
aleman_valido(Aleman, Casa, Bebida, Mascota) :-
    ( (persona(Aleman), casa(Casa), bebida(Bebida), mascota(Mascota)),
    (Casa = verde, Aleman = aleman )),
    (( Bebida = agua, Mascota = pez )).

sueco_valido(Sueco, Casa, Bebida, Mascota) :-
    (( persona(Sueco), casa(Casa), bebida(Bebida), mascota(Mascota) ),
    ( Sueco=sueco ,Bebida = cafe, \+ Casa = azul, \+ Casa = verde )),
    (( Bebida = agua, Mascota = pez ) ; ( Mascota = perro, Casa = blanca )).

britanico_valido(Britanico, Casa, Bebida, Mascota) :-
    ((persona(Britanico), casa(Casa), bebida(Bebida), mascota(Mascota)),
    (Britanico=britanico,\+ Mascota = gato)),
    (( Bebida = agua, Mascota = pez ) ; ( Mascota = perro, Casa = blanca ) ).

combinacion_valida(Persona, Casa, Bebida, Mascota) :-
    (aleman_valido(Persona, Casa, Bebida, Mascota),not(sueco_valido(Persona, Casa, Bebida, Mascota)), not(britanico_valido(Persona, Casa, Bebida, Mascota)));
    (sueco_valido(Persona, Casa, Bebida, Mascota), not(aleman_valido(Persona, Casa, Bebida, Mascota)), not(britanico_valido(Persona, Casa, Bebida, Mascota)));
    (britanico_valido(Persona, Casa, Bebida, Mascota), not(aleman_valido(Persona, Casa, Bebida, Mascota)), not(sueco_valido(Persona, Casa, Bebida, Mascota))).