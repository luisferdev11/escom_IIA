-- Ingredientes
CREATE TABLE Ingredientes (
    id SERIAL PRIMARY KEY,
    Nombre VARCHAR(100),
    Unidad VARCHAR(50),
    Cantidad DECIMAL,
    Clasificacion VARCHAR(50)
);

-- Cuenta
CREATE TABLE Cuenta (
    id SERIAL PRIMARY KEY,
    Metodo_pago VARCHAR(50),
    Monto DECIMAL,
    Fecha DATE
);

-- Platillo
CREATE TABLE Platillo (
    id_platillo SERIAL PRIMARY KEY,
    Nombre VARCHAR(100),
    Descripcion TEXT,
    Tiempo VARCHAR(50),
    Precio DECIMAL
);

-- Cliente
CREATE TABLE Cliente (
    id_clientes SERIAL PRIMARY KEY,
    Nombre VARCHAR(100)
);

-- Mesa
CREATE TABLE Mesa (
    id_mesa SERIAL PRIMARY KEY,
    Capacidad INT,
    Ubicacion VARCHAR(100),
    Estado VARCHAR(50)
);

-- Evento
CREATE TABLE Evento (
    id_evento SERIAL PRIMARY KEY,
    Tipo VARCHAR(50),
    No_Personas INT
);

-- Mesero
CREATE TABLE Mesero (
    id_empleados SERIAL PRIMARY KEY,
    Nombre VARCHAR(100),
    Apellido_Paterno VARCHAR(100),
    Apellido_Materno VARCHAR(100)
);

-- Horario
CREATE TABLE Horario (
    id_horario SERIAL PRIMARY KEY,
    hora_inicio TIME,
    hora_fin TIME,
    dia VARCHAR(50)
);

-- Platillo_Ingredientes
CREATE TABLE Platillo_Ingredientes (
    id_platillo INT,
    id_ingrediente INT,
    PRIMARY KEY (id_platillo, id_ingrediente),
    FOREIGN KEY (id_platillo) REFERENCES Platillo(id_platillo),
    FOREIGN KEY (id_ingrediente) REFERENCES Ingredientes(id)
);

-- Cliente_Platillo
CREATE TABLE Cliente_Platillo (
    id_clientes INT,
    id_platillo INT,
    PRIMARY KEY (id_clientes, id_platillo),
    FOREIGN KEY (id_clientes) REFERENCES Cliente(id_clientes),
    FOREIGN KEY (id_platillo) REFERENCES Platillo(id_platillo)
);

-- Cliente_Mesa
CREATE TABLE Cliente_Mesa (
    id_clientes INT,
    id_mesa INT,
    fecha DATE,
    hora TIME,
    fecha_de_generacion DATE,
    estado VARCHAR(50),
    PRIMARY KEY (id_clientes, id_mesa),
    FOREIGN KEY (id_clientes) REFERENCES Cliente(id_clientes),
    FOREIGN KEY (id_mesa) REFERENCES Mesa(id_mesa)
);

-- Cliente_Evento
CREATE TABLE Cliente_Evento (
    id_clientes INT,
    id_evento INT,
    fecha DATE,
    hora TIME,
    fecha_de_generacion DATE,
    estado VARCHAR(50),
    PRIMARY KEY (id_clientes, id_evento),
    FOREIGN KEY (id_clientes) REFERENCES Cliente(id_clientes),
    FOREIGN KEY (id_evento) REFERENCES Evento(id_evento)
);

-- Mesero_Evento
CREATE TABLE Mesero_Evento (
    id_empleados INT,
    id_evento INT,
    PRIMARY KEY (id_empleados, id_evento),
    FOREIGN KEY (id_empleados) REFERENCES Mesero(id_empleados),
    FOREIGN KEY (id_evento) REFERENCES Evento(id_evento)
);

-- Mesero_Mesa
CREATE TABLE Mesero_Mesa (
    id_empleados INT,
    id_mesa INT,
    PRIMARY KEY (id_empleados, id_mesa),
    FOREIGN KEY (id_empleados) REFERENCES Mesero(id_empleados),
    FOREIGN KEY (id_mesa) REFERENCES Mesa(id_mesa)
);

-- Mesero_Horario
CREATE TABLE Mesero_Horario (
    id_empleados INT,
    id_horario INT,
    PRIMARY KEY (id_empleados, id_horario),
    FOREIGN KEY (id_empleados) REFERENCES Mesero(id_empleados),
    FOREIGN KEY (id_horario) REFERENCES Horario(id_horario)
);

-- Cliente_Cuenta
CREATE TABLE Cliente_Cuenta (
    id_clientes INT,
    id_cuenta INT,
    PRIMARY KEY (id_clientes, id_cuenta),
    FOREIGN KEY (id_clientes) REFERENCES Cliente(id_clientes),
    FOREIGN KEY (id_cuenta) REFERENCES Cuenta(id)
);
