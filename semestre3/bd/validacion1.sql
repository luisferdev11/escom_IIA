 -- insertar alumno con 4 materias de primer semestre del plantel 7

-- carrera 17 (computacion) plantel 7

--select * from materia where id_carrera=17 AND semestre =1;

--INSERT INTO Materia(id_carrera, clave, nombre_materia, creditos, semestre, academia) VALUES
--(17, 'CLC', 'Calcula', 7.5, 01, 'Formación Básica'),
--(17, 'ALG', 'Algebra', 7.5, 01, 'Formación Básica'),
--(17, 'FIS', 'Fisica', 7.5, 01, 'Formación Básica'),
-- (17, 'NC', 'Programacion', 7.5, 01, 'Ciencias en Computacion');


--INSERT INTO estudiante_materia (id_boleta,id_materia, calificacion) VALUES
--(2019000081, 112, 9),
--(2019000081, 113, 9),
--(2019000081, 115, 9),
--(2019000081, 114, 9);

-- select * from estudiante_materia where id_boleta=2019000081;



-- select * from docente where grado_academico = 'Maestría' or grado_academico = 'Doctorado';

-- REGRESAR PERSONAS QUE POSEAN DELEGACION Y FECHA DE NACIMIENTO PERO NO CORREO
SELECT * FROM personas WHERE correo IS NULL and fecha_nacimiento IS NOT NULL and municipio IS NOT NULL;
