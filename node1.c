//*************************************************
// Michael Meluso
// CSC 360 - Networking
// Project 3 - Distance Vector Algorithm
// Node1.c
//*************************************************

#include <stdio.h>
extern struct rtpkt {
	int sourceid; /* id of sending router sending this pkt */
	int destid; /* id of router to which pkt being sent
	(must be an immediate neighbor) */
	int mincost[4]; /* min cost to node 0 ... 3 */
};
extern int TRACE;
extern int YES;
extern int NO;
int connectcosts1[4] = { 1, 0, 1, 999 };
struct distance_table
{
	int costs[4][4];
} dt1;

# define INFINITY 999
# define NODE 4 
static int neighbour[NODE] = {0,1,1,1}; 
static int dtcost[NODE] = {0,1,3,7}; 
static int dtvector1[NODE] = {0,1,3,7};

int i, j;

/* students to write the following two routines, and maybe some others*/
void rtinit1(float clocktime)
{
	printf("rtinit1 is called at t=%.3f\n",clocktime);
	for(i = 0; i < NODE; i++)
 		for(j = 0; j < NODE; j++) {
 			if((neighbour[i] == 1)&&(i == j)) 
 				dt1.costs[i][j] = dtcost[i]; 
 			else 
 				dt1.costs[i][j] = INFINITY;
 		}

 	struct rtpkt temp; 
	for(i = 0; i < NODE; i++)
	{ 
 		if(neighbour[i] == 1){ 
 			temp.sourceid = 0; 
 			temp.destid = i; 
 			for(j = 0;j< NODE; j++){ 
				temp.mincost[j] = dtvector1[j]; 
 			}

 			tolayer2(temp); 
 		}
 	}
}

void rtupdate1(struct rtpkt *rcvdpkt, float clocktime)
{
	int tempCost, vectorChange = 0;
	printf("rtupdate1 is called at t=%.3f. ",clocktime);
	printf("node 1 is receiving packet from node %d\n", rcvdpkt->sourceid);
	for(i = 0; i < NODE; i++){
		if(i != 0){ 
 			tempCost = dtcost[rcvdpkt->sourceid] + rcvdpkt->mincost[i]; 
 			if(tempCost < dt1.costs[i][rcvdpkt->sourceid]){ 
 				dt1.costs[i][rcvdpkt->sourceid] = tempCost;
 				printf("Node 1's distance table updated.\n"); 
				printdt1(&dt1); 
 			} 
 			if(tempCost < dtvector1[i]) { 
 				vectorChange = 1;
 				dtvector1[i] = tempCost; 
 			} 
 		} 
 	}

 	if(vectorChange == 1){
		struct rtpkt temp; 
 		for(i = 0; i < NODE; i++) 
 		{ 
 			if(neighbour[i] == 1) { 
 				temp.sourceid = 0;
 				temp.destid = i; 
				for(j = 0;j< NODE; j++) { 
					temp.mincost[j] = dtvector1[j];
				}
				printf("Packet is being sent to node %d from Node 1.\n",i); 
				tolayer2(temp);
			}  
 		}
		printf("\n");
	}
}

printdt1(struct distance_table *dtptr)
{
	printf(" via \n");
	printf(" D1 | 0 2 \n");
	printf(" ----|-----------\n");
	printf(" 0| %3d %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
	printf("dest 2| %3d %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
	printf(" 3| %3d %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);
	printf("\n");
}

linkhandler1(linkid, newcost)
	int linkid, newcost;
	/* called when cost from 1 to linkid changes from current value to
	newcost*/
	/* You can leave this routine empty if you're an undergrad. If you want
	*/
	/* to use this routine, you'll need to change the value of the
	LINKCHANGE */
	/* constant definition in prog3.c from 0 to 1 */
{

}
