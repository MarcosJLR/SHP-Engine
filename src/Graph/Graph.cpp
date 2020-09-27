#include "Graph.hpp"

#include <SDL.h>
#include <queue>
#include <fstream>
#include <iostream>
#include <algorithm>

#include "Kinematic.hpp"
#include "Engine.hpp"
#include "CollisionHandler.hpp"

namespace shp
{
    Graph* Graph::s_Instance = nullptr;

    bool Node::Contains(Vector3 position)
    {
        double A = fabs(m_Vertex1.orient2D(m_Vertex2, m_Vertex3));
        double B = fabs(position.orient2D(m_Vertex1, m_Vertex2));
        double C = fabs(position.orient2D(m_Vertex2, m_Vertex3));
        double D = fabs(position.orient2D(m_Vertex3, m_Vertex1));

        return fabs(A - (B + C + D)) < EPS;
    }

    void Node::Draw()
    {
        int x1 = round(m_Vertex1.x), y1 = round(m_Vertex1.z);
        int x2 = round(m_Vertex2.x), y2 = round(m_Vertex2.z);
        int x3 = round(m_Vertex3.x), y3 = round(m_Vertex3.z);

        SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();

        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
        SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    }

    int Graph::GetNodeFromPosition(Vector3 position)
    {
        for(int i = 0; i < m_NodeCount; i++)
        {
            if(m_NodeList[i].Contains(position))
                return i;
        }

        return -1;
    }

    Path Graph::GetShortestPath(int src, int dst)
    {
        std::priority_queue <std::tuple<double, int, int>> pq;
        std::vector <double> distance(m_NodeCount, INF);
        std::vector <int> parent(m_NodeCount, -1);

        distance[src] = 0.0;
        parent[src] = src;
        pq.push({0.0, src, src});

        while(!pq.empty())
        {
            auto [cost, v, par] = pq.top();
            pq.pop();

            if(par != parent[v]) continue;
            
            for(int u : m_AdjacencyList[v])
            {
                double c = GetCost(v, u);
                if(distance[v] + c < distance[u])
                {
                    distance[u] = distance[v] + c;
                    parent[u] = v;
                    pq.push({-distance[u] - GetCost(u, dst), u, v});
                }
            }
        }

        Path result;
        int v;
        for(v = dst; parent[v] != -1 && parent[v] != v; v = parent[v])
        {
            result.push_back(m_NodeList[v].GetCenter());
        }

        if(v != src){
            result.clear();
            return result;
        }

        result.push_back(m_NodeList[src].GetCenter());
        std::reverse(result.begin(), result.end());
        return result;
    }

    Path Graph::GetShortestPath(Vector3 srcPos, Vector3 dstPos)
    {
        int src = GetNodeFromPosition(srcPos);
        int dst = GetNodeFromPosition(dstPos);

        if(src == -1 || dst == -1)
        {
            return Path();
        }
        
        Path path = GetShortestPath(src, dst);
        path.push_back(dstPos);
        path.insert(path.begin(), srcPos);

        return path;
    }

    Path Graph::SmoothPath(Path path)
    {
        if(path.empty())
            return path;
        
        Path result;
        Vector3 currPos = path.front();
        for(int i = 1; i+1 < (int) path.size(); i++)
        {
            Vector3 direction = path[i+1] - currPos;
            Vector3 perpendicular = {-direction.z, direction.y, direction.x};
            perpendicular.scale(34.0);

            Ray ray1(currPos + perpendicular, path[i+1] - currPos);     
            Ray ray2(currPos - perpendicular, path[i+1] - currPos);     
            Collision* collision1 = CollisionHandler::GetInstance()->RayCast(ray1);
            Collision* collision2 = CollisionHandler::GetInstance()->RayCast(ray2);

            if(collision1 != nullptr || collision2 != nullptr){
                result.push_back(path[i]);
                currPos = path[i];
            }
        }

        result.push_back(path.back());
        return result;
    }

    void Graph::DrawPath(Path path)
    {
        SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();

        SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
        for(int i = 1; i < (int) path.size(); i++)
        {
            int x1 = path[i-1].x, z1 = path[i-1].z;
            int x2 = path[i].x, z2 = path[i].z;
            SDL_RenderDrawLine(renderer, x1, z1, x2, z2);
        }
    }

    void Graph::Draw()
    {
        for(Node node : m_NodeList)
            node.Draw();
    }

    void Graph::Clean()
    {
        m_NodeCount = 0;
        m_NodeList.clear();
        m_AdjacencyList.clear();
    }

    void Graph::Load(const std::string filename)
    {
        Clean();

        std::ifstream nodeFile(filename + ".node");
        std::ifstream elementFile(filename + ".ele");
        std::ifstream neighborFile(filename + ".neigh");

        if(!nodeFile.is_open()){
            std::cerr << "Couldn't Open " << filename << ".node file\n";
            return;
        }
        if(!elementFile.is_open()){
            std::cerr << "Couldn't Open " << filename << ".ele file\n";
            return;
        }
        if(!neighborFile.is_open()){
            std::cerr << "Couldn't Open " << filename << ".neigh file\n";
            return;
        }

        int pointCount, dimensions, attributeCount, boundMarks;
        std::vector<Vector3> points;
        nodeFile >> pointCount >> dimensions;
        nodeFile >> attributeCount >> boundMarks;

        for(int i = 0; i < pointCount; i++)
        {
            int id;
            double x, z, ignoreVar;

            nodeFile >> id >> x >> z;

            for(int j = 0; j < attributeCount; j++)
                nodeFile >> ignoreVar;

            for(int j = 0; j < boundMarks; j++)
                nodeFile >> ignoreVar;

            points.push_back({x, 0.0, z});
        }

        int pointsPerTriangle;
        elementFile >> m_NodeCount >> pointsPerTriangle;
        elementFile >> attributeCount;
        for(int i = 0; i < m_NodeCount; i++)
        {
            int id, v1, v2, v3;
            double ignoreVar;

            elementFile >> id >> v1 >> v2 >> v3;
            for(int j = 0; j < attributeCount; j++)
                elementFile >> ignoreVar;
            
            m_NodeList.push_back(Node(points[v1-1], points[v2-1], points[v3-1]));
        }

        m_AdjacencyList = std::vector<std::vector<int>>(m_NodeCount);
        int edgeCount, neighborsPerNode;
        neighborFile >> edgeCount >> neighborsPerNode;
        for(int i = 0; i < edgeCount; i++)
        {
            int id, neighbor;
            neighborFile >> id;
            id--;

            for(int j = 0; j < neighborsPerNode; j++)
            {
                neighborFile >> neighbor;
                if(neighbor != -1) { m_AdjacencyList[id].push_back(neighbor - 1); }
            }
        }

        std::cout << "Graph Loaded correctly\n";

        nodeFile.close();
        elementFile.close();
        neighborFile.close();
    }


};