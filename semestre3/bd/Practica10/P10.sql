-- Muestra solo a las personas que su nombre tiene más de 5 letras
SELECT * FROM personas WHERE LENGTH(nombre) > 5;

-- Muestra a las personas que su nombre tiene entre 5 y 7 caracteres
SELECT * FROM personas WHERE LENGTH(nombre) BETWEEN 5 AND 7;

-- Muestra a las personas que su nombre tiene más de 7 caracteres y alguno de sus apellidos tenga entre 5 y 7 caracteres
SELECT * FROM personas WHERE LENGTH(nombre) > 7 AND (LENGTH(primerapellido) BETWEEN 5 AND 7 OR LENGTH(segundoapellido) BETWEEN 5 AND 7);

-- Muestra los primeros tres caracteres del nombre
SELECT SUBSTRING(nombre, 1, 3) AS primeros_tres_caracteres FROM personas;

-- Muestra los últimos 3 caracteres del nombre
SELECT SUBSTRING(nombre, LENGTH(nombre)-2, 3) AS ultimos_tres_caracteres FROM personas;

-- Muestra del 2do al 5to carácter del nombre
SELECT SUBSTRING(nombre, 2, 4) AS del_segundo_al_quinto_caracter FROM personas;

-- Reemplaza las 'd' por 's' en nombre
SELECT REPLACE(nombre, 'd', 's') AS nombre_reemplazado FROM personas;

-- Obtén la longitud del apellido paterno
SELECT LENGTH(primerapellido) AS longitud_primer_apellido FROM personas;

-- Muestra en mayúsculas el nombre
SELECT UPPER(nombre) AS nombre_mayusculas FROM personas;

-- Muestra en minúsculas el apellido paterno
SELECT LOWER(primerapellido) AS primer_apellido_minusculas FROM personas;

-- Muestra a las personas con su delegación, reemplazando Benito Juárez por B. Juárez
SELECT nombre, REPLACE(municipio, 'Benito Juárez', 'B. Juárez') AS delegacion FROM personas WHERE municipio = 'Benito Juárez';;

-- Muestra el nombre completo empezando por el apellido paterno con mayúsculas en una sola columna
SELECT UPPER(primerapellido) || ' ' || segundoapellido || ' ' || nombre AS nombre_completo FROM personas;

-- Muestra el nombre de las personas con las 'E' reemplazadas con el número 3
SELECT REPLACE(nombre, 'e', '3') AS nombre_reemplazado FROM personas;

-- Muestra el nombre completo de las personas con las 'o' reemplazados con el número 0 en una sola columna
SELECT REPLACE(primerapellido || ' ' || segundoapellido || ' ' || nombre, 'o', '0') AS nombre_completo FROM personas;
