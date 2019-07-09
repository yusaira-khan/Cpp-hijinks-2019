#include <list>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <utility>
#include <random>
#include <map>
#include <memory>
#include <set>
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
	//todo: change vertex and edges to classes
	//todo: add all the missing api required in question
	//todo: finish djikstra
	//todo: change raw objects to ptrs
	//todo: change ptrs to unique ptrs
	//todo: make forloops less redundant. foreach perhaps?
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
	UndirectedGraph getShortestPath(Vertex src, Vertex dst){
		std::queue<Vertex> open({src});
		std::set<Vertex> closed;
		UndirectedGraph shortest;
		//todo: add adding arbitrary edges and vertices to graph
		//todo: let changing weights of edges
		while(!open.empty()){
			Vertex current = open.front();
			if (current == dst){
				//todo: done
			}
			for (auto v = adjacencyList[current].begin();
				v!=adjacencyList[current].end();
				v++){
				//update edges

				//don't know if neeeded
				if (closed.find(*v)==closed.end()){//not in closed set
					open.push(*v);
				}
			}
			open.pop();
			closed.insert(current);
		}
		return closed.size() == this->numVertices;
		// std::for_each(adjacencyList[src].begin(), adjacencyList[src].end(),
		// 	[open](Vertex n){ open.push(n)});
	}
	bool isConnected(){
		const Vertex src = 0;
		std::queue<Vertex> open({src});
		std::set<Vertex> closed;
		//breath first search
		while(!open.empty()){
			Vertex current = open.front();
			for (auto v = adjacencyList[current].begin();
				v!=adjacencyList[current].end();
				v++){
				if (closed.find(*v)==closed.end()){//not in closed set
					open.push(*v);
				}
			}
			open.pop();
			closed.insert(current);
		}
		return closed.size() == this->numVertices;
		// std::for_each(adjacencyList[src].begin(), adjacencyList[src].end(),
		// 	[open](Vertex n){ open.push(n)});

	}
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
	std::cout << g->isConnected();
	// delete &g;
	// g->print();
	return 0;
}
