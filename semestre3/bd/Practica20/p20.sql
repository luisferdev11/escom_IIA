-- 1. Vista de resumen de alumnos
CREATE VIEW vista_resumen_alumnos AS
WITH detalles_alumnos AS (
    SELECT 
        p.id AS id_persona,
        p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
        m.nombre_materia,
        h.dia,
        h.hora_inicio,
        h.hora_fin,
        g.grupo,
        dp.nombre || ' ' || dp.primerapellido || ' ' || dp.segundoapellido AS docente
    FROM 
        personas p
    JOIN 
        estudiantes e ON p.id = e.id_persona
    LEFT JOIN 
        estudiante_materia em ON e.id_boleta = em.id_boleta
    LEFT JOIN 
        materia m ON em.id_materia = m.id
    LEFT JOIN 
        horarios h ON m.id = h.id_materia
    LEFT JOIN 
        grupos g ON h.id_grupo = g.id
    LEFT JOIN 
        docente d ON g.id_profesor = d.id_profesor
    LEFT JOIN 
        personas dp ON d.id_persona = dp.id
)
SELECT 
    nombre_completo,
    COALESCE(nombre_materia, 'S/N') AS nombre_materia,
    COALESCE(dia || ' ' || hora_inicio::text || '-' || hora_fin::text, 'S/N') AS horario,
    COALESCE(grupo, 'S/N') AS grupo,
    COALESCE(docente, 'S/N') AS docente
FROM 
    detalles_alumnos;

-- 2. Vista de información de los docentes
CREATE VIEW vista_info_docentes AS
SELECT DISTINCT
    p.id,
    p.nombre,
    p.primerapellido,
    p.segundoapellido,
    p.fecha_nacimiento,
    p.municipio AS delegacion,
    EXTRACT(YEAR FROM AGE(NOW(), p.fecha_nacimiento)) AS edad,
    d.grado_academico,
    pl.nombre_plantel
FROM 
    personas p
JOIN 
    docente d ON p.id = d.id_persona
JOIN 
    grupos g ON d.id_profesor = g.id_profesor
JOIN 
    materia m ON g.id_materia = m.id
JOIN 
    carrera c ON m.id_carrera = c.id
JOIN 
    plantel pl ON c.id_plantel = pl.id;

-- 3. Vista con información de las materias
CREATE VIEW vista_info_materias AS
SELECT 
	m.nombre_materia,
	p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_docente,
    c.nombre_carrera,
    m.clave AS codigo_materia,
    pl.nombre_plantel
FROM 
    materia m
JOIN 
    grupos g ON m.id = g.id_materia
JOIN 
    docente d ON g.id_profesor = d.id_profesor
JOIN 
    personas p ON d.id_persona = p.id
JOIN 
    carrera c ON m.id_carrera = c.id
JOIN 
    plantel pl ON c.id_plantel = pl.id;