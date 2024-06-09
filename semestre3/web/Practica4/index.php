<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Trayectoria Académica</title>
    <link rel="stylesheet" href="style.css">
</head>
<body>
    <h1>Trayectoria Académica</h1>
    <div class="trayectoria">
    <?php
        require 'trayectoria.php';

        function mostrarCampo(?string $campo): string {
            return $campo !== '' ? $campo : '---';
        }

        foreach ($semestres as $semestre) {
            echo "<h2>{$semestre->nombre}</h2>";
            echo "<table>";
            echo "<tr><th>Clave</th><th>Materia</th><th>Fecha</th><th>Periodo</th><th>Forma Eval.</th><th>Calificación</th><th>Estado</th></tr>";
            foreach ($semestre->materias as $materia) {
                echo "<tr>";
                echo "<td>" . mostrarCampo($materia->clave) . "</td>";
                echo "<td>" . mostrarCampo($materia->nombre) . "</td>";
                echo "<td>" . mostrarCampo($materia->fecha) . "</td>";
                echo "<td>" . mostrarCampo($materia->periodo) . "</td>";
                echo "<td>" . mostrarCampo($materia->formaEval) . "</td>";
                echo "<td>" . ($materia->calificacion !== null ? $materia->calificacion : '---') . "</td>";
                echo "<td>{$materia->estado}</td>";
                echo "</tr>";
            }
            $promedioSemestral = $semestre->calcularPromedio();
            echo "<tr><td colspan='6'>Promedio Semestral</td><td>{$promedioSemestral}</td></tr>";
            echo "</table>";
        }

        $promedioGeneral = calcularPromedioGeneral($semestres);
        $resumenMaterias = contarMaterias($semestres);

        echo "<div class='summary-card'>";
        echo "<h3>Resumen de elementos académicos</h3>";
        echo "<p>Total de materias con registro hasta el momento: {$resumenMaterias['totalMaterias']}</p>";
        echo "<p>Materias cursadas: {$resumenMaterias['materiasCursadas']}</p>";
        echo "<p>Materias aprobadas: {$resumenMaterias['materiasAprobadas']}</p>";
        echo "<p>Materias reprobadas: {$resumenMaterias['materiasReprobadas']}</p>";
        echo "<p>Materias en curso: {$resumenMaterias['materiasEnCurso']}</p>";
        echo "<p>Materias por cursar: {$resumenMaterias['materiasPorCursar']}</p>";
        echo "<p>Promedio general: {$promedioGeneral}</p>";
        echo "</div>";
    ?>
    </div>
    <footer>
        <p>&copy; <?php echo date("Y"); ?> Luis Fernando Rodriguez Dominguez, Pillofon. Todos los derechos reservados.</p>
        <p>Esta información es solo para fines informativos y no tiene validez oficial.</p>
    </footer>
</body>
</html>
