SELECT * FROM personas WHERE nombre = 'Eduardo';
SELECT * FROM personas WHERE nombre != 'Eduardo';

SELECT numero_docente, id_persona, area_especialidad 
FROM docente 
WHERE grado_academico = 'Maestría';

SELECT numero_docente, id_persona, area_especialidad 
FROM docente 
WHERE grado_academico != 'Maestría';

SELECT CONCAT(nombre, ' ', segundo_nombre, ' ', primerapellido, ' ', segundoapellido) AS nombre_completo, municipio 
FROM personas 
WHERE ciudad = 'Ciudad de México';

SELECT CONCAT(nombre, ' ', segundo_nombre, ' ', primerapellido, ' ', segundoapellido) AS nombre_completo, municipio 
FROM personas 
WHERE ciudad != 'Ciudad de México';


SELECT CONCAT(nombre, ' ', segundo_nombre, ' ', primerapellido, ' ', segundoapellido) AS nombre_completo 
FROM personas 
WHERE genero = 'Femenino';


SELECT CONCAT('La persona ', nombre, ' ', segundo_nombre, ' ', primerapellido, ' ', segundoapellido, ' vive en la delegación o Municipio ', municipio) AS leyenda 
FROM personas;


SELECT nombre_materia, semestre 
FROM Materia;

SELECT CONCAT('En la academia de ', academia, ' posee la materia ', nombre_materia, ' con ', creditos, ' créditos.') AS leyenda 
FROM Materia;
