#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

struct Rtree {
    std::vector<int> parent;
    std::vector<std::vector<int>> Struct_Adj;
    std::string tree_code;
    int index;
};

void Read(std::vector<Rtree> &Data) {
    for (int i = 0; i < Data.size() - 1; ++i) {
        for (int j = 0; j < Data[i].parent.size(); ++j) {
            std::cin >> Data[i].parent[j];
        }
        Data[i].index = i;
    }
}

void Print(std::vector<Rtree> &Data) {
    for (int i = 0; i < Data.size() - 1; ++i) {
        std::cout << "ind " << Data[i].index << " value ";
        for (int j = 0; j < Data[i].parent.size(); ++j) {
            std::cout << Data[i].parent[j] << " ";
        }
        std::cout << "\n";
    }
}

bool cmp(const std::string &lhs, const std::string &rhs) {
    return lhs < rhs;
}


std::vector<std::string> new_sort_str(std::vector<std::string> &vector) {
    std::sort(vector.begin(), vector.end(), cmp);
    return vector;
}

std::string get_full_str(std::vector<std::string> &vector) {
    vector = new_sort_str(vector);
    std::string result;
    for (int i = 0; i < vector.size(); ++i) {
        result += vector[i];
    }
    return result;
}


std::string str_dfs(int vertex, std::vector<Rtree> &Data, std::vector<char> &used, int k, std::string &code) {
    used[vertex] = true;
    std::vector<std::string> tmp;
    std::string str;

    //std:: cout << vertex << "\n";
    if (Data[k].Struct_Adj[vertex].empty()) {
        return "10";
    }

    for (std::vector<int>::iterator i = Data[k].Struct_Adj[vertex].begin();
         i != Data[k].Struct_Adj[vertex].end(); ++i) {
        if (!used[*i]) {
            //tmp += str_dfs(*i, Data, used, k, code);
            //tmp = sort_str(tmp, str_dfs(*i, Data, used, k, code));
            tmp.push_back(str_dfs(*i, Data, used, k, code));
            str = get_full_str(tmp);
        }
    }

    code = '1' + str + '0';
    return code;
}

void Tree_str_dfs(std::vector<Rtree> &Data) {
    for (int k = 0; k < Data.size() - 1; ++k) {
        std::string code;
        std::vector<char> used;
        used.resize(Data[k].parent.size() + 1);
        code = str_dfs(Data[k].parent[0], Data, used, k, code);
        Data[k].tree_code = code;
        //std::cout << "index: " << Data[k].index << " code: " << code << "\n";
    }

}

bool res_cmp(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    return lhs.size() < rhs.size();
}

bool first_ind_cmp(const std::vector<int> &lhs, const std::vector<int> &rhs) {
    if (lhs.size() == rhs.size())
        return lhs[0] < rhs[0];
    else
        return false;
}

void AHU(std::vector<Rtree> &Data, int n) {
    std::vector<std::vector<int>> Adj;

    //Получение массива детей (список смежности)
    for (int i = 0; i < Data.size() - 1; ++i) {
        Data[i].Struct_Adj.resize(n + 1);
        for (int j = 0; j < Data[i].parent.size(); ++j) {
            Data[i].Struct_Adj[Data[i].parent[j]].push_back(j + 1);
        }
    }

    Tree_str_dfs(Data);

    std::map<std::string, std::vector<int>> mapp;
    std::vector<char> was_taken(Data.size() - 1, false);
    for (int i = 0; i < Data.size() - 1; ++i) {
        if (was_taken[i] == false) {
            mapp[Data[i].tree_code].push_back(Data[i].index);
            was_taken[i] = true;
        }
        for (int j = i + 1; j < Data.size() - 1; ++j) {
            if (Data[i].tree_code == Data[j].tree_code && was_taken[j] == false) {
                was_taken[j] = true;
                mapp[Data[j].tree_code].push_back(Data[j].index);
            }
        }
    }

    std::vector<std::vector<int>> result;
    std::cout << mapp.size() << "\n";
    for (auto &i: mapp) {
        result.push_back(i.second);
    }

    std::sort(result.begin(), result.end(), res_cmp);
    std::sort(result.begin(), result.end(), first_ind_cmp);
    for (int i = 0; i < result.size(); ++i) {
        std::cout << result[i].size() << " ";
        for (int j = 0; j < result[i].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
        std::cout << "\n";
    }

    //Вывод списка смежности
    /*for (int i = 0; i < Data.size() - 1; ++i) {
        std::cout << "Index_" << Data[i].index << "\n";
        for (int k = 0; k < Data[i].Struct_Adj.size() - 1; ++k) {
            std::cout << k << ": ";
            for (int j = 0; j < Data[i].Struct_Adj[k].size(); ++j) {
                std::cout << Data[i].Struct_Adj[k][j] << " ";
            }
            std::cout << "\n";
        }
    }*/
}

int main() {
    std::vector<Rtree> Data;
    std::vector<int> tree;
    int k, n, N = 0;
    std::cin >> k >> N;
    n = N - 1;
    if (k == 0 || n == 0 || n == -1) {
        std::cout << "0\n";
        return 0;
    }
    Data.resize(k + 1);
    for (int i = 0; i < Data.size(); ++i) {
        Data[i].parent.resize(n);
    }

    Read(Data);
    Print(Data);
    AHU(Data, n);
    return 0;
}