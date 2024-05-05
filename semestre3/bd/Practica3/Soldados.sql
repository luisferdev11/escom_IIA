-- Crear la base de datos
CREATE DATABASE SOLDADOS;

-- Conectar a la base de datos creada
\c SOLDADOS;


CREATE TABLE Cuarteles (
    CuartelID SERIAL PRIMARY KEY,
    Nombre VARCHAR(255),
    Ubicacion TEXT
);

CREATE TABLE CuerposEjercito (
    CuerpoID SERIAL PRIMARY KEY,
    Nombre VARCHAR(255)
);

CREATE TABLE Compañias (
    CompañiaID SERIAL PRIMARY KEY,
    ActividadPrincipal TEXT
);

CREATE TABLE Soldados (
    SoldadoID SERIAL PRIMARY KEY,
    Nombre VARCHAR(255),
    ApellidoPaterno VARCHAR(255),
    ApellidoMaterno VARCHAR(255),
    Edad INTEGER CHECK (Edad > 0),
    Direccion TEXT,
    CuerpoID INTEGER REFERENCES CuerposEjercito(CuerpoID),
    CompañiaID INTEGER REFERENCES Compañias(CompañiaID),
    CuartelID INTEGER REFERENCES Cuarteles(CuartelID)
);

CREATE TABLE Servicios (
    ServicioID SERIAL PRIMARY KEY,
    Descripcion TEXT
);

CREATE TABLE RegistroServicios (
    RegistroID SERIAL PRIMARY KEY,
    SoldadoID INTEGER REFERENCES Soldados(SoldadoID),
    ServicioID INTEGER REFERENCES Servicios(ServicioID),
    Fecha DATE
);
