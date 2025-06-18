DIGIT     [0-9]
LETRA    [a-zA-Z]
MAYUS     [A-Z]
SPECIAL   [_*]
VOCAB   [a-zA-Z0-9_*]

P1        {VOCAB}*{MAYUS}{VOCAB}*{DIGIT}{VOCAB}*{SPECIAL}{VOCAB}*
P2        {VOCAB}*{MAYUS}{VOCAB}*{SPECIAL}{VOCAB}*{DIGIT}{VOCAB}*
P3        {VOCAB}*{DIGIT}{VOCAB}*{MAYUS}{VOCAB}*{SPECIAL}{VOCAB}*
P4        {VOCAB}*{DIGIT}{VOCAB}*{SPECIAL}{VOCAB}*{MAYUS}{VOCAB}*
P5        {VOCAB}*{SPECIAL}{VOCAB}*{MAYUS}{VOCAB}*{DIGIT}{VOCAB}*
P6        {VOCAB}*{SPECIAL}{VOCAB}*{DIGIT}{VOCAB}*{MAYUS}{VOCAB}*
PASSWORD  ({P1}|{P2}|{P3}|{P4}|{P5}|{P6})

ID        {LETRA}({LETRA}|{DIGIT})*
NUMBER    [0-9]+
INT       {NUMBER}
FLOAT     {NUMBER}\.{NUMBER}
EXP       ({INT}|{FLOAT})\^({INT})
MODFUNC   [Mm][Oo][Dd]\(({INT}|{FLOAT})\)

%%

{PASSWORD}              { printf("Contraseña válida: %s\n", yytext); }
{MODFUNC}               { printf("Función MOD: %s\n", yytext); }
{EXP}                   { printf("Potencia: %s\n", yytext); }
{FLOAT}                 { printf("Número decimal: %s\n", yytext); }
{ID}                     { printf("Nombre de variable: %s\n", yytext); }
"+"                     { printf("Operador de suma: %s\n", yytext); }
"-"                     { printf("Operador de resta: %s\n", yytext); }
"*"                     { printf("Operador de multiplicación: %s\n", yytext); }
"/"                     { printf("Operador de división: %s\n", yytext); }
{INT}                   { printf("Número entero: %s\n", yytext); }
[ \t\n]+                ;
.                       { printf("Carácter no reconocido: %s\n", yytext); }

%%