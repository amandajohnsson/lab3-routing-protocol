#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt3;

void printdt3(struct distance_table *dtptr);

struct rtpkt new_rtpkt;
/* students to write the following two routines, and maybe some others */
void send_3()
{
  for (int i = 0; i < 4; i++)
    new_rtpkt.mincost[i] = 999;

  for (int i = 0; i < 4; i++)
  {
    if (i != 3 && dt3.costs[i][i] != 999)
    {
      new_rtpkt.sourceid = 3;
      new_rtpkt.destid = i;
      for (int j = 0; j < 4; j++)
      {
        for (int k = 0; k < 4; k++)
        {
          if (new_rtpkt.mincost[j] > dt3.costs[j][k])
            new_rtpkt.mincost[j] = dt3.costs[j][k];
        }
      }
      tolayer2(new_rtpkt);
    }
  }
}

void rtinit3()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      dt3.costs[i][j] = 999;
    }
  }
  dt3.costs[3][3] = 0;
  dt3.costs[0][0] = 7;
  dt3.costs[2][2] = 3;
  send_3();
}

void rtupdate3(struct rtpkt *rcvdpkt)
{
  int source = rcvdpkt->sourceid;

  for (int destination = 0; destination < 4; destination++)
  {
    if (dt3.costs[destination][source] > dt3.costs[source][source] + rcvdpkt->mincost[destination])
    {
      dt3.costs[destination][source] = dt3.costs[source][source] + rcvdpkt->mincost[destination];
      send_3();
    }
  }

  printdt3(&dt3);
}

void printdt3(struct distance_table *dtptr)

{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n", dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n", dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n", dtptr->costs[2][0], dtptr->costs[2][2]);
}
