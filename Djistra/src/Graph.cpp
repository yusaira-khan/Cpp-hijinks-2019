#include <list>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
#include <random>
#include <memory>
using std::list;
using std::vector;
// namespace Djistra{
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
	UndirectedGraph(int numVertices=5,float density=1.0f)
	:edgelist(0),
	numVertices(numVertices),
	initialDensity(density){
 		std::default_random_engine eng((std::random_device())());
 		std::uniform_real_distribution<float> edgeProbability(0, 1.0);
 		// edgelist = new list<Edge>();
 		// list<Edge> w;
 		for (int i =0; i < numVertices; i++){
			for (int j = i+1; j < numVertices; j++){
				if (edgeProbability(eng) < density){
					edgelist.push_front(std::unique_ptr<Edge>(new Edge(i,j)));
				}
			}
		}
	}
	~UndirectedGraph(){
		// delete edgelist;
		// for (auto e = edgelist.begin(); e!= edgelist.end(); e++){
		// 	delete(*e);
		// }
		// delete adjacencyList;
		// delete adjacencyMatrix;
	};
	inline std::string getStr() const {
		return getEdgeStr();
	}
	int getNumVertices(){
		return numVertices;
	};
	int getNumEdges(){
		return edgelist.size();
	}
	std::string getShortestPath();
	bool isConnected();
	float getCurrentDensity();
	float getAverageDegree();
private:
	std::list<std::unique_ptr<Edge>> edgelist;
	list<list<Vertex>> adjacencyList;
	vector<vector<Vertex>> adjacencyMatrix;
	const int numVertices;
	const float initialDensity;
	void alignAdjagencylist(){

	}
	void alignMatrix();
	void alignReprWEdgelist();
	inline std::string getEdgeStr()const{
		std::stringstream res;
		for (auto e = edgelist.begin(); e!= edgelist.end(); e++){
			res<<(*e)->first<<"<-->"<<(*e)->second<<std::endl;
		}
		return res.str();
	}

};
std::ostream & operator << (std::ostream &out, const UndirectedGraph &c){
    out << c.getStr() << std::endl;
    return out;
}
// }
int main(int argc, char const *argv[]){
	/* code */
	auto g = new UndirectedGraph (5,0.8);
	std::cout << g << std::endl;
	std::cout << *g;
	// delete &g;
	// g->print();
	return 0;
}
