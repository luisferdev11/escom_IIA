select * from personas where not (nombre='Pedro' or nombre ='Juan');

insert into personas (nombre,primerapellido,segundoapellido,genero) VALUES
('Pedro', 'Ramírez','Gonzalez','Masculino');
select * from personas where nombre='Pedro' and primerapellido='Ramírez';

select * from personas where not(nombre='Héctor') and  primerapellido='Lopez';

select * from personas where nombre='Claudia' and  primerapellido='Lopez';

insert into personas (nombre,primerapellido,segundoapellido,genero) VALUES
('Chucho', 'Ruiz','Perez','Masculino'),
('Juana', 'Rodriguez','Ruiz','Femenino');
select * from personas where segundoapellido='Ruiz' or primerapellido='Ruiz';


select * from personas where primerapellido='Gómez' or primerapellido='Romero' or primerapellido='Flores';

insert into personas (nombre,primerapellido,segundoapellido,genero) VALUES
('Daniel', 'Govea','Manriquez','Masculino'),
('Daniel', 'Perez','Huerta','Masculino');
select * from personas where nombre='Daniel' and  (primerapellido='Govea' or primerapellido='Perez');

select * from personas where municipio in ('Iztacalco','Coyoacan','Benito Juarez');

insert into personas (nombre,primerapellido,segundoapellido,municipio) VALUES
('panfila','Flores','Magaña','Azcapotzalco');
select * from personas where municipio in('Azcapotzalco','Coyoacan','Benito Juarez')
	and primerapellido in ('Flores'); 
	
insert into personas (nombre,primerapellido,segundoapellido, municipio) VALUES
('Javier','Perez','Magaña','Iztacalco');
select * from personas where municipio in ('Iztacalco','Tlalpan','Iztapalapa')
			and (primerapellido in ('Blanco','Perez', 'García')
			or segundoapellido in ('Blanco','Perez', 'García'));
			
insert into personas (nombre,primerapellido,segundoapellido, municipio, telefono, fecha_nacimiento) VALUES
('Luis','Diaz','Vazquez','Iztacalco', '5511836526', '11/11/1992');
select * from personas where fecha_nacimiento is not null 
	and (primerapellido in ('Martinez', 'Garcia', 'Vazquez', 'Diaz', 'Lopez', 'Hernandez')
		or segundoapellido in ('Martinez', 'Garcia', 'Vazquez', 'Diaz', 'Lopez', 'Hernandez'));
		
select * from personas where telefono isnull 
	and ( not (primerapellido in ('Flores', 'Garcia', 'Ramírez'))
		or (not(segundoapellido in ('Flores', 'Garcia', 'Ramírez'))));





