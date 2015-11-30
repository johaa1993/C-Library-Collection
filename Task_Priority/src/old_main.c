#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <assert.h>
#include <time.h>
#include "BRS_Schedule_P.h"

struct BRS_Task_Handler
{
  struct BRS_Lists_DL_Node Node;
  size_t Time;
  size_t Priority;
};

#define BRS_Task_Handler_Iterator_Entry(Iterator) BRS_Lists_DL_Node_Entry (Iterator, struct BRS_Task_Handler, Node)

struct BRS_Task_Handler Handlers [7];

//Setup priority scheduler.
#define Schedule_P_List_Count 10
struct BRS_Schedule_P Schedule_P;
struct BRS_Lists_DL_Node Schedule_P_List [Schedule_P_List_Count];


int main (int argc, char** argv)
{

  BRS_Schedule_P_Initialize (Schedule_P_List, Schedule_P_List_Count, &Schedule_P);

  Handlers[0].Priority = 2;
  Handlers[1].Priority = 4;
  Handlers[2].Priority = 7;
  Handlers[3].Priority = 2;
  Handlers[4].Priority = 0;
  Handlers[5].Priority = 7;
  Handlers[6].Priority = 4;

  BRS_Schedule_P_Insert (&Handlers[0].Node, Handlers[0].Priority, &Schedule_P);
  BRS_Schedule_P_Insert (&Handlers[1].Node, Handlers[1].Priority, &Schedule_P);
  BRS_Schedule_P_Insert (&Handlers[2].Node, Handlers[2].Priority, &Schedule_P);
  BRS_Schedule_P_Insert (&Handlers[3].Node, Handlers[3].Priority, &Schedule_P);
  BRS_Schedule_P_Insert (&Handlers[4].Node, Handlers[4].Priority, &Schedule_P);
  BRS_Schedule_P_Insert (&Handlers[5].Node, Handlers[5].Priority, &Schedule_P);
  BRS_Schedule_P_Insert (&Handlers[6].Node, Handlers[6].Priority, &Schedule_P);

  struct BRS_Lists_DL_Node * Node;
  struct BRS_Task_Handler * Handler;

  char C;

  Node = BRS_Schedule_P_Current (&Schedule_P);

  for (;;)
  {
    scanf(" %c", &C);


    if (BRS_Schedule_P_Empty (&Schedule_P))
    {
      printf ("BRS_Schedule_P_Empty\n");
    }
    else
    {

      switch (C)
      {
        case 'r':
        if (Node != BRS_Schedule_P_Current (&Schedule_P))
        {
          printf ("BRS_Schedule_P_Remove\n");
          Handler = BRS_Task_Handler_Iterator_Entry (Node);
          printf ("Handler->Priority %i\n", Handler->Priority);
          printf ("Handler->ID %p\n", Handler);
          BRS_Schedule_P_Remove (Node, &Schedule_P);
          Node = BRS_Schedule_P_Current (&Schedule_P);
        }
        break;

        case 'n':
        printf ("BRS_Schedule_P_Next\n");
        Node = BRS_Schedule_P_Next (Node, &Schedule_P);
        Handler = BRS_Task_Handler_Iterator_Entry (Node);
        printf ("Handler->Priority %i\n", Handler->Priority);
        printf ("Handler->ID %p\n", Handler);
        break;
      }

    }

  }



  getchar();

  return 0;
}