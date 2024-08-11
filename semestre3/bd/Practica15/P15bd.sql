-- 1. Clasificar a los docentes según su edad:

SELECT
    P.nombre,
    P.fecha_nacimiento,
    DATE_PART('year', AGE(P.fecha_nacimiento)) as edad,
    'Docente Joven' AS clasificacion
FROM 
    Personas P
WHERE 
    DATE_PART('year', AGE(P.fecha_nacimiento)) >= 18 
    AND DATE_PART('year', AGE(P.fecha_nacimiento)) < 30 
    AND EXISTS (SELECT 1 FROM Docente D WHERE D.id_persona = P.id)

UNION

SELECT
    P.nombre,
    P.fecha_nacimiento,
    DATE_PART('year', AGE(P.fecha_nacimiento)) as edad,
    'Docente Veterano' AS clasificacion
FROM 
    Personas P
WHERE 
    DATE_PART('year', AGE(P.fecha_nacimiento)) >= 30 
    AND DATE_PART('year', AGE(P.fecha_nacimiento)) < 45 
    AND EXISTS (SELECT 1 FROM Docente D WHERE D.id_persona = P.id)

UNION

SELECT
    P.nombre,
    P.fecha_nacimiento,
    DATE_PART('year', AGE(P.fecha_nacimiento)) as edad,
    'Docente Antiguo' AS clasificacion
FROM 
    Personas P
WHERE 
    DATE_PART('year', AGE(P.fecha_nacimiento)) >= 45 
    AND DATE_PART('year', AGE(P.fecha_nacimiento)) < 65 
    AND EXISTS (SELECT 1 FROM Docente D WHERE D.id_persona = P.id)

UNION

SELECT
    P.nombre,
    P.fecha_nacimiento,
    DATE_PART('year', AGE(P.fecha_nacimiento)) as edad,
    'Docente casi Jubilado' AS clasificacion
FROM 
    Personas P
WHERE 
    DATE_PART('year', AGE(P.fecha_nacimiento)) > 65
    AND EXISTS (SELECT 1 FROM Docente D WHERE D.id_persona = P.id);

-- 2. Clasificar a los alumnos según su calificación:
SELECT
    EM.id_boleta as boleta,
    (SELECT nombre_materia FROM Materia M WHERE M.id = EM.id_materia) as materia,
    EM.calificacion,
    'Reprobado' AS clasificacion
FROM 
    estudiante_materia EM
WHERE 
    EM.calificacion < 5

UNION

SELECT
    EM.id_boleta as boleta,
    (SELECT nombre_materia FROM Materia M WHERE M.id = EM.id_materia) as materia,
    EM.calificacion,
    'Aplicar examen de recuperacion' AS clasificacion
FROM 
    estudiante_materia EM
WHERE 
    EM.calificacion >= 5 AND EM.calificacion < 6

UNION

SELECT
    EM.id_boleta as boleta,
    (SELECT nombre_materia FROM Materia M WHERE M.id = EM.id_materia) as materia,
    EM.calificacion,
    'Aprobado' AS clasificacion
FROM 
    estudiante_materia EM
WHERE 
    EM.calificacion >= 6 AND EM.calificacion < 8.6

UNION

SELECT
    EM.id_boleta as boleta,
    (SELECT nombre_materia FROM Materia M WHERE M.id = EM.id_materia) as materia,
    EM.calificacion,
    'Exento de Examen' AS clasificacion
FROM 
    estudiante_materia EM
WHERE 
    EM.calificacion >= 8.6;