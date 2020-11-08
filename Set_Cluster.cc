#include "Set_Cluster.hh"

//////////////////////////
/*private functions*//////
//////////////////////////

void Set_Cluster::print(const BinTree<nodo>& cluster) const
{
    if (not cluster.empty())
    {
        BinTree<nodo> a = cluster.left();
        if (not a.empty())
        {
            cout << "[(" << cluster.value().name << ", " << cluster.value().longitud << ") ";
            print(a);
            print(cluster.right());
            cout << ']';
        }
        //si no tiene un hijo izquierdo, quiere decir que es una raiz
        else
            cout << '[' << cluster.value().name << ']';
    }
}

void Set_Cluster::eliminar_todo()
{
    while (!set_cluster.empty())
    {
        set_cluster.erase(set_cluster.begin());
    }
}

//////////////////////////
/*main functions*/////////
//////////////////////////

void Set_Cluster::start_cluster(const map<string, Species>& ssp, const Matrix& distancia)
{
    eliminar_todo();
    dist = distancia;
    map<string, Species>::const_iterator it;
    
    for (it = ssp.begin(); it != ssp.end(); ++it)
    {
        Cluster hey;
        hey.new_cluster1(it -> first);
        set_cluster.insert(set_cluster.end(), hey);
    }
    
}

void Set_Cluster::step_wpgma()
{
    //buscamos donde estan las dos especies mas proximas
    int n = dist.size();
    //pongo un numero mas alto al maximo para que ya el primero sea considerado el menor
    double min = 101;
    //el first sera la 'i' y el second la 'j'
    pair <int, int> posicion;
    for (int i = 0; i < n; ++i){
        int aux = i + 1;
        for (int j = aux; j < n; ++j){
            if (dist[i][j] < min)
            {
                min = dist[i][j];
                posicion.first = i;
                posicion.second = j;
            }
        }
    }
    
    list<Cluster>::iterator it1 = set_cluster.begin();
    list<Cluster>::iterator it2 = set_cluster.begin();
    int pos1, pos2;
    pos1 = posicion.first;
    pos2 = posicion.second;
    for (int i = 0; i < pos1; ++i) ++it1;
    for (int i = 0; i < pos2; ++i) ++it2;
    Cluster nombre_generico;
    //añadimos la especie nueva
    nombre_generico.new_cluster2(it1 -> get_bintree(), it2 -> get_bintree(), min/2);
    set_cluster.insert(it1, nombre_generico);
    //eliminamos las especies antiguas
    set_cluster.erase(it1);
    set_cluster.erase(it2);
    //ahora actualizamos la matriz de distancia, no se me ha ocurrido otra forma de hacerlo 
    //que con este gran sistema de ifs, espero que los comentarios ayuden a entender como funciona
    Matrix nueva (n-1, Fila(n-1));
    //estos bools sirven de marcadores por si nos pasamos de la posicion de las dos especies eliminiadas
    bool pasadoj = false;
    bool pasadoi = false;
    //dos fors para hacer un recorrido de matriz
    for(int i = 0; i < nueva.size(); ++i)
    {
        int aux = i + 1;
        //si j (que sera aux) es mayor a pos2 (la posicion en la matriz de la segunda especie)
        //ponemos en true el marcador de j, si no, lo devolvemos a false, ya que puede ponerse 
        //en true dentro del segundo for
        if (aux <= pos2) pasadoj = false;
        else pasadoj = true;
        //si i es igual a pos2, el marcador de i se pone en true, esto quiere decir que pasamos
        //por la fila de la segunda especie
        if (i == pos2) pasadoi = true;
        for (int j = aux; j < nueva.size(); ++j)
        {
            if (j == pos2) pasadoj = true;
            //si i y j son distintas a pos1, simplemente hay que coger
            //los valores de la matriz original sin hacer calculos
            if (i!=pos1 && j!=pos1)
            {
                if (!pasadoi)
                {
                    if (!pasadoj) nueva[i][j] = dist[i][j];
                    //si es cierto el marcador de j, quiere decir que el valor 
                    //que buscamos de la nueva matriz esta en una posicion adelante en j 
                    //dentro de la matriz antigua
                    else nueva[i][j] = dist[i][j+1];
                }
                //si es cierto el marcador de i, quiere decir que el valor 
                //que buscamos de la nueva matriz esta en una posicion adelante en i
                //dentro de la matriz antigua
                else
                {
                    if (!pasadoj) nueva[i][j] = dist[i+1][j];
                    else nueva[i][j] = dist[i+1][j+1];
                }
            }
            //en este caso tenemos la fila de la primera especie, haremos la media
            //entre la distancia de la especie1 con 'x' y la distancia entre la especie2 con 'x'
            else if (i == pos1)
            {
                if (!pasadoj) nueva[i][j] = (dist[i][j] + dist[j][pos2])/2;
                //lo mismo de antes, si es cierto el marcador de j, buscaremos el
                //valor en la vieja matriz con j+1
                else nueva[i][j] = (dist[i][j+1] + dist[pos2][j+1])/2;
            }
            //si j es la fila de la especie1, calcularemos la media de esta posicion y la posicion de la
            //segunda especie, no hay un caso por si el maracador de j es cierto, porque no hay un caso
            //posible para esto, ya que siempre especie1 < especie2 (en posicion de la matriz)
            //if (j == pos1)
            else nueva[i][j] = (dist[i][pos1] + dist[i][pos2])/2;
        }
    }
    dist = nueva;
}

bool Set_Cluster::step_wpgma_is_printable() const
{
    return set_cluster.size() > 1;    
}

void Set_Cluster::print_cluster(string name) const
{
    list<Cluster>::const_iterator it = set_cluster.begin();
    while ((it != set_cluster.end()) and (it->get_name() != name))
        ++it;
    if (it == set_cluster.end())
        cout << "ERROR: El cluster " <<  name << " no existe.";
    //la funcion usada a continuacion esta en la parte de funciones privadas
    else
        print(it -> get_bintree());
    cout << endl;
}

void Set_Cluster::print_matrix_dist() const
{
    int i = -1;
    list<Cluster>::const_iterator it1;
    list<Cluster>::const_iterator it2;
    for (it1 = set_cluster.begin(); it1 != set_cluster.end(); ++it1){
        cout << it1 -> get_name() << ':' ;
        ++i;
        int j = i + 1;
        list<Cluster>::const_iterator aux = it1;
        ++aux;
        for (it2 = aux; it2 != set_cluster.end(); ++it2){
            cout << ' ' << it2 -> get_name() << ' ' << '(' << dist[i][j] << ')';    
            ++j;
        }
        cout << endl;
    }
}

void Set_Cluster::print_filogen_tree(const map<string, Species>& ssp, const Matrix& distancia)
{
    start_cluster(ssp, distancia);
    if (! set_cluster.empty())
    {
        int n = dist.size();
        for (int i = 0; i < n-1; ++i)
            step_wpgma();
        list<Cluster>::const_iterator it = set_cluster.begin();
        print(it -> get_bintree());
        cout << endl;
    }
    else cout << "ERROR: El conjunto de clusters es vacio." << endl;
}
