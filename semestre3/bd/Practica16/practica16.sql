-- 1. Muestra el nombre completo, boleta, materia y horario de los estudiantes
SELECT 
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    e.id_boleta,
    m.nombre_materia,
    h.dia,
    h.hora_inicio,
    h.hora_fin
FROM 
    personas p
JOIN 
    estudiantes e ON p.id = e.id_persona
JOIN 
    estudiante_materia em ON e.id_boleta = em.id_boleta
JOIN 
    materia m ON em.id_materia = m.id
JOIN 
    horarios h ON m.id = h.id_materia;

-- 2. Muestra el nombre completo, grado académico y materia que imparten los docentes
SELECT 
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    d.grado_academico,
    m.nombre_materia
FROM 
    docente d
JOIN 
    personas p ON d.id_persona = p.id
JOIN 
    grupos g ON d.id_profesor = g.id_profesor
JOIN 
    materia m ON g.id_materia = m.id;

-- 3. Muestra el nombre y la boleta de los estudiantes con materias en maestría
SELECT 
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    e.id_boleta
FROM 
    estudiantes e
JOIN 
    personas p ON e.id_persona = p.id
JOIN 
    estudiante_materia em ON e.id_boleta = em.id_boleta
JOIN 
    materia m ON em.id_materia = m.id
JOIN 
    carrera c ON m.id_carrera = c.id
WHERE 
    c.clave_carrera LIKE 'M%';


-- 4. Muestra la boleta y el nombre de los estudiantes indicando en qué materias reprobaron
SELECT 
    e.id_boleta,
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    m.nombre_materia
FROM 
    estudiantes e
JOIN 
    personas p ON e.id_persona = p.id
JOIN 
    estudiante_materia em ON e.id_boleta = em.id_boleta
JOIN 
    materia m ON em.id_materia = m.id
WHERE 
    em.calificacion < 6;


-- 5. Muestra las carreras y materias que se imparten en cada plantel
SELECT 
    pl.nombre_plantel,
    c.nombre_carrera,
    m.nombre_materia
FROM 
    plantel pl
JOIN 
    carrera c ON pl.id = c.id_plantel
JOIN 
    materia m ON c.id = m.id_carrera;

-- 6. ¿Qué planteles aún no tienen una carrera asignada?
SELECT 
    pl.nombre_plantel
FROM 
    plantel pl
LEFT JOIN 
    carrera c ON pl.id = c.id_plantel
WHERE 
    c.id IS NULL;

-- 7. Indica en qué aulas y carreras se imparten las materias de Bases de Datos
SELECT 
    a.nombre_aula,
    c.nombre_carrera
FROM 
    aula a
JOIN 
    horarios h ON a.id = h.id_aula
JOIN 
    materia m ON h.id_materia = m.id
JOIN 
    carrera c ON m.id_carrera = c.id
WHERE 
    m.nombre_materia = 'Bases de Datos';

-- 8. Muestra los grupos y el horario que tienen
SELECT 
    g.codigo_grupo,
    h.dia,
    h.hora_inicio,
    h.hora_fin
FROM 
    grupos g
JOIN 
    horarios h ON g.id = h.id_grupo;

-- 9. Muestra las delegaciones con más de 2 personas y señala qué son (Docente/Alumno)
SELECT 
    p.municipio,
    CASE
        WHEN d.id_persona IS NOT NULL THEN 'Docente'
        WHEN e.id_persona IS NOT NULL THEN 'Alumno'
    END AS tipo,
    COUNT(*) AS total_personas
FROM 
    personas p
LEFT JOIN 
    docente d ON p.id = d.id_persona
LEFT JOIN 
    estudiantes e ON p.id = e.id_persona
GROUP BY 
    p.municipio, tipo
HAVING 
    COUNT(*) > 2;

-- 10. Muestra la boleta y nombre del alumno que toma más de 3 materias
SELECT 
    e.boleta,
    p.nombre || ' ' || p.primerapellido || ' ' || p.segundoapellido AS nombre_completo,
    COUNT(em.id_materia) AS total_materias
FROM 
    personas p
JOIN 
    estudiantes e ON p.id = e.id_persona
JOIN 
    estudiante_materia em ON e.boleta = em.boleta
GROUP BY 
    e.boleta, p.nombre, p.primerapellido, p.segundoapellido
HAVING 
    COUNT(em.id_materia) > 3;