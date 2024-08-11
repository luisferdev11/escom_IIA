-- 1. Muestra a la primer persona con mayor edad
SELECT 
    *
FROM 
    personas
ORDER BY 
    fecha_nacimiento ASC
LIMIT 1;

-- 2. Muestra al alumno con el promedio más alto
WITH promedios AS (
    SELECT 
        e.id_persona,
        AVG(em.calificacion) AS promedio
    FROM 
        estudiantes e
    JOIN 
        estudiante_materia em ON e.id_boleta = em.id_boleta
    GROUP BY 
        e.id_persona
)
SELECT 
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    pr.promedio
FROM 
    personas p
JOIN 
    promedios pr ON p.id = pr.id_persona
ORDER BY 
    pr.promedio DESC
LIMIT 1;

-- 3. Muestra a las personas ordenadas alfabéticamente por nombre
SELECT 
    *
FROM 
    personas
ORDER BY 
    nombre ASC;

-- 4. Muestra las primeras 3 personas de Azcapotzalco
SELECT 
    *
FROM 
    personas
WHERE 
    municipio = 'Azcapotzalco'
ORDER BY 
    id
LIMIT 3;

-- 5. Muestra los alumnos ordenados de acuerdo con su promedio de manera descendente
WITH promedios AS (
    SELECT 
        e.id_persona,
        AVG(em.calificacion) AS promedio
    FROM 
        estudiantes e
    JOIN 
        estudiante_materia em ON e.id_boleta = em.id_boleta
    GROUP BY 
        e.id_persona
)
SELECT 
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    pr.promedio
FROM 
    personas p
JOIN 
    promedios pr ON p.id = pr.id_persona
ORDER BY 
    pr.promedio DESC;

-- 6. Muestra a los 5 primeros docentes que tienen un doctorado
SELECT 
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    d.grado_academico
FROM 
    personas p
JOIN 
    docente d ON p.id = d.id_persona
WHERE 
    d.grado_academico = 'Doctorado'
ORDER BY 
    p.id
LIMIT 5;

-- 7. Muestra los alumnos ordenados por delegación, las delegaciones deben estar en orden ascendente y los alumnos de cada delegación ordenados en forma descendente basados en su promedio
WITH promedios AS (
    SELECT 
        e.id_persona,
        AVG(em.calificacion) AS promedio
    FROM 
        estudiantes e
    JOIN 
        estudiante_materia em ON e.id_boleta = em.id_boleta
    GROUP BY 
        e.id_persona
)
SELECT 
    p.municipio as delegacion,
    pr.promedio, 
	p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo
FROM 
    personas p
JOIN 
    promedios pr ON p.id = pr.id_persona
ORDER BY 
    p.municipio ASC,
    pr.promedio DESC;