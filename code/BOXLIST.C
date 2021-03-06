
/*=============================================================*
 *           BOXLIST.C                                         *
 * This .C contains the most specified linked list used        *
 * it is one of the main workhorses of the diagrammer          *
 * and as such has been the most formally described.           *
 *                                                             *
 * No other linked list in the project undergoes so much       *
 * and so they have used the formal description presented here.*
 *=============================================================*/ 
#include <stdio.h>
#include "structs.h"
#include "box.h"
#include "boxlist.h"

/******************************************************************
*******************************************************************
sort            linked_list
based on        int,type

    (* type * linked_list -> linked_list  *)


(c)   NEWLIST:             ->      linked_list
(c)   ADDLIST:  type x linked_list      ->      linked_list
      DELETE_NODE:            linked_list ->
      DELETE_FROM_LIST:       type x linked_list  ->      linked_list
      ADD_AT:         int x type x linked_list    ->      linked_list
      APPEND:         linked_list x linked_list   ->      linked_list
      POSITION_IN:            type x linked_list  ->      linked_list
      OVERWRITE_AT: int x type x linked_list  ->      linked_list
      JOIN_LISTS: linked_list x linked_list x int -> linked_list

(*      currently not implemented *)
      GET_AT:      int x linked_list     ->      type
      UNITLIST:    type       ->      linked_list
*******************************************************************
******************************************************************/



/****************************************************************************
JOIN_LISTS(ADDLIST(b1,l1),ADDLIST(b2,l2),pos)= if pos = 0
                         then ADDLIST(b1,APPEND((b2,l2),l1))
                         else ADDLIST(b1,JOIN_LISTS(l1,(b2,l2),pos));
****************************************************************************/
BOXLIST *join_box_lists(BOXLIST *boxlist1,BOXLIST *boxlist2,int position)
  {
    if(position==0)
       {
         boxlist1->link=append(boxlist2,boxlist1->link);
         return boxlist1;
       }
    else
       {
         boxlist1->link=join_box_lists(boxlist1->link,
                                      boxlist2,position-1);
         return boxlist1;
       }
  }

/*************************************************************************
POSITION_IN(b,ADDLIST(t,l))=    POS_IN(b,ADDLIST(t,l),0);
POS_IN(b,ADDLIST(t,l),pos)      =       if b=t
                                        then pos
                                        else POS_IN(b,l,pos+1);
**************************************************************************/
int position_in(BOX *box,BOXLIST *boxlist)
        {
                return pos_in(box,boxlist,0);
        }

int pos_in(BOX *box,BOXLIST *boxlistpointer,int pos)
        {
                if(box==boxlistpointer->box)
                        return pos;
                else
                        pos_in(box,boxlistpointer->link,pos+1);
        }

/****************************************************************
APPEND(ADDLIST(b1,l1),ADDLIST(b2,l2))   =       ADDLIST(b1,
                                                APPEND(l1,ADDLIST(b2,l2)));
APPEND(ADDLIST(b1,NEWLIST),ADDLIST(b2,l2))=     ADDLIST(b1,ADDLIST(b2,l2));
*****************************************************************/
BOXLIST *append(BOXLIST *boxlist1,BOXLIST *boxlist2)
  {
     if(boxlist1->link==NULL)
         {
           boxlist1->link=boxlist2;
           return boxlist1;
         }
     else
         {
           boxlist1->link=append(boxlist1->link,boxlist2);
           return boxlist1;
         }
  }

/*******************************************************************
DELETE_FROM_LIST(b,NEWLIST) = NEWLIST;
DELETE_FROM_LIST(b,ADDLIST(t,l))        = if b=t then l
                                    else ADDLIST(DELETE_FROM_LIST(b,l));
*******************************************************************/
BOXLIST *delete_from_list(BOX *box,BOXLIST *boxlistpointer)
   {
    if(boxlistpointer==NULL)
         return NULL;

    if(box==boxlistpointer->box)
        {
          scrub_box(box);
          scrub_boxlist(boxlistpointer);
          return boxlistpointer->link;
        }
    else
        {
          boxlistpointer->link=delete_from_list(box,
                                       boxlistpointer->link);
          return boxlistpointer;
        }
   }

/***************************************************************
ADD_AT(pos,b,NEWLIST)   = ADDLIST(b,NEWLIST);
ADD_AT(pos,b,ADDLIST(t,l))      = if pos=0  then ADDLIST(b,ADDLIST(t,l))
                                            else ADD_AT(pos-1,b,l);
***************************************************************/
BOXLIST *add_at(int position,BOX *box,BOXLIST *boxlistpointer)
   {
     BOXLIST *newboxlist;

     if(boxlistpointer==NULL)
       {
         newboxlist=create_boxlist();
         newboxlist->box=box;
         newboxlist->link=NULL;
         return newboxlist;
       }
     else
       {
        if(position==0)
           {
             newboxlist=create_boxlist();
             newboxlist->box=box;
             newboxlist->link=boxlistpointer;
             return newboxlist;
           }
        else
           {
             boxlistpointer->link=add_at(position-1,
                                         box,
                                         boxlistpointer->link);
             return boxlistpointer;
           }
       }
  }

/*************************************************************************
OVERWRITE_AT(pos,b1,ADDLIST(b2,l2)) = if pos=0
                                      then ADDLIST(b1,l2);
                              else ADDLIST(b2,overwrite_at(pos-1,b1,l2));
*************************************************************************/
BOXLIST *overwrite_at(int position,BOX *box,BOXLIST *boxlistpointer)
   {
     if(position==0)
       {
         boxlistpointer->box=box;
         return boxlistpointer;
       }
     else
       {
         boxlistpointer->link=overwrite_at(position-1,
                                           box,
                                           boxlistpointer->link);
         return boxlistpointer;
       }
  }

/**************************************************************
(c)             NEWLIST:    ->      linked_list
**************************************************************/
BOXLIST *create_boxlist()
{
    BOXLIST *list;

    if((list=(BOXLIST *)malloc(sizeof(BOXLIST)))==NULL)
           fatal_error("no more room for boxlist");

    list->box=NULL;
    list->link=NULL;
    return list;
}

/**********************************************
                DELETE_NODE:    linked_list ->
*********************************************/
void scrub_boxlist(boxlist)
        BOXLIST *boxlist;
{
        free(boxlist);
}

/******************************************************
       constructor for a box list with a supplied box
*******************************************************/
BOXLIST *unit_box_list(BOX *box)
{
  BOXLIST *list;

  if((list=(BOXLIST *)malloc(sizeof(BOXLIST)))==NULL)
        fatal_error("no more room for boxlist");

  list->box=box;
  list->link=NULL;
  return list;
}


