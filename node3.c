#include "prog3.h"

extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt3;

struct rtpkt new_rtpkt;
/* students to write the following two routines, and maybe some others */
void send()
{
  for (int i = 0; i < 4; i++)
  {
    if (i != 3 && dt3.costs[i][i] != 999)
    {
      new_rtpkt.sourceid = 3;
      new_rtpkt.destid = i;
      for (int j = 0; j < 4; j++)
      {
        for(int k = 0; k < 4; k++)
        {
          if(new_rtpkt.mincost[j] > dt3.costs[j][k])
            new_rtpkt.mincost[j] = dt3.costs[j][k];
        }
      }
      tolayer2(new_rtpkt);
    }
  }
}

void rtinit3() 
{
  for(int i = 0; i < 4; i++)
  {
		for(int j = 0; j < 4; j++)
    {
			dt1.costs[i][j] = 999;
		}
	}
  dt0.costs[3][3] = 0;
	dt0.costs[0][0] = 7;
	dt0.costs[2][2] = 3;
  send();

}


void rtupdate3(struct rtpkt *rcvdpkt)

  
{

}


void printdt3(struct distance_table *dtptr)

  
{
  printf("             via     \n");
  printf("   D3 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 1|  %3d   %3d\n",dtptr->costs[1][0], dtptr->costs[1][2]);
  printf("     2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);

}







