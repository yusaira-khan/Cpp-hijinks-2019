#include <list>
#include <iostream>
#include <sstream>
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
// static inline createEdge(i,j){
// 	new
// }
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
	std::string getStr(){
		return getEdgeStr();
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
		void alignAdjagencylist();
		void alignMatrix();
		void alignReprWEdgelist();
		std::string getEdgeStr(){
		std::stringstream res;
		for (e in edgelist){
			res<<e.first<<"<-->"<<e.second+std::endl;
		}
		return res.str();
	}

}
ostream & operator << (ostream &out, const UndirectedGraph &c)
{
    out << c.getStr() << endl;
    return out;
}

int main(int argc, char const *argv[]){
	/* code */
	auto g =  new UndirectedGraph(5,0.8);
	std::cout << g;
	return 0;
}