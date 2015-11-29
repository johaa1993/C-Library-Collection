#ifndef BRS_Schedule_P_h
#define BRS_Schedule_P_h

#include "BRS_Lists_DL.h"

struct BRS_Schedule_P
{
  struct BRS_Lists_DL_Node * List;
  size_t Priority;
};


static inline void
BRS_Schedule_P_Initialize
(struct BRS_Lists_DL_Node * List, size_t Count, struct BRS_Schedule_P * Schedule)
{
  Schedule->List = List;
  BRS_Lists_DL_Link_Self_Vector (Schedule->List, Count);
}



//Insert task handler <Item> into <Schedule>.
//Calulates new highest priority if nesseracy.
static inline void BRS_Schedule_P_Insert
(struct BRS_Lists_DL_Node * Item, size_t Priority, struct BRS_Schedule_P * Schedule)
{
  //Calulates new highest priority if nesseracy.
  if (Priority > Schedule->Priority)
  {
    Schedule->Priority = Priority;
  }
  BRS_Lists_DL_Insert_After (Item, Schedule->List + Priority);
}



struct BRS_Lists_DL_Node * BRS_Schedule_P_Current
(struct BRS_Schedule_P * Schedule)
{
  return Schedule->List + Schedule->Priority;
}


//Calulates new highest priority if nesseracy.
static inline void BRS_Schedule_P_Update
(struct BRS_Schedule_P * Schedule)
{
  struct BRS_Lists_DL_Node const * Node;
  for (;;)
  {
    Node = BRS_Schedule_P_Current (Schedule);
    Node = Node->Next;
    if ((Node != BRS_Schedule_P_Current (Schedule)) || (Schedule->Priority == 0)) break;
    Schedule->Priority--;
  }
}



static inline void BRS_Schedule_P_Remove
(struct BRS_Lists_DL_Node * Node, struct BRS_Schedule_P * Schedule)
{
  //A node can be a list. Do not remove a list thanks.
  //assert ((Node == Schedule->List) && (Node != Node->Next));

  BRS_Lists_DL_Remove (Node);
  BRS_Schedule_P_Update (Schedule);
}



static inline int BRS_Schedule_P_Empty
(struct BRS_Schedule_P * Schedule)
{
  struct BRS_Lists_DL_Node * List;
  List = BRS_Schedule_P_Current (Schedule);
  if (List == List->Next)
  {
    return 1;
  }
  return 0;
}


//Return a node.
//Return NULL if list is empty.
static inline struct BRS_Lists_DL_Node * BRS_Schedule_P_Next
(struct BRS_Lists_DL_Node * Node, struct BRS_Schedule_P * Schedule)
{
  Node = Node->Next;
  if (Node == BRS_Schedule_P_Current (Schedule))
  {
    Node = Node->Next;
  }
  return Node;
}


#endif
