SELECT * FROM personas WHERE telefono IS NULL;

SELECT * FROM personas WHERE correo IS NOT NULL;

INSERT INTO Materia(id_carrera, clave, nombre_materia, creditos, academia) VALUES
    (33, 'CALC', 'Cálculo', 8, 01, 'Matemáticas'),
SELECT nombre_materia FROM Materia WHERE semestre IS NULL;

SELECT nombre_materia FROM Materia WHERE academia IS NOT NULL;

ALTER TABLE Carrera ALTER COLUMN clave_carrera DROP NOT NULL;
INSERT INTO Carrera (nombre_carrera, id_plantel) VALUES ('Ingeniería en Robótica', 1);

SELECT nombre_carrera FROM Carrera WHERE clave_carrera IS NULL;


ALTER TABLE personas ALTER COLUMN segundoapellido DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN primerapellido DROP NOT NULL;
INSERT INTO personas (nombre, segundo_nombre, segundoapellido, genero, ciudad, municipio, estado, fecha_nacimiento, telefono, correo)
VALUES 
('Juan', 'Carlos', 'García', 'Masculino', 'Ciudad de México', 'Coyoacán', 'CDMX', '01/01/1990', '5512345678', 'juan.perez@example.com');
SELECT * FROM personas WHERE primerapellido IS NULL;

