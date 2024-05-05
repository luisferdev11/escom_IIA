hombre(bertram).
hombre(percival).
mujer(lucinda).
mujer(camila).
pareja(X,Y) :- hombre(X),mujer(Y).

% ?- pareja(percival, X).
% X = lucinda;
% X = camila.

% ?- pareja(apollo, daphne).
% false.

% ?- pareja(camila, X).
% false.

% ?- pareja(X, lucinda).
% X = bertram ;
% X = percival.

% ?- pareja(X, X).
% false.

% ?- pareja(bertram, lucinda).
% true.

% ?- pareja(X, fido).
% false.

% ?- pareja(X, Y).
% X = bertram,