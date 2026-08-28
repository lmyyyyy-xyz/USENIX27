#ifndef HEADER_lp_network
#define HEADER_lp_network

#include "commonlib.h"
#include "lp_types.h"

/* Define constants for network types */
#define network_Unknown            0
#define network_MinCost            1
#define network_MaxFlow            2
#define network_Assignment         3
#define network_MaxEdgeMatch       4
#define network_MaxGeoMatch        5

#define network_stdNodeSource     +1
#define network_stdNodeSink       -(network_stdNodeSource)

/* Define Dimacs format strings */
#define DimacsCommentFmt           "c %s"
#define DimacsProblemFmt           "p %s %d %d"
#define DimacsMinCostNodeFmt       "n %d %d"
#ifdef INTCOST
#define DimacsMinCostArcFmt        "a %d %d %d %d %d"
#else
#define DimacsMinCostArcFmt        "a %d %d %d %d %-12g"
#endif
#define DimacsMaxFlowNodeFmt       "n %d %s"
#define DimacsMaxFlowArcFmt        "a %d %d %d"
#define DimacsAssignmentNodeFmt    "n %d"
#ifdef INTCOST
#define DimacsAssignmentArcFmt     "a %d %d %d"
#else
#define DimacsAssignmentArcFmt     "a %d %d %-12g"
#endif
#ifdef INTCOST
#define DimacsMatchingEdgeFmt      "e %d %d %d"
#else
#define DimacsMatchingEdgeFmt      "e %d %d %-12g"
#endif
#define DimacsMatchingGeometricFmt "v %d %d"

#define DimacsSolutionFmt          "s %-12g"
#define DimacsFlowFmt              "f %d %d %-12g"

#ifdef __cplusplus
extern "C" {
#endif

/* Put function headers here */
STATIC int get_Dimacs_type(char *_Label);
STATIC char *get_Dimacs_name(int nwtype, MYBOOL longname);
int __WINAPI get_network_type(lprec *lp, int *rowset, int *sinkValue);

#ifdef __cplusplus
 }
#endif

#endif /* HEADER_lp_network */
