/**
 * @file Set_Cluster.hh
 * @version 1.0
 * @date 17/05/2020
 * @author Sabater Andrade, Celeste
 * @brief Es la clase conjunto cluster y contiene todas sus funciones y utilidades
 */
#ifndef SET_CLUSTER_HH
#define SET_CLUSTER_HH

#include <iostream>
#include "Cluster.hh"
#include "Species.hh"
#ifndef NO_DIAGRAM
#include <list>
#include <map>
#include <vector>
#endif

using namespace std;

typedef vector <double> Fila;
typedef vector <Fila> Matrix;

/**
 * @class Set_Cluster
 * @brief Es la clase encargada de hacer los clusters a partir de un conjunto de especies y todo lo relacionado con los clusters (imprimirlos, inicializarlos, hacer el algoritmo WPGMA...).
 */

class Set_Cluster {
    
private:

    list<Cluster> set_cluster; /*!< Es el conjunto de cluster ordenado alfabeticamente*/
    Matrix dist; /*!< Es una matriz de n por n (n siendo el tamaño de la lista set_cluster) que contiene los datos de distancia en su triangular superior, se actualiza al realizar las siguientes funciones: Set_Cluster::start_cluster(), Set_Cluster::step_wpgma() y Set_Cluster::print_filogen_tree().*/

    /**
     * @pre Necesita que se le de un arbol binario.
     * @post Imprime de forma recursiva todo el arbol binario con el nombre de los nodos y la distancia a la raiz, imprime el arbol de forma "recorregut en inordre".
     * @param cluster Es el arbol binario que se usara para imprimir de forma recursiva.
     */
    void print(const BinTree<nodo>& cluster) const;
    
    /**
     * @pre Ninguno.
     * @post Elimina todos los elementos de la lista Set_Cluster::set_cluster.
     */
    void eliminar_todo();
    
public:

    /**
     * @pre Necesita que se le de un conjunto de especies y una matriz de distancias.
     * @post Inicializa los clusters, es decir, crea los clusters con las especies y inicializa la matriz dist.
     * @param spp Es el conjunto de especies que utiliza para inicializar los clusters.
     * @param distancia Es la matriz de distancias que haremos que el parametro dist copie.
     */
    //initialize the cluster with a set of species, then prints the clusters and the 
    //matrix of the distances
    void start_cluster(const map<string, Species>& ssp, const Matrix& distancia);
    
    /**
     * @pre Que se haya ejecutado la inicializacion del cluster (Set_Cluster::start_cluster()).
     * @post Fusiona los dos clusteres a menor distancia.
     */
    //execute a step from the WPGMA algorithm 
    void step_wpgma();
    
    /**
     * @pre Que se haya ejecutado la inicializacion del cluster (Set_Cluster::start_cluster()).
     * @post Si se puede ejecutar el paso WPGMA, devuelve cierto.
     */
    bool step_wpgma_is_printable() const;
    
    /**
     * @pre Que se haya ejecutado la inicializacion del cluster (Set_Cluster::start_cluster()), tambien necesita el nombre de una especie.
     * @post Imprime la estructura de arbol del cluster con ese nombre, imprime error si no existe un cluster con ese nombre.
     * @param name Buscaremos en la lista de bintrees uno que su identificador corresponda con este string.
     */
    //prints the bintree of the cluster with the given name
    //prints an error if the string doesn't match any cluster
    void print_cluster(string name) const;
    
    /**
     * @pre Que se haya ejecutado la inicializacion del cluster (Set_Cluster::start_cluster()).
     * @post Imprime la matriz de la clase, que tiene como valor las distancias entre clusters.
     */
    void print_matrix_dist() const;
    
    /**
     * @pre Necesita que se le de un conjunto de especies y una matriz de distancias.
     * @post Inicializa los clusters, ejecuta el algoritmo WPGMA e imprime el cluster final. Imprime error si el conjunto ssp esta vacio.
     * @param spp Es el conjunto de especies que utiliza para inicializar los clusters.
     * @param distancia Es la matriz de distancias que haremos que el parametro dist copie.
     */
    //does the whole WPGMA algorithm with the current set of species
    //then prints the bintree and the distance between the clusters
    void print_filogen_tree(const map<string, Species>& ssp, const Matrix& distancia);
    
};

#endif
