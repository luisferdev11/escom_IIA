PGDMP     6                    |            Escuela %   14.11 (Ubuntu 14.11-0ubuntu0.22.04.1) %   14.11 (Ubuntu 14.11-0ubuntu0.22.04.1) \    �           0    0    ENCODING    ENCODING        SET client_encoding = 'UTF8';
                      false            �           0    0 
   STDSTRINGS 
   STDSTRINGS     (   SET standard_conforming_strings = 'on';
                      false            �           0    0 
   SEARCHPATH 
   SEARCHPATH     8   SELECT pg_catalog.set_config('search_path', '', false);
                      false            �           1262    17970    Escuela    DATABASE     ^   CREATE DATABASE "Escuela" WITH TEMPLATE = template0 ENCODING = 'UTF8' LOCALE = 'en_US.UTF-8';
    DROP DATABASE "Escuela";
                pillogod    false            �            1259    18074    aula    TABLE     h  CREATE TABLE public.aula (
    id integer NOT NULL,
    nombre_aula character varying NOT NULL,
    tipo character varying(20),
    capacidad integer NOT NULL,
    CONSTRAINT aula_tipo_check CHECK (((tipo)::text = ANY ((ARRAY['Aula'::character varying, 'Laboratorio'::character varying, 'Clínico'::character varying, 'Otro'::character varying])::text[])))
);
    DROP TABLE public.aula;
       public         heap    pillogod    false            �            1259    18073    aula_id_seq    SEQUENCE     �   CREATE SEQUENCE public.aula_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 "   DROP SEQUENCE public.aula_id_seq;
       public          pillogod    false    226            �           0    0    aula_id_seq    SEQUENCE OWNED BY     ;   ALTER SEQUENCE public.aula_id_seq OWNED BY public.aula.id;
          public          pillogod    false    225            �            1259    18103 
   boleta_seq    SEQUENCE     |   CREATE SEQUENCE public.boleta_seq
    START WITH 2019000000
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 !   DROP SEQUENCE public.boleta_seq;
       public          pillogod    false            �            1259    18021    carrera    TABLE     �   CREATE TABLE public.carrera (
    id integer NOT NULL,
    clave_carrera character varying NOT NULL,
    nombre_carrera character varying NOT NULL,
    id_plantel integer
);
    DROP TABLE public.carrera;
       public         heap    pillogod    false            �            1259    18020    carrera_id_seq    SEQUENCE     �   CREATE SEQUENCE public.carrera_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 %   DROP SEQUENCE public.carrera_id_seq;
       public          pillogod    false    218            �           0    0    carrera_id_seq    SEQUENCE OWNED BY     A   ALTER SEQUENCE public.carrera_id_seq OWNED BY public.carrera.id;
          public          pillogod    false    217            �            1259    17997    docente    TABLE       CREATE TABLE public.docente (
    id_persona integer NOT NULL,
    numero_docente character varying,
    grado_academico character varying NOT NULL,
    area_especialidad character varying DEFAULT '---'::character varying NOT NULL,
    id_profesor integer NOT NULL
);
    DROP TABLE public.docente;
       public         heap    pillogod    false            �            1259    17996    docente_id_persona_seq    SEQUENCE     �   CREATE SEQUENCE public.docente_id_persona_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 -   DROP SEQUENCE public.docente_id_persona_seq;
       public          pillogod    false    214            �           0    0    docente_id_persona_seq    SEQUENCE OWNED BY     Q   ALTER SEQUENCE public.docente_id_persona_seq OWNED BY public.docente.id_persona;
          public          pillogod    false    213            �            1259    18130    docente_id_profesor_seq    SEQUENCE     �   CREATE SEQUENCE public.docente_id_profesor_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 .   DROP SEQUENCE public.docente_id_profesor_seq;
       public          pillogod    false    214            �           0    0    docente_id_profesor_seq    SEQUENCE OWNED BY     S   ALTER SEQUENCE public.docente_id_profesor_seq OWNED BY public.docente.id_profesor;
          public          pillogod    false    230            �            1259    17983    estudiantes    TABLE     �   CREATE TABLE public.estudiantes (
    id_persona integer NOT NULL,
    id_boleta bigint DEFAULT nextval('public.boleta_seq'::regclass) NOT NULL,
    CONSTRAINT estudiante_boleta_check CHECK ((id_boleta >= 2019000000))
);
    DROP TABLE public.estudiantes;
       public         heap    pillogod    false    228            �            1259    17982    estudiante_id_persona_seq    SEQUENCE     �   CREATE SEQUENCE public.estudiante_id_persona_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 0   DROP SEQUENCE public.estudiante_id_persona_seq;
       public          pillogod    false    212            �           0    0    estudiante_id_persona_seq    SEQUENCE OWNED BY     X   ALTER SEQUENCE public.estudiante_id_persona_seq OWNED BY public.estudiantes.id_persona;
          public          pillogod    false    211            �            1259    18083    estudiante_materia    TABLE     �   CREATE TABLE public.estudiante_materia (
    id_boleta integer NOT NULL,
    id_materia integer NOT NULL,
    calificacion double precision
);
 &   DROP TABLE public.estudiante_materia;
       public         heap    pillogod    false            �            1259    18035    grupos    TABLE     �   CREATE TABLE public.grupos (
    id integer NOT NULL,
    grupo character varying(4) NOT NULL,
    numero_estudiantes integer NOT NULL,
    id_profesor integer,
    id_materia integer
);
    DROP TABLE public.grupos;
       public         heap    pillogod    false            �            1259    18034    grupo_id_seq    SEQUENCE     �   CREATE SEQUENCE public.grupo_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 #   DROP SEQUENCE public.grupo_id_seq;
       public          pillogod    false    220            �           0    0    grupo_id_seq    SEQUENCE OWNED BY     >   ALTER SEQUENCE public.grupo_id_seq OWNED BY public.grupos.id;
          public          pillogod    false    219            �            1259    18061    horarios    TABLE     	  CREATE TABLE public.horarios (
    id_materia integer NOT NULL,
    dia character varying(10),
    hora_inicio time without time zone NOT NULL,
    hora_fin time without time zone NOT NULL,
    id_grupo integer,
    id_aula integer,
    id integer NOT NULL,
    CONSTRAINT horario_dia_check CHECK (((dia)::text = ANY ((ARRAY['Lunes'::character varying, 'Martes'::character varying, 'Miércoles'::character varying, 'Miercoles'::character varying, 'Jueves'::character varying, 'Viernes'::character varying])::text[])))
);
    DROP TABLE public.horarios;
       public         heap    pillogod    false            �            1259    18060    horario_id_seq    SEQUENCE     �   CREATE SEQUENCE public.horario_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 %   DROP SEQUENCE public.horario_id_seq;
       public          pillogod    false    224            �           0    0    horario_id_seq    SEQUENCE OWNED BY     J   ALTER SEQUENCE public.horario_id_seq OWNED BY public.horarios.id_materia;
          public          pillogod    false    223            �            1259    18113    horarios_id_seq    SEQUENCE     �   CREATE SEQUENCE public.horarios_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 &   DROP SEQUENCE public.horarios_id_seq;
       public          pillogod    false    224            �           0    0    horarios_id_seq    SEQUENCE OWNED BY     C   ALTER SEQUENCE public.horarios_id_seq OWNED BY public.horarios.id;
          public          pillogod    false    229            �            1259    18047    materia    TABLE       CREATE TABLE public.materia (
    id integer NOT NULL,
    clave character varying(4) NOT NULL,
    nombre_materia character varying NOT NULL,
    creditos integer NOT NULL,
    semestre integer,
    id_carrera integer,
    academia character varying(255)
);
    DROP TABLE public.materia;
       public         heap    pillogod    false            �            1259    18046    materia_id_seq    SEQUENCE     �   CREATE SEQUENCE public.materia_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 %   DROP SEQUENCE public.materia_id_seq;
       public          pillogod    false    222            �           0    0    materia_id_seq    SEQUENCE OWNED BY     A   ALTER SEQUENCE public.materia_id_seq OWNED BY public.materia.id;
          public          pillogod    false    221            �            1259    17972    personas    TABLE     w  CREATE TABLE public.personas (
    id integer NOT NULL,
    nombre character varying NOT NULL,
    segundo_nombre character varying,
    primerapellido character varying NOT NULL,
    segundoapellido character varying DEFAULT '---'::character varying NOT NULL,
    genero character varying(10),
    ciudad character varying,
    municipio character varying,
    direccion character varying,
    fecha_nacimiento date,
    telefono character varying,
    correo character varying,
    CONSTRAINT persona_genero_check CHECK (((genero)::text = ANY ((ARRAY['Masculino'::character varying, 'Femenino'::character varying])::text[])))
);
    DROP TABLE public.personas;
       public         heap    pillogod    false            �            1259    17971    persona_id_seq    SEQUENCE     �   CREATE SEQUENCE public.persona_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 %   DROP SEQUENCE public.persona_id_seq;
       public          pillogod    false    210            �           0    0    persona_id_seq    SEQUENCE OWNED BY     B   ALTER SEQUENCE public.persona_id_seq OWNED BY public.personas.id;
          public          pillogod    false    209            �            1259    18012    plantel    TABLE     �   CREATE TABLE public.plantel (
    id integer NOT NULL,
    nombre_plantel character varying NOT NULL,
    clave_plantel character varying NOT NULL
);
    DROP TABLE public.plantel;
       public         heap    pillogod    false            �            1259    18011    plantel_id_seq    SEQUENCE     �   CREATE SEQUENCE public.plantel_id_seq
    AS integer
    START WITH 1
    INCREMENT BY 1
    NO MINVALUE
    NO MAXVALUE
    CACHE 1;
 %   DROP SEQUENCE public.plantel_id_seq;
       public          pillogod    false    216            �           0    0    plantel_id_seq    SEQUENCE OWNED BY     A   ALTER SEQUENCE public.plantel_id_seq OWNED BY public.plantel.id;
          public          pillogod    false    215            �           2604    18077    aula id    DEFAULT     b   ALTER TABLE ONLY public.aula ALTER COLUMN id SET DEFAULT nextval('public.aula_id_seq'::regclass);
 6   ALTER TABLE public.aula ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    225    226    226            �           2604    18024 
   carrera id    DEFAULT     h   ALTER TABLE ONLY public.carrera ALTER COLUMN id SET DEFAULT nextval('public.carrera_id_seq'::regclass);
 9   ALTER TABLE public.carrera ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    218    217    218            �           2604    18000    docente id_persona    DEFAULT     x   ALTER TABLE ONLY public.docente ALTER COLUMN id_persona SET DEFAULT nextval('public.docente_id_persona_seq'::regclass);
 A   ALTER TABLE public.docente ALTER COLUMN id_persona DROP DEFAULT;
       public          pillogod    false    214    213    214            �           2604    18131    docente id_profesor    DEFAULT     z   ALTER TABLE ONLY public.docente ALTER COLUMN id_profesor SET DEFAULT nextval('public.docente_id_profesor_seq'::regclass);
 B   ALTER TABLE public.docente ALTER COLUMN id_profesor DROP DEFAULT;
       public          pillogod    false    230    214            �           2604    17986    estudiantes id_persona    DEFAULT        ALTER TABLE ONLY public.estudiantes ALTER COLUMN id_persona SET DEFAULT nextval('public.estudiante_id_persona_seq'::regclass);
 E   ALTER TABLE public.estudiantes ALTER COLUMN id_persona DROP DEFAULT;
       public          pillogod    false    211    212    212            �           2604    18038 	   grupos id    DEFAULT     e   ALTER TABLE ONLY public.grupos ALTER COLUMN id SET DEFAULT nextval('public.grupo_id_seq'::regclass);
 8   ALTER TABLE public.grupos ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    220    219    220            �           2604    18064    horarios id_materia    DEFAULT     q   ALTER TABLE ONLY public.horarios ALTER COLUMN id_materia SET DEFAULT nextval('public.horario_id_seq'::regclass);
 B   ALTER TABLE public.horarios ALTER COLUMN id_materia DROP DEFAULT;
       public          pillogod    false    223    224    224            �           2604    18114    horarios id    DEFAULT     j   ALTER TABLE ONLY public.horarios ALTER COLUMN id SET DEFAULT nextval('public.horarios_id_seq'::regclass);
 :   ALTER TABLE public.horarios ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    229    224            �           2604    18050 
   materia id    DEFAULT     h   ALTER TABLE ONLY public.materia ALTER COLUMN id SET DEFAULT nextval('public.materia_id_seq'::regclass);
 9   ALTER TABLE public.materia ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    222    221    222            �           2604    17975    personas id    DEFAULT     i   ALTER TABLE ONLY public.personas ALTER COLUMN id SET DEFAULT nextval('public.persona_id_seq'::regclass);
 :   ALTER TABLE public.personas ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    209    210    210            �           2604    18015 
   plantel id    DEFAULT     h   ALTER TABLE ONLY public.plantel ALTER COLUMN id SET DEFAULT nextval('public.plantel_id_seq'::regclass);
 9   ALTER TABLE public.plantel ALTER COLUMN id DROP DEFAULT;
       public          pillogod    false    216    215    216            �          0    18074    aula 
   TABLE DATA           @   COPY public.aula (id, nombre_aula, tipo, capacidad) FROM stdin;
    public          pillogod    false    226   ;m       }          0    18021    carrera 
   TABLE DATA           P   COPY public.carrera (id, clave_carrera, nombre_carrera, id_plantel) FROM stdin;
    public          pillogod    false    218   �m       y          0    17997    docente 
   TABLE DATA           n   COPY public.docente (id_persona, numero_docente, grado_academico, area_especialidad, id_profesor) FROM stdin;
    public          pillogod    false    214   �o       �          0    18083    estudiante_materia 
   TABLE DATA           Q   COPY public.estudiante_materia (id_boleta, id_materia, calificacion) FROM stdin;
    public          pillogod    false    227   =q       w          0    17983    estudiantes 
   TABLE DATA           <   COPY public.estudiantes (id_persona, id_boleta) FROM stdin;
    public          pillogod    false    212   �t                 0    18035    grupos 
   TABLE DATA           X   COPY public.grupos (id, grupo, numero_estudiantes, id_profesor, id_materia) FROM stdin;
    public          pillogod    false    220   v       �          0    18061    horarios 
   TABLE DATA           a   COPY public.horarios (id_materia, dia, hora_inicio, hora_fin, id_grupo, id_aula, id) FROM stdin;
    public          pillogod    false    224   hw       �          0    18047    materia 
   TABLE DATA           f   COPY public.materia (id, clave, nombre_materia, creditos, semestre, id_carrera, academia) FROM stdin;
    public          pillogod    false    222   {       u          0    17972    personas 
   TABLE DATA           �   COPY public.personas (id, nombre, segundo_nombre, primerapellido, segundoapellido, genero, ciudad, municipio, direccion, fecha_nacimiento, telefono, correo) FROM stdin;
    public          pillogod    false    210   e}       {          0    18012    plantel 
   TABLE DATA           D   COPY public.plantel (id, nombre_plantel, clave_plantel) FROM stdin;
    public          pillogod    false    216   ��       �           0    0    aula_id_seq    SEQUENCE SET     :   SELECT pg_catalog.setval('public.aula_id_seq', 21, true);
          public          pillogod    false    225            �           0    0 
   boleta_seq    SEQUENCE SET     A   SELECT pg_catalog.setval('public.boleta_seq', 2019000080, true);
          public          pillogod    false    228            �           0    0    carrera_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.carrera_id_seq', 32, true);
          public          pillogod    false    217            �           0    0    docente_id_persona_seq    SEQUENCE SET     E   SELECT pg_catalog.setval('public.docente_id_persona_seq', 1, false);
          public          pillogod    false    213            �           0    0    docente_id_profesor_seq    SEQUENCE SET     F   SELECT pg_catalog.setval('public.docente_id_profesor_seq', 20, true);
          public          pillogod    false    230            �           0    0    estudiante_id_persona_seq    SEQUENCE SET     H   SELECT pg_catalog.setval('public.estudiante_id_persona_seq', 1, false);
          public          pillogod    false    211            �           0    0    grupo_id_seq    SEQUENCE SET     ;   SELECT pg_catalog.setval('public.grupo_id_seq', 46, true);
          public          pillogod    false    219            �           0    0    horario_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.horario_id_seq', 1, false);
          public          pillogod    false    223            �           0    0    horarios_id_seq    SEQUENCE SET     ?   SELECT pg_catalog.setval('public.horarios_id_seq', 138, true);
          public          pillogod    false    229            �           0    0    materia_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.materia_id_seq', 46, true);
          public          pillogod    false    221            �           0    0    persona_id_seq    SEQUENCE SET     >   SELECT pg_catalog.setval('public.persona_id_seq', 101, true);
          public          pillogod    false    209            �           0    0    plantel_id_seq    SEQUENCE SET     =   SELECT pg_catalog.setval('public.plantel_id_seq', 14, true);
          public          pillogod    false    215            �           2606    18082    aula aula_pkey 
   CONSTRAINT     L   ALTER TABLE ONLY public.aula
    ADD CONSTRAINT aula_pkey PRIMARY KEY (id);
 8   ALTER TABLE ONLY public.aula DROP CONSTRAINT aula_pkey;
       public            pillogod    false    226            �           2606    18087 $   estudiante_materia calificacion_pkey 
   CONSTRAINT     u   ALTER TABLE ONLY public.estudiante_materia
    ADD CONSTRAINT calificacion_pkey PRIMARY KEY (id_boleta, id_materia);
 N   ALTER TABLE ONLY public.estudiante_materia DROP CONSTRAINT calificacion_pkey;
       public            pillogod    false    227    227            �           2606    18028    carrera carrera_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.carrera
    ADD CONSTRAINT carrera_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.carrera DROP CONSTRAINT carrera_pkey;
       public            pillogod    false    218            �           2606    18133    docente docente_pkey 
   CONSTRAINT     [   ALTER TABLE ONLY public.docente
    ADD CONSTRAINT docente_pkey PRIMARY KEY (id_profesor);
 >   ALTER TABLE ONLY public.docente DROP CONSTRAINT docente_pkey;
       public            pillogod    false    214            �           2606    17990    estudiantes estudiante_pkey 
   CONSTRAINT     a   ALTER TABLE ONLY public.estudiantes
    ADD CONSTRAINT estudiante_pkey PRIMARY KEY (id_persona);
 E   ALTER TABLE ONLY public.estudiantes DROP CONSTRAINT estudiante_pkey;
       public            pillogod    false    212            �           2606    18040    grupos grupo_pkey 
   CONSTRAINT     O   ALTER TABLE ONLY public.grupos
    ADD CONSTRAINT grupo_pkey PRIMARY KEY (id);
 ;   ALTER TABLE ONLY public.grupos DROP CONSTRAINT grupo_pkey;
       public            pillogod    false    220            �           2606    18119    horarios horarios_pkey 
   CONSTRAINT     T   ALTER TABLE ONLY public.horarios
    ADD CONSTRAINT horarios_pkey PRIMARY KEY (id);
 @   ALTER TABLE ONLY public.horarios DROP CONSTRAINT horarios_pkey;
       public            pillogod    false    224            �           2606    18054    materia materia_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.materia
    ADD CONSTRAINT materia_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.materia DROP CONSTRAINT materia_pkey;
       public            pillogod    false    222            �           2606    17981    personas persona_pkey 
   CONSTRAINT     S   ALTER TABLE ONLY public.personas
    ADD CONSTRAINT persona_pkey PRIMARY KEY (id);
 ?   ALTER TABLE ONLY public.personas DROP CONSTRAINT persona_pkey;
       public            pillogod    false    210            �           2606    18019    plantel plantel_pkey 
   CONSTRAINT     R   ALTER TABLE ONLY public.plantel
    ADD CONSTRAINT plantel_pkey PRIMARY KEY (id);
 >   ALTER TABLE ONLY public.plantel DROP CONSTRAINT plantel_pkey;
       public            pillogod    false    216            �           2606    18106    estudiantes unique_id_boleta 
   CONSTRAINT     \   ALTER TABLE ONLY public.estudiantes
    ADD CONSTRAINT unique_id_boleta UNIQUE (id_boleta);
 F   ALTER TABLE ONLY public.estudiantes DROP CONSTRAINT unique_id_boleta;
       public            pillogod    false    212            �           2606    18107 2   estudiante_materia calificacion_id_estudiante_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.estudiante_materia
    ADD CONSTRAINT calificacion_id_estudiante_fkey FOREIGN KEY (id_boleta) REFERENCES public.estudiantes(id_boleta);
 \   ALTER TABLE ONLY public.estudiante_materia DROP CONSTRAINT calificacion_id_estudiante_fkey;
       public          pillogod    false    3277    212    227            �           2606    18093 /   estudiante_materia calificacion_id_materia_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.estudiante_materia
    ADD CONSTRAINT calificacion_id_materia_fkey FOREIGN KEY (id_materia) REFERENCES public.materia(id);
 Y   ALTER TABLE ONLY public.estudiante_materia DROP CONSTRAINT calificacion_id_materia_fkey;
       public          pillogod    false    3287    227    222            �           2606    18029    carrera carrera_id_plantel_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.carrera
    ADD CONSTRAINT carrera_id_plantel_fkey FOREIGN KEY (id_plantel) REFERENCES public.plantel(id);
 I   ALTER TABLE ONLY public.carrera DROP CONSTRAINT carrera_id_plantel_fkey;
       public          pillogod    false    218    3281    216            �           2606    18006    docente docente_id_persona_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.docente
    ADD CONSTRAINT docente_id_persona_fkey FOREIGN KEY (id_persona) REFERENCES public.personas(id);
 I   ALTER TABLE ONLY public.docente DROP CONSTRAINT docente_id_persona_fkey;
       public          pillogod    false    3273    210    214            �           2606    17991 &   estudiantes estudiante_id_persona_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.estudiantes
    ADD CONSTRAINT estudiante_id_persona_fkey FOREIGN KEY (id_persona) REFERENCES public.personas(id);
 P   ALTER TABLE ONLY public.estudiantes DROP CONSTRAINT estudiante_id_persona_fkey;
       public          pillogod    false    212    210    3273            �           2606    18125    grupos fk_grupos_materia    FK CONSTRAINT     |   ALTER TABLE ONLY public.grupos
    ADD CONSTRAINT fk_grupos_materia FOREIGN KEY (id_materia) REFERENCES public.materia(id);
 B   ALTER TABLE ONLY public.grupos DROP CONSTRAINT fk_grupos_materia;
       public          pillogod    false    222    220    3287            �           2606    18120    horarios fk_horarios_materia    FK CONSTRAINT     �   ALTER TABLE ONLY public.horarios
    ADD CONSTRAINT fk_horarios_materia FOREIGN KEY (id_materia) REFERENCES public.materia(id);
 F   ALTER TABLE ONLY public.horarios DROP CONSTRAINT fk_horarios_materia;
       public          pillogod    false    224    3287    222            �           2606    18140    grupos grupo_id_docente_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.grupos
    ADD CONSTRAINT grupo_id_docente_fkey FOREIGN KEY (id_profesor) REFERENCES public.docente(id_profesor);
 F   ALTER TABLE ONLY public.grupos DROP CONSTRAINT grupo_id_docente_fkey;
       public          pillogod    false    220    214    3279            �           2606    18098    horarios horario_id_aula_fkey    FK CONSTRAINT     {   ALTER TABLE ONLY public.horarios
    ADD CONSTRAINT horario_id_aula_fkey FOREIGN KEY (id_aula) REFERENCES public.aula(id);
 G   ALTER TABLE ONLY public.horarios DROP CONSTRAINT horario_id_aula_fkey;
       public          pillogod    false    226    224    3291            �           2606    18068    horarios horario_id_grupo_fkey    FK CONSTRAINT        ALTER TABLE ONLY public.horarios
    ADD CONSTRAINT horario_id_grupo_fkey FOREIGN KEY (id_grupo) REFERENCES public.grupos(id);
 H   ALTER TABLE ONLY public.horarios DROP CONSTRAINT horario_id_grupo_fkey;
       public          pillogod    false    3285    224    220            �           2606    18055    materia materia_id_carrera_fkey    FK CONSTRAINT     �   ALTER TABLE ONLY public.materia
    ADD CONSTRAINT materia_id_carrera_fkey FOREIGN KEY (id_carrera) REFERENCES public.carrera(id);
 I   ALTER TABLE ONLY public.materia DROP CONSTRAINT materia_id_carrera_fkey;
       public          pillogod    false    218    222    3283            �   �   x�e�11D�:9�8��[�s��!!EZ���il���˃�R����LU��b�d56�;ٍJ�q�ø%�<t��u��:��ug����\CsY�{ȕYCn�#���J��O���-��>����>���s��W�      }     x��T�n�0>���'�bC�����R����Y{N�����Þ��؎�6��D�����o�� R��hU�d�L��ƩJ6�կ����F��J��v:S&����u�l�\�G� �x�,�S�.:t�N?i�*A�S�@"U����/�
�������a�9ll�l-sۓ���-���-z�h1�Z��c���+Xd� 9��[�b�6"�'�&����%���ٞ��l���$Ꟍ���.�oF�H׾UYIqYX�u>!"������0�#�va(o�-U��JP�I'G�^����z�L=(���E"��mb#�~I���-�j��?cZ���?I��}��%���ǂ�u7��_jkT]�o]��d3HDz}��H��X�\��|���(%��l]]Z`%�q�X�ִ�G���"��x�5����\�S�1k���0tFX8�k��gվvF���x���-�3�����G���.+#lu��D�-�{1jr=V��^�'A�mCξ�1"!�z����#"?!��P�      y   >  x��S�n�0�}O�'�r&q�R�RF�dɱQl�>;0T<�_�THnAJ����~�3���̝�[G�6(���J-�z�Se��Y��[8���jT'<���pBjg�Q����M��0(/c��!����:�ْ	4�KK����P>��$�ZI���wO��A�v������7��~GgZ�O����<��`�&�ϕW�A�OGj�u>�RR$��]�8��KZ��lP�9֠#m�0���<A�v����$�����a&P���=?���i���X��Xs`�sD�lF������(zw=A5�{X�' �1�      �   �  x�e�A� ��1*K��ߑ����o��
��������v��>�\mg] +�	F�ꖳ�v~k^������zۭw�=�.t��o��U��Q��hw-Ed��6��-[F;7����u��^�x@.��l��Ef�Cgr��\����ծ��z�O�X�Ӻ����aK�tD\�Y����/��d�L�Y,N�њ�����n�.Е��ǃD��}`��u�M�[O^ ���F&���f��`� ��j>����*���������L3L�DV�a�v3�&3�T3�i�"���4Äf�T3�Y�N3LP�
3�i�Ɏ-0Ùf��0C��&�g�aB3Lh�	�Љ��0Äf����j�3�0�&4C�O3h��f�]���0C�f\i�f�h�I����	�0�&3�T3�Y4C�E3`�3�0�&��'�P{�&(U�
3�i�Ɏ-0�N3Lh�	�0�fH�0Äf���aR��_�&4Ä}`R�p�&4CO3z��ӌ�f�4��:��f��i� ��f8�Y�aB3L�n:�0���a�3�0ٱf�^��aR�pf�w�a2sI5Ùf���3� a�	�0�&�5U�aB3Lh�	�0�f�+�0�&��p�&4Äf�Ќ{�4c�1r����3h� ���J3�k��9c�a@3Lf.�f�לa�v��4Äf�T3�3h��9cĜ�L3Lvl�c�&4Äf�T3�i�	�O�1^sƌ9C9�0�&��j�3͘g�1_s��9c�1sΘw�1s��Μ3f�4C f8ӌ��3Lh��9c�挙sƌ9c���ی9c�4c���V|M9�T�a�R�I3�iƺ���L3VO3Lh�I5c�i�	�X������Z�5�f�Ќ���Z�5�V�aB3Lh��XO�!@3h� �X�f<�0C������J:�      w   "  x�Mӻ��0C�د����_��80��.@Q�Ǐ�����TpJ!��*v�3����/Jf�f��3��Y��,qyV�k�o�����?�w$��y�<B�<	�^�toB�|u�%��/�.qu����K8�.��D��EJ�&�Ő����]JBJB%!�ˢ���LJB%!�֢��~�KK�CkQ��,�%�ws%T2ZT�H�fa�GX�.�}}�kc����;X靬�.Vz7+�����>�e��a��q��s�Opu����ҧ�ҧ��g��������#p?�_aG�,         =  x�E�;n1Кs�@��W�Y8�����R�"�V#j�L�x1bb��-!P���P��2T��#Qш���Pj�&#3�$&�D\�؏�#f�D�&�d��T�E�^5p%ͽ�����x:}����{s�'I&;'�Ī9;I�p���n��狓��\�B|��U� 1H�+X�B�U��Az\a�vȈ6����UU�k�	���In-P���2��[xq���n+�"��6蚭���
mW�Qm����v�j{�w=�3���	+���'�ym�a�^��;�������~�Nf�J��
k�?�~? ��m      �   �  x����n1��0�v�7��GN� �)���e��H����O]ن�=ݧןϿ]h!����n�y�좋>����/�~��F	�����+ѝ�4s��1�6"�r֨ ͜��z;r���yDx˹@��Y���3g~����)�BE���"�rD��US|7� ޢ�T�:��Q������a�!���.T���jE�}�Q�/b?��q�Z��fԊt|G�g��Os_��!	�u�jF����Nå�����I.U�&��cP}BP'�I+�1�F*9>FU��,�QK�1�Fu
�|L�U��$3je0�ШR�TM�
Q��Z��4�T0XrV�.�M��ˑL�
{.�XH3��Õ��L�z�=WU,DU��2�hT�`�禊e.Us%�|�����
��U�0(�����=ly�!��^THTu`*�[�jk>U0�$�<0���<ق����*f�FU�D3��g�p�H�d�IT{`
���-O7�U�Lu���L���-�7�a�Y��\$�A0���<�kXvQ=ˮ��F�{V�S}�,�����T���q�N5���2Hv�C\��dv+�m �dwKD�ѩVb>T�@
��J�z�Y�H�8�N��-"nЩff7���:Iv7��F�S��,�T�@2��ֈ�B�ډYxl1ջ�F#Q7G\zF'R�� l;���)Ш�#�b�T�s�mU:�Q�[\�R��(l����Tu���5*�9��*͠QI��yњ�F�qѺ*M�ٵ��F�j�iX�P��)4�By��T�v�|�w4�F]*oq�J�������]��4�� �*����MM�ٝyL,����V}��Dh���cb'T�4�^���ce޿A".�~E�iX�|IBc4�Ï��P5�Ӱz��������F���i�?}���6(�      �   J  x��VA��0<w^�����pD�8 �a�{��,��+�ox���	��:F3#���S���L�,�rǎ\Ze��7Z4;�Z��
H�g!��31��BOg{+G%,�kS���F�l��|F�۫qQ�W0g��Ls��]��]������H��X~t�V�/E�۪���4w�k.�uk!��3
�ȡ��o���:���5����X*}��,��2��i��3$��,��I&��Y�c�0I��!>k2��4Ma�*����7��c�R[��[�K�a�j���iXw6��zu�PVk(�ﳰ��g}�0'e�'cݾ_D�M��I�A�U�8J��!g�1C�*����gϘ�-[4�n[�DKԎ����W���w��7&B��v=^X
�%��_����ɿl�z�T� ,�&H�q�0E$�����HY�0&���tg�T�ZD����`�xgF�q�5y6S:�{NC�Z��N�A��ţ��"� ͟�S�Z6�Ih1��ޫ���iG��tj��O�n�Q*2�~'Kw���6s��ɣv[���Z�Few�#��6�7�G��Y��^S3��GE��z��      u   {  x��X�r�8}V��_��-`	$L��-̦jR��`(+K�l���j�a~lO�������!ࣖZ��v[<H'�]�`�본!Y�1e��ڊ'ʖ�V��O���:�I9Ei4�2�U�p���H��T��v�T�-CѴ��t����U����:Gip��xSd��C�N�ɥx�!��ڑ�-�1�D:k�a]��K��ųT���k2�3�]!=��Ω����U��)���Ԛ���~)d�KK�������s��f���{�R��ʅ����DQ)n��ς9n���y���^� �]�5��ͺ��)�%>qm9�v�%�T��F�U�y|Q�dč#�2\��.��_�j��t�L�ʸ��'>����B6�ѝԪ:vUUo���c_��Y��
�G!�F%R��v_�J��j������9�V&(�`�a���>��P׭��Վ�JZG��<�"wV���p�!�c���J�3[��n�B'�]��:-q�*����+N�y�+N״Wt�-F8������j�/ZmɅ���%N���bF�b�CA.|O����K$�M��2Uu�5�f���:�{j�#�$�����ѓZ��־"g����� �#��SKe�	�)��
�-f2�\1�d��ZQ¼�nlP����`��L�_[�h$��r�xX����h<�>�3�mC�'�M�T��i�V�B���3	ʣI��<ZJ��(��g�7��`�+>�6���G�"����tP���CcfE��B.�׊��C6�I�Z�gDK�� 5+q 0-�Į�{g��0�6<S\&<+;%��
�1��S����Ǜ��"Q "�^*���D%�7\��������6uf�%��Dg�b�j���h�d�p���|�C��r���W�,�ܺ��$D���{`�����b����J��$����N���S*6�˦�"��3S���9�[�@�b*m������!��\_:��o��SѠ�]�
�b�0VU��!]�*�6�2�kV!��BF��+K������dCa�!��	�����lb%���ةx?_��yfQ�D�C��SAdWx�ͤwʟ�%����Md�,x;Z��W�)|�Lk��3�N��a4l?��m���l#Y�C���b���+�}����w�v�f�\.�P*�����"��2̪ױ%������A���2GKV)�M<]�2�D�+�>p��8�S%+�%5�o���5��<�̏�LUC�����J%�&H���k��C�l��w�;%�1�@�>p��v��J3��d/��>��bi�����SјJj�����9���bD2�9���H�w<1)��0zP������Z����ᱸM����G��4�Óq�,�S����R�'��mt����]$T�6������/;�RE�߫\�k�}_0���`3��)+�`!*/���䠇��Q���{���E�_�8VEN4L%\IC����V�'�U8|�<�1X��� ����#��j8�Ǳ�aݪ!5�z����
�.��$��p١�,�r<�F�[�9�o��R�;Wq�n��R�G0���9���>ǝ�>#��o���ʦA+��O��{�QZz���&+�x�̗5����b~�fT�B�kt�=3����h�F��"\^V1c�^��U~��P�y(:)�wJ�͆K.�ML��p~����戇�v5���W��%-��aO�YSG��G��Ͱ��\Cʣ�Z:l�j�����a�M�䷴_��+>�K�|�Edt㩈�ȜU�p9j0�p���
ɍ�@�d�L����Vak�_�����a|,���?�}�����	�ש]�3y<�m�|��[��h���K��.�ϳ���� �Cض�ډ٪���I��j�v��~`����^�]�.ߩ��@�`�@i}�����/�Xi�      {   f  x���Kn�0���)|�V��2�"5*au3r�ԕG�C�u��#�buHDbA����|���/D%5�U�K������9l�4_�爌<&����
��E�2�9 ��-f!#�_R4u��ҙ,�Z����htsȔ03sF&g]͛}�8S�ܞ�Dͧ t"� �R��=_��E;Qq���";�)w�O� a�~�U��rV�'��yD�]d�S��֨RH�ҚWY(��]����*�ʵB�
Z�T���ɚ=x�e8�s9 �L���u����
��+\߿���������WA�p)Gl�o���E�J�?��Qڬ��Z鶭�����Ꮊ*��!@C7y�&�|��@x     