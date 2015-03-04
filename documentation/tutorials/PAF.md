# Getting started

Este framework partió con la idea de lograr que la interacción con el usuario sea lo más intuitiva posible. El estado actual del framework permite lograr grandes resultados sin 

La idea de interacción con el usuario parte del concepto de proyecto. Un proyecto contiene la información suficiente para ser lanzado.

## Primera ejecución
Partiremos este apartado en dos subapartados, la configuración del proyecto y la creación de un analizador.

###Configuración del proyecto.
Paradójicamente comenzamos la casa por el tejado, pero dado que la mayor parte de los usuarios ya saben crear TSelectors y las adaptaciones son mínimas, comezamos por lo menos fácil.

Vamos a tratar de crear un proyecto que lance un analizador llamado "MyAnalizer", el cual crearemos en el siguiente apartado. Este analizador, creará un histograma con TODO.

Como antes ya comentabamos, debemos crear un proyecto. así que:
```cpp
    PAFProject* myProject = new PAFProject();
```

El proyecto que acabamos de crear, ya se puede ejecutar, pero arrojará un error debido a que hay algunas cosas que quedan pendientes de establecer. Faltan por indicar cuál es el analizador que debe usar, y los archivos sobre los que se tiene que ejecutar.

Le indicamos cual es el selector. El paquete se lo identificamos como un string, y el se encargará de buscar el paquete en los repositorios que ya le hemos configurado y de hacer el resto. 
```cpp
    myProject->AddSelectorPackage("MyAnalizer");
```

Ahora sólo nos queda por configurar sobre que archivo se ejecutará el analizador, en mi caso, utilizaré un archivo que tengo en local:
```cpp
	myProject->AddDataFile("/home/javier/Documents/Tree_ZJets_Madgraph_0.root");
```

Probablemente habrá notado que los métodos no establecen sino que añaden, por lo que si se necesita correr sobre varios archivos root, no hace falta más que añadir el resto. Igualmente para los selectores, los cuales pasarán uno detrás de otro en cada event, pero esto ya lo trataremos más adelante.

Pues ahora sí está el proyecto en condiciones de ser ejecutado, así que
```cpp
    myProject->Run();
```
