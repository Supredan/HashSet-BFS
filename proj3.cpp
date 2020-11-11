#include "proj3.hpp"
#include "Wordset.hpp"
#include <iostream>
#include <set>
#include <sstream>
#include <map>
#include <stack>
#include <queue>

// You should not need to change this function.
void loadWordsIntoTable(WordSet & words, std::istream & in)
{
	std::string line, word;
	std::stringstream ss;

	while(	getline(in, line) )
	{
		ss.clear();
		ss << line;
		while( ss >> word )
		{
			words.insert( word );
		}
	}

}

struct node {
    std::string value;
    std::vector<std::string> trace;
    node(std::string _value){
        value = _value;
        trace.push_back(_value);
    }
};

void findOneCharDiff(node node, std::map<std::string, std::vector<std::string>> &graph,
                            std::queue<::node> &queue, const WordSet & words)
{
    for (int i = 0; i < node.value.size(); ++i) {
        for (int j = 0; j < 24; ++j) {
            ::node temp = node;
            temp.value[i] = 'a' + j;
            if (!words.contains(temp.value))
                continue;
            if (temp.value == node.value)
                continue;
            graph[node.value].push_back(temp.value);
            temp.trace.push_back(temp.value);
            queue.push(temp);
        }
    }
}


// You probably want to change this function.
std::string convert(std::string s1, std::string s2, const WordSet & words)
{
    std::map<std::string, std::vector<std::string>> graph;
    std::queue<node> queue;

    node start(s1);
    findOneCharDiff(start, graph, queue, words);

    while (!queue.empty()) {
        int size = queue.size();
        for (int i = 0; i < size; ++i) {
            node temp = queue.front();
            if (temp.value == s2)
            {
                std::vector<std::string> v = temp.trace;
                std::string str = v.front();
                for (int index = 1; index < v.size(); ++index) {
                    str += " --> " + v[index];
                }
                return str;
            }
            queue.pop();
            if (graph.count(temp.value)) {
                continue;
            }
            findOneCharDiff(temp, graph, queue, words);
        }
    }

	return "";
}
