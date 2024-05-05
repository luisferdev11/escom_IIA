es_par(X):- X mod 2 =:= 0.
suma(X,Y,N):- X + Y =:= N.
resta(N,X,Y):- N - X =:= Y.
es_impar(X):- X mod 2 =:= 1.
menor_igual(X,N):- X =< N.
mayor(X,N):- X > N.

%primerasolucion
en_pares1(N,X,Y):-
    es_par(X),    %generar
    es_par(Y),    %generar
    suma(X,Y,N).    %comprobar

%segundasolucion
en_pares2(N,X,Y):-
    menor_igual(X,N),    %generar
    menor_igual(Y,N),    %generar
    suma(X,Y,N),    %comprobar
    es_par(X),    %comprobar
    es_par(Y).    %comprobar

%tercerasolucion
en_pares3(N,X,Y):-
    menor_igual(X,N),    %generar
    es_par(X),    %comprobar
    suma(X,Y,N),    %generar
    es_par(Y).    %comprobar

%cuartasolucion
en_pares4(N,X,Y):-
    suma(X,Y,N),    %generar
    es_par(X),    %comprobar
    es_par(Y).    %comprobar

%quintasolucion
en_pares5(N,X,Y):-
    es_par(N),    %comprobar
    suma(X,Y,N),    %generar
    es_par(Y).    %comprobar

%sextasolucion
en_pares6(N,X,Y):-
    resta(N,X,Y),    %generar
    es_par(N),    %comprobar
    es_par(X).    %comprobar

%septimasolucion
en_pares7(N,X,Y):-
    not(es_impar(X)),    %comprobar
    suma(X,Y,N),    %generar
    not(es_impar(Y)).    %comprobar

%octavasolucion
en_pares8(N,X,Y):-
    resta(N,X,Y),    %generar
    not(es_impar(N)),    %comprobar
    not(es_impar(X)).    %comprobar

%novenasolucion
en_pares9(N,X,Y):-
    not(es_impar(N)),    %comprobar
    suma(X,Y,N),    %generar
    not(es_impar(Y)).    %comprobar

%decimasolucion
en_pares10(N,X,Y):-
    not(mayor(X,N)),    %generar
    es_par(X),    %comprobar
    not(es_impar(N)),    %comprobar
    suma(X,Y,N).    %generar