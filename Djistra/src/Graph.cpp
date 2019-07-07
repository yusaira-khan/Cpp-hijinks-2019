#include <list>
#include <iostream>
#include <vector>
#include <queue>
#include <pair>
#include <random>
using std::list;
using std::vector;
namespace Djistra{
// const bool UNDIRECTED = true;
// class Edge{
// }
// class Vertex{
// }
typedef int32_t Vertex;
typedef std::pair<Vertex,Vertex> Edge;

class UndirectedGraph {
public:
	UndirectedGraph(int numVertices,float density)
	:edgelist(0)
	{
		this.numVertices = numVertices;
		this.initialDensity = density;

 		std::default_random_engine eng((std::random_device())());
 		std::uniform_real_distribution<float> edgeProbability(0, 1.0);
 		for (int i =0; i < numVertices; i++){
			for int j = i+1; j < numVertices; j++;{
				if (edgeProbability() < density){
				edgelist.prepend(new Edge(i,j));
			}
			}
		}
	}
	~UndirectedGraph(){
		delete edgelist;
		delete adjacencyList;
		delete adjacencyMatrix;
	};
	string getStr(){
		string res = "";
		for (e in edgelist){
			e[0]+"<-->"+e[1];
		}
	}
	int getNumVertices(){
		return numVertices;
	};
	int getNumEdges(){
		return edgelist.size();
	}
	string getShortestPath();
	bool isConnected();
	float getCurrentDensity();
	float getAverageDegree();

private:
		list<Edge> edgelist;
		list<list<Vertex>> adjacencyList;
		vector<vector<Vertex>> adjacencyMatrix;
		const int numVertices;
		const float initialDensity;
		void alignReprWEdgelist();


}
ostream & operator << (ostream &out, const UndirectedGraph &c)
{
    out << c.getStr() << endl;
    return out;
}
}