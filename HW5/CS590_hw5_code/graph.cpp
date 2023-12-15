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
      m_edge[i][j] = INT_MAX;

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

}

// TODO: Implement problem 3
bool graph::bellman_ford(int s, int*& v_d, int*& v_pi)
{
  return true;
}

// TODO: Implement problem 4
void graph::floyd_warshall(int**& d, int**& pi)
{

}
