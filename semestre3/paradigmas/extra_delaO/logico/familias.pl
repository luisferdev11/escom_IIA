% Definición de hombres y mujeres
hombre('Tomás García Pérez').
hombre('Juan García López').
hombre('José Pérez Ruiz').
hombre('Juan Luis Pérez Pérez').
hombre('José María Pérez Pérez').

mujer('Ana López Ruiz').
mujer('María García López').
mujer('Luisa Gálvez Pérez').
mujer('María José Pérez Pérez').

% Definición de padre y madre
padre('Tomás García Pérez', 'Juan García López').
padre('Tomás García Pérez', 'María García López').
padre('José Pérez Ruiz', 'Juan Luis Pérez Pérez').
padre('José Pérez Ruiz', 'María José Pérez Pérez').
padre('José Pérez Ruiz', 'José María Pérez Pérez').

madre('Ana López Ruiz', 'Juan García López').
madre('Ana López Ruiz', 'María García López').
madre('Luisa Gálvez Pérez', 'Juan Luis Pérez Pérez').
madre('Luisa Gálvez Pérez', 'María José Pérez Pérez').
madre('Luisa Gálvez Pérez', 'José María Pérez Pérez').

% Definición de hijo e hija
hijo('Juan García López', 'Tomás García Pérez', 'Ana López Ruiz').
hija('María García López', 'Tomás García Pérez', 'Ana López Ruiz').
hijo('Juan Luis Pérez Pérez', 'José Pérez Ruiz', 'Luisa Gálvez Pérez').
hija('María José Pérez Pérez', 'José Pérez Ruiz', 'Luisa Gálvez Pérez').
hijo('José María Pérez Pérez', 'José Pérez Ruiz', 'Luisa Gálvez Pérez').

% Definición de familias
familia(
    'Tomás García Pérez',
    'Ana López Ruiz',
    [
        'Juan García López',
        'María García López'
    ]
).

familia(
    'José Pérez Ruiz',
    'Luisa Gálvez Pérez',
    [
        'Juan Luis Pérez Pérez',
        'María José Pérez Pérez',
        'José María Pérez Pérez'
    ]
).

% Consultas sobre familias
familia_sin_hijos :-
    familia(_, _, []).

familia_un_hijo :-
    familia(_, _, [Hijo]),
    hijo(Hijo, _, _) ; hija(Hijo, _, _).

familia_dos_hijos :-
    familia(_, _, [_, _]).

familia_tres_hijos :-
    familia(_, _, [_, _, _]).

familia_cuatro_hijos :-
    familia(_, _, [_, _, _, _]).

% Buscar los nombres de los padres de familia con tres hijos
padres_familia_tres_hijos(Padre, Madre) :-
    familia(Padre, Madre, [_, _, _]).

% Definir relación casado(X) y preguntar por hombres casados
casado(X) :-
    familia(X, _, _),
    hombre(X).

hombres_casados(X) :-
    casado(X).

% Definir relación casada(X) y preguntar por mujeres casadas
casada(X) :-
    familia(_, X, _),
    mujer(X).

mujeres_casadas(X) :-
    casada(X).

% Determinar el nombre de todas las mujeres casadas que trabajan
trabaja('Ana López Ruiz').
trabaja('Luisa Gálvez Pérez').

mujeres_casadas_trabajan(Nombre) :-
    casada(Nombre),
    trabaja(Nombre).

% Definir relación hijo(X) y preguntar por los hijos
hijo(X) :-
    familia(_, _, Hijos),
    member(X, Hijos).

todos_los_hijos(X) :-
    hijo(X).
