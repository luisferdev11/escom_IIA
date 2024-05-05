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
