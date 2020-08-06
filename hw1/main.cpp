#include <eigen3/Eigen/Eigen>
//#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

class mesh_node
{
public:
    int index;
    std::vector<int> edges;
    std::vector<float> length;
};
class ObjFile
{
public:
    ObjFile(std::string fileName)
    {
        std::string v;
        float values[3];
        std::ifstream file(fileName, std::ios::binary);
        while (!file.eof())
        {
            file >> v >> values[0] >> values[1] >> values[2];
            if (v == "v")
            {
                vertices.push_back(Eigen::Vector3f(values[0], values[1], values[2]));
            }
            else if (v == "f")
            {
                index.push_back(Eigen::Vector3i(values[0], values[1], values[2]));

                for(int i = 0; i < 3; i++){
                    if(i == 1){
                        Pos_edge[values[i]].push_back(values[2]);
                        Pos_edge[values[i]].push_back(values[0]);
                    }else{
                        Pos_edge[values[i]].push_back(values[abs(2-i)]);
                        Pos_edge[values[i]].push_back(values[abs(1-i)]);
                    }
                    
                }
            }
        }

        GenNode();
        std::cout << vertices.size() << ":" << index.size();
    }
    ~ObjFile()
    {
    }

    void GenNode(){
        for(auto it = Pos_edge.begin(); it != Pos_edge.end(); it++){
            //std::cout<<it->first<<std::endl;
            mesh_node node;
            node.index = it->first;
            node.edges = it->second;
            for(auto edgeIt = node.edges.begin(); edgeIt != node.edges.end(); edgeIt++){
                Eigen::Vector3f leng = vertices[it->first] - vertices[*edgeIt];
                node.length.push_back(leng.norm());
            }
            nodes[it->first] = node;
        }
    }

    std::vector<Eigen::Vector3f> vertices;
    std::vector<Eigen::Vector3i> index;
    std::unordered_map<int, mesh_node> nodes;
    std::unordered_map<int, std::vector<int>> Pos_edge;
};



class Dijkstra
{
public:
    Dijkstra(std::unordered_map<int, mesh_node> *inNode)
    {
        nodes = inNode;
    }

    void compute(int start, int dest){

    }

    std::unordered_map<int, mesh_node> *nodes;
};

int
main(int argc, char **argv)
{
    ObjFile obj("./teapot.obj");
    Dijkstra path_find(&obj.nodes);
    std::cout << "3333";
}