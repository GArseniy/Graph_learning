///< TO FIX: this library





#include <sstream>
#include <iostream>
#include <cmath>
#include <string.h>
#include <string>
#include <cstdlib>
#include <limits>
#include <vector>


class EdgesList_t;
class AdjacencyList_t;
class AdjacencyMatrix_t;
struct Edge;

class EdgesList_t{
public:
    int VertexesCount;
    int EdgesCount;
    std::vector<Edge> Edges;
};
class AdjacencyList_t;
class AdjacencyMatrix_t{
public:
    int VertexesCount;
    int EdgesCount;
    std::vector<std::vector<int>> AdjacencyMatrix;
};
struct Edge{
    std::pair<int, int> vec;
    int weight { 1 };
};

char* stoa(std::string str);
std::string get_line();


class AdjacencyMatrix_t{
/**
    AdjacencyMatrix is description of oriented graph:
    vertexes: {v0, v1, v2, ... , v(N-1)};
    count of vertexes = N;
    adjacency matrix:{{1, 0, 0, 1},
                      {0, 0, 0, 0},
                      {0, 0, 0, 1},
                      {1, 0, 1, 0}} is Matrix shows count of oriented edges from each vertex to others;
    edges: {(0, 0), (0, 3), (2, 3), (3, 0), (3, 2)};
*/

public:
    int VertexesCount;
    int EdgesCount;
    std::vector<std::vector<int>> AdjacencyMatrix;

public:
    AdjacencyMatrix_t(const std::string& data){
    /// data format: "0 1 0 \n1 0 1 \n0 0 1 \n"
        std::string number;
        std::vector<int> vec;
        for (const char &ch: data){
            if (ch == ' ' or ch == '\n'){
                if (number != "")
                    vec.push_back(stoi(number));
            }
            else{
                number += ch;
            }
        }
        VertexesCount = pow(vec.size(), 0.5);
        EdgesCount = 0;
        std::vector<int> templ(VertexesCount, 0);
        std::vector<std::vector<int>> vec__(VertexesCount, templ);
        AdjacencyMatrix = vec__;
        int it = 0;
        for (int i=0; i < VertexesCount; ++i)
            for (int j=0; j < VertexesCount; ++j){
                AdjacencyMatrix[i][j] = vec[it++];
                EdgesCount += AdjacencyMatrix[i][j];
            }
    }

    AdjacencyMatrix_t(const EdgesList_t &EL){
        VertexesCount = EL.VertexesCount;
        EdgesCount = EL.EdgesCount;
        std::vector<int> templ (VertexesCount, 0);
        std::vector<std::vector<int>> vec__(VertexesCount, templ);
        AdjacencyMatrix = vec__;
        for (int i=0; i < EdgesCount; ++i)
            ++AdjacencyMatrix[EL.Edges[i].vec.first][EL.Edges[i].vec.second];
    }

    AdjacencyMatrix_t(const AdjacencyList_t& AL){
        VertexesCount = AL.VertexesCount;
        EdgesCount = AL.EdgesCount;
        std::vector<int> templ (VertexesCount, 0);
        std::vector<std::vector<int>> vec__(VertexesCount, templ);
        AdjacencyMatrix = vec__;
        for (int i=0; i < VertexesCount; ++i)
            for (int j=0; j < AL.AdjacenciesSize[i]; ++j)
                ++AdjacencyMatrix[i][AL.Adjacencies[i][j]];
    }

    operator std::string() const {
        /// Casting  <AdjacencyMatrix_t>  to  <std::string>  returns string like this: "1 0 0 1 \n0 0 0 0 \n0 0 0 1 \n1 0 1 0 \n"
        std::string string_out;
        for (int i=0; i < VertexesCount; ++i){
            for (int j=0; j < VertexesCount; ++j){
                string_out += std::to_string(AdjacencyMatrix[i][j]) + " ";
            }
            string_out += '\n';
        }
        return string_out;
    }

    std::vector<int> VertexesDegreeOut() const {
        std::vector<int> vec(VertexesCount, 0);
        for (int i=0; i < VertexesCount; ++i)
            for (int j=0; j < VertexesCount; ++j)
                vec[i] += AdjacencyMatrix[i][j];
        return vec;
    }

    std::vector<int> VertexesDegreeIn() const {
        std::vector<int> vec(VertexesCount, 0);
        for (int i=0; i < VertexesCount; ++i)
            for (int j=0; j < VertexesCount; ++j)
                vec[j] += AdjacencyMatrix[i][j];
        return vec;
    }

    bool IsOriented() const {
        for (int i=0; i < VertexesCount; ++i)
            for (int j=(i + 1); j < VertexesCount; ++j)
                if (AdjacencyMatrix[i][j] != AdjacencyMatrix[j][i])
                    return true;
        return false;
    }

    bool IsSelfLoopsIn() const {
        for (int i = 0; i < VertexesCount; ++i)
            if (AdjacencyMatrix[i][i])
                return true;
        return false;
    }
};

std::ostream& operator<<(std::ostream& output, const AdjacencyMatrix_t& AM) {
    for (int i=0; i < AM.VertexesCount; ++i){
        for (int j=0; j < AM.VertexesCount; ++j){
            output << std::to_string(AdjacencyMatrix[i][j]) << ' ';
        }
        output << '\n';
    }
    return output;
}

std::istream& operator>>(std::istream &input, AdjacencyMatrix_t &AM) {
    input >> AM.VertexesCount;
    AM.EdgesCount = 0;
    std::vector<int> templ (AM.VertexesCount, 0);
    std::vector<std::vector<int>> vec(AM.VertexesCount, templ);
    AM.AdjacencyMatrix = vec;
    for (int i=0; i < AM.VertexesCount; ++i)
        for (int j=0; j < AM.VertexesCount; ++j){
            input >> AM.AdjacencyMatrix[i][j];
            AM.EdgesCount += AM.AdjacencyMatrix[i][j];
        }
    return input;
}

struct Edge{
    std::pair<int, int> vec;
    int weight { 1 };
};

class EdgesList_t{
/**
    EdgesList is description of oriented graph:
    vertexes: {v0, v1, v2, ... , v(N-1)};
    count of vertexes = N;
    edges: {(v0, v2), (v2, v0), (v0, v0), ...} is vector of oriented edges;
*/

public:
    int VertexesCount;
    int EdgesCount;
    std::vector<Edge> Edges;

public:
    EdgesList_t(const std::string& data){
    {/**
        AdjacencyMatrix of graph:
                v0 v1 v2 v3
            v0  1  1  0  0
            v1  1  0  1  0
            v2  0  0  1  0
            v3  0  0  0  0

        EdgesList of graph:
                {(0, 0),
                 (0, 1),
                 (1, 0),
                 (1, 2),
                 (2, 2)} - there is zero information about v3 as if it does not exist,
                         for this reason, it is necessary to initialize the count of vertexes;

        data format:
            firstly: count of vertexes and count of edges
                  "v4 e5 \n" + ...
            secondly: line by line from first to last:
            ... + "0 0 \n" +
                + "0 1 \n" +
                + "1 0 \n" +
                + "1 2 \n" +
                + "2 2 \n"
        comment: each number is followed by a space symbol and each new edge is followed by a '\n' symbol
        data = "v4 e5 \n0 0 \n0 1 \n1 0 \n1 2 \n2 2 \n" or "cin" for keyboard input
    */}
        if (data == "cin"){
            std::cout << "Vertexes count and Edges count (separated by a space): ";
            int n, edges_count;
            std::cin >> n >> edges_count;
            std::cout << "Edges list: \n";
            EL.EdgesCount = edges_count;
            EL.VertexesCount = n;
            EL.Edges = new int*[EL.EdgesCount];
            for (int i = 0; i < EL.EdgesCount; i++){
                EL.Edges[i] = new int[2];
                std::cin >> EL.Edges[i][0] >> EL.Edges[i][1];
            }
        }
        else{
            std::string n_str = "";
            int caret = 1;
            while (data[caret] != ' ')
                n_str += data[caret++];
            EL.VertexesCount = stoi(n_str);
            caret += 2;
            std::string edges_count_str = "";
            while (data[caret] != ' ')
                edges_count_str += data[caret++];
            EL.EdgesCount = stoi(edges_count_str);
            caret += 2;
            EL.Edges = new int*[EL.EdgesCount];
            for (int i = 0; i < EL.EdgesCount; i++){
                EL.Edges[i] = new int[2];
                std::string number = "";
                while (data[caret] != ' ')
                    number += data[caret++];
                EL.Edges[i][0] = stoi(number);
                caret++;
                number = "";
                while (data[caret] != ' ')
                    number += data[caret++];
                EL.Edges[i][1] = stoi(number);
                caret += 2;
            }
        }
        return EL;
    }

    EdgesList_t(const AdjacencyMatrix_t& AM){
        VertexesCount = AM.VertexesCount;
        EdgesCount = AM.EdgesCount;
        std::vector<Edge> __vec(EdgesCount);
        Edges = __vec;
        int it = 0;
        for (int i=0; i < VertexesCount; ++i)
            for (int j=0; j < VertexesCount; ++j)
                if (AM.AdjacencyMatrix[i][j]){
                    Edges[it].vec.first = i;
                    Edges[it].vec.second = j;
                    ++it;
                }
    }

    char* get_string_EL(EdgesList_type EL){
        char buffer[33];
        std::string string_out = "";
        string_out += "v"; string_out += itoa(EL.VertexesCount, buffer, 10);
        string_out += " e"; string_out += itoa(EL.EdgesCount, buffer, 10);
        string_out += " \n";
        for (int i = 0; i < EL.EdgesCount; i++){
            for (int j = 0; j < 2; j++){
                string_out += itoa(EL.Edges[i][j], buffer, 10);
                string_out += " ";
            }
            string_out += "\n";
        }
        EL.__String = stoa(string_out);
        return EL.__String;
    }


    int search_edge_EL(EdgesList_type EL, int* edge){
        int left = 0, right = EL.EdgesCount - 1;
        int res = -1;
        while (left <= right){
            int mid = (left + right) / 2;
            if (EL.Edges[mid][0] == edge[0]){
                res = mid;
                right = mid - 1;
            }
            else if (EL.Edges[mid][0] > edge[0])
                right = mid - 1;
            else
                left = mid + 1;
        }
        if (res == -1) return -1;
        int Great_left = res;
        left = res; right = EL.EdgesCount - 1;
        while (left <= right){
            int mid = (left + right) / 2;
            if (EL.Edges[mid][0] == edge[0]){
                res = mid;
                left = mid + 1;
            }
            else if (EL.Edges[mid][0] > edge[0])
                right = mid - 1;
            else
                left = mid + 1;
        }
        int Great_right = res;
        res = -1;
        left = Great_left; right = Great_right;
        while (left <= right){
            int mid = (left + right) / 2;
            if (EL.Edges[mid][1] == edge[1]){
                res = mid;
                right = mid - 1;
            }
            else if (EL.Edges[mid][1] > edge[1])
                right = mid - 1;
            else
                left = mid + 1;
        }
        return res;
    }


    bool is_parallel_oriented_edges_EL(EdgesList_type EL){
        for (int i = 0; i < EL.EdgesCount; i++){
            int reverse_edge[] = {EL.Edges[i][1], EL.Edges[i][0]};
            int it_searched = search_edge_EL(EL, reverse_edge);
            if (it_searched != -1) return 1;
        }
        for (int i = 1; i < EL.EdgesCount; i++){
            if (EL.Edges[i][0] == EL.Edges[i-1][0] and EL.Edges[i][1] == EL.Edges[i-1][1]) return 1;
        }
        return 0;
    }


    AdjacencyList_type make_AL_from_EL(EdgesList_type EL){

    }

};


std::ostream& operator<<(std::ostream& output, const EdgesList_t& EL) {
    output << EL.VertexesCount << ' ' << EL.EdgesCount << '\n';
    for (int i=0; i < EL.EdgesCount; ++i)
        output << EL.Edges[i].vec.first << ' ' << EL.Edges[i].vec.second  << ' ' << EL.Edges[i].weight << ' ' << '\n';
    return output;
}

std::istream& operator>>(std::istream &input, EdgesList_t &EL) {
    input >> EL.VertexesCount >> EL.EdgesCount;
    std::vector<Edge> __vec(EdgesCount);
    Edges = __vec;
    for (int i=0; i < VertexesCount; ++i)
        input >> EL.Edges[i].vec.first >> EL.Edges[i].vec.second >> EL.Edges[i].weight;
    return input;
}


class AdjacencyList_t{
/**
    AdjacencyList is description of the graph:
    vertexes: {v0, v1, v2, ... , v(N-1)};
    count of vertexes = N is VertexesCount;
    adjacency matrix:{{1, 0, 0, 1},
                      {0, 0, 0, 0},
                      {0, 0, 0, 1},
                      {1, 0, 1, 0}};
    edges: {(0, 0), (0, 3), (3, 0), (2, 3), (3, 2)};
    adjacency list: {{0, 3},
                     {},
                     {3},
                     {0, 2}} is Adjacencies, and "v4 \n0 3 \n\n3 \n0 2 \n" is __String;
*/
    int VertexesCount;
    int EdgesCount;
    int** Adjacencies;
    int* AdjacenciesSize; ///< size of each line in int** Adjacencies;
/// parameters below will be initialized after calling the corresponding functions
    char* __String;
    int* __VertexesDegree;
    int* __VertexesDegreeIn;
    int* __VertexesDegreeOut;

/// AdjacencyList functions


/// TODO: "not cin" input;
AdjacencyList_type init_AL(std::string data){
{/**
    adjacency matrix of graph:
            v0 v1 v2 v3
        v0  1  1  0  0
        v1  1  0  1  0
        v2  0  0  1  0
        v3  0  0  0  0

    adjacency list: {{0, 1},
                     {0, 2},
                     {2},
                     {}};

    data format:
        firstly: count of vertexes
              "v4 \n" + ...
        secondly: line by line from first to last:
        ... + "0 1 \n" +
            + "0 2 \n" +
            + "2 \n" +
            + "\n"
    comment: each number is followed by a space symbol and each new edge is followed by a '\n' symbol
    data = "v4 \n0 1 \n0 2 \n2 \n\n" or "cin" for keyboard input
*/}
    AdjacencyList_type AL;
    if (data == "cin"){
        std::cout << "Vertexes count: ";
        int n;
        std::cin >> n;
        AL.VertexesCount = n;
        std::cin.ignore();
        std::cout << "Adjacency List: \n";
        AL.Adjacencies = new int*[AL.VertexesCount];
        AL.AdjacenciesSize = new int[AL.VertexesCount];
        int edges_count = 0;
        for (int i = 0, vc = AL.VertexesCount; i < vc; i++){
            std::string line = get_line();
            if (line == ""){
                AL.Adjacencies[i] = nullptr;
                AL.AdjacenciesSize[i] = 0;
                continue;
            }
            while (line[line.length() - 1] == ' ') line.erase(line.length() - 1); ///< line -= ' ' == deleting extra spaces;
            line += ' '; ///< only one space at the end of the line;
            int size_Adjacencies = 0;
            for (int j = 0, line_length = line.length(); j < line_length; j++)
                if (line[j] == ' ')
                    size_Adjacencies++;
            AL.Adjacencies[i] = new int[size_Adjacencies];
            AL.AdjacenciesSize[i] = size_Adjacencies;
            int caret = 0, line_length = line.length(), counter_edges_out = 0;
            while (caret < line_length){
                if (line[caret] == ' ') caret++;
                int number_start = caret, number_length = 1;
                while (line[caret++] != ' ') number_length++;
                std::string number_str = line.substr(number_start, number_length);
                AL.Adjacencies[i][counter_edges_out++] = stoi(number_str);
            }
            edges_count += AL.AdjacenciesSize[i];
        }
        AL.EdgesCount = edges_count;
    }
    else{}
    return AL;
}

AdjacencyList_type make_AL_from_AM(AdjacencyMatrix_type AM){

    }

/// TODO:
int* get_vertexes_degree_AL(AdjacencyList_type AL){
}


char* get_string_AL(AdjacencyList_type AL){
    std::string string_out = "v";
    char buffer[33];
    string_out += itoa(AL.VertexesCount, buffer, 10);
    string_out += " \n";
    for (int i = 0, vc = AL.VertexesCount; i < vc; i++){
        for (int j = 0, as = AL.AdjacenciesSize[i]; j < as; j++){
            string_out += itoa(AL.Adjacencies[i][j], buffer, 10);
            string_out += ' ';
        }
        string_out += '\n';
    }
    AL.__String = stoa(string_out);
    return AL.__String;
}


AdjacencyList_type reverse_oriented_AL(AdjacencyList_type AL){
    AdjacencyList_type AL_return = {.VertexesCount = AL.VertexesCount, .EdgesCount = AL.EdgesCount};
    std::vector < std::vector <int> > AL_vec;
    AL_vec.resize(AL.VertexesCount);
    AL_return.AdjacenciesSize = new int[AL_return.VertexesCount];
    AL_return.Adjacencies = new int*[AL_return.VertexesCount];
    for (int i = 0; i < AL.VertexesCount; i++)
        for (int j = 0; j < AL.AdjacenciesSize[i]; j++)
            AL_vec[AL.Adjacencies[i][j]].push_back(i);
    for (int i = 0; i < AL_return.VertexesCount; i++){
        AL_return.AdjacenciesSize[i] = AL_vec[i].size();
        if (AL_return.AdjacenciesSize[i] == 0){
            AL_return.Adjacencies[i] = nullptr;
            continue;
        }
        AL_return.Adjacencies[i] = new int[AL_return.AdjacenciesSize[i]];
        for (int j = 0; j < AL_return.AdjacenciesSize[i]; j++){
            AL_return.Adjacencies[i][j] = AL_vec[i][j];
        }
    }
    return AL_return;
}

EdgesList_type make_EL_from_AL(AdjacencyList_type AL){
    EdgesList_type EL = {.VertexesCount = AL.VertexesCount, .EdgesCount = AL.EdgesCount};
    EL.Edges = new int*[EL.VertexesCount];
    int counter_of_edges = 0;
    for (int i = 0; i < AL.VertexesCount; i++)
        for (int j = 0; j < AL.AdjacenciesSize[i]; j++){
            EL.Edges[counter_of_edges] = new int[2];
            EL.Edges[counter_of_edges][0] = i;
            EL.Edges[counter_of_edges][1] = AL.Adjacencies[i][j];
            counter_of_edges++;
        }
    return EL;
}


};


/// Common functions


char* stoa(std::string str){
    return strdup(str.c_str());
}


std::string get_line(){
    std::string line;
    std::getline(std::cin, line);
    return line;
}
