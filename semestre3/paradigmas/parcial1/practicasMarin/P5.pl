%Aplicando la regla generar-comprobar
%1.1
%entradas
entrada(ensalada, 1500).
entrada(aguacateconatun, 1200).
entrada(arrozalajardinera, 1800).
entrada(consomedepollo, 1400).
entrada(spaghettiblanco, 1600).
entrada(alitasbbq, 6000).
entrada(nachosconqueso, 5500).

%platos principales
plato_principal(filetedepescado, 3500).
plato_principal(mixiotedepollo, 3800).
plato_principal(polloconpapas, 4200).
plato_principal(enchiladasdemole, 3900).
plato_principal(bisteck, 4600).
plato_principal(cangreburger, 13000).
plato_principal(hotdog, 10000).

%postres
postre(pastelchocolate, 9000).
postre(tiramisu, 10000).
postre(mazapan, 4500).
postre(platanosconcrema, 4200).
postre(gelatina, 1200).
postre(trozodesandia, 1000).
postre(donasdechocolate, 12000).

%funciones para comprobar
es_light(X):- X < 10000.%comprobar
es_razonable(X):-(X>=10000,X<20000).%comprobar
es_gloton(X):- X >= 20000.%comprobar
entrada_light(X):-X<1600.
plato_light(X):-X<4000.
postre_light(X):-X<1500.
entrada_razonable(X):-(X>=1600,X<5000).
plato_razonable(X):-(X>=4000,X<8000).
postre_razonable(X):-(X>=1500,X<5000).
entrada_gloton(X):-X>5000.
plato_gloton(X):-X>8000.
postre_gloton(X):-X>5000.

menu_light(Entrada, PlatoPrincipal, Postre, TotalCalorias) :-
    entrada(Entrada, CaloriasEntrada),
    plato_principal(PlatoPrincipal, CaloriasPlato),
    postre(Postre, CaloriasPostre),
    entrada_light(CaloriasEntrada),
    plato_light(CaloriasPlato),
    postre_light(CaloriasPostre),
    TotalCalorias is CaloriasEntrada + CaloriasPlato + CaloriasPostre,
    es_light(TotalCalorias).

menu_razonable(Entrada, PlatoPrincipal, Postre, TotalCalorias) :-
    entrada(Entrada, CaloriasEntrada),
    plato_principal(PlatoPrincipal, CaloriasPlato),
    postre(Postre, CaloriasPostre),
    entrada_razonable(CaloriasEntrada),
    plato_razonable(CaloriasPlato),
    postre_razonable(CaloriasPostre),
    TotalCalorias is CaloriasEntrada + CaloriasPlato + CaloriasPostre,
    es_razonable(TotalCalorias).

menu_gloton(Entrada, PlatoPrincipal, Postre, TotalCalorias) :-
    entrada(Entrada, CaloriasEntrada),
    plato_principal(PlatoPrincipal, CaloriasPlato),
    postre(Postre, CaloriasPostre),
    entrada_gloton(CaloriasEntrada),
    plato_gloton(CaloriasPlato),
    postre_gloton(CaloriasPostre),
    TotalCalorias is CaloriasEntrada + CaloriasPlato + CaloriasPostre,
    es_gloton(TotalCalorias).


