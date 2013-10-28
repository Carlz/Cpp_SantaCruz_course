////////////////////////////////////////////////////////////////////////////////
/// \brief      Graph class implementation
/// \author     Carlos Sampaio
/// \file       Graph.cpp
/// \date       20/10/2013
///
///     Graph class implementation.
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <assert.h>
#include "Graph.h"

//-----------------
// Public methods
//-----------------

/// \brief  Generate a random graph structure base on node count and edge density
/// \param  nd_cnt      Node count: number of nodes in the Graph
/// \param  density     Graph edges density: values range from 0.0 to 1.0
void Graph::randomize(unsigned int nd_cnt, float density, float cost_low, float cost_high)
{
    this->destroy();                                    // clear previous Graph data
    if (nd_cnt == 0) return;                            // stop if empty Graph was defined
    nodes.resize(nd_cnt);                               // else create requested number of nodes
    if (density <= 0) return;                           // stop if zero density Graph was defined
    for (node src = 0; src < nd_cnt; ++src)             // else iterate over possible edges
       for (node dst = src + 1; dst < nd_cnt; ++dst)    // and add them randomly based on requested
           this->add_random_edge(src, dst, density, cost_low, cost_high); // density and cost range
}

/// \brief  Returns the number of edges in the graph.
/// \return Number of edges
int Graph::edge_cnt() const
{
    int n_edges = 0;
    for (int i = 0; i < nodes.size(); ++i )
        n_edges += nodes[i].edges.size();
    return n_edges/2;   // undirected graph - edges counted in double
}

// Tests whether there is an edge from node x to node y.
// Assuming that is undirected graph
bool Graph::adjacent(node x, node y) const
{
    assert(x < nodes.size());

    for (int i = 0; i < nodes[x].edges.size(); ++i)
    {
        if (nodes[x].edges[i].dest_node == y)
            return true;
    }
    return false;
}

// Lists all nodes y such that there is an edge from x to y.
vector<node> Graph::neighbours(node x) const
{
    assert(x < nodes.size());
    vector<node> nb_list = {};       // Neighbours list
    if (x >= nodes.size())
        return nb_list;    
    for (int i = 0; i < nodes[x].edges.size(); ++i)
        nb_list.push_back(nodes[x].edges[i].dest_node);
    return nb_list;
}

// Adds the edge from x to y, if it is not there.
// Assuming that is undirected graph
void Graph::add_edge(node x, node y, float cost = 0.0)
{
    assert(cost >= 0);
    
    if (x >= nodes.size())
        nodes.resize(x);
            
    if (y >= nodes.size())
        nodes.resize(y);
        
    if (!this->adjacent(x, y))
    {
        edge_data new_edge;
        new_edge.cost = cost;        
        new_edge.dest_node = y;
        nodes[x].edges.push_back(new_edge);
        new_edge.dest_node = x;
        nodes[y].edges.push_back(new_edge);
    }
}

// Removes the edge from x to y, if it is there.
// Assuming that is undirected graph
void Graph::delete_edge(node x, node y)
{
    assert(x < nodes.size() && y < nodes.size());

    this->delete_edge_uni(x, y);
    this->delete_edge_uni(y, x);
}

// Returns the value associated with the node x.
float Graph::get_node_value(node x) const
{
    assert(x < nodes.size());
    return nodes[x].value;
}

// Sets the value associated with the node x.
void Graph::set_node_value(node x, float val)
{
    assert(x < nodes.size() && val >= 0);
    nodes[x].value = val;
}

// Returns the value associated to the edge (x,y).
// -1 does not exist
float Graph::get_edge_value(node x, node y) const
{
    assert(x < nodes.size());
    
    for (int i = 0; i < nodes[x].edges.size(); ++i)
        if (nodes[x].edges[i].dest_node == y)
            return nodes[x].edges[i].cost;
    // If edge does not exist, return a negative number
    return -1.0;
}

//Sets the value associated to the edge (x,y) to cost.    
void Graph::set_edge_value (node x, node y, float cost)
{
    assert(x < nodes.size() && y < nodes.size() && cost >= 0);

    this->set_edge_value_uni(x, y, cost);
    this->set_edge_value_uni(y, x, cost);
}

// Clear all graph structure
void Graph::destroy()
{
    int n_nodes = this->node_cnt();
    if (n_nodes == 0) return;
    for (int i = 0; i < n_nodes; ++i)
        nodes[i].edges.clear();
    nodes.clear();
}


ostream& operator<<(ostream& out, const Graph& data)
{
    if (data.nodes.size() == 0)
        return (out << "Empty graph!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Number of nodes: " << data.node_cnt() << endl;
    out << "Number of edges: " << data.edge_cnt() << endl;
    out << "Source\tDestination(cost)" << endl;
    for (node src = 0; src < data.nodes.size(); ++src)
    {
        out << src << "\t";
        for (int dst = 0; dst < data.nodes[src].edges.size(); ++dst)
        {
            out << data.nodes[src].edges[dst].dest_node << "(";
            out << data.nodes[src].edges[dst].cost << ") ";
        }
        out << endl;
    }
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}

//-----------------
// Private methods
//-----------------

void Graph::delete_edge_uni(node x, node y)
{
    vector<edge_data>* node_edges = &(nodes[x].edges);
    for (edge_iterator it = node_edges->begin(); it != node_edges->end(); ++it )
        if (it->dest_node == y)
        {
            node_edges->erase(it);
            break;
        }
}

//Sets the value associated to the edge (x,y) to cost.    
void Graph::set_edge_value_uni(node x, node y, float cost)
{
    for (int i = 0; i < nodes[x].edges.size(); ++i)
        if (nodes[x].edges[i].dest_node == y)
            nodes[x].edges[i].cost = cost;
}

inline float Graph::random_cost(float low, float high) const
{
    return low + static_cast<float>(rand())/(static_cast<float>(RAND_MAX)/(high-low));
}

/// \brief  Test
void Graph::add_random_edge(node src, node dst, float density, float cost_low, float cost_high)
{
    float prob = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
    if (prob < density)
        this->add_edge(src, dst, this->random_cost(cost_low, cost_high));
}