-- Crear la base de datos Biblioteca
CREATE DATABASE BIBLIOTECA;

-- Conectar a la base de datos creada
\c BIBLIOTECA;


CREATE TABLE Autor (
    AutorID SERIAL PRIMARY KEY,
    Nombre VARCHAR(255) UNIQUE,
    Nacionalidad VARCHAR(100),
    FechaNacimiento DATE
);


CREATE TABLE Libro (
    LibroID SERIAL PRIMARY KEY,
    Titulo VARCHAR(255) UNIQUE,
    Idioma VARCHAR(100),
    Paginas INT,
    LibroReferenciaID INT NULL REFERENCES Libro(LibroID) -- Referencia opcional a otro libro
);


CREATE TABLE Autor_Libro (
    AutorID INT NOT NULL REFERENCES Autor(AutorID),
    LibroID INT NOT NULL REFERENCES Libro(LibroID),
    PRIMARY KEY (AutorID, LibroID)
);


CREATE TABLE Edicion (
    ISBN SERIAL PRIMARY KEY,
    LibroID INT NOT NULL REFERENCES Libro(LibroID),
    Ano INT
);


CREATE TABLE Copia (
    CopiaID SERIAL PRIMARY KEY,
    NumeroCopia INT,
    EdicionID INT NOT NULL REFERENCES Edicion(ISBN),
    PrecioAlquiler NUMERIC(5, 2),
    UNIQUE (NumeroCopia, EdicionID)
);


CREATE TABLE Usuario (
    RFC VARCHAR(13) PRIMARY KEY,
    Nombres VARCHAR(255),
    Apellidos VARCHAR(255),
    Domicilio TEXT
);


CREATE TABLE Prestamo (
    PrestamoID SERIAL PRIMARY KEY,
    CopiaID INT NOT NULL REFERENCES Copia(CopiaID),
    UsuarioRFC VARCHAR(13) NOT NULL REFERENCES Usuario(RFC),
    FechaPrestamo DATE,
    FechaDevolucion DATE
);
