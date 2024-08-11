-- Clasifica a los alumnos de acuerdo con el promedio que tienen de acuerdo a lo siguiente:
-- 3< ..... Sin Derecho a ETS
-- 3 a 5 ..... Con derecho a ETS
-- 5 a 8 Curso de Recuperacion
-- 8-mas..... Materia Aprobada

SELECT 
    p.id,
    p.nombre,
    p.primerapellido,
    p.segundoapellido,
    e.id_boleta,
    AVG(em.calificacion) AS promedio,
    CASE
        WHEN AVG(em.calificacion) < 3 THEN 'Sin Derecho a ETS'
        WHEN AVG(em.calificacion) BETWEEN 3 AND 5 THEN 'Con derecho a ETS'
        WHEN AVG(em.calificacion) BETWEEN 5 AND 8 THEN 'Curso de Recuperacion'
        WHEN AVG(em.calificacion) > 8 THEN 'Materia Aprobada'
    END AS clasificacion
FROM 
    personas p
JOIN 
    estudiantes e ON p.id = e.id_persona
JOIN 
    estudiante_materia em ON e.id_boleta = em.id_boleta
GROUP BY 
    p.id, e.id_boleta;



-- Genere el siguiente reporte a partir del formato que se presenta a continuacion:

--  /* PROMEDIO            CANTIDAD           CARRERA                      PLANTEL
-- -------------------------------------------------------------------------------------
--             0                               #                              CUALQUIERA                  CUALQUIERA
-- -------------------------------------------------------------------------------------
--             0-6                               #                        SUPERIOR                 CUALQUIERA
--                                                #                          MAESTRIA                 CUALQUIERA
--                                              #                       DOCTORADO                        CUALQUIERA
-- -------------------------------------------------------------------------------------
--             6-8                               #                        SUPERIOR                 CUALQUIERA
--                                                #                          MAESTRIA                 CUALQUIERA
--                                              #                       DOCTORADO                        CUALQUIERA
-- -----------------------------------------------------------------------------------------      
--   8 O MAS                        #                        APROBADOS                      
-- -------------------------------------------------------------------------------------
-- */


-- Calcular el promedio de cada estudiante
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
),

-- Obtener el nivel académico de cada estudiante basado en la clave de carrera
niveles_academicos AS (
    SELECT 
        e.id_persona,
        CASE 
            WHEN c.clave_carrera LIKE 'L%' THEN 'LICENCIATURA'
            WHEN c.clave_carrera LIKE 'M%' THEN 'MAESTRÍA'
            WHEN c.clave_carrera LIKE 'D%' THEN 'DOCTORADO'
        END AS nivel_academico,
        pl.nombre_plantel
    FROM 
        estudiantes e
    JOIN 
        estudiante_materia em ON e.id_boleta = em.id_boleta
    JOIN 
        materia m ON em.id_materia = m.id
    JOIN 
        carrera c ON m.id_carrera = c.id
    JOIN 
        plantel pl ON c.id_plantel = pl.id
),

-- Contar la cantidad de estudiantes por rango de promedio, nivel académico y plantel
conteo_promedios AS (
    SELECT 
        CASE
            WHEN p.promedio = 0 THEN '0'
            WHEN p.promedio BETWEEN 0 AND 6 THEN '0-6'
            WHEN p.promedio BETWEEN 6 AND 8 THEN '6-8'
            ELSE '8 O MAS'
        END AS rango_promedio,
        n.nivel_academico,
        n.nombre_plantel,
        COUNT(*) AS cantidad
    FROM 
        promedios p
    JOIN 
        niveles_academicos n ON p.id_persona = n.id_persona
    GROUP BY 
        rango_promedio, n.nivel_academico, n.nombre_plantel
)

-- Seleccionar y formatear el reporte final
SELECT 
    rango_promedio AS "PROMEDIO",
    cantidad AS "CANTIDAD",
    nivel_academico AS "CARRERA",
    nombre_plantel AS "PLANTEL"
FROM 
    conteo_promedios

UNION ALL

-- Adicionalmente, incluir los aprobados
SELECT 
    '8 O MAS' AS "PROMEDIO",
    COUNT(*) AS "CANTIDAD",
    'APROBADOS' AS "CARRERA",
    'CUALQUIERA' AS "PLANTEL"
FROM 
    promedios
WHERE 
    promedio >= 8

UNION ALL

-- Incluir el reporte de estudiantes con promedio 0
SELECT 
    '0' AS "PROMEDIO",
    COUNT(*) AS "CANTIDAD",
    'CUALQUIERA' AS "CARRERA",
    'CUALQUIERA' AS "PLANTEL"
FROM 
    promedios
WHERE 
    promedio = 0;
