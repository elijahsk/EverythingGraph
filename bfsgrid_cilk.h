//
// Created by JaSmiNa on 04/10/16.
//

#ifndef BFSGRID_H
#define BFSGRID_H

void bfsgrid_construct(void);
void bfsgrid_destruct(void);
void bfsgrid_reset(struct node *nodes);
void bfsgrid(struct node *nodes);

struct edge {
	uint32_t src;
    uint32_t dst;
#if LABELED
    uint8_t label;
#endif
};

extern uint32_t* dist;



#endif //GRAPH_UP_BFS_LIGRA_H
