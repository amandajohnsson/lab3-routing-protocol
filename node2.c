#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table
{
  int costs[4][4];
} dt2;

struct rtpkt new_rtpkt;
/* students to write the following two routines, and maybe some others */
void send_2()
{
  for (int i = 0; i < 4; i++)
  {
    if (i != 2 && dt2.costs[i][i] != 999)
    {
      new_rtpkt.sourceid = 2;
      new_rtpkt.destid = i;
      for (int j = 0; j < 4; j++)
      {
        for(int k = 0; k < 4; k++)
        {
          if(new_rtpkt.mincost[j] > dt2.costs[j][k])
            new_rtpkt.mincost[j] = dt2.costs[j][k];
        }
      }
      tolayer2(new_rtpkt);
    }
  }
}
void rtinit2()
{
  for(int i = 0; i < 4; i++)
  {
		for(int j = 0; j < 4; j++)
    {
			dt2.costs[i][j] = 999;
		}
	}
  dt2.costs[2][2] = 0;
  dt2.costs[0][0] = 3;
  dt2.costs[1][1] = 1;
  dt2.costs[3][3] = 2;
  send_2();
}


void rtupdate2(struct rtpkt *rcvdpkt)
{
  int source = rcvdpkt->sourceid;

  for (int destination = 0; destination < 4; destination++) {
    if (dt2.costs[destination][source] > dt2.costs[source][source] + rcvdpkt->mincost[destination]) {
      dt2.costs[destination][source] = dt2.costs[source][source] + rcvdpkt->mincost[destination];
    }
  }
  send_2();

}


void printdt2(struct distance_table *dtptr)


{
  printf("                via     \n");
  printf("   D2 |    0     1    3 \n");
  printf("  ----|-----------------\n");
  printf("     0|  %3d   %3d   %3d\n",dtptr->costs[0][0],
	 dtptr->costs[0][1],dtptr->costs[0][3]);
  printf("dest 1|  %3d   %3d   %3d\n",dtptr->costs[1][0],
	 dtptr->costs[1][1],dtptr->costs[1][3]);
  printf("     3|  %3d   %3d   %3d\n",dtptr->costs[3][0],
	 dtptr->costs[3][1],dtptr->costs[3][3]);
}
