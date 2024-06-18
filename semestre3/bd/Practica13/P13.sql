-- Inserción de registros de prueba detectados de inicio
INSERT INTO personas (nombre, segundo_nombre, primerapellido, segundoapellido, genero, fecha_nacimiento)
VALUES 
('Eduardo', 'Perez', 'Gomez', 'Castillo', 'Masculino', '1990-05-12'),
('Eduardo', 'Luis', 'Castro', 'Rodriguez', 'Masculino', '1985-09-23'),
('Adrian', 'Mendez', 'Diaz', 'Lara', 'Masculino', '1995-07-19'),
('Oscar', 'Eduardo', 'Cardenas', 'Montalvo', 'Masculino', '1992-11-30'),
('Carlos', 'Andres', 'Esteban', 'Ocampo', 'Masculino', '1987-01-16'),
('Gustavo', 'Ignacio', 'Mendoza', 'Enriquez', 'Masculino', '1993-03-04'),
('Angela', 'Maria', 'Gonzalez', 'Sandoval', 'Femenino', '1988-08-14'),
('Luis', 'Manuel', 'Navarro', 'Bermudez', 'Masculino', '1990-02-28'),
('Fernando', 'Eduardo', 'Cuellar', 'Jimenez', 'Masculino', '1989-05-25');

SELECT * FROM personas WHERE nombre LIKE 'Eduardo%' OR segundo_nombre LIKE 'Eduardo%';

SELECT * FROM personas WHERE SUBSTRING(nombre, 2, 1) = 'd';

SELECT * FROM personas WHERE nombre !~* '^[AEIOU]';

SELECT * FROM personas WHERE nombre ~* '^[AEIOU].*s$';

SELECT * FROM personas WHERE SUBSTRING(nombre, 3, 1) = 'g';

-- valor que hacia falta para la consulta
INSERT INTO personas (nombre, segundo_nombre, primerapellido, segundoapellido, genero, ciudad, municipio, direccion, fecha_nacimiento, telefono, correo)
VALUES 
('Natanael', 'Cano', 'Endamantado', 'Siemprevolado', 'Masculino', 'Ciudad de México', 'Coyoacán', 'CDMX', '01/01/1990', '5512345678', 'juan.perez@example.com')
SELECT * FROM personas WHERE primerapellido LIKE 'E__a%';

SELECT * FROM personas WHERE nombre LIKE '%E%' OR nombre LIKE '%e%';

SELECT * FROM personas WHERE (nombre LIKE 'Eduardo%' OR segundo_nombre LIKE 'Eduardo%') AND (primerapellido LIKE 'C%' OR segundoapellido LIKE 'C%');

SELECT * FROM personas WHERE segundoapellido ~* '^[B-DF-M]';

SELECT * FROM personas WHERE primerapellido ~* '^[N-Z]';
