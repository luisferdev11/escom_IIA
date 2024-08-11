-- 1. Muestra el total de docentes por plantel
SELECT 
    pl.nombre_plantel,
    COUNT(DISTINCT d.id_profesor) AS total_docentes
FROM 
    docente d
JOIN 
    grupos g ON d.id_profesor = g.id_profesor
JOIN 
    materia m ON g.id_materia = m.id
JOIN 
    carrera c ON m.id_carrera = c.id
JOIN 
    plantel pl ON c.id_plantel = pl.id
GROUP BY 
    pl.nombre_plantel;

-- 2. ¿Cuántas personas están registradas de Gustavo A. Madero o Azcapotzalco?
SELECT 
    COUNT(*) AS total_personas
FROM 
    personas
WHERE 
    municipio IN ('Gustavo A. Madero', 'Azcapotzalco');

-- 3. ¿Cuál es el promedio por delegación de los alumnos?
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
    p.municipio,
    AVG(pr.promedio) AS promedio_delegacion
FROM 
    personas p
JOIN 
    promedios pr ON p.id = pr.id_persona
GROUP BY 
    p.municipio;

-- 4. ¿Cuántos docentes tenemos de cada grado académico?
SELECT 
    grado_academico,
    COUNT(*) AS total_docentes
FROM 
    docente
GROUP BY 
    grado_academico;

-- 5. ¿Cuántos docentes tenemos por carrera?
SELECT 
    c.nombre_carrera,
    COUNT(DISTINCT d.id_profesor) AS total_docentes
FROM 
    docente d
JOIN 
    grupos g ON d.id_profesor = g.id_profesor
JOIN 
    materia m ON g.id_materia = m.id
JOIN 
    carrera c ON m.id_carrera = c.id
GROUP BY 
    c.nombre_carrera;

-- 6. Muestra el total de personas dadas de alta por delegación
SELECT 
    municipio,
    COUNT(*) AS total_personas
FROM 
    personas
WHERE municipio IS NOT NULL
GROUP BY 
    municipio
ORDER BY
	total_personas DESC;

-- 7. Muestra el total de docentes por materia
SELECT 
    m.nombre_materia,
    COUNT(DISTINCT d.id_profesor) AS total_docentes
FROM 
    docente d
JOIN 
    grupos g ON d.id_profesor = g.id_profesor
JOIN 
    materia m ON g.id_materia = m.id
GROUP BY 
    m.nombre_materia;

-- 8. Muestra el promedio más alto, el promedio bajo y el promedio general de los alumnos
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
    MAX(promedio) AS promedio_mas_alto,
    MIN(promedio) AS promedio_mas_bajo,
    AVG(promedio) AS promedio_general
FROM 
    promedios;

-- 9. Reporte del total de las personas que nacieron en cada año, pero solo para los años en los que nacieron 3 o más personas
SELECT 
    EXTRACT(YEAR FROM fecha_nacimiento) AS anio_nacimiento,
    COUNT(*) AS total_personas
FROM 
    personas
WHERE fecha_nacimiento IS NOT NULL
GROUP BY 
    anio_nacimiento
HAVING 
    COUNT(*) >= 3;


-- 10. Reporte de delegaciones con #Alumnos, Promedio Edad de Alumnos, #Docentes y Promedio Edad de Docentes
WITH alumnos AS (
    SELECT 
        p.municipio,
        COUNT(DISTINCT e.id_persona) AS num_alumnos,
        AVG(EXTRACT(YEAR FROM AGE(NOW(), p.fecha_nacimiento))) AS promedio_edad_alumnos
    FROM 
        personas p
    JOIN 
        estudiantes e ON p.id = e.id_persona
    GROUP BY 
        p.municipio
),
docentes AS (
    SELECT 
        p.municipio,
        COUNT(DISTINCT d.id_persona) AS num_docentes,
        AVG(EXTRACT(YEAR FROM AGE(NOW(), p.fecha_nacimiento))) AS promedio_edad_docentes
    FROM 
        personas p
    JOIN 
        docente d ON p.id = d.id_persona
    GROUP BY 
        p.municipio
)
SELECT 
    COALESCE(a.municipio, d.municipio) AS delegacion,
    COALESCE(a.num_alumnos, 0) AS num_alumnos,
    COALESCE(a.promedio_edad_alumnos, 0) AS promedio_edad_alumnos,
    COALESCE(d.num_docentes, 0) AS num_docentes,
    COALESCE(d.promedio_edad_docentes, 0) AS promedio_edad_docentes
FROM 
    alumnos a
FULL OUTER JOIN 
    docentes d ON a.municipio = d.municipio
ORDER BY 
    delegacion;