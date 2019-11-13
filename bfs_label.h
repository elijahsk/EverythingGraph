//
// Created by JaSmiNa on 04/10/16.
//

#ifndef BFSLABEL_H
#define BFSLABEL_H

void bfs_construct(void);
void bfs_destruct(void);
void bfs_reset(struct node *nodes);
void bfs(struct node *nodes);
void bfs_rerun(struct node *nodes);

struct edge {
    uint32_t dst;
    uint8_t src;
};

extern struct node* node_list;
extern uint32_t* dist;



#endif //GRAPH_UP_BFS_LIGRA_H
