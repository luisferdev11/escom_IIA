<?php
declare(strict_types=1);

class Materia {
    public string $clave;
    public string $nombre;
    public string $fecha;
    public string $periodo;
    public string $formaEval;
    public ?int $calificacion; // La calificación puede ser null
    public string $estado; // "cursada", "en curso", "por cursar"

    public function __construct(string $clave, string $nombre, string $fecha, string $periodo, string $formaEval, ?int $calificacion, string $estado) {
        $this->clave = $clave;
        $this->nombre = $nombre;
        $this->fecha = $fecha;
        $this->periodo = $periodo;
        $this->formaEval = $formaEval;
        $this->calificacion = $calificacion;
        $this->estado = $estado;
    }
}

class Semestre {
    public string $nombre;
    /** @var Materia[] */
    public array $materias;

    public function __construct(string $nombre, array $materias) {
        $this->nombre = $nombre;
        $this->materias = $materias;
    }

    public function calcularPromedio(): float {
        $totalCalificaciones = 0;
        $numeroMaterias = 0;
        foreach ($this->materias as $materia) {
            if ($materia->estado === "cursada" && $materia->calificacion !== null) {
                $totalCalificaciones += $materia->calificacion;
                $numeroMaterias++;
            }
        }
        return $numeroMaterias > 0 ? $totalCalificaciones / $numeroMaterias : 0;
    }
}

$semestres = [
    new Semestre('PRIMER SEMESTRE', [
        new Materia('B101', 'FUNDAMENTOS DE PROGRAMACIÓN', 'Jul 3 2023', '23/2', 'ORD', 9, 'cursada'),
        new Materia('B102', 'MATEMATICAS DISCRETAS', 'Jul 3 2023', '23/2', 'ORD', 9, 'cursada'),
        new Materia('B103', 'COMUNICACIÓN ORAL Y ESCRITA', 'Jul 3 2023', '23/2', 'ORD', 9, 'cursada'),
        new Materia('B104', 'CALCULO', 'Jul 3 2023', '23/2', 'ORD', 8, 'cursada'),
        new Materia('B105', 'MECANICA Y ELECTROMAGNETISMO', 'Jul 3 2023', '23/2', 'ORD', 10, 'cursada'),
        new Materia('B106', 'FUNDAMENTOS ECONOMICOS', 'Jul 3 2023', '23/2', 'ORD', 9, 'cursada')
    ]),
    new Semestre('SEGUNDO SEMESTRE', [
        new Materia('B201', 'ALGORITMOS Y ESTRUCTURAS DE DATOS', 'Ene 22 2024', '24/1', 'ORD', 10, 'cursada'),
        new Materia('B202', 'ALGEBRA LINEAL', 'Ene 22 2024', '24/1', 'ORD', 7, 'cursada'),
        new Materia('B203', 'FUNDAMENTOS DE DISEÑO DIGITAL', 'Ene 22 2024', '24/1', 'ORD', 8, 'cursada'),
        new Materia('B204', 'CALCULO MULTIVARIABLE', 'Ene 22 2024', '24/1', 'ORD', 9, 'cursada'),
        new Materia('B205', 'INGENIERIA, ETICA Y SOCIEDAD', 'Ene 22 2024', '24/1', 'ORD', 9, 'cursada'),
        new Materia('B206', 'FINANZAS EMPRESARIALES', '', '', '', null, 'por cursar')
    ]),
    new Semestre('TERCER SEMESTRE', [
        new Materia('B301', 'ANÁLISIS Y DISEÑO DE ALGORITMOS', '', '', '', null, 'cursando'),
        new Materia('B302', 'PARADIGMAS DE PROGRAMACIÓN', '', '', '', null, 'cursando'),
        new Materia('B303', 'ECUACIONES DIFERENCIALES', '', '', '', null, 'cursando'),
        new Materia('B304', 'BASES DE DATOS', '', '', '', null, 'cursando'),
        new Materia('B305', 'DISEÑO DE SISTEMAS DIGITALES', '', '', '', null, 'cursando'),
        new Materia('B306', 'LIDERAZGO PERSONAL', 'Ene 22 2024', '24/1', 'ORD', 7, 'cursada')
    ])
    ,
    new Semestre('CUARTO SEMESTRE', [
        new Materia('B401', 'FUNDAMENTOS DE INTELIGENCIA ARTIFICIAL', '', '', '', null, 'por cursar'),
        new Materia('B402', 'PROBABILIDAD Y ESTADÍSTICA', '', '', '', null, 'por cursar'),
        new Materia('B403', 'MATEMÁTICAS AVANZADAS PARA LA INGENIERÍA', '', '', '', null, 'por cursar'),
        new Materia('B404', 'TECNOLOGÍAS PARA EL DESARROLLO DE APLICACIONES WEB', '', '', '', null, 'cursando'),
        new Materia('B405', 'ANÁLISIS Y DISEÑO DE SISTEMAS', '', '', '', null, 'por cursar'),
        new Materia('B406', 'PROCESAMIENTO DIGITAL DE IMÁGENES', '', '', '', null, 'por cursar')
    ])
];

function calcularPromedioGeneral(array $semestres): float {
    $totalCalificaciones = 0;
    $totalMaterias = 0;
    foreach ($semestres as $semestre) {
        foreach ($semestre->materias as $materia) {
            if ($materia->estado === "cursada" && $materia->calificacion !== null) {
                $totalCalificaciones += $materia->calificacion;
                $totalMaterias++;
            }
        }
    }
    return $totalMaterias > 0 ? $totalCalificaciones / $totalMaterias : 0;
}

function contarMaterias(array $semestres): array {
    $totalMaterias = 0;
    $materiasAprobadas = 0;
    $materiasReprobadas = 0;
    $materiasCursadas = 0;
    $materiasEnCurso = 0;
    $materiasPorCursar = 0;

    foreach ($semestres as $semestre) {
        foreach ($semestre->materias as $materia) {
            $totalMaterias++;
            if ($materia->estado === "cursada") {
                $materiasCursadas++;
                if ($materia->calificacion !== null && $materia->calificacion >= 6) {
                    $materiasAprobadas++;
                } else {
                    $materiasReprobadas++;
                }
            } elseif ($materia->estado === "cursando") {
                $materiasEnCurso++;
            } elseif ($materia->estado === "por cursar") {
                $materiasPorCursar++;
            }
        }
    }

    return [
        'totalMaterias' => $totalMaterias,
        'materiasAprobadas' => $materiasAprobadas,
        'materiasReprobadas' => $materiasReprobadas,
        'materiasCursadas' => $materiasCursadas,
        'materiasEnCurso' => $materiasEnCurso,
        'materiasPorCursar' => $materiasPorCursar
    ];
}

?>
