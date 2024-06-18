SELECT CURRENT_DATE AS fecha_actual;

SELECT CURRENT_DATE + INTERVAL '7 days' AS fecha_en_una_semana;

SELECT id, nombre, primerapellido, EXTRACT(YEAR FROM AGE(fecha_nacimiento)) AS edad FROM personas WHERE fecha_nacimiento is not null;

SELECT id, nombre, primerapellido, EXTRACT(YEAR FROM fecha_nacimiento) AS año, EXTRACT(MONTH FROM fecha_nacimiento) AS mes, EXTRACT(DAY FROM fecha_nacimiento) AS dia FROM personas WHERE fecha_nacimiento IS NOT NULL;

SELECT 'el día de hoy [' || TO_CHAR(CURRENT_DATE, 'DD/MM/YYYY') || '] es [' || TO_CHAR(CURRENT_DATE, 'Day') || ']' AS mensaje;

INSERT INTO personas (nombre, segundo_nombre, primerapellido, segundoapellido, genero, ciudad, municipio, direccion, fecha_nacimiento, telefono)
VALUES 
('Roberto', 'Carlos', 'Alvarado', 'García', 'Masculino', 'Ciudad de México', 'Coyoacán', 'CDMX', '01/01/1990', '5512345678');
SELECT nombre || ' ' || primerapellido || ' se nació el [' || TO_CHAR(fecha_nacimiento, 'Day') || '] [' || TO_CHAR(fecha_nacimiento, 'DD/MM/YYYY') || ']' AS mensaje FROM personas WHERE nombre = 'Roberto' AND primerapellido = 'Alvarado';

SELECT * FROM personas WHERE EXTRACT(YEAR FROM fecha_nacimiento) = 2010;

SELECT * FROM personas WHERE EXTRACT(MONTH FROM fecha_nacimiento) = 12;

SELECT * FROM personas WHERE EXTRACT(MONTH FROM fecha_nacimiento) = 2 AND EXTRACT(YEAR FROM fecha_nacimiento) = 1999;

SELECT * FROM personas WHERE AGE(fecha_nacimiento) < INTERVAL '6 months';

SELECT * FROM personas WHERE EXTRACT(YEAR FROM AGE(fecha_nacimiento)) < 30;

SELECT * FROM personas WHERE EXTRACT(MONTH FROM fecha_nacimiento) = EXTRACT(MONTH FROM CURRENT_DATE) AND EXTRACT(DAY FROM fecha_nacimiento) = EXTRACT(DAY FROM CURRENT_DATE);

SELECT * FROM personas WHERE EXTRACT(MONTH FROM fecha_nacimiento) IN (1, 2, 3, 4);

SELECT * FROM personas WHERE EXTRACT(YEAR FROM AGE(fecha_nacimiento)) BETWEEN 20 AND 40;

SELECT * FROM personas WHERE EXTRACT(YEAR FROM AGE(fecha_nacimiento)) > 40;

SELECT * FROM personas WHERE EXTRACT(YEAR FROM AGE(fecha_nacimiento)) < 25;
