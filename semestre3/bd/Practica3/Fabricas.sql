-- Crear la base de datos
CREATE DATABASE FABRICAS;

-- Conectar a la base de datos creada
\c FABRICAS;

-- Tabla de Clientes
CREATE TABLE clientes (
    ClienteID SERIAL PRIMARY KEY,
    Saldo NUMERIC(15, 2) CHECK (Saldo >= 0),
    LimiteCredito NUMERIC(15, 2) CHECK (LimiteCredito <= 30000),
    Descuento NUMERIC(5, 2) CHECK (Descuento >= 0 AND Descuento <= 100)
);

-- Tabla de Direcciones
CREATE TABLE direcciones (
    DireccionID SERIAL PRIMARY KEY,
    ClienteID INTEGER NOT NULL REFERENCES clientes(ClienteID),
    Calle VARCHAR(255),
    Colonia VARCHAR(255),
    CodigoPostal VARCHAR(10),
    NumeroInterior VARCHAR(10),
    NumeroExterior VARCHAR(10),
    MunicipioDelegacion VARCHAR(255),
    Estado VARCHAR(255)
);

-- Tabla de Fabricantes
CREATE TABLE fabricantes (
    FabricanteID SERIAL PRIMARY KEY,
    Telefono VARCHAR(20)
);

-- Tabla de Artículos
CREATE TABLE articulos (
    ArticuloID SERIAL PRIMARY KEY,
    FabricanteID INTEGER NOT NULL REFERENCES fabricantes(FabricanteID),
    Descripcion TEXT,
    CantidadEnStock INTEGER CHECK (CantidadEnStock >= 0)
);

-- Tabla de Pedidos
CREATE TABLE pedidos (
    PedidoID SERIAL PRIMARY KEY,
    ClienteID INTEGER NOT NULL REFERENCES clientes(ClienteID),
    DireccionID INTEGER NOT NULL REFERENCES direcciones(DireccionID),
    FechaPedido TIMESTAMP NOT NULL
);

-- Tabla de Detalle de Pedidos
CREATE TABLE detalle_pedidos (
    DetallePedidoID SERIAL PRIMARY KEY,
    PedidoID INTEGER NOT NULL REFERENCES pedidos(PedidoID),
    ArticuloID INTEGER NOT NULL REFERENCES articulos(ArticuloID),
    Cantidad INTEGER CHECK (Cantidad > 0)
);

-- Tabla de Fabricantes Alternativos (relación muchos a muchos)
CREATE TABLE fabricantes_alternativos (
    FabricantePrincipalID INTEGER NOT NULL REFERENCES fabricantes(FabricanteID),
    FabricanteAlternativoID INTEGER NOT NULL REFERENCES fabricantes(FabricanteID),
    CONSTRAINT PK_FabricantesAlternativos PRIMARY KEY (FabricantePrincipalID, FabricanteAlternativoID),
    CONSTRAINT FK_DiferenteFabricante CHECK (FabricantePrincipalID != FabricanteAlternativoID)
);
