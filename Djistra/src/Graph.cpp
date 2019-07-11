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

class Vertex{
public:
	int name;
	int weight;
	Vertex(int name):name(name),weight(0){
	}

};
bool operator==(const Vertex& a, const Vertex& b){
	return a.name == b.name;
}
bool operator==(const Vertex& a, int& b){
	return a.name == b;
}
struct vtxcmp : public std::binary_function<Vertex, Vertex, bool>{
    bool operator()(const Vertex& a, const Vertex& b) const {
        return a.name < b.name;
    }
};
std::ostream & operator << (std::ostream &out, const Vertex &c){
	return out<<c.name;
}
class Edge{
public:
	const Vertex first;
	const Vertex second;
	int weight;
	Edge(Vertex &first,Vertex& second):
	first(first),second(second),weight(0){}
};
std::ostream & operator << (std::ostream &res, const Edge &e){
return res<<e.first<<"<-"<<e.weight<<"->"<<e.second;
}
// typedef int32_t Vertex;
// typedef std::pair<Vertex,Vertex> Edge;
// static inline createEdge(i,j){
// 	new
// }
class ShortestPath{

};
class UndirectedGraph {
	//todo: change vertex and edges to classes
	//todo: add all the missing api required in question
	//todo: finish djikstra
	//todo: change raw objects to ptrs
	//todo: change ptrs to unique ptrs
	//todo: make forloops less redundant. foreach perhaps?
	//todo:TDD
	//todo: add vtx to adj list even if disconnected
public:
	UndirectedGraph(int numVertices=5,float density=1.0f)
	:
	numVertices(numVertices),
	initialDensity(density){
	std::default_random_engine eng((std::random_device())());
	std::uniform_real_distribution<float> edgeProbability(0, 1.0);
	vertexList.reserve(numVertices);
	//create random edges
	for (int i =0; i < numVertices; i++){
		vertexList.push_back(Vertex(i));
	}
	for (int i =0; i < numVertices; i++){
		for (int j = i+1; j < numVertices; j++){
			if (edgeProbability(eng) < density){
				edgelist.push_front(Edge(vertexList[i],vertexList[j]));
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
	int V(){
		return vertexList.size();
	};
	int E(){
		return edgelist.size();
	}
	int getNodeValue(int vertex_name){
		return findVertex(vertex_name).weight;
	}
	void setNodeValue(int vertex_name,int value){
	 	findVertex(vertex_name).weight = value;
	}

	int getEdgeValue(int start_vertex, int end_vertex){
		return findEdge(start_vertex,end_vertex).weight;
	}
	void setEdgeValue(int start_vertex, int end_vertex,int value){
		findEdge(start_vertex,end_vertex).weight=value;
	}
	UndirectedGraph getShortestPath(Vertex src, Vertex dst){
		std::queue<Vertex> open({src});
		std::set<Vertex,vtxcmp> closed;
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
		std::set<Vertex,vtxcmp> closed;
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
	std::list<Edge> edgelist;
	std::map<Vertex,list<Vertex>,vtxcmp> adjacencyList;
	vector<vector<Vertex>> adjacencyMatrix;
	const int numVertices;
	std::vector<Vertex> vertexList;
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
			auto b = (e)->second;
			auto a = (e)->first;
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
			res<<*e<<std::endl;
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
	Edge& findEdge(int start, int end){
		if (start < end){
			return findEdge(end,start);
		}
		return findEdge(findVertex(start),findVertex(end));
	}
	Edge& findEdge(const Vertex& start,const Vertex& end){
		for (auto e = edgelist.begin(); e!= edgelist.end(); e++){
			if (e->first == start && e->second == end){
				return *e;
			}
		}
		throw "edge not found";
	}
	Vertex& findVertex(int name){
		if (name>=0 && name< vertexList.size()){
			return vertexList[name];
		}
		throw "vertex not found!";

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
