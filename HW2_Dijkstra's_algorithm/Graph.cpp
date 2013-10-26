////////////////////////////////////////////////////////////////////////////////
/// \brief      Graph class implementation
/// \author     Carlos Sampaio
/// \file       Graph.cpp
/// \date       20/10/2013
///
///     Graph class implementation.
///
////////////////////////////////////////////////////////////////////////////////


#include <iostream>

#include <assert.h>
#include "Graph.h"

//-----------------
// Public methods
//-----------------


/// \brief  Returns the number of edges in the graph.
/// \return Number of edges
int Graph::edge_cnt()
{
    int n_edges = 0;
    for (int i = 0; i < nodes.size(); ++i )
        n_edges += nodes[i].edges.size();
    return n_edges/2;   // undirected graph - edges counted in double
}

// Tests whether there is an edge from node x to node y.
// Assuming that is undirected graph
bool Graph::adjacent(node x, node y)
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
vector<node> Graph::neighbours(node x)
{
    assert(x < nodes.size());
    vector<node> nb_list;       // Neighbours list
    if (x >= nodes.size())
        return nb_list;    
    for (int i = 0; nodes[x].edges.size(); ++i)
        nb_list.push_back(nodes[x].edges[i].dest_node);
    return nb_list;
}

// Adds the edge from x to y, if it is not there.
// Assuming that is undirected graph
void Graph::add_edge(node x, node y, int cost = 0)
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
int Graph::get_node_value(node x)
{
    assert(x < nodes.size());
    return nodes[x].value;
}

// Sets the value associated with the node x.
void Graph::set_node_value(node x, int val)
{
    assert(x < nodes.size() && val >= 0);
    nodes[x].value = val;
}

// Returns the value associated to the edge (x,y).
// -1 does not exist
int Graph::get_edge_value(node x, node y)
{
    assert(x < nodes.size());
    
    for (int i = 0; i < nodes[x].edges.size(); ++i)
        if (nodes[x].edges[i].dest_node == y)
            return nodes[x].edges[i].cost;
    //
    return -1;
}

//Sets the value associated to the edge (x,y) to v.    
void Graph::set_edge_value (node x, node y, int cost)
{
    assert(x < nodes.size() && y < nodes.size());

    this->set_edge_value_uni(x, y, cost);
    this->set_edge_value_uni(y, x, cost);
}


//-----------------
// Private methods
//-----------------

void Graph::delete_edge_uni(node x, node y)
{
    vector<edge_data>* node_edges = &(nodes[x].edges);
    for (vector<edge_data>::iterator it = node_edges->begin(); it != node_edges->end(); ++it )
    {
        if (it->dest_node == y)
        {
            node_edges->erase(it);
            break;
        }
    }        
}

//Sets the value associated to the edge (x,y) to v.    
void Graph::set_edge_value_uni(node x, node y, int cost)
{
    for (int i = 0; i < nodes[x].edges.size(); ++i)
        if (nodes[x].edges[i].dest_node == y)
            nodes[x].edges[i].cost = cost;
}