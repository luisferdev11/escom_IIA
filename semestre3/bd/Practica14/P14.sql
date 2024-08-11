-- 1. Muestre solo a las personas que son Alumnos.
SELECT *
FROM personas
WHERE id IN (SELECT id_persona FROM estudiantes);

-- 2. Muestre solo a las personas que son Docentes.
SELECT *
FROM personas
WHERE id IN (SELECT id_persona FROM docente);

-- 3. Muestre el/los grupos de cada docente.
SELECT 
    g.grupo,
    (
        SELECT CONCAT(p.nombre, ' ', p.primerapellido, ' ', p.segundoapellido) AS nombre_profesor
        FROM Personas p
        WHERE p.id = (SELECT d.id_persona FROM docente d WHERE d.id_profesor = g.id_profesor)
    ) AS profesor
FROM 
    grupos g;

-- 4. ¿Qué alumno o alumnos han reprobado?
SELECT CONCAT(p.nombre, ' ', p.primerapellido, ' ', p.segundoapellido) AS alumnos_reprobados,
(
	SELECT MIN(em.calificacion)
	FROM estudiante_materia em
	WHERE em.id_boleta IN (
		SELECT e.id_boleta
		FROM estudiantes e
		WHERE e.id_persona = P.id
	)
) AS calificacion
FROM personas p
WHERE id IN (
    SELECT id_persona 
    FROM estudiantes 
    WHERE id_boleta IN (
        SELECT id_boleta 
        FROM estudiante_materia 
        WHERE calificacion < 6
    )
);

-- 5. ¿Qué promedio tiene cada estudiante?
SELECT 
    id_persona,
    (SELECT nombre FROM personas WHERE id = e.id_persona) AS nombre,
    (SELECT primerapellido FROM personas WHERE id = e.id_persona) AS primerapellido,
    (SELECT AVG(calificacion) FROM estudiante_materia WHERE id_boleta = e.id_boleta) AS promedio
FROM estudiantes e;

-- 6. ¿Qué materia tiene cada carrera?
SELECT nombre_materia AS materia, 
       (SELECT nombre_carrera 
        FROM Carrera c 
        WHERE m.id_carrera = c.id_carrera) AS carrera
FROM Materia m;

-- 7. ¿Qué materias se imparten a las 10:00 pm?
INSERT INTO horarios (id_materia, dia, hora_inicio, hora_fin, id_grupo, id_aula) VALUES 
(1, 'Lunes', '22:00:00', '23:00:00', 1, 1),  -- Laboratorio

SELECT *
FROM materia
WHERE id IN (
    SELECT id_materia 
    FROM horarios 
    WHERE hora_inicio = '22:00:00'
);

-- 8. ¿Qué carreras se imparten en qué plantel?
SELECT 
    nombre_carrera,
    (SELECT nombre_plantel FROM plantel WHERE id = c.id_plantel) AS nombre_plantel
FROM carrera c;

-- 9. Muestre el horario de cada laboratorio.
SELECT *
FROM horarios
WHERE id_aula IN (
    SELECT id 
    FROM aula 
    WHERE tipo = 'Laboratorio'
);

-- 10. ¿En qué delegación/municipio existen más docentes?
SELECT municipio, COUNT(*) AS numero_docentes
FROM personas
WHERE id IN (
    SELECT id_persona 
    FROM docente
)
GROUP BY municipio
ORDER BY numero_docentes DESC
LIMIT 1;