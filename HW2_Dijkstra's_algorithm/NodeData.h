/* 
 * File:   NodeData.h
 * Author: Capacitare
 *
 * Created on November 1, 2013, 11:08 PM
 */

#ifndef NODEDATA_H
#define	NODEDATA_H

typedef unsigned short int node;            // Node index type
typedef float cost_type;                    // Edge and Node cost type

class NodeData {
public:
    NodeData();
    NodeData(const NodeData& orig);
    virtual ~NodeData();
private:

};

#endif	/* NODEDATA_H */

