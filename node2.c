//*************************************************
// Michael Meluso
// CSC 360 - Networking
// Project 3 - Distance Vector Algorithm
// Node2.c
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
struct distance_table
{
	int costs[4][4];
} dt2;

# define INFINITY 999
# define NODE 4 
static int neighbour[NODE] = {0,1,1,1}; 
static int dtcost[NODE] = {0,1,3,7}; 
static int dtvector2[NODE] = {0,1,3,7};

int i, j;

/* students to write the following two routines, and maybe some others*/
void rtinit2(float clocktime)
{
	printf("rtinit2 is called at t=%.3f\n",clocktime);
	for(i = 0; i < NODE; i++)
 		for(j = 0; j < NODE; j++) {
 			if((neighbour[i] == 1)&&(i == j)) 
 				dt2.costs[i][j] = dtcost[i]; 
 			else 
 				dt2.costs[i][j] = INFINITY;
 		}

 	struct rtpkt temp; 
	for(i = 0; i < NODE; i++)
	{ 
 		if(neighbour[i] == 1){ 
 			temp.sourceid = 0; 
 			temp.destid = i; 
 			for(j = 0;j< NODE; j++){ 
				temp.mincost[j] = dtvector2[j]; 
 			}

 			tolayer2(temp); 
 		}
 	}
}

void rtupdate2(struct rtpkt *rcvdpkt, float clocktime)
{
	int tempCost, vectorChange = 0;
	printf("rtupdate2 is called at t=%.3f. ",clocktime);
	printf("node 2 is receiving packet from node %d\n", rcvdpkt->sourceid);
	for(i = 0; i < NODE; i++){
		if(i != 0){ 
 			tempCost = dtcost[rcvdpkt->sourceid] + rcvdpkt->mincost[i]; 
 			if(tempCost < dt2.costs[i][rcvdpkt->sourceid]){ 
 				dt2.costs[i][rcvdpkt->sourceid] = tempCost;
 				printf("Node 2's distance table updated.\n"); 
				printdt2(&dt2); 
 			} 
 			if(tempCost < dtvector2[i]) { 
 				vectorChange = 1;
 				dtvector2[i] = tempCost; 
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
					temp.mincost[j] = dtvector2[j];
				}
				printf("Packet is being sent to node %d from Node 2.\n",i); 
				tolayer2(temp);
			}  
 		}
		printf("\n");
	}
}

printdt2(struct distance_table *dtptr)
{
	printf(" via \n");
	printf(" D2 | 0 1 3 \n");
	printf(" ----|-----------------\n");
	printf(" 0| %3d %3d %3d\n",dtptr->costs[0][0],
	dtptr->costs[0][1],dtptr->costs[0][3]);
	printf("dest 1| %3d %3d %3d\n",dtptr->costs[1][0],
	dtptr->costs[1][1],dtptr->costs[1][3]);
	printf(" 3| %3d %3d %3d\n",dtptr->costs[3][0],
	dtptr->costs[3][1],dtptr->costs[3][3]);
	printf("\n");
}
