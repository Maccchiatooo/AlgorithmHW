#include <iostream>

using namespace std;

struct v_l{ int v; struct v_l *next;};
typedef struct v_l vertex_list;
vertex_list * graph_part(int n, int k, vertex_list * edges[], int r);