-- 1. Muestre solo a las personas que son Alumnos:

SELECT p.*, e.id_boleta
FROM personas p
JOIN estudiantes e ON p.id = e.id_persona;
-- 2. Muestre solo a las personas que son Docentes:

SELECT p.*
FROM personas p
JOIN docente d ON p.id = d.id_persona;
-- 3. Muestre el/los grupos de cada docente:

SELECT d.id_persona, p.nombre, p.primerapellido, p.segundoapellido, g.codigo_grupo
FROM docente d
JOIN personas p ON d.id_persona = p.id
JOIN grupos g ON d.id_persona = g.id_docente;
-- 4. ¿Qué alumno o alumnos han reprobado?

SELECT p.*, em.calificacion
FROM personas p
JOIN estudiantes e ON p.id = e.id_persona
JOIN estudiante_materia em ON e.id_boleta = em.id_boleta
WHERE em.calificacion < 6.0;
-- 5. ¿Qué promedio tiene cada estudiante?

SELECT p.*, e.id_boleta, AVG(em.calificacion) AS promedio
FROM personas p
JOIN estudiantes e ON p.id = e.id_persona
JOIN estudiante_materia em ON e.id_boleta = em.id_boleta
GROUP BY p.id, e.id_boleta;
-- 6. ¿Qué materia tiene cada carrera?

SELECT c.nombre_carrera, m.nombre_materia
FROM carrera c
JOIN materia m ON c.id = m.id_carrera;
-- 7. ¿Qué materias se imparten a las 10:00 pm?

SELECT m.nombre_materia, h.*
FROM materia m
JOIN horarios h ON m.id = h.id_materia
WHERE h.hora_inicio = '22:00:00';
-- 8. ¿Qué carreras se imparten en qué plantel?

SELECT p.nombre_plantel, c.nombre_carrera
FROM plantel p
JOIN carrera c ON p.id = c.id_plantel;
-- 9. Muestre el horario de cada laboratorio:

SELECT a.nombre_aula, h.*
FROM aula a
JOIN horarios h ON a.id = h.id_aula
WHERE a.tipo = 'Laboratorio';
-- 10. ¿En qué delegación/municipio existen más docentes?

SELECT p.municipio, COUNT(d.id_persona) AS numero_docentes
FROM personas p
JOIN docente d ON p.id = d.id_persona
GROUP BY p.municipio
ORDER BY numero_docentes DESC
LIMIT 1;