Voy a proporcionar las consultas SQL para cada uno de los requerimientos, incluyendo las transformaciones específicas de los caracteres en los nombres. Aquí están las consultas:

-- 1. **Muestra el nombre de las personas reemplazando los siguientes caracteres A-->@, E-->3, I-->!, O-->0 (Murcielago--> Murc!3l@g0):**
   
SELECT 
  REPLACE(
    REPLACE(
      REPLACE (
        REPLACE(
          REPLACE(
            REPLACE(
              REPLACE(
                REPLACE(nombre, 'A', '@'), 
                'E', 
                '3'
              ), 
              'I', 
              '!'
            ), 
            'O', 
            '0'
          ), 
          'a', 
          '@'
        ), 
        'e', 
        '3'
      ), 
      'i', 
      '!'
    ), 
    'o', 
    '0'
  ) AS nombre_transformado 
FROM 
  personas;

-- 2. **Convierte los primeros tres caracteres del nombre en mayúscula (Edgar-->EDgar):**
   
SELECT 
    UPPER(SUBSTRING(nombre, 1, 3)) || SUBSTRING(nombre, 4) AS nombre_transformado 
FROM personas;
   

-- 3. **Convierte el último carácter del nombre en mayúsculas (Edgar-->EdgaR):**
   
SELECT 
    SUBSTRING(nombre, 1, LENGTH(nombre) - 1) || UPPER(SUBSTRING(nombre, LENGTH(nombre), 1)) AS nombre_transformado 
FROM personas;
   

-- 4. **Convierte el 3er carácter del nombre en Mayúscula (Edgar--> EdGar):**
   
SELECT 
    SUBSTRING(nombre, 1, 2) || UPPER(SUBSTRING(nombre, 3, 1)) || SUBSTRING(nombre, 4) AS nombre_transformado 
FROM personas;


-- 5. **Convierte el 2do y 4to carácter del nombre a Mayúscula(Edgar-->EDgAr):**
   
SELECT 
    SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || 
    SUBSTRING(nombre, 3, 1) || UPPER(SUBSTRING(nombre, 4, 1)) || 
    SUBSTRING(nombre, 5) AS nombre_transformado 
FROM personas;


-- 6. **Convierte a mayúsculas el segundo y último carácter (Armando-->ArmandO):**
   
SELECT 
    SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || 
    SUBSTRING(nombre, 3, LENGTH(nombre) - 3) || UPPER(SUBSTRING(nombre, LENGTH(nombre), 1)) AS nombre_transformado 
FROM personas;
   

-- 7. **Convierte a mayúscula el segundo, cuarto y penúltimo carácter del nombre (Armando--> ARmAnDo):**
   
-- SELECT nombre,
--     CASE 
--         WHEN length(nombre) <= 4 THEN 
--             left(nombre, 1) || upper(substring(nombre, 2))
--         WHEN length(nombre) = 5 THEN 
--             left(nombre, 1) || upper(substring(nombre, 2, 1)) || substring(nombre, 3, 1) || upper(substring(nombre, 4, 1)) || substring(nombre, 5, 1)
--         ELSE 
--             left(nombre, 1) || upper(substring(nombre, 2, 1)) || substring(nombre, 3, 1) || upper(substring(nombre, 4, 1)) || substring(nombre, 5, length(nombre) - 6) || upper(substring(nombre, length(nombre) - 1, 1)) || substring(nombre, length(nombre), 1)
--     END AS nombre_transformado
-- FROM personas;

SELECT 
    nombre,
    CASE 
        WHEN length(nombre) > 4 THEN 
		(
			CASE 
        WHEN LENGTH(CASE 
    WHEN LENGTH(nombre) >= 4 
    THEN 
      SUBSTRING(nombre, 1, 1) || 
      UPPER(SUBSTRING(nombre, 2, 1)) || 
      SUBSTRING(nombre, 3, 1) || 
      UPPER(SUBSTRING(nombre, 4, 1)) || 
      CASE 
        WHEN LENGTH(nombre) > 4 
        THEN 
          SUBSTRING(nombre, 5, LENGTH(nombre) - 5 ) || 
          UPPER(SUBSTRING(nombre, LENGTH(nombre) - 1, 1)) || 
          SUBSTRING(nombre, LENGTH(nombre), 1) 
        ELSE ''
      END 
    ELSE 
      CASE 
        WHEN LENGTH(nombre) >= 2 
        THEN SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || SUBSTRING(nombre, 3) 
        ELSE nombre
      END
  END) >= 3 THEN 
            LEFT((CASE 
    WHEN LENGTH(nombre) >= 4 
    THEN 
      SUBSTRING(nombre, 1, 1) || 
      UPPER(SUBSTRING(nombre, 2, 1)) || 
      SUBSTRING(nombre, 3, 1) || 
      UPPER(SUBSTRING(nombre, 4, 1)) || 
      CASE 
        WHEN LENGTH(nombre) > 4 
        THEN 
          SUBSTRING(nombre, 5, LENGTH(nombre) - 5 ) || 
          UPPER(SUBSTRING(nombre, LENGTH(nombre) - 1, 1)) || 
          SUBSTRING(nombre, LENGTH(nombre), 1) 
        ELSE ''
      END 
    ELSE 
      CASE 
        WHEN LENGTH(nombre) >= 2 
        THEN SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || SUBSTRING(nombre, 3) 
        ELSE nombre
      END
  END), LENGTH((CASE 
    WHEN LENGTH(nombre) >= 4 
    THEN 
      SUBSTRING(nombre, 1, 1) || 
      UPPER(SUBSTRING(nombre, 2, 1)) || 
      SUBSTRING(nombre, 3, 1) || 
      UPPER(SUBSTRING(nombre, 4, 1)) || 
      CASE 
        WHEN LENGTH(nombre) > 4 
        THEN 
          SUBSTRING(nombre, 5, LENGTH(nombre) - 5 ) || 
          UPPER(SUBSTRING(nombre, LENGTH(nombre) - 1, 1)) || 
          SUBSTRING(nombre, LENGTH(nombre), 1) 
        ELSE ''
      END 
    ELSE 
      CASE 
        WHEN LENGTH(nombre) >= 2 
        THEN SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || SUBSTRING(nombre, 3) 
        ELSE nombre
      END
  END)) - 3) || RIGHT((CASE 
    WHEN LENGTH(nombre) >= 4 
    THEN 
      SUBSTRING(nombre, 1, 1) || 
      UPPER(SUBSTRING(nombre, 2, 1)) || 
      SUBSTRING(nombre, 3, 1) || 
      UPPER(SUBSTRING(nombre, 4, 1)) || 
      CASE 
        WHEN LENGTH(nombre) > 4 
        THEN 
          SUBSTRING(nombre, 5, LENGTH(nombre) - 5 ) || 
          UPPER(SUBSTRING(nombre, LENGTH(nombre) - 1, 1)) ||
          SUBSTRING(nombre, LENGTH(nombre), 1) 
        ELSE ''
      END 
    ELSE 
      CASE 
        WHEN LENGTH(nombre) >= 2 
        THEN SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || SUBSTRING(nombre, 3) 
        ELSE nombre
      END
  END), 2)
        ELSE 
            nombre
    END
		)
        WHEN length(nombre) = 4 THEN 
		(SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || UPPER(SUBSTRING(nombre, 3)))
		ELSE
		(SUBSTRING(nombre, 1, 1) || UPPER(SUBSTRING(nombre, 2, 1)) || SUBSTRING(nombre, 3))
    END AS longitud_nombre
FROM personas;