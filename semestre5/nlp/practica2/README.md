# PRÁCTICA 2

## VECTORIZACIÓN DE DOCUMENTOS

Generar el reporte de un programa en Python (Jupyter Notebook) para vectorizar  documentos a través de distintas técnicas. En específico, a partir del cuerpo de documentos de la Tabla 1 hacer lo indicado en cada uno de los siguientes numerales.

### Tabla 1. Documentos para analizar.

| Doc. ID | Clinical Statement (Before pre-processing)                                                                                                                                  |
|---------|-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| 1       | Metastasis pancreatic cancer. Acute renal failure, evaluate for hydronephrosis or obstructive uropathy.                                                                      |
| 2       | Pancreatic cancer with metastasis. Jaundice with transaminitis, evaluate for obstruction process.                                                                            |
| 3       | Breast cancer. Pancreatitis. No output from enteric tube, assess tube.                                                                                                         |

---

## 1. Obtener los documentos resultado de una etapa de normalización. (10 puntos)

En específico, después de:

- **a.** Convertir cada palabra a minúscula y de remover “stop-words” y signos de puntuación.
- **b.** Al resultado de a), solo aplicar “lemmatization”.
- **c.** Al resultado de a), solo aplicar “stemming”.
- **d.** Al resultado de a), aplicar “lemmatization” y “stemming” (en ese orden).
- **e.** Al resultado de a), aplicar “stemming” y “lemmatization” (en ese orden).
- **f.** Al resultado de a), aplicar POS-Tagging y después “lemmatization” (en ese orden).
- **g.** Al resultado de a), aplicar POS-Tagging y después “stemming” (en ese orden).

**Nota:** como evidencia se debe mostrar el resultado después de cada etapa.

Para los siguientes incisos, se debe elegir y justificar el texto normalizado a utilizar de entre los resultados obtenidos en los incisos **b)** a **e)**.

---

## 2. Generar y mostrar el vocabulario y el histograma de términos únicos extraídos de los documentos normalizados. (05 puntos)

---

## 3. Generar los vectores para representar numéricamente cada documento de acuerdo con las siguientes técnicas: (25 puntos)

- **a.** One Hot Encoding o “Term Presence”.
- **b.** Cantidad de términos o “Term Count”.
- **c.** Probabilidad del término.

  $$
  P(t) = \frac{\text{Number of times term } t \text{ appears in the corpus}}{\text{Total number of terms in the corpus}}
  $$

- **d.** TDF-IDF.

  $$
  \text{TDF-IDF} = \text{TDF} \times \text{IDF}
  $$

  Donde:

  - **Frecuencia de términos o “Term Frequency (TF)”**:

    $$
    TF = \frac{\text{Number of times term } t \text{ appears in a document}}{\text{Total number of terms in the document}}
    $$

  - **Frecuencia inversa de documentos “Inverse Document Frequency (IDF)”**:

    $$
    IDF = \log \frac{\text{Number of documents in corpus}}{\text{Number of documents where term appears}}
    $$

---

## Análisis y conclusiones (35 puntos)

Se deben contrastar los resultados obtenidos en el punto 1 para identificar las diferencias entre el cuerpo original y el cuerpo de documentos después de haber sido normalizado. En específico, se debe indicar y argumentar el efecto de aplicar cada una de las técnicas de normalización sobre los respectivos documentos, así como el impacto del orden en que se realizan.

Con base en lo anterior, se debe justificar la elección del cuerpo de documentos normalizados a utilizar y comentar los resultados obtenidos en el punto 3.  
Particularmente, se deben demostrar las diferencias conceptuales de cada una de las técnicas de vectorización al contrastar los documentos vectorizados a través de las distintas técnicas.

---

## Reporte formal (30 puntos)

El reporte debe ser formal por lo que al menos debe estar dividido en secciones y nombrar todas las tablas e imágenes incluidas en el mismo. Además, cada sección debe describir su propósito, el resultado de las tareas ejecutadas sobre el texto o cuerpo de documentos, así como incluir la respectiva evidencia para comprobar dichos resultados.

**Notas:**

1. Las imágenes de código no son evidencia de funcionamiento.
2. Se asignará una calificación de cero “0” en la práctica en caso de que:
   - **a)** No se entregue reporte formal de la misma.
   - **b)** El reporte y/o el código no se apeguen a las características indicadas en el documento “Reglas de Evaluación”.
