bebe(john, martini).
bebe(mary, ginebra).
bebe(susan, vodka).
bebe(john, ginebra).
bebe(fred, ginebra).
par(X, Y, Z) :- bebe(X, Z), bebe(Y, Z).

% ?- par(X, john, martini).
% X = john.

% ?- par(mary, susan, ginebra).
% false.

% ?- par(john, mary, ginebra).
% true ;
% false.

% ?- par(john, john, ginebra).
% ?- par(X, Y, ginebra).
% ?- pareja(bertram, lucinda, vodka).
% ?- pareja(X, Y, Z).