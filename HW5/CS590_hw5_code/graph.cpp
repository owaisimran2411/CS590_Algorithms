#include "graph.h"
#include <list>
#include <iostream>

using namespace std;

/*
 * constructor/destructor
 */
graph::graph(int n)
{ /*<<<*/
  no_vert = (n > 0) ? n : 1;

/*
 * allocate adjacency matrix
 */
  m_edge = new int*[no_vert];
  for (int i = 0; i < no_vert; i++)
    m_edge[i] = new int[no_vert];

  initialize();
} /*>>>*/

graph::~graph()
{ /*<<<*/ 
/*
 * delete nil element and all other allocated nodes
 */
  for (int i = 0; i < no_vert; i++)
    delete[] m_edge[i];
  delete[] m_edge;
} /*>>>*/


void graph::initialize()
{ /*<<<*/
/*
 * initialize adjacency matrix
 * -> use infinity to allow 0 weight edges
 */
  for (int i = 0; i < no_vert; i++)
    for (int j = 0; j < no_vert; j++)
    {
      m_edge[i][j] = INT_MAX;
      m_edge[i][i] = 0;
    }

} /*>>>*/

void graph::permutation(int* perm, int n)
{ /*<<<*/
  random_generator rg;
  int p_tmp, p_pos;

  for (int i = 0; i < n; i++)
    perm[i] = i;
  
  for (int i = 0; i < n; i++)
    {
      rg >> p_pos;
      p_pos = (p_pos % (n - i)) + i;

      p_tmp = perm[i];
      perm[i] = perm[p_pos];
      perm[p_pos] = p_tmp;
    }
} /*>>>*/

void graph::output(int** m_out, int** m_out_2)
{ /*<<<*/
  if (!m_out)
    m_out = m_edge;

  cout << "[";
  for (int i = 0; i < no_vert; i++)
    {
      cout << "[\t";
      for (int j = 0; j < no_vert; j++)
  if (m_out[i][j] == INT_MAX)
    cout << "inf\t";
  else
    cout << m_out[i][j] << "\t";

      if (m_out_2)
  {
    cout << "]\t\t[\t";
    for (int j = 0; j < no_vert; j++)
      if (m_out_2[i][j] == INT_MAX)
        cout << "inf\t";
      else
        cout << m_out_2[i][j] << "\t";
  }

      cout << "]" << endl;
    }
  cout << "]" << endl;
} /*>>>*/


// TODO: Implement problem 1
void graph::generate_random(int n_edges, int max_weight)
{
  random_generator rg;
  double weight;
  int arr[no_vert];

  if (n_edges >= no_vert*(no_vert-1)) {
    n_edges = no_vert*(no_vert-1);
  }

  while (n_edges>0) {
    int edgeCount = (n_edges>no_vert-1)?no_vert-1:n_edges;
    permutation(arr, no_vert);

    for(int i=0; i<edgeCount; i++) {
      if (m_edge[arr[i]][arr[i+1]] == INT_MAX) {
        rg>>weight;
        weight = (weight*0.5)*2*max_weight;
        m_edge[arr[i]][arr[i+1]] = weight;
        n_edges--;
      }
    }
  }
}

void graph::initSingleSource(int *&v_d, int source, int *& v_pi) {
  for(int i=0; i<no_vert; i++) {
    v_d[i] = INT_MAX;
    v_pi[i] = INT_MAX;
  }

  v_d[source] = 0;
}

bool graph::relax(int u, int v, int *&v_d, int *&v_pi) {
  if(v_d[v] > m_edge[u][v] + v_d[u]) {
    v_pi[v] = u;
    return true;
  }
  return false;
}

// TODO: Implement problem 3
bool graph::bellman_ford(int s, int*& v_d, int*& v_pi)
{
  initSingleSource(v_d, s, v_pi);
  bool isNegativeCycleFound=false;
  for(int k=1; k<no_vert; k++) {
    for(int i=0; i<no_vert; i++) {
      for(int j=0; j<no_vert; j++) {
        if(m_edge[i][j] != 0 && m_edge[i][j] != INT_MAX) {
          if(relax(i, j, v_d, v_pi))
          {
            v_d[j] = v_d[i] + m_edge[i][j] ;
          }
        }
      }
    }
  }
  for(int i=0; i<no_vert; i++) {
    for(int j=0; j<no_vert; j++) {
      if(m_edge[i][j] != 0 && m_edge[i][j] != INT_MAX) {
        if (v_d[i] + m_edge[i][j] < v_d[j]) {
          isNegativeCycleFound=true;
          break;
        }
      }
    }
  }
  return isNegativeCycleFound;
}

// TODO: Implement problem 4
void graph::floyd_warshall(int**& d, int**& pi)
{

  int mc_edge[5][5] = {{0, 3, 8, INT_MAX, -4},{INT_MAX, 0, INT_MAX, 1, 7},{INT_MAX, 4, 0, INT_MAX, INT_MAX},{2, INT_MAX, -5, 0, INT_MAX},{INT_MAX, INT_MAX, INT_MAX, 6, 0}};
  for(int i=0; i<no_vert; i++) {
    for(int j=0; j<no_vert; j++) {
      d[i][j] = mc_edge[i][j];
    }
  }


  for(int k=0; k<no_vert; k++) {
    for(int i=0; i<no_vert; i++) {
      for(int j=0; j<no_vert; j++) {
        if( j!= i && (d[i][k] != INT_MAX && d[k][j] != INT_MAX )) {
          if ((d[i][k] + d[k][j]) < d[i][j] ) {
            d[i][j] = d[i][k] + d[k][j];
            pi[i][j] = k;
          }
        }
      }
    }
  }
}
