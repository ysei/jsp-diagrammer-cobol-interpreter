
/*=============================*
 *          TREE.C             *
 * the tree specific functions *
 *=============================*/

#include "tree.h"


/********
*********       FUNCTIONS
*********/

TREE *create_tree()
{
        TREE *tree;

        if((tree=(TREE *)malloc(sizeof(TREE)))==NULL)
                fatal_error("no more room for tree");

        tree->total_boxes=1;
        tree->root=create_box();
        make_root(tree->root);
        return tree;
}


