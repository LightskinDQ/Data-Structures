/*
 * algorithm.h
 *
 *  Created on: Jul. 27, 2024
 *      Author: dillonquick
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "edgelist.h"
#include "graph.h"

EDGELIST *mst_prim(GRAPH *g, int start);
EDGELIST *spt_dijkstra(GRAPH *g, int start);
EDGELIST *sp_dijkstra(GRAPH *g, int start, int end);


#endif /* ALGORITHM_H_ */
