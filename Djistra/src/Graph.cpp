#include <list>
#include <iostream>
#include <vector>
#include <queue>

using std::list;
using std::vector;
namespace Djistra{

class Edge{
}
class Vertex{
}
class Graph {
public:
	Graph(int numVertices,int density){

	}
	~Graph(){
		delete edgelist;
		delete adjacencyList;
		delete adjacencyMatrix;
	};
	getStr();
	getNumVertices();
	getNumEdges();
	getShortestPath();
	isConnected();
	getCurrentDensity();
	getAverageDegree();

private:
		std::list<Edge> edgelist;
		list<list<Vertex>> adjacencyList;
		vector<vector<Vertex>> adjacencyMatrix;
		const int numVertices;
		const int initialDensity;

}
ostream & operator << (ostream &out, const Graph &c)
{
    out << c.getStr() << endl;
    return out;
}
}