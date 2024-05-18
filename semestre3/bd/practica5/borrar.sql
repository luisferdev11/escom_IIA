-- restriccion quitada del script original
alter table estudiante_materia drop constraint calificacion_pkey;

-- Borrado materia FP
update carrera_materia set id_materia=1 where id_materia in (7, 12, 25, 31, 35, 39);
update horarios set id_materia=1 where id_materia in (7, 12, 25, 31, 35, 39);
update grupos set id_materia=1 where id_materia in (7, 12, 25, 31, 35, 39);
update materia_horario set id_materia=1 where id_materia in (7, 12, 25, 31, 35, 39);
update estudiante_materia set id_materia=1 where id_materia in (7, 12, 25, 31, 35, 39);

-- Materia--CA
update carrera_materia set id_materia=2 where id_materia = 26;
update horarios set id_materia=2 where id_materia = 26;
update grupos set id_materia=2 where id_materia = 26;
update materia_horario set id_materia=2 where id_materia = 26;
update estudiante_materia set id_materia=2 where id_materia = 26;

-- Materia--BD
update carrera_materia set id_materia=3 where id_materia in (8, 14, 27, 33, 37, 40, 46);
update horarios set id_materia=3 where id_materia in (8, 14, 27, 33, 37, 40);
update grupos set id_materia=3 where id_materia in (8, 14, 27, 33, 37, 40);
update materia_horario set id_materia=3 where id_materia in (8, 14, 27, 33, 37, 40);
update estudiante_materia set id_materia=3 where id_materia in (8, 14, 27, 33, 37, 40);

-- Materia--IS
update carrera_materia set id_materia=4 where id_materia = 28;
update horarios set id_materia=4 where id_materia = 28;
update grupos set id_materia=4 where id_materia = 28;
update materia_horario set id_materia=4 where id_materia = 28;
update estudiante_materia set id_materia=4 where id_materia = 28;

update carrera_materia set id_materia=10 where id_materia = 42;
update horarios set id_materia=10 where id_materia = 42;
update grupos set id_materia=10 where id_materia = 42;
update materia_horario set id_materia=10 where id_materia = 42;
update estudiante_materia set id_materia=10 where id_materia = 42;

-- Materia--MD
update carrera_materia set id_materia=5 where id_materia in (41, 29, 9);
update horarios set id_materia=5 where id_materia in (41, 29, 9);
update grupos set id_materia=5 where id_materia in (41, 29, 9);
update materia_horario set id_materia=5 where id_materia in (41, 29, 9);
update estudiante_materia set id_materia=5 where id_materia in (41, 29, 9);

-- Materia--MDD
update carrera_materia set id_materia=6 where id_materia in (11, 15, 30, 34, 38, 43);
update horarios set id_materia=6 where id_materia in (11, 15, 30, 34, 38, 43);
update grupos set id_materia=6 where id_materia in (11, 15, 30, 34, 38, 43);
update materia_horario set id_materia=6 where id_materia in (11, 15, 30, 34, 38, 43);
update estudiante_materia set id_materia=6 where id_materia in (11, 15, 30, 34, 38, 43);

-- Materia--FIA
update carrera_materia set id_materia=13 where id_materia in (32, 36);
update horarios set id_materia=13 where id_materia in (32, 36);
update grupos set id_materia=13 where id_materia in (32, 36);
update materia_horario set id_materia=13 where id_materia in (32, 36);
update estudiante_materia set id_materia=13 where id_materia in (32, 36);

-- HORARIOS

-- 7-8:30 lunes
update materia_horario set id_horario=1 where id_horario in (49, 73, 97, 25, 121);
update horario_aula set id_horario=1 where id_horario in (49, 73, 97, 25, 121);

-- 7-8:30 miércoles
update materia_horario set id_horario=2 where id_horario in (74, 122);
update horario_aula set id_horario=2 where id_horario in (74, 122);

-- 7-8:30 jueves
update materia_horario set id_horario=3 where id_horario in (50, 75, 99, 27, 123);
update horario_aula set id_horario=3 where id_horario in (50, 75, 99, 27, 123);

-- 8:30-10 lunes
update materia_horario set id_horario=4 where id_horario in (28, 52, 76, 124, 100);
update horario_aula set id_horario=4 where id_horario in (28, 52, 76, 124, 100);

-- 8:30-10 miércoles
update materia_horario set id_horario=5 where id_horario in (77, 125);
update horario_aula set id_horario=5 where id_horario in (77, 125);

-- 8:30-10 jueves
update materia_horario set id_horario=6 where id_horario in (30, 53, 78, 126, 102);
update horario_aula set id_horario=6 where id_horario in (30, 53, 78, 126, 102);

-- 10:30-12 lunes
update materia_horario set id_horario=7 where id_horario in (55, 103, 79, 31, 127);
update horario_aula set id_horario=7 where id_horario in (55, 103, 79, 31, 127);

-- 10:30-12 miércoles
update materia_horario set id_horario=8 where id_horario in (80, 128);
update horario_aula set id_horario=8 where id_horario in (80, 128);

-- 10:30-12 jueves
update materia_horario set id_horario=9 where id_horario in (56, 105, 81, 33, 129);
update horario_aula set id_horario=9 where id_horario in (56, 105, 81, 33, 129);

-- 12-1:30 lunes
update materia_horario set id_horario=10 where id_horario in (58, 130, 34, 82, 106);
update horario_aula set id_horario=10 where id_horario in (58, 130, 34, 82, 106);

-- 12-1:30 miércoles
update materia_horario set id_horario=11 where id_horario in (131, 83);
update horario_aula set id_horario=11 where id_horario in (131, 83);

-- 12-1:30 jueves
update materia_horario set id_horario=12 where id_horario in (59, 132, 36, 84, 108);
update horario_aula set id_horario=12 where id_horario in (59, 132, 36, 84, 108);

-- 20-21:30 lunes
update materia_horario set id_horario=13 where id_horario in (37, 61, 133, 109, 85);
update horario_aula set id_horario=13 where id_horario in (37, 61, 133, 109, 85);

-- 20-21:30 miércoles
update materia_horario set id_horario=14 where id_horario in (134, 86);
update horario_aula set id_horario=14 where id_horario in (134, 86);

-- 20-21:30 jueves
update materia_horario set id_horario=15 where id_horario in (39, 62, 135, 111, 87);
update horario_aula set id_horario=15 where id_horario in (39, 62, 135, 111, 87);

-- 15-16:30 lunes
update materia_horario set id_horario=16 where id_horario in (64, 136, 40, 88, 112);
update horario_aula set id_horario=16 where id_horario in (64, 136, 40, 88, 112);

-- 15-16:30 miércoles
update materia_horario set id_horario=17 where id_horario in (137, 41, 89, 113);
update horario_aula set id_horario=17 where id_horario in (137, 41, 89, 113);

-- 15-16:30 jueves
update materia_horario set id_horario=18 where id_horario in (65, 138, 42, 90, 114);
update horario_aula set id_horario=18 where id_horario in (65, 138, 42, 90, 114);

-- 8:30-10 martes
update materia_horario set id_horario=29 where id_horario = 101;
update horario_aula set id_horario=29 where id_horario = 101;

-- 20:00-21:30 martes
update materia_horario set id_horario=38 where id_horario = 110;
update horario_aula set id_horario=38 where id_horario = 110;

-- 18:30-20:00 lunes
update materia_horario set id_horario=46 where id_horario in (70, 22, 118, 94);
update horario_aula set id_horario=46 where id_horario in (70, 22, 118, 94);

-- 18:30-20:00 martes
update materia_horario set id_horario=47 where id_horario = 119;
update horario_aula set id_horario=47 where id_horario = 119;

-- 18:30-20:00 miércoles
update materia_horario set id_horario=23 where id_horario = 95;
update horario_aula set id_horario=23 where id_horario = 95;

-- 18:30-20:00 jueves
update materia_horario set id_horario=48 where id_horario in (71, 24, 120, 96);
update horario_aula set id_horario=48 where id_horario in (71, 24, 120, 96);

-- 16:30-18:00 lunes
update materia_horario set id_horario=67 where id_horario in (19, 91, 115, 43);
update horario_aula set id_horario=67 where id_horario in (19, 91, 115, 43);

-- 16:30-18:00 jueves
update materia_horario set id_horario=68 where id_horario in (21, 93, 117, 45);
update horario_aula set id_horario=68 where id_horario in (21, 93, 117, 45);

-- 16:30-18:00 miércoles
update materia_horario set id_horario=20 where id_horario = 92;
update horario_aula set id_horario=20 where id_horario = 92;

-- 12-13:30 martes
update materia_horario set id_horario=35 where id_horario = 107;
update horario_aula set id_horario=35 where id_horario = 107;

-- 10:30-12 martes
update materia_horario set id_horario=32 where id_horario = 104;
update horario_aula set id_horario=32 where id_horario = 104;

-- 16:30-18:00 martes
update materia_horario set id_horario=44 where id_horario = 116;
update horario_aula set id_horario=44 where id_horario = 116;

-- 7-8:30 martes
update materia_horario set id_horario=26 where id_horario = 98;
update horario_aula set id_horario=26 where id_horario = 98;

-- CARRERAS

-- ISC Sistemas
update materia set id_carrera=1 where id_carrera=27;
update carrera_plantel set id_carrera=1 where id_carrera=27;
update carrera_materia set id_carrera=1 where id_carrera=27;
 
-- LCD Ciencia de datos
update materia set id_carrera=2 where id_carrera=31;
update carrera_plantel set id_carrera=2 where id_carrera=31;
update carrera_materia set id_carrera=2 where id_carrera=31;

-- IAA Inteligencia artificial
update materia set id_carrera=3 where id_carrera in (28, 32);
update carrera_plantel set id_carrera=3 where id_carrera in (28, 32);
update carrera_materia set id_carrera=3 where id_carrera in (28, 32);

-- DSRIM
update materia set id_carrera=9 where id_carrera=16;
update carrera_plantel set id_carrera=9 where id_carrera=16;
update carrera_materia set id_carrera=9 where id_carrera=16;

-- ICE
update materia set id_carrera=11 where id_carrera=18;
update carrera_plantel set id_carrera=11 where id_carrera=18;
update carrera_materia set id_carrera=11 where id_carrera=18;

-- IB
update materia set id_carrera=22 where id_carrera in (23, 30);
update carrera_plantel set id_carrera=22 where id_carrera in (23, 30);
update carrera_materia set id_carrera=22 where id_carrera in (23, 30);

-- Borramos duplicados
delete from materia where id in (7, 12, 25, 31, 35, 39);
delete from materia where id=26;
delete from materia where id in (8, 14, 27, 33, 37, 40);
delete from materia where id=28;
delete from materia where id=42;
delete from materia where id in (41, 29, 9);
delete from materia where id in (11, 15, 30, 34, 38, 43);
delete from materia where id in (32, 36);
delete from horarios where id in (49, 73, 97, 25, 121, 74, 122, 50, 75, 99, 27, 123, 28, 52, 76, 124, 100, 77, 125, 30, 53, 78, 126, 102, 55, 103, 79, 31, 127, 80, 128, 56, 105, 81, 33, 129, 58, 130, 34, 82, 106, 131, 83, 59, 132, 36, 84, 108, 37, 61, 133, 109, 85, 134, 86, 39, 62, 135, 111, 87, 64, 136, 40, 88, 112, 137, 41, 89, 113, 65, 138, 42, 90, 114, 101, 110, 70, 22, 118, 94, 119, 95, 71, 24, 120, 96, 19, 91, 115, 43, 21, 93, 117, 45, 92, 107, 104, 116, 98);
delete from carrera where id=27;
delete from carrera where id=31;
delete from carrera where id in (28, 32);
delete from carrera where id=16;
delete from carrera where id=18;
delete from carrera where id in (23, 30);


delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=1 and id_horario=1 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=1 and id_horario=3 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=1 and id_horario=68 LIMIT 2);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=1 and id_horario=67 LIMIT 2);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=1 and id_horario=2 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=1 and id_horario=20 LIMIT 1);

delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=2 and id_horario=4 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=2 and id_horario=5 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=2 and id_horario=6 LIMIT 1);

delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=3 and id_horario=7 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=3 and id_horario=8 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=3 and id_horario=9 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=3 and id_horario=46 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=3 and id_horario=48 LIMIT 1);

delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=4 and id_horario=10 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=4 and id_horario=11 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=4 and id_horario=12 LIMIT 1);

delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=5 and id_horario=13 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=5 and id_horario=14 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=5 and id_horario=15 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=5 and id_horario=1 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=5 and id_horario=3 LIMIT 1);


delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=6 and id_horario=16 LIMIT 2);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=6 and id_horario=17 LIMIT 2);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=6 and id_horario=18 LIMIT 2);

delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=10 and id_horario=4 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=10 and id_horario=6 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=6 and id_horario=7 LIMIT 1);
delete from materia_horario where ctid in(select ctid from materia_horario where id_materia=6 and id_horario=9 LIMIT 1);


delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=1 and id_materia=2 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=1 and id_materia=1 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=1 and id_materia=3 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=1 and id_materia=6 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=1 and id_materia=4 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=1 and id_materia=5 LIMIT 1);

delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=2 and id_materia=3 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=2 and id_materia=1 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=2 and id_materia=5 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=2 and id_materia=6 LIMIT 1);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=2 and id_materia=10 LIMIT 1);


delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=3 and id_materia=1 LIMIT 2);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=3 and id_materia=13 LIMIT 2);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=3 and id_materia=6 LIMIT 2);
delete from carrera_materia where ctid in(select ctid from carrera_materia where id_carrera=3 and id_materia=3 LIMIT 2);