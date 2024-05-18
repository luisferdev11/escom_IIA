% Definición de las relaciones entre las tablas

% vendedor(Clave, Nombre, Departamento)
vendedor(120, 'Paulo', 'D1').
vendedor(239, 'Virginia', 'D3').
vendedor(321, 'Maria', 'D5').
vendedor(430, 'Mauricio', 'D2').
vendedor(532, 'Patricia', 'D4').

% departamento(Departamento, Descripción)
departamento('D1', 'Computo').
departamento('D2', 'Ropa para dama').
departamento('D3', 'Telefonia').
departamento('D4', 'Audio').
departamento('D5', 'Television').

% producto(Producto, Descripción, Costo, Departamento)
producto(102, 'TV Sharp 65 pulgadas', 12000.0, 'D5').
producto(104, 'Top verde varias tallas', 235.0, 'D2').
producto(110, 'Vestido de gala negro', 1500.0, 'D2').
producto(112, 'Laptop Dell 511', 11234.0, 'D1').
producto(113, 'PC Armada Gamer', 33000.0, 'D1').
producto(120, 'Celular LG 1296', 4500.0, 'D3').
producto(121, 'Iphone 123', 12000.0, 'D3').
producto(122, 'Amplificador Denon 1x23', 17000.0, 'D4').
producto(125, 'Jeans ajustables varias tallas', 570.0, 'D2').
producto(128, 'Guitarra electrica varios colores', 4589.0, 'D4').
producto(130, 'Bajo electrico 4 cuerdas', 6503.0, 'D4').
producto(134, 'TV Sony 75 pulgadas android', 26700.0, 'D5').
producto(137, 'Celular Huawey 64M', 12000.0, 'D5').

% venta(Producto, Total)
venta(102, 36000.0).
venta(125, 21090.0).
venta(137, 60000.0).
venta(130, 19509.0).
venta(122, 68000.0).
venta(102, 60000.0).
venta(110, 55500.0).
venta(104, 16685.0).
venta(112, 78638.0).
venta(113, 99000.0).
venta(120, 36000.0).
venta(134, 53400.0).
venta(128, 13767.0).

% venta(Producto, Total)
venta(102, 36000.0).
venta(125, 21090.0).
venta(137, 60000.0).
venta(130, 19509.0).
venta(122, 68000.0).
venta(102, 60000.0).
venta(110, 55500.0).
venta(104, 16685.0).
venta(112, 78638.0).
venta(113, 99000.0).
venta(120, 36000.0).
venta(134, 53400.0).
venta(128, 13767.0).

% Reglas de consulta
departamento_mas_vendio(Departamento, TotalVendido) :-
    findall(Total, (departamento(Depart, _), ventas_por_departamento(Depart, Ventas), sumatoria_ventas(Ventas, Total)), Totales),
    max_list(Totales, TotalVendido),
    ventas_por_departamento(Departamento, _),
    departamento(Departamento, _),
    ventas_por_departamento(Departamento, Ventas),
    sumatoria_ventas(Ventas, TotalVendido).

ventas_por_departamento(Departamento, Ventas) :-
    findall(Total, (producto(Producto, _, _, Departamento), venta(Producto, Total)), Ventas).

sumatoria_ventas([], 0).
sumatoria_ventas([Venta|Resto], Total) :-
    sumatoria_ventas(Resto, RestoTotal),
    Total is RestoTotal + Venta.

cantidad_vendida_producto(Producto, CantidadVendida) :-
    producto(Producto, _, _, _),
    ventas_producto(Producto, Ventas),
    sumatoria_ventas(Ventas, CantidadVendida).

ventas_producto(Producto, Ventas) :-
    findall(Total, venta(Producto, Total), Ventas).

vendedor_del_mes(Vendedor, TotalVendido) :-
    vendedor(Clave, Vendedor, _),
    ventas_vendedor(Clave, Ventas),
    sumatoria_ventas(Ventas, TotalVendido).
    
vendedor_max_ganancia_mes(Vendedor, MaxGanancia) :-
    vendedor_del_mes(Vendedor, MaxGanancia),
    \+ (vendedor_del_mes(_, OtraGanancia), OtraGanancia > MaxGanancia).

ventas_vendedor(Clave, Ventas) :-
    findall(Total, (vendedor(Clave, _, Departamento), producto(_, _, _, Departamento), venta(_, Total)), Ventas).

ganancia_vendedor(Vendedor, Ganancia) :-
    vendedor(Clave, Vendedor, _),
    ventas_vendedor(Clave, Ventas),
    calcular_comision(Ventas, Comision),
    sumatoria_ventas(Comision, Ganancia).

calcular_comision([], []).
calcular_comision([Venta|Resto], [Comision|RestoComision]) :-
    Comision is Venta * 0.03,
    calcular_comision(Resto, RestoComision).

