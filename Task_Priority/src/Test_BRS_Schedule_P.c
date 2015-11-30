#include "Test_BRS_Schedule_P.h"


struct Task_Handler
{
  struct BRS_Lists_DL_Node Node [1];
  size_t Time;
  size_t Priority;
};

#define Task_Handler_Entry(Iterator) \
BRS_Lists_DL_Node_Entry (Iterator, struct Task_Handler, Node)


void Test_BRS_Schedule_P_1 ()
{
  struct Task_Handler Handlers [10];
  struct BRS_Schedule_P Schedule [1];
  struct BRS_Lists_DL_Node Schedule_Lists [100];

  BRS_Schedule_P_Initialize (Schedule_Lists, 100, Schedule);

  Handlers[0].Priority = 2;
  Handlers[1].Priority = 4;
  Handlers[2].Priority = 7;
  Handlers[3].Priority = 2;
  Handlers[4].Priority = 0;
  Handlers[5].Priority = 7;
  Handlers[6].Priority = 4;
  Handlers[7].Priority = 4;

  BRS_Schedule_P_Insert (Handlers[0].Node, Handlers[0].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[1].Node, Handlers[1].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[2].Node, Handlers[2].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[3].Node, Handlers[3].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[4].Node, Handlers[4].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[5].Node, Handlers[5].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[6].Node, Handlers[6].Priority, Schedule);
  BRS_Schedule_P_Insert (Handlers[7].Node, Handlers[7].Priority, Schedule);

  printf ("Testing Round-Robin\n");
  printf ("Testing BRS_Schedule_P_Current\n");
  printf ("Testing BRS_Schedule_P_Current_Next_Node\n");
  {
    struct BRS_Lists_DL_Node * Node;
    struct Task_Handler * Handler;
    Node = BRS_Schedule_P_Current (Schedule);
    for (int I = 0; I < 1000; I = I + 1)
    {
      Node = BRS_Schedule_P_Current_Next_Node (Node, Schedule);
      Handler = Task_Handler_Entry (Node);
      assert (Handler->Priority == 7);
    }
  }
  printf ("Testing Complete\n\n\n");



  printf ("Testing Remove\n");
  printf ("Testing BRS_Schedule_P_Current\n");
  printf ("Testing BRS_Schedule_P_Remove\n");
  {
    struct BRS_Lists_DL_Node * Node;
    struct Task_Handler * Handler;
    Node = BRS_Schedule_P_Current (Schedule);
    Node = Node->Next;
    BRS_Schedule_P_Remove (Node, Schedule);
    Node = BRS_Schedule_P_Current (Schedule);
    Node = Node->Next;
    BRS_Schedule_P_Remove (Node, Schedule);
    Node = BRS_Schedule_P_Current (Schedule);
    Node = Node->Next;
    Handler = Task_Handler_Entry (Node);
    assert (Handler->Priority == 4);
  }
  printf ("Testing Complete\n\n\n");



  printf ("Testing Remove all\n");
  printf ("Testing BRS_Schedule_P_Current\n");
  printf ("Testing BRS_Schedule_P_Current_Next_Node\n");
  printf ("Testing BRS_Schedule_P_Remove\n");
  printf ("Testing BRS_Schedule_P_Empty\n");
  {
    struct BRS_Lists_DL_Node * Node;
    struct Task_Handler * Handler;
    for (int I = 0; I < 1000; I = I + 1)
    {
      Node = BRS_Schedule_P_Current (Schedule);
      Node = BRS_Schedule_P_Current_Next_Node (Node, Schedule);
      BRS_Schedule_P_Remove (Node, Schedule);
    }
    assert (BRS_Schedule_P_Empty (Schedule) == 1);
  }
  printf ("Testing Complete\n\n\n");





  getchar ();
}
