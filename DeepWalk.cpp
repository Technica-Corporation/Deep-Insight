#include "stdafx.h"
#include "DeepWalk.h"

DeepWalk::DeepWalk(std::string fNameGraph, int walks_per_node_num, int in_walk_length, int in_feat_num, bool graphFile_binary){
	Graph = TNGraph::New();
	std::ifstream in;
	if (graphFile_binary)
		in.open(fNameGraph, ifstream::binary);
	else
		in.open(fNameGraph);
	if (!in){
		std::cout << "Unable to open file" << std::endl;
		return;
	}
	long long e1, e2;
	std::vector<int> E;
	std::set<int> V;
	bool good = 1;
	while (!in.eof()){
		if (graphFile_binary){
			in.read((char*)&e1, sizeof(long long));
			in.read((char*)&e2, sizeof(long long));
		}
		else in >> e1 >> e2;
		E.push_back(e1); E.push_back(e2);
		V.insert(e1); V.insert(e2);
	}
	in.close();
	size_t nodeCounter=0;
	for (auto it = V.begin(); it != V.end(); it++){
		Graph->AddNode(*it);
		nodes_ids.push_back(*it);
		nodeCounter++;
	}
	for (int i = 0; i < E.size(); i += 2)
		Graph->AddEdge(E[i], E[i + 1]);

	//init vars
	walks_num = walks_per_node_num;
	walk_length = in_walk_length;
	feat_num = in_feat_num;
         std::cout<<"The node count is "<<nodeCounter<< " the walk number is "<<walks_num<<" the walk length is "<<walk_length<<std::endl;
}


bool DeepWalk::corpus_save(string outFile_name)
{
	int walks_num = Walks.size();
	ofstream outFile(outFile_name);
	if (!outFile) return 0;
	for (int walk_cur_id = 0; walk_cur_id < walks_num; walk_cur_id++){
		Walk walk_cur = Walks[walk_cur_id];
		int words_perWalk = walk_cur.words.size();
		for (int word_cur_id = 0; word_cur_id < words_perWalk; word_cur_id++){
			outFile << walk_cur.words[word_cur_id]-1<<" ";
		}
		outFile << endl;
	}
	return 1;
}

bool DeepWalk::corpus_build()
{
	for (int path_cur = 0; path_cur < walks_num; path_cur++)
	{
		cout << "Done with " << path_cur * 10 << "% of walks ..." << endl;
		vector<int> nod_shuffle;
		for (int node_cur = 0; node_cur < Graph->GetNodes(); node_cur++)
		{
			Walk  oneWalk = random_walk_gen(walk_length, std::time(0), nodes_ids[node_cur]);
			Walks.push_back(oneWalk);
		}
	}
	return 1;
}

Walk DeepWalk::random_walk_gen(int walk_length, int srand_val, int snode_id)
{
	Walk walk;
	int len_cur = 1;
	int node_cur_id = snode_id;
	
	//TODO add uniformity condition 
	walk.words.push_back(snode_id); 
	while (len_cur<walk_length){
		TNGraph::TNodeI node_cur = Graph->GetNI(node_cur_id);
		int outNodes_num = node_cur.GetOutDeg();
		if (outNodes_num > 0){
			int outNode_rand = rand() % outNodes_num;
			// path.append(rand.choice(G[cur]))
			walk.words.push_back(node_cur.GetOutNId(outNode_rand));
			node_cur_id = node_cur.GetOutNId(outNode_rand);
			len_cur++;
		}
		else
			break;
	}
	return walk;
}

bool DeepWalk::fv_gen_and_save(string corpusFile_name, string fvFile_name){
	word2vec_main(corpusFile_name, fvFile_name, 1, 1, 0, 0, 2, 12); //FIXME use feature number in main
	return 1;
}
