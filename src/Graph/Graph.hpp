#pragma once

#include "vector3D.hpp"

#include <vector>
#include <string>

namespace shp
{
    typedef std::vector<Vector3> Path;

    class Node
    {
        public: 
            Node(Vector3 v1, Vector3 v2, 
                 Vector3 v3, double height = 0.0)
                : m_Vertex1(v1), 
                  m_Vertex2(v2),
                  m_Vertex3(v3)
            {
                m_Vertex1.y = m_Vertex2.y = m_Vertex3.y = height;
            }

            inline Vector3 GetCenter() { return (m_Vertex1 + m_Vertex2 + m_Vertex3) / 3.0; }
            bool Contains(Vector3 position);
            void Draw();

        private:
            Vector3 m_Vertex1, m_Vertex2, m_Vertex3;
    };

    class Graph
    {
        public: 
            inline static Graph* GetInstance(){
                return s_Instance = (s_Instance == nullptr ? new Graph() : s_Instance);
            }

            void Load(const std::string filename);
            int GetNodeFromPosition(Vector3	position);
            Path GetShortestPath(int src, int dst);
            Path GetShortestPath(Vector3 src, Vector3 dst);
            void Draw();
            void Clean();

            static Path SmoothPath(Path path);
            static void DrawPath(Path path);

            inline int GetSize() { return m_NodeCount; }
            inline Vector3 GetCenter(int i) { return m_NodeList[i].GetCenter(); }
            inline double GetCost(int i, int j)
            {
                return m_NodeList[i].GetCenter().distance(m_NodeList[j].GetCenter());
            }

        private:
            Graph() 
                : m_NodeCount(0),
                  m_NodeList(),
                  m_AdjacencyList()
            {}

            int m_NodeCount;
            std::vector<Node> m_NodeList;
            std::vector<std::vector<int>> m_AdjacencyList;

            static Graph* s_Instance;
    };
};