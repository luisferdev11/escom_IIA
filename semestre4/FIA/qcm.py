import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.metrics import classification_report, confusion_matrix

# Cargar los datos
qcm3 = pd.read_csv('Dataset/QCM3.csv', sep=';')
qcm6 = pd.read_csv('Dataset/QCM6.csv', sep=';')
qcm7 = pd.read_csv('Dataset/QCM7.csv', sep=';')
qcm10 = pd.read_csv('Dataset/QCM10.csv', sep=';')
qcm12 = pd.read_csv('Dataset/QCM12.csv', sep=';')

# Concatenar los datasets
dataset = pd.concat([qcm3, qcm6, qcm7, qcm10, qcm12])

# Imprimir columnas para verificar nombres y estructura
print("Columnas del dataset:")
print(dataset.columns)

# Separar características (X) y etiquetas (y)
X = dataset.iloc[:, :-5]  
y = dataset.iloc[:, -5:]  


y = y.idxmax(axis=1)  
y = y.replace({
    '1-Octanol': 0,
    '1-Propanol': 1,
    '2-Butanol': 2,
    '2-propanol': 3, 
    '1-isobutanol': 4
})

# Verificar si hay valores nulos o desconocidos en y
print("Etiquetas únicas en y:", y.unique())

# Asegurar que las etiquetas son de tipo int
y = y.astype(int)

# Dividir en conjunto de entrenamiento y prueba
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.3, random_state=42)


# Normalizar los datos (es importante para KNN)
from sklearn.preprocessing import StandardScaler
scaler = StandardScaler()
X_train = scaler.fit_transform(X_train)
X_test = scaler.transform(X_test)

# Entrenar el modelo KNN
knn = KNeighborsClassifier(n_neighbors=5)  # Puedes ajustar el número de vecinos
knn.fit(X_train, y_train)

# Predicción
y_pred = knn.predict(X_test)

# Evaluación del modelo
print("Matriz de confusión:")
print(confusion_matrix(y_test, y_pred))

print("\nReporte de clasificación:")
print(classification_report(y_test, y_pred))

# Visualizar la matriz de confusión
plt.figure(figsize=(8, 6))
sns.heatmap(confusion_matrix(y_test, y_pred), annot=True, fmt='d', cmap='Blues', xticklabels=['1-Octanol', '1-Propanol', '2-Butanol', '2-Propanol', '1-Isobutanol'], yticklabels=['1-Octanol', '1-Propanol', '2-Butanol', '2-Propanol', '1-Isobutanol'])
plt.xlabel("Predicción")
plt.ylabel("Real")
plt.title("Matriz de Confusión")
plt.show()
