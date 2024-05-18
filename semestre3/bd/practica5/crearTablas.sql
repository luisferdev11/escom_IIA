


create table carrera_plantel(
id_plantel int,
id_carrera int
);
alter table carrera_plantel add constraint "Carrera_FK_Carrera_Plantel" foreign key (id_carrera) references Carrera(id);
alter table carrera_plantel add constraint "Plantel_FK_Carrera_Plantel" foreign key (id_plantel) references Plantel(id);


insert into carrera_plantel
select id_plantel,id
from carrera;

create table carrera_materia(
id_carrera int,
id_materia int
);

alter table carrera_materia add constraint "materia_FKcarreramateria" foreign key (id_materia) references materia(id);
alter table carrera_materia add constraint "carrera_FKcarreramateria" foreign key (id_carrera) references carrera(id);

insert into carrera_materia
	select id_carrera, id
	from materia;



create table materia_horario(
id_materia int,
id_horario int
);
alter table materia_horario add constraint "materia_FKmateriahorario" foreign key (id_materia) references materia(id);
alter table materia_horario add constraint "horario_FKmateriahorario" foreign key (id_horario) references horarios(id);

insert into materia_horario
select id_materia,id
from horarios;

create table horario_aula(
id_horario int,
id_aula int

);
alter table horario_aula add constraint "aula_FKaulamateria" foreign key (id_aula) references aula(id);
alter table horario_aula add constraint "horario_FKaulamateria" foreign key (id_horario) references horarios(id);

insert into horario_aula
select id,id_aula
from horarios;






