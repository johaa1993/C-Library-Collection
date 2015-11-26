#ifndef BRS_Lists_DL_h
#define BRS_Lists_DL_h


#define BRS_Lists_DL_Node_Entry(Pointer, Type, Member) \
((Type *)((char *)(Pointer) - __builtin_offsetof(Type, Member)))

struct BRS_Lists_DL_Node
{
  struct BRS_Lists_DL_Node * Next;
  struct BRS_Lists_DL_Node * Prev;
};



//Link the node <Item> to it self.
static inline void BRS_Lists_DL_Link_Self
(struct BRS_Lists_DL_Node * Item)
{
  Item->Next = Item;
  Item->Prev = Item;
}


//Link the every node item in <Items> to it self.
static inline void BRS_Lists_DL_Link_Self_Vector
(struct BRS_Lists_DL_Node * Items, size_t Count)
{
  for (size_t I = 0; I < Count; I = I + 1)
  {
    BRS_Lists_DL_Link_Self (Items + I);
  }
}


//Insert the node <Item> between nodes <Prev> and <Next>.
static inline void BRS_Lists_DL_Insert
(struct BRS_Lists_DL_Node * Item, struct BRS_Lists_DL_Node * Prev, struct BRS_Lists_DL_Node * Next)
{
  Item->Next = Next;
  Item->Prev = Prev;
  Next->Prev = Item;
  Prev->Next = Item;
}


//Insert the node <Item> after the node <Item_0>.
static inline void BRS_Lists_DL_Insert_After
(struct BRS_Lists_DL_Node * Item, struct BRS_Lists_DL_Node * Item_0)
{
  BRS_Lists_DL_Insert (Item, Item_0, Item_0->Next);
}


//Insert the node <Item> before the node <Item_0>.
static inline void BRS_Lists_DL_Insert_Before
(struct BRS_Lists_DL_Node * Item, struct BRS_Lists_DL_Node * Item_0)
{
  BRS_Lists_DL_Insert (Item, Item_0->Prev, Item_0);
}


//Remove the node between <Prev> and <Next>.
//Link <Prev> and <Next> to each other.
static inline void BRS_Lists_DL_Remove_Between
(struct BRS_Lists_DL_Node * Prev, struct BRS_Lists_DL_Node * Next)
{
  Next->Prev = Prev;
  Prev->Next = Next;
}

//Remove the node <Item>.
//Link nodes beside node <Item> to each other.
static inline void BRS_Lists_DL_Remove
(struct BRS_Lists_DL_Node * Item)
{
  BRS_Lists_DL_Remove_Between (Item->Prev, Item->Next);
}




#endif