#include <vector>
#include <iostream>
#include <string>
#include <chrono>       //Para medir tiempos de ejecución
#include <iomanip>      //Para formatear la salida
#include <filesystem>   //Para manejo de archivos y directorios
#include <fstream>      //Para operaciones de archivo
#include "dijkstra.cpp" //Algoritmo de Dijkstra para grafos ponderados
#include "BFS.cpp"      //Algoritmo BFS para grafos no ponderados
using namespace std;
namespace fs = filesystem; //Alias para el namespace filesystem

bool leerArchivo(string& nombreArchivo, Grafo*& grafo, bool& dirigido){
        //Convertir a path y verificar existencia del archivo
        fs::path filePath = nombreArchivo;
        if(!fs::exists(filePath)){
            cout << "Error: El archivo " << nombreArchivo << " no existe" << endl;
            return false;
        }
        
        //Abrir el archivo para lectura
        ifstream file(filePath);
        if(!file.is_open()){
            cout << "Error: No se pudo abrir el archivo " << nombreArchivo << endl;
            return false;
        }

    int cantidadVertices, cantidadAristas, fuente, tipo;
    file >> cantidadVertices >> cantidadAristas >> fuente >> tipo;

    if(cantidadVertices <= 0 || cantidadAristas < 0 || fuente < 0 || fuente >= cantidadVertices){
        cout << "Error: Datos invalidos en el archivo " << nombreArchivo << endl;
        return false;
    }

    if(tipo != 0 && tipo != 1){
        cout << "Error: Tipo de grafo invalido en el archivo " << nombreArchivo << endl;
        return false;
    }

    //Leer aristas
    vector<tuple<int, int, int>> aristas;
    for(int i = 0; i < cantidadAristas; i++){
        int u, v, w;
        file >> u >> v >> w;

        if(u < 0 || u >= cantidadVertices || v < 0 || v >= cantidadVertices){
            cout << "Error: Datos invalidos en el archivo " << nombreArchivo << endl;
            return false;
        }
        
        aristas.push_back(make_tuple(u, v, w));
    }
    file.close();

    //Detectar si el grafo es dirigido
    dirigido = false;
    for(size_t i = 0; i < aristas.size(); i++){
        int u1 = get<0>(aristas[i]);
        int v1 = get<1>(aristas[i]);
        bool bilateral = false;
        
        for(size_t j = 0; j < aristas.size(); j++){
            int u2 = get<0>(aristas[j]);
            int v2 = get<1>(aristas[j]);
            if(u1 == v2 && v1 == u2){
                bilateral = true;
                break;
            }
        }
        
        if(!bilateral){
            dirigido = true;
            break;
        }
    }

    //Crear grafo apropiado
    if(dirigido){
        grafo = new GrafoDirigido(cantidadVertices);
    } else {
        grafo = new Grafo(cantidadVertices);
    }

    grafo->setFuente(fuente);
    grafo->setTipo(tipo);
    grafo->setCantidadAristas(cantidadAristas);

    //Agregar aristas
    for(const auto& arista : aristas){
        grafo->agregarArista(get<0>(arista), get<1>(arista), get<2>(arista));
    }

    return true;
}

//Función para escribir resultados en formato CSV
void csv(string nombreArchivo, const string& nombreCaso, Grafo& grafo, double tiempo, bool dirigido = false, bool append = true){
    // Asegurar existencia del directorio de resultados y si no existe lo crea
    fs::path dirPath = "../results";
    if (!fs::exists(dirPath)) {
        fs::create_directories(dirPath);
    }
    
    ofstream file;
    bool archivoExiste = fs::exists(nombreArchivo);

    if(append && archivoExiste){
        file.open(nombreArchivo, ios::app);
    }
    else{
        file.open(nombreArchivo);
    }

    if(!file.is_open()){
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    //Escribir encabezado si el archivo es nuevo o se está agregando
    if(!archivoExiste || !append){
        file << "caso,algoritmo,n,m,s,tipo,tiempo_ms" << endl;
    }


    //Escribe la informacion de los grafos
    file << nombreCaso << ",";
    file << (grafo.getTipo() == 0 ? "BFS" : "Dijkstra") << ",";
    file << grafo.getCantidadVertices() << ",";
    file << grafo.getCantidadAristas() << ",";
    file << grafo.getFuente() << ",";
    file << (dirigido ? "dirigido" : "no_dirigido") << ",";
    file << fixed << setprecision(6) << tiempo << endl;

    file.close();
}

//Función para escribir resultados en formato txt
void escribirResultados(string nombreArchivo, Grafo& grafo, vector<int>& distancia, vector<vector<int>>& caminos, double tiempo, bool dirigido){
    //Asegurar existencia del directorio de datos
    fs::path dirPath = "../data";
    if (!fs::exists(dirPath)) {
        cout << "Error: El directorio " << dirPath.string() << " no existe" << endl;
    }
    
    ofstream file(nombreArchivo);
    if(!file.is_open()){
        cout << "Error: No se pudo crear el archivo " << nombreArchivo << endl;
        return;
    }

    file << "resultados";
    file << (grafo.getTipo() == 0 ? "BFS" : "DIJKSTRA") << endl;
    file << "Grafo: " << (dirigido ? "Dirigido" : "No dirigido") << endl;
    file << "Vertices: n = " << grafo.getCantidadVertices() << endl;
    file << "Aristas: m = " << grafo.getCantidadAristas() << endl;
    file << "Fuente: s = " << grafo.getFuente() << endl;
    file << "Tiempo: " << fixed << setprecision(6) << tiempo << " ms" << endl;

    if(grafo.getTipo() == 1 && grafo.pesoNegativo()){
        file << "ERROR: PESOS NEGATIVOS DETECTADOS" << endl;
        file.close();
        return;
    }

    file << "distanicias minimas desde el vertice " << grafo.getFuente() << ":" << endl;

    for(int i = 0; i < grafo.getCantidadVertices(); i++){
        file << "Vertice " << setw(3) << i << ": ";

        if(distancia[i] == INF || distancia[i] == -1){
            file << "INF (inalcanzable)" << endl;
        }
        else{
            file << setw(6) << distancia[i];
            
            if(!caminos[i].empty()){
                file << " | Camino: ";
                for(size_t j = 0; j < caminos[i].size(); j++){
                    file << caminos[i][j];
                    if(j < caminos[i].size() - 1) file << " -> ";
                }
            }
            file << endl;
        }
    }
    
    file.close();
}

void procesarCaso(string& nombreArchivo, bool primeraEjecucion){
    cout << "Procesando: " << nombreArchivo << endl;

    //grafo se declara como puntero null para convertirlo a dirigido o no dirigido segun el caso
    Grafo* grafo = nullptr;
    bool dirigido = false;

    if(!leerArchivo(nombreArchivo, grafo, dirigido)){
        cout << "Error: No se pudo leer el archivo " << nombreArchivo << endl;
        return;
    }

    cout << "Grafo: " << (dirigido ? "Dirigido" : "No dirigido") << endl;
    cout << "Vertices: " << grafo->getCantidadVertices() << endl;
    cout << "Aristas: " << grafo->getCantidadAristas() << endl;
    cout << "Fuente: " << grafo->getFuente() << endl;
    cout << "Tipo: " << (grafo->getTipo() == 0 ? "No ponderado (BFS)" : "Ponderado (Dijkstra)") << endl;

    if(grafo->getTipo() == 1 && grafo->pesoNegativo()){
        cout << "ADVERTENCIA: Pesos negativos detectados" << endl;
        
        auto inicio = chrono::high_resolution_clock::now();
        auto fin = chrono::high_resolution_clock::now();
        double tiempo = chrono::duration<double, milli>(fin - inicio).count();
    
        vector<int> distancia;
        vector<vector<int>> caminos;
    
        string nombreCaso = fs::path(nombreArchivo).stem().string();
        escribirResultados("../results/dist_" + nombreCaso + ".txt", *grafo, distancia, caminos, tiempo, dirigido);
        csv("../results/tiempos.csv", nombreCaso, *grafo, tiempo, dirigido, !primeraEjecucion);
        
        delete grafo;
        return;
    }

    int n = grafo->getCantidadVertices();
    vector<int> distancia(n);
    vector<vector<int>> caminos(n);

    auto inicio = chrono::high_resolution_clock::now();
    
    if(grafo->getTipo() == 0){
        cout << "Ejecutando BFS..." << endl;
        for(int destino = 0; destino < n; destino++){
            if(destino != grafo->getFuente()){
                vector<int> vis(n, 0);
                vector<int> dist(n, -1);
                vector<int> camino;

                bool encontrado;
                if(dirigido){
                    encontrado = encontrarElCaminoMasCortoBFSGrafoDirigido(*(GrafoDirigido*)grafo, grafo->getFuente(), destino, vis, dist, camino);
                } else {
                    encontrado = encontrarElCaminoMasCortoBFSGrafoNoDirigido(*grafo, grafo->getFuente(), destino, vis, dist, camino);
                }
                
                if(encontrado){
                    distancia[destino] = dist[destino];
                    caminos[destino] = camino;
                } else {
                    distancia[destino] = -1;
                }
            } else {
                distancia[destino] = 0;
                caminos[destino].push_back(destino);
            }
        }       
    } else {
        cout << "Ejecutando Dijkstra..." << endl;
        for(int destino = 0; destino < n; destino++){
            if(destino != grafo->getFuente()){
                vector<int> vis(n, 0);
                vector<int> dist(n, INF);
                vector<int> camino;

                bool encontrado;
                if(dirigido){
                    encontrado = encontrarElCaminoMasCortoDijstraDirigido(*(GrafoDirigido*)grafo, grafo->getFuente(), destino, vis, dist, camino);
                } else {
                    encontrado = encontrarElCaminoMasCortoDijstraNoDirigido(*grafo, grafo->getFuente(), destino, vis, dist, camino);
                }
                
                if(encontrado){
                    distancia[destino] = dist[destino];
                    caminos[destino] = camino;
                } else {
                    distancia[destino] = INF;
                }
            } else {
                distancia[destino] = 0;
                caminos[destino].push_back(destino);
            }
        }
    }
    
    auto fin = chrono::high_resolution_clock::now();
    double tiempo = chrono::duration<double, milli>(fin - inicio).count();
    cout << "Tiempo de ejecucion: " << fixed << setprecision(6) << tiempo << " ms" << endl;

    string nombreCaso = fs::path(nombreArchivo).stem().string();
    escribirResultados("../results/dist_" + nombreCaso + ".txt", *grafo, distancia, caminos, tiempo, dirigido);
    csv("../results/tiempos.csv", nombreCaso, *grafo, tiempo, dirigido, !primeraEjecucion);

    cout << "Caso procesado exitosamente" << endl;
    delete grafo;
}

int main(int argc, char* argv[]){ //los argumentos se usan para especificar un archivo de prueba particular
    cout << "BFS vs Dijkstra" << endl;

    // Crear directorios fuera de src/
    fs::create_directories("../data");
    fs::create_directories("../results");

    if(argc > 1){ 
        string argStr(argv[1]); //obtiene el primer argumento (el nombre del archivo)
        procesarCaso(argStr, true);
    }
    else{
        
        vector<string> archivos;
        for(auto entry : fs::directory_iterator("../data")){
            if(entry.path().extension() == ".txt"){
                archivos.push_back(entry.path().string()); //añade cada archivo txt encontrado en la carpeta data al vector archivos
            }
        }

        if(archivos.empty()){
           cout << "No se encontraron archivos .txt en /data/" << endl;
           cout << "Por favor, agregue archivos de prueba en la carpeta data/" << endl;
           return 1;
        }

        bool primero = true;
        for(auto& archivo : archivos){
            procesarCaso(archivo, primero);
            primero = false; //Se pone falso despues de la primera iteracion para que no se sobreescriba el archivo de resultados
        }
    }

    cout << "Completado. Resultados en /results/" << endl;

    return 0;
}