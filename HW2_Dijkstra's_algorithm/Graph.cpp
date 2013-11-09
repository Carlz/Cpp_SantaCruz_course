////////////////////////////////////////////////////////////////////////////////
/// \brief      Graph class implementation
/// \author     Carlos Sampaio
/// \file       Graph.cpp
/// \date       20/10/2013
///
///     Graph class implements an undirected Graph with positive costs.
///
////////////////////////////////////////////////////////////////////////////////

#include <iomanip>
#include <assert.h>
#include "Graph.h"

//-----------------
// Public methods
//-----------------

// Generate a random graph structure based on node count, edge density and edge cost range
void Graph::randomize(unsigned int node_cnt, float density, cost_type cost_low, cost_type cost_high)
{
    this->destroy();                                      // clear previous Graph data
    if (node_cnt == 0) return;                            // stop if empty Graph was defined
    nodes.resize(node_cnt);                               // else create requested number of nodes
    node_values.resize(node_cnt);                         // else create requested number of nodes
    if (density <= 0) return;                             // stop if zero density Graph was defined
    for (node src = 0; src < node_cnt; ++src)             // else iterate over possible edges
       for (node dst = src + 1; dst < node_cnt; ++dst)    // and add them randomly based on requested
           this->add_random_edge(src, dst, density, cost_low, cost_high); // density and cost range
}

// Clear all graph structure
void Graph::destroy()
{
    int n_nodes = this->node_cnt();
    if (n_nodes == 0) return;
    for (node_iterator it = nodes.begin() ; it != nodes.end(); ++it)
        it->clear();
    nodes.clear();
}

// Returns the number of edges in the graph.
int Graph::edge_cnt() const
{
    int n_edges = 0;
    for (node_const_iterator it = nodes.begin(); it != nodes.end(); ++it )
        n_edges += it->size();
    return n_edges/2;   // undirected graph - edges counted in double
}

// Tests whether there is an edge from node src to node dst.
// Assuming that is undirected graph
bool Graph::adjacent(node src, node dst) const
{
    assert(src < nodes.size());

    // Search in the adjacent list the destination node
    for (edge_const_iterator it = nodes[src].begin(); it != nodes[src].end(); ++it)
    {
        if (it->first == dst)             // first = dest_node
            return true;
    }
    return false;
}

// Lists all nodes dst such that there is an edge from src to dst.
vector<edge_data> Graph::neighbors(node src) const
{
    assert(static_cast<size_t>(src) < nodes.size());   // check if node is within graph's range
  
    return nodes[src];
}

// Adds the edge from src to dst, if it is not there.
// Assuming that is undirected graph
void Graph::add_edge(node src, node dst, cost_type cost = 0.0)
{
    assert(cost >= 0);
    
    if (src >= nodes.size())        // expand graph if source node is beyond limits
    {
        nodes.resize(src);
        node_values.resize(src);
    }
            
    if (dst >= nodes.size())        // expand graph if destination node is beyond limits
    {
        nodes.resize(dst);
        node_values.resize(dst);
    }
        
    if (!this->adjacent(src, dst))      // If there isn't already an edge between src and dest
    {
        edge_data new_edge;             // Create a new edge in boath directions
        new_edge.first  = dst;          // dest_node
        new_edge.second = cost;         // edge cost
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

    this->delete_edge_uni(src, dst);    // delete edges in both directions
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
    
    for (edge_const_iterator it = nodes[src].begin(); it != nodes[src].end(); ++it)
        if (it->first == dst)             // first = dest_node
            return it->second;            // second = cost
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

// Prints Graph structure on the screen
ostream& operator<<(ostream& out, const Graph& data)
{
    if (data.node_cnt() == 0)
        return (out << "Empty graph!" << endl);
    
    ios_base::fmtflags flags = out.flags( );    // Save old output stream flags
    out << fixed << setprecision(2);            // Configure floating point display

    out << "Number of nodes: " << data.node_cnt() << endl;
    out << "Number of edges: " << data.edge_cnt() << endl;
    out << "Source\tDestination(cost)" << endl;
    for (node src = 0; src < data.nodes.size(); ++src)              // Go through all nodes
    {
        out << src << "\t";                                         // for edge print destination and cost
        for (edge_const_iterator it = data.nodes[src].begin(); it != data.nodes[src].end(); ++it)
        {
            out << it->first << "(";       // dest_node
            out << it->second << ") ";     // cost
        }
        out << endl;
    }
    out.flags(flags);  // Set the output flags to the way they were
    return out;
}

//-----------------
// Private methods
//-----------------

// Delete unidirectional edge, as helper function for delete_edge method.
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

//Sets the value associated to the unidirection edge (src,dst) to cost. Helper for set_edge_value method.
void Graph::set_edge_value_uni(node src, node dst, cost_type cost)
{
    for (edge_iterator it = nodes[src].begin(); it != nodes[src].end(); ++it)
        if (it->first == dst)       // dest_node
            it->second = cost;      // cost
}

// Produces a random cost
inline cost_type Graph::random_cost(cost_type low, cost_type high) const
{
    return low + (high-low) * static_cast<cost_type>(rand())/static_cast<cost_type>(RAND_MAX);
}

// Add a random edge for given density and cost range
void Graph::add_random_edge(node src, node dst, float density, cost_type cost_low, cost_type cost_high)
{
    float prob = static_cast<float>(rand())/static_cast<float>(RAND_MAX);
    if (prob < density)
        this->add_edge(src, dst, this->random_cost(cost_low, cost_high));
}