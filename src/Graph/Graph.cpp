#include "Graph.hpp"

#include <SDL.h>
#include <queue>

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
        int x1 = round(m_Vertex1), y1 = round(m_Vertex1.y);
        int x2 = round(m_Vertex2), y2 = round(m_Vertex2.y);
        int x3 = round(m_Vertex3), y3 = round(m_Vertex3.y);

        SDL_Renderer* renderer = Engine::GetInstance()->GetRenderer();

        SDL_SetRenderDrawColor(0x00, 0x00, 0x00, 0xFF);
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
        SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
        SDL_RenderDrawLine(renderer, x2, y2, x3, y3);
    }

    int Graph::GetNodeFromPosition(Vector3 position)
    {
        for(uint i = 0; i < m_NodeCount; i++)
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
                c = GetCost(v, u);
                if(distance[v] + c < distance[u])
                {
                    distance[u] = distance[v] + c;
                    parent[u] = v;
                    pq.push({-distance[u] - cost(u, dst), u, v});
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
        Path path = GetShortestPath(src, dst);
        path.push_back(dstPos);
        path.push_front(srcPos);

        return path;
    }

    Path Graph::SmoothPath(Path path)
    {
        if(path.empty())
            return path;
        
        Path result;
        Vector3 currPos = path.front();
        for(uint i = 1; i+1 < path.size(); i++)
        {
            Ray ray = { currPos, path[i+1] - currPos };     
            Collision* collision = CollisionHandler::GetInstance()->RayCast(ray);

            if(collision != nullptr){
                result.push_back(path[i]);
                currPos = path[i];
            }
        }

        result.push_back(path.back());
        return result;
    }

    void Graph::Draw()
    {
        for(Node node : m_NodeList)
            node.Draw();
    }
};