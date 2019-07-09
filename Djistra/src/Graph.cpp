#include <list>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
#include <random>
#include <map>
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

	//create random edges
	for (int i =0; i < numVertices; i++){
		for (int j = i+1; j < numVertices; j++){
			if (edgeProbability(eng) < density){
				edgelist.push_front(std::unique_ptr<Edge>(new Edge(i,j)));
			}
		}
	}
	alignReprWEdgelist();
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
		return getEdgeStr().str()+getAdjListStr().str();
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
	std::map<Vertex,list<Vertex>> adjacencyList;
	vector<vector<Vertex>> adjacencyMatrix;
	const int numVertices;
	const float initialDensity;
	void addToList(const Vertex find, const Vertex add){
		auto find_it = adjacencyList.find(find);
		if (find_it != adjacencyList.end()){
			find_it->second.push_front(add);
		}else{
			adjacencyList[find]=list<Vertex>({add});
		}
	}
	void alignAdjagencylist(){
		for (auto e = edgelist.begin(); e!= edgelist.end(); e++){
			auto b = (*e)->second;
			auto a = (*e)->first;
			// std::cout<<"adding edge"<<a<<b;

			addToList(a, b);
			addToList(b, a);
		}
	}
	void alignMatrix();
	void alignReprWEdgelist(){
		alignAdjagencylist();
	}
	inline std::stringstream getEdgeStr()const {
		std::stringstream res;
		for (auto e = edgelist.begin(); e!= edgelist.end(); e++){
			res<<(*e)->first<<"<-->"<<(*e)->second<<std::endl;
		}
		return res;
	}
	inline std::stringstream getAdjListStr()const {
		std::stringstream res;
		for (auto v = adjacencyList.begin(); v!= adjacencyList.end(); v++){
			res<<v->first<<":";
			for (auto e = v->second.begin(); e!= v->second.end(); e++){
				res <<*e<<",";
			}
			res<<std::endl;
		}
		return res;
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
