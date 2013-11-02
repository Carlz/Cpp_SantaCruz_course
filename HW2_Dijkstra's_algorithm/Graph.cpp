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
/// \param  node_cnt      Node count: number of nodes in the Graph
/// \param  density     Graph edges density: values range from 0.0 to 1.0
void Graph::randomize(unsigned int node_cnt, float density, cost_type cost_low, cost_type cost_high)
{
    this->destroy();                                    // clear previous Graph data
    if (node_cnt == 0) return;                            // stop if empty Graph was defined
    nodes.resize(node_cnt);                               // else create requested number of nodes
    node_values.resize(node_cnt);                               // else create requested number of nodes
    if (density <= 0) return;                           // stop if zero density Graph was defined
    for (node src = 0; src < node_cnt; ++src)             // else iterate over possible edges
       for (node dst = src + 1; dst < node_cnt; ++dst)    // and add them randomly based on requested
           this->add_random_edge(src, dst, density, cost_low, cost_high); // density and cost range
}

// Clear all graph structure
void Graph::destroy()
{
    int n_nodes = this->node_cnt();
    if (n_nodes == 0) return;
    for (int i = 0; i < n_nodes; ++i)
        nodes[i].clear();
    nodes.clear();
}

/// \brief  Returns the number of edges in the graph.
/// \return Number of edges
int Graph::edge_cnt() const
{
    int n_edges = 0;
    for (size_t i = 0; i < nodes.size(); ++i )
        n_edges += nodes[i].size();
    return n_edges/2;   // undirected graph - edges counted in double
}

// Tests whether there is an edge from node src to node dst.
// Assuming that is undirected graph
bool Graph::adjacent(node src, node dst) const
{
    assert(src < nodes.size());

    for (size_t i = 0; i < nodes[src].size(); ++i)
    {
        if (nodes[src][i].first == dst)     // first = dest_node
            return true;
    }
    return false;
}

// Lists all nodes dst such that there is an edge from src to dst.
vector<node> Graph::neighbours(node src) const
{
    assert(static_cast<size_t>(src) < nodes.size());
    vector<node> nb_list;         // Neighbours list
    if (static_cast<size_t>(src) >= nodes.size())
        return nb_list;    
    for (size_t i = 0; i < nodes[src].size(); ++i)
        nb_list.push_back(nodes[src][i].first);   // first = dest_node
    return nb_list;
}

// Adds the edge from src to dst, if it is not there.
// Assuming that is undirected graph
void Graph::add_edge(node src, node dst, cost_type cost = 0.0)
{
    assert(cost >= 0);
    
    if (src >= nodes.size())
    {
        nodes.resize(src);
        node_values.resize(src);
    }
            
    if (dst >= nodes.size())
    {
        nodes.resize(dst);
        node_values.resize(dst);
    }
        
    if (!this->adjacent(src, dst))
    {
        edge_data new_edge;
        new_edge.first  = dst;          // dest_node
        new_edge.second = cost;       // cost
        nodes[src].push_back(new_edge);
        new_edge.first = src;
        nodes[dst].push_back(new_edge);
    }
}

// Removes the edge from src to dst, if it is there.
// Assuming that is undirected graph
void Graph::delete_edge(node src, node dst)
{
    assert(src < nodes.size() && dst < nodes.size());

    this->delete_edge_uni(src, dst);
    this->delete_edge_uni(dst, src);
}

// Returns the value associated with the node src.
cost_type Graph::get_node_value(node src) const
{
    assert(src < nodes.size());
    return node_values[src];
}

// Sets the value associated with the node src.
void Graph::set_node_value(node src, cost_type val)
{
    assert(src < nodes.size() && val >= 0);
    node_values[src] = val;
}

// Returns the value associated to the edge (src,dst).
// -1 does not exist
cost_type Graph::get_edge_value(node src, node dst) const
{
    assert(src < nodes.size());
    
    for (size_t i = 0; i < nodes[src].size(); ++i)
        if (nodes[src][i].first == dst)             // first = dest_node
            return nodes[src][i].second;          // second = cost
    // If edge does not exist, return a negative number
    return -1.0;
}

//Sets the value associated to the edge (src,dst) to cost.    
void Graph::set_edge_value (node src, node dst, cost_type cost)
{
    assert(src < nodes.size() && dst < nodes.size() && cost >= 0);

    this->set_edge_value_uni(src, dst, cost);
    this->set_edge_value_uni(dst, src, cost);
}

ostream& operator<<(ostream& out, const Graph& data)
{
    if (data.node_cnt() == 0)
        return (out << "Empty graph!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Number of nodes: " << data.node_cnt() << endl;
    out << "Number of edges: " << data.edge_cnt() << endl;
    out << "Source\tDestination(cost)" << endl;
    for (node src = 0; src < data.nodes.size(); ++src)
    {
        out << src << "\t";
        for (size_t dst = 0; dst < data.nodes[src].size(); ++dst)
        {
            out << data.nodes[src][dst].first << "(";       // dest_node
            out << data.nodes[src][dst].second << ") ";     // cost
        }
        out << endl;
    }
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}

//-----------------
// Private methods
//-----------------

void Graph::delete_edge_uni(node src, node dst)
{
    vector<edge_data>* node_edges = &(nodes[src]);
    for (edge_iterator it = node_edges->begin(); it != node_edges->end(); ++it )
        if (it->first == dst)     // dest_node
        {
            node_edges->erase(it);
            break;
        }
}

//Sets the value associated to the edge (src,dst) to cost.    
void Graph::set_edge_value_uni(node src, node dst, cost_type cost)
{
    for (size_t i = 0; i < nodes[src].size(); ++i)
        if (nodes[src][i].first == dst)     // dest_node
            nodes[src][i].second = cost;  // cost
}

inline cost_type Graph::random_cost(cost_type low, cost_type high) const
{
    return low + (high-low) * static_cast<cost_type>(rand())/static_cast<cost_type>(RAND_MAX);
}

/// \brief  Test
void Graph::add_random_edge(node src, node dst, float density, cost_type cost_low, cost_type cost_high)
{
    float prob = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
    if (prob < density)
        this->add_edge(src, dst, this->random_cost(cost_low, cost_high));
}