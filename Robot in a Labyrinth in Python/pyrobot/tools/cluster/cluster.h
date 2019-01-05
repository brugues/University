/*
 * cluster.h -- declarations for clustering routines
 *
 * $Header: /cvs/pyrobot/tools/cluster/cluster.h,v 1.1 2002/07/03 01:08:51 dblank Exp $
 * $Log: cluster.h,v $
 * Revision 1.1  2002/07/03 01:08:51  dblank
 * Cluster 2.9 added to pyro/tools
 *
 * Revision 1.1  1991/07/14  01:09:48  stolcke
 * Initial revision
 *
 *
 */

typedef struct _tree {
    FLOAT  *pat;
    int     size;
    int     root;
    int     leaf;
    FLOAT   y;
    FLOAT   distance;
    struct _tree *r_tree, *l_tree;
}       BiTree;

extern BiTree *new_tree();

#define LEAF -1

#ifndef TRUE
#define TRUE	1
#endif
#ifndef FALSE
#define FALSE	0
#endif


