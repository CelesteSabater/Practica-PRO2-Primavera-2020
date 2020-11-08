/**
 * @file Cluster.hh
 * @version 1.0
 * @date 17/05/2020
 * @author Sabater Andrade, Celeste
 * @brief Es la clase cluster y contiene sus generadoras y una funcion para imprimir el cluster.
 */
#ifndef CLUSTER_HH
#define CLUSTER_HH

#include <iostream>
#ifndef NO_DIAGRAM
#include "BinTree.hh"
#endif

using namespace std;

/**
 * @class Cluster
 * @brief Es la clase encargada de gestionar un unico cluster.
 */

/**
 * @struct nodo
 * @brief Es un struct creado al ver la necesidad de cuando queria imprimir un arbol binario de un cluster necesitaba la distancia del nodo a la raiz y el nombre del nodo en cuestion.
 */

struct nodo {
    string name; /*!< Simplemente es el nombre del nodo.*/
    double longitud = 0; /*!< La distancia del nodo a la raiz. Si es 0, es una raiz.*/
};

class Cluster {
    
private:
    
    BinTree<nodo> cluster; /*!< Es un arbol binario que tiene en el nodo un struct llamado "nodo", esta detallado en su respectivo lugar, pero en resumen es un struct que 
    contiene el nombre del nodo (string name) y la distancia de la raiz (double longitud).*/
    
public:
    
    /**
     * @pre Necesita un string.
     * @post Se creara un cluster con un BinTree de solo una raiz.
     * @param name Es el nombre que tendra el nodo.
     */
    void new_cluster1(string name);

    /**
     * @pre Necesita dos BinTree y un double.
     * @post El cluster hara un BinTree juntando ambos BinTree
     * @brief Es una generadora que combina dos BinTree.
     * @param tree1 Es el primer arbol usado.
     * @param tree2 Es el segundo arbol usado.
     * @param distance Es la distancia entre las dos especies (ya dividida entre 2).
     */
    void new_cluster2(const BinTree<nodo>& tree1, const BinTree<nodo>& tree2, double distance);
    
    /**
     * @pre Ninguna.
     * @post Devuelve el parametro name del nodo padre.
     */
    string get_name() const;
    
    /**
     * @pre Ninguna.
     * @post Devuelve el BinTree entero.
     */
    BinTree<nodo> get_bintree() const;
    
};

#endif
