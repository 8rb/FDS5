Algorithms and Data Structures
=================================

Final Assignment
-------------

### Team
* Rodrigo Ramírez
* Marcelo Martínez
* Juan Carlos Hernández
* Gino Quispe Calixto

(Spanish)

### Intro
##### Motivacion : Lo que nos motiva a realizar este trabajo, es la satisfacción de aprobar el curso con un buen promedio y nuestra pasión por la programación. Además, tenemos motivaciones extrínsecas como nuestro historial de profesores de programación: Abraham Sopla y Ricardo Gonzales, y nuestro actual profesor Luis Martin Canaval, quien con sus exigencias, nos motiva a practicar día a día con el fin de mejorar nuestras habilidades de programación. Asimismo, el tópico del trabajo final despierta en nosotros, un deseo constante de poner en práctica los recursos que hemos aprendido en clase, así como lo que aprendemos de forma autodidacta.
##### Problema : El lenguaje de programación c++ es uno de los más conocidos, y por ende uno de los más usado. Sin embargo, debido a su relativa antigüedad, cada año se ha quedado más corto respecto a la organización de datos, debido a que en todos estos años que han pasado desde que el C++ apareció, han surgido otros lenguajes de programación que pueden organizar fácilmente los datos, haciendo un uso eficiente de sus recursos. Por esa razón, el problema del que se va a solucionar es la carencia de una biblioteca que tenga funciones que organicen de manera eficiente un conjunto de datos, independientemente del tamaño de este conjunto. 
##### Solucion : La solución ante la problematica planteada, será implementar la librería Panda de Python en C++ la cuál nos permitirá trabajar con millones de datos de una forma eficiente.

### Goals
# Objetivo general: responder al problema y le da solucion
Tras la introducción del informe, se procederá a explicar los objetivos generales que deberá de satisfacer las funciones de la biblioteca que se va a crear.

1)Importación de datos: Las funciones serán capaces de reconocer, leer, y utilizar cualquier formato con un separador de campo, utilizando archivos con extensión csv, tsv, y ser capaz de convertirla a un dataframe.

2)Indexado de datos por columna: Las funciones podrán indexar las columnas del dataframe, para optimizar la búsqueda de un elemento específico, usando una estructura de tipo árbol.

3)Selección de datos por columnas: las funciones podrán seleccionar un dato en especifico, creando para eso un nuevo dataframe

4)Filtrado de datos por columna: las funciones podrán filtrar una búsqueda usando distintos tipos de algoritmos.

5)Ordenamiento de columnas: Mediante un tipo en especifico de algoritmo de ordenamiento, las columnas se ordenarán en un orden especifico, dependiendo del criterio que se desea hacer.

6)Exportación de archivos: las funciones podrán exportar la información de un dataframe en una determinada extensión de archivo.

# Objetivos especificos: analizar, diseñar, desarrollar solucion
El informe tendrá los siguientes objetivos específicos:

1)Analizar al dataframe: Las funciones de la biblioteca podrán analizar la información de un dataframe, pudiendo modificarla, borrarla, ordenarla (dependiendo de un filtro) o exportarla.

2)Crear un dataframe y exportarlo: Las funciones de la biblioteca podrán leer y exportar un archivo en el formato csv, tsv, etc.

3)Diseñar el dataframe: Las funciones serán capaces de diseñar un dataframe a partir de un archivo y/o a partir de ciertos criterios.

### Marco Conceptual
* Arboles: Los árboles son estructuras de datos no lineales, lo que los hace jerarquicos, las cuales poseen nodos que pueden apuntar a varios nodos. Los conceptos que se pueden definir son: 
  * Nodo raiz: Primer nodo del arbol.
  * Nodo padre: Cualquier nodo que tenga al menos un hijo.
  * Nodo hijo: Cualquier nodo que tenga padre
  * Nodo hermano: Cualquier nodo que comparte el mismo padre con otro nodo.
  * Nodo rama: Cualquier nodo que posea al menos un hijo y un padre.
  * Nodo hoja: Cualquier nodo que no posea hijos.
* DataFrame: En la informática, un DataFrame se le puede definir como un paquete de datos, semejante a una matriz, la cual posee filas que se asocian a un sujeto, y también posee columnas, asociadas sus variables u objetos.
* Ordenamiento Estable: Existen distintos algoritmos para ordenar datos, pero solo algunos de estos son estables, estos son definidos así ya que mantienen un orden parcial al ordenarse nuevamente por distinto objeto. Un ejemplo sería que el algoritmo realice un primer ordenamiento por nombre, para posteriormente ser ordenado por peso, pero este seguirá ordenado por orden alfabetico.

### Cronograma de trabajo
* Hito 1:
-Crear repositorio
-Crear proyecto
-Editar Informe
  -Intro
  -Objetivos
  -Marco teorico
  -Diagrama de clases
  -Cronograma
* Hito 2:
  -Implementacion de clases
  -UI, data grid, cargar, exportar, filtros
  -Designar dependencias
* Hito 3:
  -Interfaz
  -diseño de tipos de datos abstractos (TDA)
  -TDA 1 BIN TREE
  -TDA 2 PILA
  -Diagrama de componentes (se hace en clases)
  -Diagrama de clases de bajo nivel
* notas:
 ES EN TERNO
 VISIO O YUML.ME PARA DIAGRAMA DE CLASES