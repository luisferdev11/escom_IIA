--- CREATE DATABASE Escuela;

--- \c Escuela;

CREATE TABLE Persona (
    id SERIAL PRIMARY KEY,
    primer_nombre VARCHAR NOT NULL,
    segundo_nombre VARCHAR NOT NULL,
    primer_apellido VARCHAR NOT NULL,
    segundo_apellido VARCHAR NOT NULL DEFAULT '---',
    genero VARCHAR(10) CHECK (genero IN ('Masculino', 'Femenino')),
    ciudad VARCHAR NOT NULL,
    municipio VARCHAR NOT NULL,
    direccion VARCHAR NOT NULL,
    fecha_nacimiento DATE NOT NULL,
    telefono VARCHAR NOT NULL,
    correo VARCHAR NOT NULL
);

CREATE TABLE Estudiante (
    id_persona SERIAL PRIMARY KEY REFERENCES Persona(id),
    boleta BIGINT NOT NULL DEFAULT 2019000000 CHECK (boleta >= 2019000000)
);

CREATE TABLE Docente (
    id_persona SERIAL PRIMARY KEY REFERENCES Persona(id),
    numero_docente VARCHAR NOT NULL,
    grado_academico VARCHAR NOT NULL,
    area_especialidad VARCHAR NOT NULL DEFAULT '---'
);

CREATE TABLE Plantel (
    id SERIAL PRIMARY KEY,
    nombre VARCHAR NOT NULL,
    clave_plantel VARCHAR NOT NULL
);

CREATE TABLE Carrera (
    id SERIAL PRIMARY KEY,
    clave_carrera VARCHAR NOT NULL,
    nombre VARCHAR NOT NULL,
    id_plantel INT REFERENCES Plantel(id)
);

CREATE TABLE Grupo (
    id SERIAL PRIMARY KEY,
    codigo_grupo VARCHAR(4) NOT NULL,
    capacidad INT NOT NULL,
    id_docente INT REFERENCES Docente(id_persona)
);

CREATE TABLE Materia (
    id SERIAL PRIMARY KEY,
    clave_materia VARCHAR(4) NOT NULL,
    nombre VARCHAR NOT NULL,
    creditos INT NOT NULL,
    semestre INT,
    id_academia INT,
    id_carrera INT REFERENCES Carrera(id)
);

CREATE TABLE Horario (
    id SERIAL PRIMARY KEY,
    dia VARCHAR(10) CHECK (dia IN ('Lunes', 'Martes', 'Miércoles', 'Jueves', 'Viernes')),
    hora_inicio TIME NOT NULL,
    hora_fin TIME NOT NULL,
    id_aula INT,
    id_grupo INT REFERENCES Grupo(id)
);

CREATE TABLE Aula (
    id SERIAL PRIMARY KEY,
    nombre VARCHAR NOT NULL,
    tipo VARCHAR(20) CHECK (tipo IN ('Aula', 'Laboratorio', 'Clínico', 'Otro')),
    capacidad INT NOT NULL
);

CREATE TABLE Calificacion (
    id_estudiante INT REFERENCES Estudiante(id_persona),
    id_materia INT REFERENCES Materia(id),
    calificacion DOUBLE PRECISION,
    PRIMARY KEY (id_estudiante, id_materia)
);

-- Faltaba la relacion xd
ALTER TABLE Horario DROP COLUMN id_aula;
ALTER TABLE Horario ADD COLUMN id_aula INT REFERENCES Aula(id);

-- Cambiar nombre de tablas y columnas para coincidir con los INSERTs
ALTER TABLE Persona RENAME TO personas;
ALTER TABLE personas RENAME COLUMN primer_nombre TO nombre;
ALTER TABLE personas RENAME COLUMN primer_apellido TO primerapellido;
ALTER TABLE personas RENAME COLUMN segundo_apellido TO segundoapellido;
ALTER TABLE personas ALTER COLUMN ciudad DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN municipio DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN direccion DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN telefono DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN correo DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN segundo_nombre DROP NOT NULL;
ALTER TABLE personas ALTER COLUMN fecha_nacimiento DROP NOT NULL;

-- Renombrar la tabla Calificacion a estudiante_materia para alinear con los INSERTs
ALTER TABLE Calificacion RENAME TO estudiante_materia;

-- Ajustar los nombres de las columnas si son diferentes
ALTER TABLE estudiante_materia RENAME COLUMN id_estudiante TO id_boleta;

-- Corregir la referencia en la tabla estudiantes (según tus INSERTs parece que debe ser 'estudiantes' en plural)
CREATE SEQUENCE boleta_seq START WITH 2019000000;
ALTER TABLE Estudiante RENAME TO estudiantes;
ALTER TABLE estudiantes ALTER COLUMN boleta SET DEFAULT nextval('boleta_seq');
ALTER TABLE estudiantes RENAME COLUMN boleta TO id_boleta;
ALTER TABLE estudiante_materia DROP CONSTRAINT IF EXISTS calificacion_id_estudiante_fkey;
ALTER TABLE estudiantes ADD CONSTRAINT unique_id_boleta UNIQUE (id_boleta);
ALTER TABLE estudiante_materia ADD CONSTRAINT calificacion_id_estudiante_fkey FOREIGN KEY (id_boleta) REFERENCES estudiantes(id_boleta);

-- Corregir la referencia en la tabla docente
ALTER TABLE docente ALTER COLUMN numero_docente DROP NOT NULL;


-- Ajustar nombres de las columnas de la tabla Aula para coincidir con los INSERTs
ALTER TABLE aula RENAME COLUMN nombre TO nombre_aula;

-- Cambiar nombres en la tabla Plantel para coincidir con los INSERTs
ALTER TABLE Plantel RENAME COLUMN nombre TO nombre_plantel;

-- Ajustar los nombres de la tabla Carrera para coincidir con los INSERTs
ALTER TABLE carrera RENAME COLUMN nombre TO nombre_carrera;

-- Corregir la tabla Materia para coincidir con los INSERTs
ALTER TABLE Materia RENAME COLUMN nombre TO nombre_materia;
ALTER TABLE Materia RENAME COLUMN clave_materia TO clave;
ALTER TABLE Materia DROP COLUMN id_academia;
ALTER TABLE Materia ADD COLUMN academia VARCHAR(255);

-- Cambiar la estructura de Horario para coincidir con el nombre en los INSERTs
ALTER TABLE Horario RENAME TO Horarios;
ALTER TABLE Horarios RENAME COLUMN id TO id_materia;
ALTER TABLE Horarios DROP CONSTRAINT horario_dia_check;
ALTER TABLE Horarios ADD CONSTRAINT horario_dia_check CHECK (dia IN ('Lunes', 'Martes', 'Miércoles', 'Miercoles', 'Jueves', 'Viernes'));
ALTER TABLE Horarios DROP CONSTRAINT horario_pkey;
ALTER TABLE Horarios ADD COLUMN id SERIAL;
ALTER TABLE Horarios ADD PRIMARY KEY (id);
ALTER TABLE Horarios ADD CONSTRAINT fk_horarios_materia FOREIGN KEY (id_materia) REFERENCES Materia(id);




ALTER TABLE Grupo RENAME TO grupos;
ALTER TABLE grupos ADD COLUMN id_materia INTEGER;
ALTER TABLE grupos ADD CONSTRAINT fk_grupos_materia FOREIGN KEY (id_materia) REFERENCES Materia(id);
ALTER TABLE grupos RENAME COLUMN capacidad TO numero_estudiantes;
ALTER TABLE grupos RENAME COLUMN codigo_grupo TO grupo;

ALTER TABLE grupos DROP CONSTRAINT grupo_id_docente_fkey;

ALTER TABLE docente DROP CONSTRAINT docente_pkey;

ALTER TABLE docente ADD COLUMN id_profesor SERIAL PRIMARY KEY;

ALTER TABLE grupos RENAME COLUMN id_docente TO id_profesor;
ALTER TABLE grupos ADD CONSTRAINT grupo_id_docente_fkey FOREIGN KEY (id_profesor) REFERENCES docente(id_profesor);





INSERT INTO personas(
	nombre, primerapellido, segundoapellido,genero)
	VALUES ('Jeremy Job','Baez','Castillo','Masculino'),
	('Miriam Alessia','Basurto','Lara','Femenino'),
	('Giovanna Guadalupe','Bautista','Guadarrama','Femenino'),
	('Vianey','Belmonte','Lopez','Femenino'),
	('Dayanara','Calderon','Cahuantzi','Femenino'),
	('Neide Shany','Calderon','Fuentes','Femenino'),
	('Frida','Capetillo','Salas','Femenino'),
	('Gonzalo Quetzalcoatl','Cruz','Torrijos','Masculino'),
	('Irma Lizbeth','Diaz','Espinosa','Femenino'),
	('Guadalupe','Diaz','Roque','Femenino'),
	('Frida Sophia','Garcia','Castro','Femenino'),
	('Francisco Javier','Guzman','Braulio','Masculino'),
	('Brenda Paola','Hernandez','Badillo','Femenino'),
	('Yaotl Felipe','Lopez','Vizuet','Masculino'),
	('Angelica','Loranca','Vazquez','Femenino'),
	('Azael','Martinez','Saavedra','Masculino'),
	('Maria Fernanda','Mejia','Vargas','Femenino'),
	('Fidel Zeus','Moreno','Perez','Masculino'),
	('Jeyna Evelyn','Muñoz','Montoya','Femenino'),
	('Emiliano Pedro','Noguez','Torres','Masculino'),
	('Arian Pamela','Perez','Olivares','Femenino'),
	('Andrea Lizeth','Ramirez','Juarez','Femenino'),
	('Itzel Virginia','Rivas','Sosa','Femenino'),
	('Roxana','Riveros','Juarez','Femenino'),
	('Karol Michelle','Rosas','Gonzalez','Femenino'),
	('Mauricio David','Rosiles','Redonda','Masculino'),
	('David','Salgado','Samano','Masculino'),
	('Brandon Ian','Sandoval','Villanueva','Masculino'),
	('Itzel Jacqueline','Suarez','Florez','Femenino'),
	('Guadalupe Denise','Tagle','Perez','Femenino'),
	('Monserrat Dulce','Aguilar','Gonzalez','Femenino'),
	('Danae','Aguilar','Romero','Femenino'),
	('Hypatia Abigali','Cervantez','Lopez','Femenino'),
	('Jesus Ricardo','Chiman','Olivera','Masculino'),
	('Isaac','Espinosa','Moreno','Masculino'),
	('Alexa Ali','Franco','Malpica','Femenino'),
	('Gloria Rubi','Gallegos','Rodriguez','Femenino'),
	('Monserrat','Gudiño','Macin','Femenino'),
	('Melanie Valeria','Guzman','Alvarez','Femenino'),
	('Paola Monserrat','Hernandez','Castelan','Femenino'),
	('Brandon Abraham','Hernandez','Gonzalez','Masculino'),
	('Jesus Nestor','Hernandez','Vergara','Masculino'),
	('Israel','Herrans','Martinez','Masculino'),
	('Angel Edson de Jesus','Jimenez','Lopez','Masculino'),
	('Aniel Patricia','Lopez','Calderon','Femenino'),
	('Geodibelit','Lopez','Jimenez','Femenino'),
	('Miguel Angel','Marcial','Reyes','Masculino'),
	('Cristian','Martinez','Dominguez','Masculino'),
	('Karla Lilian','Martinez','Martinez','Femenino'),
	('Ismael','Mejia','Alvarez','Masculino'),
	('Ana Dalay','Morales','Morales','Femenino'),
	('Samantha','Navidad','Zuñiga','Femenino'),
	('Denisse Evelin','Osornio','De la Cruz','Femenino'),
	('Andrea Getzemany','Otero','Gomez','Femenino'),
	('Delia Guadalupe','Robles','Galeana','Femenino'),
	('Yoselin','Rosas','Ordoñez','Femenino'),
	('Carlos Sebastian','Trejo','Pacheco','Masculino'),
	('Adrian','Alvarez','Calderon','Masculino'),
	('Escarlet Jetzemanari','Alvarez','Martinez','Femenino'),
	('Fernando Daniel','Carrizosa','Alvarez','Masculino'),
	('Citlali Guadalupe','Castañeda','Giron','Femenino'),
	('Aranza Estefania','Chavez','Espinosa','Femenino'),
	('Zadkiel Alejandro','Cobos','Arredondo','Masculino'),
	('Abraham Alfonso','Diaz','Cazares','Masculino'),
	('Adrian','Estrada','Gallegos','Masculino'),
	('Gerardo Israel','Falcon','Duran','Masculino'),
	('Angel Gabriel','Franco','Delgado','Masculino'),
	('Eduardo','Garcia','Rodriguez','Masculino'),
	('Francisco Alejandro','Guevara','Barrera','Masculino'),
	('Carlos Eduardo','Hernandez','Martinez','Masculino'),
	('Rocio','Hernandez','Martinez','Femenino'),
	('Mitzi Aquetzali','Herrera','Vazquez','Femenino'),
	('Nuria Adilene','Jonguitud','Gonzalez','Femenino'),
	('Gisela','Muñoz','Garcia','Femenino'),
	('Gerardo','Oropeza','Magallanes','Masculino'),
	('Jovita','Perez','Muñoz','Femenino'),
	('Celia','Pulido','Romero','Femenino'),
	('Ilce Lorena','Ramirez','Bojorgez','Femenino'),
	('Maria de los Angeles','Reyes','Fernandez','Femenino'),
	('Pedro Ivan','Romero','Hernandez','Masculino'),
	('Rodrigo Ceceo','Sanchez','Florentino','Masculino'),
	('Alexander','Torres','Pizano','Masculino'),
	('Carlos Sebastian','Trejo','Pacheco','Masculino'),
	('Leonel Ranferi','Vasquez','Ramos','Masculino'),
	('Danira','Vela','Alonso','Femenino'),
	('Italivy Marsel','Velazquez','Segura','Femenino'),
	('Dante Gerardo','Zambrano','Rosendo','Masculino'),
	('Miguel Angel','Zapata','Rosales','Masculino'),
	('Mitzy Alondra','Alvarez','Alameda','Femenino'),
	('Alisson','Arredondo','Barajas','Femenino'),
	('Johana Sherlink','Arzate','Perez','Femenino'),
	('Roberto','Bartolo','Hernandez','Masculino'),
	('Jorge Gabriel','Betancourt','Campero','Masculino'),
	('Eduardo','Brown','Medina','Masculino'),
	('Gustavo Ulises','Cruz','Luciano','Masculino'),
	('Rene Ivan','Flores','Almogabar','Masculino'),
	('Alexis','Fuentes','Franco','Masculino'),
	('Yureymi','Galindez','Roman','Masculino'),
	('Edgar Daniel','Garcia','Gonzalez','Masculino'),
	('Miguel Andre','Jara','Perez','Masculino'),
	('Mitzy Damaris','Morales','Rangel','Femenino');

insert into estudiantes(id_persona) 
	values(1),(2),(4),(5),(7),(9),(10),
		   (11),(12),(13),(14),(15),(17),(19),(20),
		   (21),(23),(24),(26),(27),(28),(29),(30),
		   (31),(32),(33),(34),(35),(36),(37),(38),(39),(40),
		   (41),(42),(43),(45),(47),(48),(49),
		   (51),(52),(53),(54),(57),(58),(59),(60),
		   (62),(63),(64),(65),(66),(69),(70),
		   (71),(73),(74),(75),(76),(77),(78),(79),(80),
		   (81),(83),(84),(85),(86),(87),(88),(89),(90),
		   (91),(92),(94),(95),(96),(98),(99),(100);

INSERT INTO docente(
	id_persona, grado_academico, area_especialidad)
	VALUES (25,'Doctorado','Inteligencia Artificial'),
	(16,'Licenciatura','Sistemas Computacionales Móviles'),
	(46,'Técnico','Computación'),
	(82,'Licenciatura','Sistemas Computacionales Móviles'),
	(101,'Maestría','Tecnologás de la Información'),
	(56,'Licenciatura','Computo Científico'),
	(68,'Doctorado','Sistemas Computacionales de Alto Desempeño'),
	(67,'Doctorado','Mecatrónica'),
	(61,'Licenciatura','Sistemas Computacionales'),
	(6,'Maestría','Mecatrónica'),
	(44,'Doctorado','Ciencias de Datos'),
	(93,'Técnico','Tecnología de la Información'),
	(8,'Maestría','Inteligencia Artificial'),
	(55,'Doctorado','Computo Científico'),
	(97,'Doctorado','Sistemas Computacionales Móviles'),
	(3,'Técnico','Tecnología de la Información'),
	(22,'Licenciatura','Sistemas Computacionales'),
	(18,'Licenciatura','Computo Científico'),
	(50,'Técnico','Electronica'),
	(72,'Doctorado','Inteligencia Artificial');
	
INSERT INTO aula(
	nombre_aula, tipo, capacidad)
	VALUES ('1001','Aula',36),
	('1002','Aula',36),
	('1003','Aula',36),
	('1004','Aula',36),
	('1005','Aula',36),
	('1006','Aula',36),
	('1007','Aula',36),
	('1101','Laboratorio',36),
	('1102','Laboratorio',36),
	('1103','Laboratorio',36),
	('1104','Laboratorio',36),
	('1105','Laboratorio',36),
	('1106','Laboratorio',36),
	('1107','Laboratorio',36),
	('1201','Aula',36),
	('1202','Aula',36),
	('1203','Aula',36),
	('1204','Aula',36),
	('1205','Aula',36),
	('1206','Aula',36),
	('1207','Aula',36);

insert into Plantel(clave_plantel, nombre_plantel)
	values('ESCOM','Escuela Superior de Cómputo'),
	('CIC','Centro de Investigación en Cómputo'),
	('CIDETEC','Centro de Innovación y Desarrollo Tecnológico en Cómputo'),
	('ESFM','Escuela Superior de Física'),
	('ESIME ZAC','Escuela Superior de Mécanica y Electrica - Zacatenco'),
	('ESIME AZC','Escuela Superior de Mécanica y Electrica - Azcapotzalco'),
	('ESIME CUL','Escuela Superior de Mécanica y Electrica - Culhuacan'),
	('ESIME TIC','Escuela Superior de Mécanica y Electrica - Ticoman'),
	('UPIBI','Unidad Profesional Interdisciplinaria de Biotecnología'),
	('UPIIG','Unidad Profesional Interdisciplinaria de Ingeniería de Guanajuato'),
	('UPIITA','Unidad Profesional Interdisciplinaria en Ingeniería y Tecnologías Avanzadas'),
	('UPIIZ','Unidad Profesional Interdisciplinaria de Ingeniería de Zacatecas'),
	('UPIEM','Unidad Profesional Interdisciplinaria de Energía y Movilidad'),
	('UPIIT','Unidad Profesional Interdisciplinaria de Ingenieria de Tlaxcala');
	
insert into carrera(id_plantel,clave_carrera,nombre_carrera) values
	(1,'ISC','Ingeniería en Sistemas Computacionales'),
	(1,'LCD','Licenciatura en Ciencias de Datos'),
	(1,'IAA','Ingeniería en Inteligencia Artificial'),
	(1,'MCSCM','Maestría en Ciencias en Sistemas Computacionales Móviles'),
	(2,'DCC','Doctorado en Ciencias Computacionales'),
	(2,'MCC','Maestría en Ciencias Computacionales'),
	(2,'MCIC','Maestría en Ciencias en Ingeniería de Cómputo'),
	(3,'MTC','Maestría en Tecnología de Cómputo'),
	(3,'DISRM','Doctorado en Ingeiería de Sistemas Robóticos y Mecatrónicos'),
	(4,'LMA','Licenciatura en Matématica y Algorítmica'),
	(5,'ICE','Ingeniería en Comunicaciones y Electrónica'),
	(5,'MCIS','Maestría en Ciencias en Ingeniería de Sistemas'),
	(5,'MCIT','Maestría en Ciencias en Ingeniería de Telecomunicaciones'),
	(5,'DIS','Doctorado en Ingeniería de Sistemas'),
	(5,'DCIT','Doctorado en Ciencias en Ingeniería de Telecomunicaciones'),
	(6,'DISRM','Doctorado en Ingeiería de Sistemas Robóticos y Mecatrónicos'),
	(7,'IC','Ingeniería en Computación'),
	(7,'ICE','Ingeniería en Comunicaciones y Electrónica'),
	(7,'MCISE','Maestría en Ciencias en Sistemas Energéticos'),
	(7,'MISTI','Maestría en Ingeniería en Seguridad y Tecnologías de la Información'),
	(8,'MIA','Maestría en Ingeniería Aeronáutica'),
	(9,'IB','Ingeniería Biotecnológica'),
	(10,'IB','Ingeniería Biotecnológica'),
	(11,'IT','Ingeniería Telemática'),
	(11,'MTA','Maestría en Tecnología Avanzada'),
	(11,'DTA','Doctorado en Tecnología Avanzada'),
	(12,'ISC','Ingeniería en Sistemas Computacionales'),
	(12,'IAA','Ingeniería en Inteligencia Artificial'),
	(13,'ISERI','Ingeniería en Sistemas Energéticos y Redes Inteligentes'),
	(14,'IB','Ingeniería Biotecnológica'),
	(14,'LCD','Licenciatura en Ciencias de Datos'),
	(14,'IAA','Ingeniería en Inteligencia Artificial');
	
insert into Materia(id_carrera,clave,nombre_materia,creditos,semestre,academia)
	values(1,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(1,'CA','Cálculo Aplicado',7.5,02,'Ciencias Básicas'),
	(1,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(1,'IS','Ingeniería de Software',7.5,05,'Ciencias en Computación'),
	(1,'MD','Mineria de Datos',7.5,05,'Ciencias en Computación'),
	(1,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),
	(2,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(2,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(2,'MD','Mineria de Datos',7.5,05,'Ciencias en Computación'),
	(2,'IS','Ingeniería de Software',5,01,'Ingeniería en Sistemas'),
	(2,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),
	(3,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(3,'FIA','Fundamentos de Inteligencia Artificial',7.5,04,'Inteligencia Artificial'),
	(3,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(3,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),	
	(4,'ADM','Arquitectura de Dispositivos Móviles',7.5,02,'Sistemas Moviles'),
	(5,'MD','Mineria de Datos',5,03,'Ciencias en Computación'),
	(5,'IS','Ingeniería de Software',5,01,'Ciencias en Computación'),
	(6,'FIA','Fundamentos de Inteligencia Artificial',5,02,'Inteligencia Artificial'),
	(6,'IS','Ingeniería de Software',5,01,'Ciencias en Computación'),
	(6,'MD','Mineria de Datos',5,03,'Ciencias en Computación'),
	(7,'TG','Teoría de Grafos',5,03,'Formación Básica'),
	(8,'MDD','Matemáticas Discretas',5,01,'Formación Básica'),
	(9,'RA','Robotica Avanzada',5,03,'Digitales'),
	(27,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(27,'CA','Cálculo Aplicado',7.5,02,'Ciencias Básicas'),
	(27,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(27,'IS','Ingeniería de Software',7.5,05,'Ciencias en Computación'),
	(27,'MD','Mineria de Datos',7.5,05,'Ciencias en Computación'),
	(27,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),
	(28,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(28,'FIA','Fundamentos de Inteligencia Artificial',7.5,04,'Inteligencia Artificial'),
	(28,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(28,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),	
	(32,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(32,'FIA','Fundamentos de Inteligencia Artificial',7.5,04,'Inteligencia Artificial'),
	(32,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(32,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),	
	(31,'FP','Fundamentos de Programación',7.5,01,'Ciencias en Computación'),
	(31,'BD','Bases de Datos',7.5,03,'Ingeniería en Sistemas'),
	(31,'MD','Mineria de Datos',7.5,05,'Ciencias en Computación'),
	(31,'IS','Ingeniería de Software',5,01,'Ingeniería en Sistemas'),
	(31,'MDD','Matemáticas Discretas',7.5,01,'Formación Básica'),
	(29,'PB','Programación Básica',7.5,01,'Tecnologías Digitales'),
	(29,'PA','Programación Avanzada',7.5,02,'Tecnologías Digitales'),
	(29,'BD','Bases de Datos',7.5,05,'Tecnologías Digitales');
	

INSERT INTO Horarios(
	id_materia, id_aula, dia, hora_inicio, hora_fin) VALUES
	(1, 1, 'Lunes', '7:00', '8:30'),
	(1, 1, 'Miercoles', '7:00', '8:30'),
	(1, 8, 'Jueves', '7:00', '8:30'),
	(2, 1, 'Lunes', '8:30', '10:00'),
	(2, 1, 'Miercoles', '8:30', '10:00'),
	(2, 8, 'Jueves', '8:30', '10:00'),
	(3, 1, 'Lunes', '10:30', '12:00'),
	(3, 1, 'Miercoles', '10:30', '12:00'),
	(3, 8, 'Jueves', '10:30', '12:00'),
	(4, 1, 'Lunes','12:00','13:30'),
	(4, 1, 'Miercoles','12:00','13:30'),
	(4, 8, 'Jueves','12:00','13:30'),
	(5, 1, 'Lunes','20:00','21:30'),
	(5, 1, 'Miercoles','20:00','21:30'),
	(5, 8, 'Jueves','20:00','21:30'),
	(6, 1, 'Lunes','15:00','16:30'),
	(6, 1, 'Miercoles','15:00','16:30'),
	(6, 8, 'Jueves','15:00','16:30'),
	(7, 1, 'Lunes','16:30','18:00'),
	(7, 1, 'Miercoles','16:30','18:00'),
	(7, 8, 'Jueves','16:30','18:00'),
	(8, 1, 'Lunes','18:30','20:00'),
	(8, 1, 'Miercoles','18:30','20:00'),
	(8, 8, 'Jueves','18:30','20:00'),	
	(9, 9, 'Lunes', '7:00', '8:30'),
	(9, 2, 'Martes', '7:00', '8:30'),
	(9, 2, 'Jueves', '7:00', '8:30'),
	(10, 9, 'Lunes', '8:30', '10:00'),
	(10, 2, 'Martes', '8:30', '10:00'),
	(10, 2, 'Jueves', '8:30', '10:00'),
	(11, 9, 'Lunes', '10:30', '12:00'),
	(11, 2, 'Martes', '10:30', '12:00'),
	(11, 2, 'Jueves', '10:30', '12:00'),
	(12, 9, 'Lunes','12:00','13:30'),
	(12, 2, 'Martes','12:00','13:30'),
	(12, 2, 'Jueves','12:00','13:30'),
	(13, 9, 'Lunes','20:00','21:30'),
	(13, 2, 'Martes','20:00','21:30'),
	(13, 2, 'Jueves','20:00','21:30'),
	(14, 9, 'Lunes','15:00','16:30'),
	(14, 2, 'Miercoles','15:00','16:30'),
	(14, 2, 'Jueves','15:00','16:30'),
	(15, 9, 'Lunes','16:30','18:00'),
	(15, 2, 'Martes','16:30','18:00'),
	(15, 2, 'Jueves','16:30','18:00'),
	(16, 9, 'Lunes','18:30','20:00'),
	(16, 2, 'Martes','18:30','20:00'),
	(16, 2, 'Jueves','18:30','20:00'),	
	(17, 3, 'Lunes', '7:00', '8:30'),
	(17, 3, 'Jueves', '7:00', '8:30'),
	(17, 10, 'Viernes', '7:00', '8:30'),
	(18, 3, 'Lunes', '8:30', '10:00'),
	(18, 3, 'Jueves', '8:30', '10:00'),
	(18, 10, 'Viernes', '8:30', '10:00'),
	(19, 3, 'Lunes', '10:30', '12:00'),
	(19, 3, 'Jueves', '10:30', '12:00'),
	(19, 10, 'Viernes', '10:30', '12:00'),
	(20, 3, 'Lunes','12:00','13:30'),
	(20, 3, 'Jueves','12:00','13:30'),
	(20, 10, 'Viernes','12:00','13:30'),
	(21, 3, 'Lunes','20:00','21:30'),
	(21, 3, 'Jueves','20:00','21:30'),
	(21, 10, 'Viernes','20:00','21:30'),
	(22, 3, 'Lunes','15:00','16:30'),
	(22, 3, 'Jueves','15:00','16:30'),
	(22, 10, 'Viernes','15:00','16:30'),
	(23, 3, 'Lunes','16:30','18:00'),
	(23, 3, 'Jueves','16:30','18:00'),
	(23, 10, 'Viernes','16:30','18:00'),
	(24, 3, 'Lunes','18:30','20:00'),
	(24, 3, 'Jueves','18:30','20:00'),
	(24, 10, 'Viernes','18:30','20:00'),	
	(25, 4, 'Lunes', '7:00', '8:30'),
	(25, 11, 'Miercoles', '7:00', '8:30'),
	(25, 4, 'Jueves', '7:00', '8:30'),
	(26, 4, 'Lunes', '8:30', '10:00'),
	(26, 11, 'Miercoles', '8:30', '10:00'),
	(26, 4, 'Jueves', '8:30', '10:00'),
	(27, 4, 'Lunes', '10:30', '12:00'),
	(27, 11, 'Miercoles', '10:30', '12:00'),
	(27, 4, 'Jueves', '10:30', '12:00'),
	(28, 4, 'Lunes','12:00','13:30'),
	(28, 11, 'Miercoles','12:00','13:30'),
	(28, 4, 'Jueves','12:00','13:30'),
	(29, 4, 'Lunes','20:00','21:30'),
	(29, 11, 'Miercoles','20:00','21:30'),
	(29, 4, 'Jueves','20:00','21:30'),
	(30, 4, 'Lunes','15:00','16:30'),
	(30, 11, 'Miercoles','15:00','16:30'),
	(30, 4, 'Jueves','15:00','16:30'),
	(31, 4, 'Lunes','16:30','18:00'),
	(31, 11, 'Miercoles','16:30','18:00'),
	(31, 4, 'Jueves','16:30','18:00'),
	(32, 4, 'Lunes','18:30','20:00'),
	(32, 11, 'Miercoles','18:30','20:00'),
	(32, 4, 'Jueves','18:30','20:00'),
	(33, 5, 'Lunes', '7:00', '8:30'),
	(33, 12, 'Martes', '7:00', '8:30'),
	(33, 5, 'Jueves', '7:00', '8:30'),
	(34, 5, 'Lunes', '8:30', '10:00'),
	(34, 12, 'Martes', '8:30', '10:00'),
	(34, 5, 'Jueves', '8:30', '10:00'),
	(35, 5, 'Lunes', '10:30', '12:00'),
	(35, 12, 'Martes', '10:30', '12:00'),
	(35, 5, 'Jueves', '10:30', '12:00'),
	(36, 5, 'Lunes','12:00','13:30'),
	(36, 12, 'Martes','12:00','13:30'),
	(36, 5, 'Jueves','12:00','13:30'),
	(37, 5, 'Lunes','20:00','21:30'),
	(37, 12, 'Martes','20:00','21:30'),
	(37, 5, 'Jueves','20:00','21:30'),
	(38, 5, 'Lunes','15:00','16:30'),
	(38, 12, 'Miercoles','15:00','16:30'),
	(38, 5, 'Jueves','15:00','16:30'),
	(39, 5, 'Lunes','16:30','18:00'),
	(39, 12, 'Martes','16:30','18:00'),
	(39, 5, 'Jueves','16:30','18:00'),
	(40, 5, 'Lunes','18:30','20:00'),
	(40, 12, 'Martes','18:30','20:00'),
	(40, 5, 'Jueves','18:30','20:00'),
	(41, 6, 'Lunes', '7:00', '8:30'),
	(41, 13, 'Miercoles', '7:00', '8:30'),
	(41, 6, 'Jueves', '7:00', '8:30'),
	(42, 6, 'Lunes', '8:30', '10:00'),
	(42, 13, 'Miercoles', '8:30', '10:00'),
	(42, 6, 'Jueves', '8:30', '10:00'),
	(43, 6, 'Lunes', '10:30', '12:00'),
	(43, 13, 'Miercoles', '10:30', '12:00'),
	(43, 6, 'Jueves', '10:30', '12:00'),
	(44, 6, 'Lunes','12:00','13:30'),
	(44, 13, 'Miercoles','12:00','13:30'),
	(44, 6, 'Jueves','12:00','13:30'),
	(45, 6, 'Lunes','20:00','21:30'),
	(45, 13, 'Miercoles','20:00','21:30'),
	(45, 6, 'Jueves','20:00','21:30'),
	(46, 6, 'Lunes','15:00','16:30'),
	(46, 13, 'Miercoles','15:00','16:30'),
	(46, 6, 'Jueves','15:00','16:30');
	


insert into estudiante_materia(id_boleta,id_materia,calificacion) values
	(2019000000,1,8.2),
	(2019000000,2,6.1),
	(2019000000,3,6.2),
	(2019000000,4,9.2),
	(2019000000,5,2.1),
	(2019000001,6,10),
	(2019000001,7,1.1),
	(2019000002,8,8.6),
	(2019000003,9,3.4),
	(2019000003,10,8),
	(2019000003,11,8.5),
	(2019000003,12,8.7),
	(2019000003,13,2.9),
	(2019000003,14,10),
	(2019000004,15,4.1),
	(2019000004,16,10),
	(2019000004,17,9),
	(2019000004,18,9.1),
	(2019000005,19,10),
	(2019000005,20,9),
	(2019000005,21,7.8),
	(2019000005,22,8.2),
	(2019000006,23,2),
	(2019000006,24,10),
	(2019000006,25,3.1),
	(2019000006,26,10),
	(2019000006,27,1),
	(2019000007,28,5.6),
	(2019000008,29,10),
	(2019000008,30,5),
	(2019000008,31,9.6),
	(2019000008,32,4.5),
	(2019000008,33,8.2),
	(2019000008,34,3.0),
	(2019000009,35,6.7),
	(2019000009,36,7.9),
	(2019000009,37,5.6),
	(2019000009,38,7.3),
	(2019000010,39,4.0),
	(2019000011,40,2.4),
	(2019000011,41,6.4),
	(2019000011,42,8.7),
	(2019000011,43,9.0),
	(2019000012,44,5.7),
	(2019000012,45,1.2),
	(2019000012,46,7.2),
	(2019000013,1,8.2),
	(2019000013,2,6.1),
	(2019000013,3,6.2),
	(2019000013,4,9.2),
	(2019000014,5,2.1),
	(2019000015,6,10),
	(2019000015,7,1.1),
	(2019000015,8,8.6),
	(2019000016,9,3.4),
	(2019000016,10,8),
	(2019000016,11,8.5),
	(2019000016,12,8.7),
	(2019000017,13,2.9),
	(2019000017,14,10),
	(2019000017,15,4.1),
	(2019000017,16,10),
	(2019000017,17,9),
	(2019000017,18,9.1),
	(2019000018,19,10),
	(2019000018,20,9),
	(2019000018,21,7.8),
	(2019000018,22,8.2),
	(2019000018,23,2),
	(2019000018,24,10),
	(2019000019,25,3.1),
	(2019000019,26,10),
	(2019000020,27,1),
	(2019000020,28,5.6),
	(2019000020,29,10),
	(2019000020,30,5),
	(2019000020,31,9.6),
	(2019000021,32,4.5),



-- Inserción de 40 nuevas personas.
INSERT INTO personas (nombre, segundo_nombre, primerapellido, segundoapellido, genero, ciudad, municipio, direccion, fecha_nacimiento, telefono, correo)
VALUES 
('Juan', 'Carlos', 'Pérez', 'García', 'Masculino', 'Ciudad de México', 'Coyoacán', 'CDMX', '01/01/1990', '5512345678', 'juan.perez@example.com'),
('Ana', 'María', 'López', 'Martínez', 'Femenino', 'Ciudad de México', 'Azcapotzalco', 'CDMX', '02/02/1991', '5512345679', 'ana.lopez@example.com'),
('José', 'Luis', 'Rodríguez', 'Hernández', 'Masculino', 'Ciudad de México', 'Iztapalapa', 'CDMX', '03/03/1992', '5512345680', 'jose.rodriguez@example.com'),
-- (Agregar 37 personas más aquí)
('María', 'Guadalupe', 'González', 'Gómez', 'Femenino', 'Ciudad de México', 'Gustavo A. Madero', 'CDMX', '04/04/1993', '5512345681', 'mari@pene.com'),
('Miguel', 'Ángel', 'Hernández', 'Jiménez', 'Masculino', 'Ciudad de México', 'Iztacalco', 'CDMX', '05/05/1994', '5512345682', 'sadlk@asd.com'),
('Alejandra', 'Fernanda', 'Díaz', 'Pérez', 'Femenino', 'Ciudad de México', 'Tlalpan', 'CDMX', '06/06/1995', '5512345683', 'alejandra.diaz@example'),
('Carlos', 'Alberto', 'Gómez', 'Sánchez', 'Masculino', 'Ciudad de México', 'Benito Juárez', 'CDMX', '07/07/1996', '5512345684', 'carlos.gomez@example.com'),
('Laura', 'Isabel', 'Torres', 'Vargas', 'Femenino', 'Ciudad de México', 'Miguel Hidalgo', 'CDMX', '08/08/1997', '5512345685', 'laura.torres@example.com'),
('Javier', 'Antonio', 'Rojas', 'Flores', 'Masculino', 'Ciudad de México', 'Cuauhtémoc', 'CDMX', '09/09/1998', '5512345686', 'javier.rojas@example.com'),
('Fernanda', 'Valeria', 'Mendoza', 'Guzmán', 'Femenino', 'Ciudad de México', 'Álvaro Obregón', 'CDMX', '10/10/1999', '5512345687', 'fernanda.mendoza@example.com'),
('Roberto', 'Carlos', 'Silva', 'Ortega', 'Masculino', 'Ciudad de México', 'Tláhuac', 'CDMX', '11/11/2000', '5512345688', 'roberto.silva@example.com'),
('María', 'José', 'Cortés', 'Ramos', 'Femenino', 'Ciudad de México', 'Xochimilco', 'CDMX', '12/12/2001', '5512345689', 'maria.cortes@example.com'),
('Luis', 'Fernando', 'Vargas', 'Santos', 'Masculino', 'Ciudad de México', 'Iztapalapa', 'CDMX', '01/01/2002', '5512345690', 'luis.vargas@example.com'),
('Sofía', 'Alejandra', 'Guzmán', 'Mendoza', 'Femenino', 'Ciudad de México', 'Gustavo A. Madero', 'CDMX', '02/02/2003', '5512345691', 'sofia.guzman@example.com'),
('Diego', 'Andrés', 'Ortega', 'Cortés', 'Masculino', 'Ciudad de México', 'Azcapotzalco', 'CDMX', '03/03/2004', '5512345692', 'diego.ortega@example.com'),
('Valentina', 'Isabella', 'Ramos', 'Vargas', 'Femenino', 'Ciudad de México', 'Iztacalco', 'CDMX', '04/04/2005', '5512345693', 'valentina.ramos@example.com'),
('Jorge', 'Miguel', 'Santos', 'Gómez', 'Masculino', 'Ciudad de México', 'Tlalpan', 'CDMX', '05/05/2006', '5512345694', 'jorge.santos@example.com'),
('Ana', 'Paula', 'Mendoza', 'Rojas', 'Femenino', 'Ciudad de México', 'Cuajimalpa', 'CDMX', '06/06/2007', '5512345695', 'ana.mendoza@example.com'),
('Pedro', 'Alejandro', 'Ortega', 'Silva', 'Masculino', 'Ciudad de México', 'Milpa Alta', 'CDMX', '07/07/2008', '5512345696', 'pedro.ortega@example.com'),
('Mariana', 'Fernanda', 'Cortés', 'Cortés', 'Femenino', 'Ciudad de México', 'Venustiano Carranza', 'CDMX', '08/08/2009', '5512345697', 'mariana.cortes@example.com'),
('Carlos', 'Alberto', 'Gómez', 'Sánchez', 'Masculino', 'Guadalajara', 'Guadalajara', 'Jalisco', '09/09/1990', '5512345698', 'carlos.gomez@example.com'),
('Laura', 'Isabel', 'Torres', 'Vargas', 'Femenino', 'Monterrey', 'Monterrey', 'Nuevo León', '10/10/1991', '5512345699', 'laura.torres@example.com'),
('Javier', 'Antonio', 'Rojas', 'Flores', 'Masculino', 'Puebla', 'Puebla', 'Puebla', '11/11/1992', '5512345700', 'javier.rojas@example.com'),
('Fernanda', 'Valeria', 'Mendoza', 'Guzmán', 'Femenino', 'Guadalajara', 'Zapopan', 'Jalisco', '12/12/1993', '5512345701', 'fernanda.mendoza@example.com'),
('Roberto', 'Carlos', 'Silva', 'Ortega', 'Masculino', 'Monterrey', 'San Nicolás', 'Nuevo León', '01/01/1994', '5512345702', 'roberto.silva@example.com'),
('María', 'José', 'Cortés', 'Ramos', 'Femenino', 'Puebla', 'Cholula', 'Puebla', '02/02/1995', '5512345703', 'maria.cortes@example.com'),
('Luis', 'Fernando', 'Vargas', 'Santos', 'Masculino', 'Guadalajara', 'Tlaquepaque', 'Jalisco', '03/03/1996', '5512345704', 'luis.vargas@example.com'),
('Sofía', 'Alejandra', 'Guzmán', 'Mendoza', 'Femenino', 'Monterrey', 'Guadalupe', 'Nuevo León', '04/04/1997', '5512345705', 'sofia.guzman@example.com'),
('Diego', 'Andrés', 'Ortega', 'Cortés', 'Masculino', 'Puebla', 'Atlixco', 'Puebla', '05/05/1998', '5512345706', 'diego.ortega@example.com'),
('Valentina', 'Isabella', 'Ramos', 'Vargas', 'Femenino', 'Guadalajara', 'Tonalá', 'Jalisco', '06/06/1999', '5512345707', 'valentina.ramos@example.com'),
('Jorge', 'Miguel', 'Santos', 'Gómez', 'Masculino', 'Monterrey', 'Apodaca', 'Nuevo León', '07/07/2000', '5512345708', 'jorge.santos@example.com'),
('Ana', 'Paula', 'Mendoza', 'Rojas', 'Femenino', 'Puebla', 'Tehuacán', 'Puebla', '08/08/2001', '5512345709', 'ana.mendoza@example.com'),
('Pedro', 'Alejandro', 'Ortega', 'Silva', 'Masculino', 'Guadalajara', 'Puerto Vallarta', 'Jalisco', '09/09/2002', '5512345710', 'pedro.ortega@example.com'),
('Mariana', 'Fernanda', 'Cortés', 'Cortés', 'Femenino', 'Monterrey', 'Santa Catarina', 'Nuevo León', '10/10/2003', '5512345711', 'mariana.cortes@example.com'),
('Carlos', 'Alberto', 'Gómez', 'Sánchez', 'Masculino', 'Mérida', 'Mérida', 'Yucatán', '11/11/2004', '5512345712', 'carlos.gomez@example.com'),
('Laura', 'Isabel', 'Torres', 'Vargas', 'Femenino', 'Cancún', 'Benito Juárez', 'Quintana Roo', '12/12/2005', '5512345713', 'laura.torres@example.com'),
('Javier', 'Antonio', 'Rojas', 'Flores', 'Masculino', 'Tijuana', 'Tijuana', 'Baja California', '01/01/2006', '5512345714', 'javier.rojas@example.com'),
('Fernanda', 'Valeria', 'Mendoza', 'Guzmán', 'Femenino', 'Monterrey', 'Guadalupe', 'Nuevo León', '02/02/2007', '5512345715', 'fernanda.mendoza@example.com'),
('María', 'José', 'Cortés', 'Ramos', 'Femenino', 'Mérida', 'Progreso', 'Yucatán', '04/04/2009', '5512345717', 'maria.cortes@example.com'),
('Luis', 'Fernando', 'Vargas', 'Santos', 'Masculino', 'Tijuana', 'Playas de Rosarito', 'Baja California', '05/05/2010', '5512345718', 'luis.vargas@example.com');

-- Inserción de 35 estudiantes
INSERT INTO estudiantes(id_persona) VALUES
(102),(103),(104),(105),(106),(107),(108),(109),(110),(111),
(112),(113),(114),(115),(116),(117),(118),(119),(120),(121),
(122),(123),(124),(125),(126),(127),(128),(129),(130),(131),
(132),(133),(134),(135),(136);


-- Insercion 5 docentes
INSERT INTO docente(
	id_persona, grado_academico, area_especialidad)
	VALUES (137,'Licenciatura','Ciencias '),
	(138,'Doctorado','Matematicas '),
	(139,'Licenciatura','Ciencias'),
    (140,'Doctorado','Matematicas'),
    (141,'Licenciatura','Ciencias');


-- Introducción de 40 nuevas materias con los correspondientes horarios, grupos y docentes.
INSERT INTO Materia(id_carrera, clave, nombre_materia, creditos, semestre, academia) VALUES
(3, 'PLN', 'Procesamiento de lenguaje Natural', 7.5, 06, 'Ciencias en Computación'),
(3, 'VA', 'Vision Artificial', 7.5, 06, 'Ciencias en Computacion'),
(1, 'NC', 'Numeros Complejos', 7.5, 06, 'Formación Básica'),
(3, 'NC', 'Numeros Complejos', 7.5, 06, 'Formación Básica'),
(3, 'PF', 'Presentacion y Formalismo', 5.5, 06, 'Ciencias Basicas'),
(1, 'PF', 'Presentacion y Formalismo', 5.5, 06, 'Ciencias Basicas'),
(1, 'RC', 'Redes de Computadoras', 7.5, 06, 'Ingeniería en Redes'),
(1, 'SSO', 'Seguridad de Sistemas Operativos', 7.5, 06, 'Seguridad Informática'),
(1, 'CC', 'Circuitos y Comunicaciones', 7.5, 06, 'Ingeniería en Electrónica'),
(2, 'DB', 'Database Systems', 7.5, 06, 'Computer Science'),
(2, 'AI', 'Artificial Intelligence', 7.5, 06, 'Computer Science'),
(2, 'SE', 'Software Engineering', 7.5, 06, 'Computer Science'),
(2, 'CN', 'Computer Networks', 7.5, 06, 'Computer Science'),
(2, 'OS', 'Operating Systems', 7.5, 06, 'Computer Science'),
(2, 'DS', 'Data Structures', 7.5, 06, 'Computer Science'),
(2, 'ALG', 'Algorithms', 7.5, 06, 'Computer Science'),
(2, 'WEB', 'Web Development', 7.5, 06, 'Computer Science'),
(2, 'ML', 'Machine Learning', 7.5, 06, 'Computer Science'),
(2, 'HCI', 'Human-Computer Interaction', 7.5, 06, 'Computer Science'),
(4, 'DB', 'Database Systems', 7.5, 06, 'Computer Engineering'),

-- 20 en planteles que no tienen materias
(17, 'DB', 'Database Systems', 7.5, 06, 'Computer Science'),
(17, 'AI', 'Artificial Intelligence', 7.5, 06, 'Computer Science'),
(17, 'SE', 'Software Engineering', 7.5, 06, 'Computer Science'),
(17, 'CN', 'Computer Networks', 7.5, 06, 'Computer Science'),
(17, 'OS', 'Operating Systems', 7.5, 06, 'Computer Science'),
(17, 'DS', 'Data Structures', 7.5, 06, 'Computer Science'),
(17, 'ALG', 'Algorithms', 7.5, 06, 'Computer Science'),
(17, 'WEB', 'Web Development', 7.5, 06, 'Computer Science'),
(17, 'ML', 'Machine Learning', 7.5, 06, 'Computer Science'),
(17, 'HCI', 'Human-Computer Interaction', 7.5, 06, 'Computer Science'),
(18, 'DB', 'Database Systems', 7.5, 06, 'Computer Engineering'),
(18, 'AI', 'Artificial Intelligence', 7.5, 06, 'Computer Engineering'),
(18, 'SE', 'Software Engineering', 7.5, 06, 'Computer Engineering'),
(18, 'CN', 'Computer Networks', 7.5, 06, 'Computer Engineering'),
(18, 'OS', 'Operating Systems', 7.5, 06, 'Computer Engineering'),
(18, 'DS', 'Data Structures', 7.5, 06, 'Computer Engineering'),
(18, 'ALG', 'Algorithms', 7.5, 06, 'Computer Engineering'),
(18, 'WEB', 'Web Development', 7.5, 06, 'Computer Engineering'),
(18, 'ML', 'Machine Learning', 7.5, 06, 'Computer Engineering'),
(18, 'HCI', 'Human-Computer Interaction', 7.5, 06, 'Computer Engineering');


-- Inserción de 40 nuevos grupos
INSERT INTO Grupos(id_profesor, id_materia, grupo, numero_estudiantes) VALUES
	(13, 47, '6PL3', 0),
    (16, 48, '6VA2', 0),
    (17, 49, '6NC2', 0),
    (7, 50, '6PF2', 0),
    (2, 51, '6RC2', 0),
    (14, 52, '6SSO2', 0),
    (2, 53, '6CC2', 0),
    (12, 54, '6DB4', 0),
    (13, 55, '6AI4', 0),
    (14, 56, '6SE3', 0),
    (15, 57, '6CN3', 0),
    (16, 58, '6OS3', 0),
    (17, 59, '6DS3', 0),
    (18, 60, '6ALG3', 0),
    (19, 61, '6WEB3', 0),
    (20, 62, '6ML3', 0),
    (1, 63, '6HCI3', 0),
    (2, 64, '6DB5', 0),
    (3, 65, '6AI5', 0),
    (4, 66, '6SE4', 0),
    (5, 67, '6CN4', 0),
    (6, 68, '6OS4', 0),
    (7, 69, '6DS4', 0),
    (8, 70, '6ALG4', 0),
    (9, 71, '6WEB4', 0),
    (10, 72, '6ML4', 0),
    (11, 73, '6HCI4', 0),
    (12, 74, '6DB6', 0),
    (13, 75, '6AI6', 0),
    (14, 76, '6SE5', 0),
    (15, 77, '6CN5', 0),
    (16, 78, '6OS5', 0),
    (17, 79, '6DS5', 0),
    (18, 80, '6ALG5', 0),
    (19, 81, '6WEB5', 0),
    (20, 82, '6ML5', 0),
    (1, 83, '6HCI5', 0),
    (2, 84, '6DB7', 0),
    (3, 85, '6AI7', 0),
    (4, 86, '6SE6', 0),
    (5, 87, '6CN6', 0);


INSERT INTO Horarios (id_materia, id_aula, dia, hora_inicio, hora_fin) VALUES
	(47, 1, 'Lunes', '7:00', '8:30'),
	(47, 1, 'Miercoles', '7:00', '8:30'),
	(47, 8, 'Jueves', '7:00', '8:30'),
	(48, 1, 'Lunes', '8:30', '10:00'),
	(48, 1, 'Miercoles', '8:30', '10:00'),
	(48, 8, 'Jueves', '8:30', '10:00'),
	(49, 1, 'Lunes', '10:30', '12:00'),
	(49, 1, 'Miercoles', '10:30', '12:00'),
	(49, 8, 'Jueves', '10:30', '12:00'),
	(50, 1, 'Lunes','12:00','13:30'),
	(50, 1, 'Miercoles','12:00','13:30'),
	(50, 8, 'Jueves','12:00','13:30'),
	(51, 1, 'Lunes','20:00','21:30'),
	(51, 1, 'Miercoles','20:00','21:30'),
	(51, 8, 'Jueves','20:00','21:30'),
	(52, 1, 'Lunes','15:00','16:30'),
	(52, 1, 'Miercoles','15:00','16:30'),
	(52, 8, 'Jueves','15:00','16:30'),
	(53, 1, 'Lunes','16:30','18:00'),
	(53, 1, 'Miercoles','16:30','18:00'),
	(53, 8, 'Jueves','16:30','18:00'),
	(54, 1, 'Lunes','18:30','20:00'),
	(54, 1, 'Miercoles','18:30','20:00'),
	(54, 8, 'Jueves','18:30','20:00'),	
	(55, 9, 'Lunes', '7:00', '8:30'),
	(55, 2, 'Martes', '7:00', '8:30'),
	(55, 2, 'Jueves', '7:00', '8:30'),
	(56, 9, 'Lunes', '8:30', '10:00'),
	(56, 2, 'Martes', '8:30', '10:00'),
	(56, 2, 'Jueves', '8:30', '10:00'),
	(57, 9, 'Lunes', '10:30', '12:00'),
	(57, 2, 'Martes', '10:30', '12:00'),
	(57, 2, 'Jueves', '10:30', '12:00'),
	(58, 9, 'Lunes','12:00','13:30'),
	(58, 2, 'Martes','12:00','13:30'),
	(58, 2, 'Jueves','12:00','13:30'),
	(59, 9, 'Lunes','20:00','21:30'),
	(59, 2, 'Martes','20:00','21:30'),
	(59, 2, 'Jueves','20:00','21:30'),
	(60, 9, 'Lunes','15:00','16:30'),
	(60, 2, 'Miercoles','15:00','16:30'),
	(60, 2, 'Jueves','15:00','16:30'),
	(61, 9, 'Lunes','16:30','18:00'),
	(61, 2, 'Martes','16:30','18:00'),
	(61, 2, 'Jueves','16:30','18:00'),
	(62, 9, 'Lunes','18:30','20:00'),
	(62, 2, 'Martes','18:30','20:00'),
	(62, 2, 'Jueves','18:30','20:00'),	
	(17, 3, 'Lunes', '7:00', '8:30'),
	(17, 3, 'Jueves', '7:00', '8:30'),
	(17, 10, 'Viernes', '7:00', '8:30'),
	(63, 3, 'Lunes', '8:30', '10:00'),
	(63, 3, 'Jueves', '8:30', '10:00'),
	(63, 10, 'Viernes', '8:30', '10:00'),
	(64, 3, 'Lunes', '10:30', '12:00'),
	(64, 3, 'Jueves', '10:30', '12:00'),
	(64, 10, 'Viernes', '10:30', '12:00'),
	(65, 3, 'Lunes','12:00','13:30'),
	(65, 3, 'Jueves','12:00','13:30'),
	(65, 10, 'Viernes','12:00','13:30'),
	(66, 3, 'Lunes','20:00','21:30'),
	(66, 3, 'Jueves','20:00','21:30'),
	(66, 10, 'Viernes','20:00','21:30'),
	(67, 3, 'Lunes','15:00','16:30'),
	(67, 3, 'Jueves','15:00','16:30'),
	(67, 10, 'Viernes','15:00','16:30'),
	(68, 3, 'Lunes','16:30','18:00'),
	(68, 3, 'Jueves','16:30','18:00'),
	(68, 10, 'Viernes','16:30','18:00'),
	(69, 3, 'Lunes','18:30','20:00'),
	(69, 3, 'Jueves','18:30','20:00'),
	(69, 10, 'Viernes','18:30','20:00'),	
	(70, 4, 'Lunes', '7:00', '8:30'),
	(70, 11, 'Miercoles', '7:00', '8:30'),
	(70, 4, 'Jueves', '7:00', '8:30'),
	(71, 4, 'Lunes', '8:30', '10:00'),
	(71, 11, 'Miercoles', '8:30', '10:00'),
	(71, 4, 'Jueves', '8:30', '10:00'),
	(72, 4, 'Lunes', '10:30', '12:00'),
	(72, 11, 'Miercoles', '10:30', '12:00'),
	(72, 4, 'Jueves', '10:30', '12:00'),
	(73, 4, 'Lunes','12:00','13:30'),
	(73, 11, 'Miercoles','12:00','13:30'),
	(73, 4, 'Jueves','12:00','13:30'),
	(74, 4, 'Lunes','20:00','21:30'),
	(74, 11, 'Miercoles','20:00','21:30'),
	(74, 4, 'Jueves','20:00','21:30'),
	(75, 4, 'Lunes','15:00','16:30'),
	(75, 11, 'Miercoles','15:00','16:30'),
	(75, 4, 'Jueves','15:00','16:30'),
	(76, 4, 'Lunes','16:30','18:00'),
	(76, 11, 'Miercoles','16:30','18:00'),
	(76, 4, 'Jueves','16:30','18:00'),
	(77, 4, 'Lunes','18:30','20:00'),
	(77, 11, 'Miercoles','18:30','20:00'),
	(77, 4, 'Jueves','18:30','20:00'),
	(78, 5, 'Lunes', '7:00', '8:30'),
	(78, 12, 'Martes', '7:00', '8:30'),
	(78, 5, 'Jueves', '7:00', '8:30'),
	(79, 5, 'Lunes', '8:30', '10:00'),
	(79, 12, 'Martes', '8:30', '10:00'),
	(79, 5, 'Jueves', '8:30', '10:00'),
	(80, 5, 'Lunes', '10:30', '12:00'),
	(80, 12, 'Martes', '10:30', '12:00'),
	(80, 5, 'Jueves', '10:30', '12:00'),
	(81, 5, 'Lunes','12:00','13:30'),
	(81, 12, 'Martes','12:00','13:30'),
	(81, 5, 'Jueves','12:00','13:30'),
	(82, 5, 'Lunes','20:00','21:30'),
	(82, 12, 'Martes','20:00','21:30'),
	(82, 5, 'Jueves','20:00','21:30'),
	(83, 5, 'Lunes','15:00','16:30'),
	(83, 12, 'Miercoles','15:00','16:30'),
	(83, 5, 'Jueves','15:00','16:30'),
	(84, 5, 'Lunes','16:30','18:00'),
	(84, 12, 'Martes','16:30','18:00'),
	(84, 5, 'Jueves','16:30','18:00'),
	(85, 5, 'Lunes','18:30','20:00'),
	(85, 12, 'Martes','18:30','20:00'),
	(85, 5, 'Jueves','18:30','20:00'),
	(86, 5, 'Lunes','18:30','20:00'),
	(86, 12, 'Martes','18:30','20:00'),
	(86, 5, 'Jueves','18:30','20:00');


-- adición de 10 nuevos laboratorios y/o aulas.
INSERT INTO aula(
	nombre_aula, tipo, capacidad)
	VALUES ('2001','Aula',36),
	('2002','Aula',36),
	('2003','Aula',36),
	('2004','Aula',36),
	('2005','Aula',36),
	('2006','Laboratorio',36),
	('2007','Laboratorio',36),
	('2101','Laboratorio',36),
	('2102','Laboratorio',36),
	('2103','Laboratorio',36);


-- Agregue un nuevo plantel con 2 carreras existentes y mínimo 10 materias cada carrera.
INSERT INTO Plantel(clave_plantel, nombre_plantel) VALUES
('ESCOM2','ESCUELA SUPERIOR DE CÓMPUTO - PLANTEL 2');

INSERT INTO Carrera(id_plantel, nombre_carrera, clave_carrera) VALUES
(15,'Ingeniería en Computación','IC'),
(15,'Ingeniería en Sistemas Computacionales','ISC');


INSERT INTO Materia(id_carrera, clave, nombre_materia, creditos, semestre, academia) VALUES
	(33, 'WD', 'Desarrollo Web', 8, 01, 'Informática'),
	(33, 'DPW', 'Diseño de Páginas Web', 7, 01, 'Diseño '),
	(33, 'BDW', 'Bases de Datos para la Web', 7, 02, 'Informática'),
	(33, 'TU', 'Tecnologias de Uso', 6, 02, 'Diseño Basico'),
	(33, 'PW', 'Programación Web ', 8, 01, 'Informática'),
	(33, 'HTCS', 'HTML y CSS', 7, 01, 'Informática'),
	(33, 'JSB', 'Javascript Básico', 6, 02, 'Informática'),
	(33, 'FW', 'Funcionamiento de la Web', 6, 02, 'Informática'),
	(33, 'RW', 'Responsive Web', 7, 01, 'Diseño '),
	(33, 'SDW', 'Sistemas Distribuidos en la Web', 7, 02, 'Informática');


INSERT INTO Materia(id_carrera, clave, nombre_materia, creditos, semestre, academia) VALUES
    (33, 'CALC', 'Cálculo', 8, 01, 'Matemáticas'),
    (33, 'ALG', 'Álgebra', 7, 01, 'Matemáticas'),
    (33, 'FIS', 'Física', 8, 02, 'Ciencias Básicas'),
    (33, 'PROG', 'Programación', 9, 01, 'Informática'),
    (33, 'LOG', 'Lógica', 6, 01, 'Informática'),
    (33, 'EST', 'Estadística', 6, 02, 'Matemáticas'),
    (33, 'ING', 'Introducción a la Ingeniería', 7, 01, 'Ingeniería'),
    (33, 'COM', 'Comunicación', 6, 01, 'Comunicación'),
    (33, 'SO', 'Sistemas Operativos', 8, 02, 'Informática'),
    (33, 'RED', 'Redes', 7, 02, 'Informática');




INSERT INTO estudiante_materia (id_boleta,id_materia) VALUES
(2019000081, 1),
(2019000081, 2),
(2019000081, 3),
(2019000081, 4),
(2019000082, 7),
(2019000082, 8),
(2019000082, 9),
(2019000082, 10),
(2019000083, 12),
(2019000083, 13),
(2019000083, 14),
(2019000083, 15),
(2019000084, 5),
(2019000084, 6),
(2019000084, 7),
(2019000084, 8),
(2019000085, 17),
(2019000085, 18),
(2019000085, 19),
(2019000085, 20),
(2019000086, 21),
(2019000086, 22),
(2019000086, 23),
(2019000086, 24),
(2019000087, 25),
(2019000087, 26),
(2019000087, 27),
(2019000087, 28),
(2019000088, 29),
(2019000088, 30),
(2019000088, 31),
(2019000088, 32),
(2019000089, 33),
(2019000089, 34),
(2019000089, 35),
(2019000089, 36),
(2019000090, 37),
(2019000090, 38),
(2019000090, 39),
(2019000090, 40),
(2019000091, 41),
(2019000091, 42),
(2019000091, 43),
(2019000091, 31),
(2019000092, 44),
(2019000092, 45),
(2019000092, 46),
(2019000092, 29),
(2019000093, 47),
(2019000093, 48),
(2019000093, 50),
(2019000093, 51),
(2019000094, 53),
(2019000094, 54),
(2019000094, 55),
(2019000094, 56),
(2019000095, 57),
(2019000095, 58),
(2019000095, 59),
(2019000095, 60),
(2019000096, 64),
(2019000096, 65),
(2019000096, 66),
(2019000096, 67),
(2019000097, 68),
(2019000097, 69),
(2019000097, 70),
(2019000097, 71),
(2019000098, 72),
(2019000098, 73),
(2019000098, 74),
(2019000098, 75),
(2019000099, 76),
(2019000099, 73),
(2019000099, 74),
(2019000099, 75),
(2019000100, 19),
(2019000100, 20),
(2019000100, 21),
(2019000101, 22),
(2019000102, 23),
(2019000103, 16),
(2019000104, 19),
(2019000104, 20),
(2019000104, 21),
(2019000105, 19),
(2019000105, 20),
(2019000105, 21),
(2019000106, 19),
(2019000106, 20),
(2019000106, 21),
(2019000107, 19),
(2019000107, 20),
(2019000107, 21),
(2019000108, 24),
(2019000109, 24),
(2019000110, 21),
(2019000110, 22),
(2019000110, 23),
(2019000110, 24),
(2019000111, 25),
(2019000111, 26),
(2019000111, 27),
(2019000111, 28),
(2019000112, 29),
(2019000112, 30),
(2019000112, 31),
(2019000112, 32),
(2019000113, 33),
(2019000113, 34),
(2019000113, 35),
(2019000113, 36),
(2019000114, 37),
(2019000114, 38),
(2019000114, 39),
(2019000114, 40),
(2019000115, 41),
(2019000115, 42),
(2019000115, 43),
(2019000115, 31);



alter table personas add column Estado varchar(30);
UPDATE grupos set numero_estudiantes=31;

ALTER TABLE personas DROP COLUMN estado;
ALTER TABLE personas RENAME COLUMN direccion to estado;
