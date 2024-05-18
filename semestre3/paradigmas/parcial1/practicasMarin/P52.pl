% Predicado para calcular el factorial de un número
factorial(0, 1).
factorial(N, Resultado) :-
    N > 0,
    N1 is N-1,
    factorial(N1, Subresultado),
    Resultado is N*Subresultado.

% Predicado para calcular el n-ésimo término de la sucesión de Fibonacci
fibonacci(0, 0).
fibonacci(1, 1).
fibonacci(N, Resultado) :-
    N > 1,
    N1 is N - 1,
    N2 is N - 2,
    fibonacci(N1, Fib1),
    fibonacci(N2, Fib2),
    Resultado is Fib1 + Fib2.

