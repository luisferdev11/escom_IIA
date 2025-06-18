# PRÁCTICA 4  
## IDENTIFICACIÓN DE PALABRAS, FRASES, Y DOCUMENTOS SIMILARES

Generar el reporte de un programa en Python (Jupyter Notebook) para identificar palabras, frases y documentos similares. El reporte y el código deberán incluir evidencia de la realización y funcionamiento, según sea el caso, de lo siguiente:

---

## 1. Generación de cuerpo de documentos (0 pts)

Identificar libros de interés para el alumno del portal [Project Gutenberg](https://www.gutenberg.org/) y generar un cuerpo ¹ compuesto de 5 documentos. Los libros deben pertenecer a géneros o temas similares y cada documento debe corresponder a la **introducción** del respectivo libro.

---

# SIMILITUD SEMÁNTICA DE PALABRAS Y DOCUMENTOS

## 2. Normalización de documentos (10 pts)

- Cada documento se segmentará primero en oraciones² y luego en tokens con su respectiva categoría gramatical³.  
- Aplicar y justificar las técnicas de normalización adecuadas para los objetivos de los puntos 3 a 6 (pueden variar según cada tarea).

## 3. Similitud de palabras con synsets (10 pts)

- Para cada documento:
  1. Identificar el **verbo más común**.  
  2. Hallar los 5 términos más parecidos a ese verbo usando dos métricas distintas:
     - **wup_similarity**  
     - **path_similarity**  
  3. En total, obtener 10 verbos similares por documento (5 con cada métrica).

- Repetir el mismo procedimiento usando el **sustantivo más frecuente** de cada documento.

---

## 4. Similitud de documentos con synsets (10 pts)

- Para cada libro:
  1. Extraer la **frase más representativa** de su introducción (usar el algoritmo óptimo elegido en la Práctica 3).  
- De los cinco libros, elegir uno y comparar su frase representativa con las de los otros cuatro, calculando la similitud con **path_similarity**.

---

# SIMILITUD SINTÁCTICA DE PALABRAS Y DOCUMENTOS

## 5. Similitud de palabras con “embedding” (10 pts)

- Utilizar el modelo preentrenado de GloVe “Wikipedia 2014 + Gigaword 5”⁶ para, en cada documento, identificar los 5 términos más similares al **verbo más frecuente**, calculando la relación mediante **similitud de coseno**⁷ ⁸.

## 6. Similitud de documentos con “embedding” (10 pts)

- Realizar lo mismo que en el punto 4, pero usando el modelo “bert-base-uncased”⁹ (BERT sin distinción de mayúsculas/minúsculas) para calcular la similitud entre frases representativas.

---

## 7. Análisis y conclusiones (30 pts)

Analizar e identificar las diferencias en los resultados obtenidos por cada uno de los enfoques usados para identificar palabras y documentos similares.

---

## 8. Reporte y código (30 pts)

- **Reporte**:
  - Formal, dividido en secciones claras.  
  - Nombrar todas las tablas e imágenes incluidas.  
  - Cada sección debe describir su propósito y contener evidencia de los resultados.  
- **Código**:
  - Cabecera con nombre del autor, fecha y propósito.  
  - Comentarios relevantes según las “Reglas de Evaluación”.

---

## Notas

1. Las imágenes de código **no** son evidencia de funcionamiento.  
2. Se asignará calificación cero “0” si:
   - No se entrega reporte.  
   - El reporte o el código no siguen las características de las “Reglas de Evaluación”.

---

### Referencias y enlaces útiles

- **Project Gutenberg (introducciones):** https://www.gutenberg.org/  
- **Creación de corpus en NLTK:** https://www.nltk.org/howto/corpus.html#creating-new-corpus-reader-instances  
- **Segmentación y etiquetado en NLTK:** https://stackoverflow.com/questions/37605710/tokenize-a-paragraph-into-sentence-and-then-into-words-in-nltk  
- **Categorías gramaticales en NLTK:** https://www.nltk.org/book/ch05.html  
- **Similaridad con synsets (WordNet):** https://www.nltk.org/howto/wordnet.html#similarity  
- **Document similarity con synsets:** https://predictivehacks.com/document-similarity-with-synset-and-path-similarity/  
- **GloVe (Stanford NLP):** https://nlp.stanford.edu/projects/glove/  
- **GloVe en Python (Analytics Vidhya):** https://medium.com/analytics-vidhya/basics-of-using-pre-trained-glove-vectors-in-python-d38905f356db  
- **GloVe ejemplos (Kaggle):** https://www.kaggle.com/code/floser/examples-of-similar-word-embeddings-in-glove  
- **Text similarity con BERT:** https://spotintelligence.com/2022/12/19/text-similarity-python/  
- **BERT-base-uncased (Hugging Face):** https://huggingface.co/bert-base-uncased  
