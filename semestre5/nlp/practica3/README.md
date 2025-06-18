# PRÁCTICA 3  
## IDENTIFICACIÓN DE FRASES CLAVE Y RESUMEN AUTOMÁTICO DE TEXTO

Generar el reporte de un programa en Python (Jupyter Notebook) para ejecutar extracción de frases clave y para hacer resumen automático de textos. El reporte y el código, respectivamente, deberán incluir evidencia de la realización y funcionamiento, según sea el caso, de lo siguiente:

---

## 1. Generación de cuerpo de documentos (0 pts)

Descargar el libro “Frankenstein” de la liga  
<https://www.gutenberg.org/ebooks/84>  
y generar un cuerpo de tres documentos. Cada documento debe corresponder a las tres primeras cartas contenidas en el libro.

---

## 2. Normalización de textos (10 pts)

Por cada documento se debe determinar, justificar y, de ser el caso, ejecutar las técnicas para normalizar las cartas antes de ingresarlas a cada uno de los algoritmos indicados en el siguiente punto.

---

## 3. Resumen automático extractivo de texto (30 pts)

Generar un resumen concatenando las 4 frases más representativas de cada una de las cartas utilizando los algoritmos siguientes:

1. **TF‑IDF – NLTK**  
   - Ejemplo de código y explicación:  
     https://spotintelligence.com/2022/12/13/keyword-extraction/  
2. **Frecuencia de palabras normalizada**  
   - Ejemplos de código:  
     1. https://www.kdnuggets.com/2019/11/getting-started-automated-text-summarization.html  
     2. https://www.activestate.com/blog/how-to-do-text-summarization-with-python/  
     3. https://medium.com/1-hour-blog-series/automatic-text-summarization-made-simpler-using-python-577e7622c57a  
3. **RAKE – NLTK**  
   - Código y explicación:  
     https://www.markovml.com/blog/rake-algorithm  
4. **TextRank**  
   - Ejemplos y librerías:  
     1. https://blog.devgenius.io/create-precise-text-summaries-with-textrank-algorithm-in-python-a2441fec37a9  
     2. https://snyk.io/advisor/python/sumy/functions/sumy.summarizers.text_rank.TextRankSummarizer  
5. **BERT – Transformers**  
   - Tutoriales:  
     1. https://medium.com/analytics-vidhya/text-summarization-using-bert-gpt2-xlnet-5ee80608e961  
     2. https://www.exxactcorp.com/blog/deep-learning/extractive-summarization-with-llm-using-bert  
6. **LSA**  
   - Implementaciones:  
     1. https://snyk.io/advisor/python/sumy/functions/sumy.summarizers.text_rank.TextRankSummarizer  
     2. https://www.turing.com/kb/5-powerful-text-summarization-techniques-in-python  

Además, se debe medir y reportar el tiempo requerido por el equipo de cómputo utilizado para generar el resumen de las cartas por cada uno de los algoritmos indicados.

---

## 4. Análisis y conclusiones (30 pts)

Analizar e identificar las diferencias en los resultados obtenidos por cada uno de los algoritmos utilizados para generar un “Resumen automático extractivo de las cartas” (punto 3).

---

## 5. Reporte y código (30 pts)

- El reporte debe ser formal:  
  - Dividido en secciones.  
  - Nombrar todas las tablas e imágenes incluidas.  
  - Cada sección debe describir su propósito y contener evidencia de los resultados de cada tarea ejecutada sobre el cuerpo de documentos.  
- El código debe incluir:  
  - Cabecera con nombre del autor, fecha y propósito.  
  - Comentarios relevantes según las “Reglas de Evaluación” publicadas al inicio del semestre.

---

## Notas

1. Las imágenes de código **no** son evidencia de funcionamiento.  
2. Se asignará calificación de cero “0” si:  
   - No se entrega reporte de la misma.  
   - Los archivos del reporte y código no se apegan a las características indicadas en el documento “Reglas de Evaluación”.

---

### Referencias y enlaces útiles

- **Frankenstein (Gutenberg):** <https://www.gutenberg.org/ebooks/84>  
- **TF‑IDF – NLTK:** <https://spotintelligence.com/2022/12/13/keyword-extraction/>  
- **Frecuencia normalizada (KDnuggets):** <https://www.kdnuggets.com/2019/11/getting-started-automated-text-summarization.html>  
- **Frecuencia normalizada (ActiveState):** <https://www.activestate.com/blog/how-to-do-text-summarization-with-python/>  
- **Frecuencia normalizada (Medium):** <https://medium.com/1-hour-blog-series/automatic-text-summarization-made-simpler-using-python-577e7622c57a>  
- **RAKE – NLTK:** <https://www.markovml.com/blog/rake-algorithm>  
- **TextRank (DevGenius):** <https://blog.devgenius.io/create-precise-text-summaries-with-textrank-algorithm-in-python-a2441fec37a9>  
- **TextRank/LSA (Sumy):** <https://snyk.io/advisor/python/sumy/functions/sumy.summarizers.text_rank.TextRankSummarizer>  
- **BERT – Transformers (Vidhya):** <https://medium.com/analytics-vidhya/text-summarization-using-bert-gpt2-xlnet-5ee80608e961>  
- **BERT – Transformers (ExxactCorp):** <https://www.exxactcorp.com/blog/deep-learning/extractive-summarization-with-llm-using-bert>  
- **LSA (Turing):** <https://www.turing.com/kb/5-powerful-text-summarization-techniques-in-python>
