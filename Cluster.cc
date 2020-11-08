#include "Cluster.hh"

void Cluster::new_cluster1(string name)
{
    nodo aux;
    aux.name = name;
    cluster = BinTree<nodo>(aux);
}

void Cluster::new_cluster2(const BinTree<nodo>& tree1, const BinTree<nodo>& tree2, double distance)
{
    nodo aux;
    aux.longitud = distance;
    string string1 = tree1.value().name;
    string string2 = tree2.value().name;
    
    if(string1 < string2){
        string resultado = string1 + string2;
        aux.name = resultado;
        cluster = BinTree<nodo>(aux, tree1, tree2);
    }
    else{
        string resultado = string2 + string1;
        aux.name = resultado;
        cluster = BinTree<nodo>(aux, tree2, tree1);
    }
    
}

string Cluster::get_name() const
{
    return cluster.value().name; 
}

BinTree<nodo> Cluster::get_bintree() const
{
    return cluster;
}
