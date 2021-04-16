#include "prog3.h"


extern int TRACE;
extern int YES;
extern int NO;



struct distance_table
{
  int costs[4][4];
} dt1;

struct rtpkt new_rtpkt;
/* students to write the following two routines, and maybe some others */
void send_1()
{
  for (int i = 0; i < 4; i++)
  {
    if (i != 1 && dt1.costs[i][i] != 999)
    {
      new_rtpkt.sourceid = 1;
      new_rtpkt.destid = i;
      for (int j = 0; j < 4; j++)
      {
        for(int k = 0; k < 4; k++)
        {
          if(new_rtpkt.mincost[j] > dt1.costs[j][k])
            new_rtpkt.mincost[j] = dt1.costs[j][k];
        }
      }
      tolayer2(new_rtpkt);
    }
  }
}

void rtinit1()
{
  for(int i = 0; i < 4; i++)
  {
		for(int j = 0; j < 4; j++)
    {
			dt1.costs[i][j] = 999;
		}
	}
  dt1.costs[1][1] = 0;
	dt1.costs[0][0] = 1;
	dt1.costs[2][2] = 1;
  send_1();
}


void rtupdate1(struct rtpkt *rcvdpkt)


{
  int source = rcvdpkt->sourceid;

  for (int destination = 0; destination < 4; destination++) {
    if (dt1.costs[destination][source] > dt1.costs[source][source] + rcvdpkt->mincost[destination]) {
      dt1.costs[destination][source] = dt1.costs[source][source] + rcvdpkt->mincost[destination];
    }
  }
  send_1();

}


void printdt1(struct distance_table *dtptr)


{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}



void linkhandler1(int linkid, int newcost)

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */

{
}
