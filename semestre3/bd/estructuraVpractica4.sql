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
