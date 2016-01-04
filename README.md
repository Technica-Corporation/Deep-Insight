# Deep-Insight: A deep learning tool for discovering latent representations of graphs
# Version: 12/30/2015
# Author: Technica Corporation

Deep-Insight is a C++ implementation of the DeepWalk algorithm (http://arxiv.org/abs/1403.6652) for learning latent representations of vertices in a graph. The application generates a set of random walks on the graph. Word-to-vec(https://code.google.com/p/word2vec/) is then applied to the random walks to produce vector represenations of each vertex. The number of walks and their length are specified by the user (see section #### Run & Parameters). 

All included OSS is licensed under the Apache license v. 2.0.

# Installation and Use
## Required Packages
- Pthread
- SNAP

#### Installation 

	# add or update pthread library 
	/$ sudo apt-get install libpthread-stubs0-dev

	# clone Deep-Insight repository (note: this also clone SNAP)
	/$ git clone --recursive http://github.com/Technica-Corporation/Deep-Insight
	
	# install SNAP
	Download SNAP (http://snap.stanford.edu/snap/index.html)
	Copy the snap-core and glib-core folders from SNAP into the base Deep-Insight folder
	
	# Execute Make
	/$ make	
	
#### Run & Parameters
By default, the number of walks is set to 100, steps to 8, and test graph to testGraph.txt. These parameters can be modified inside of TestDWC.cpp. 

To run the program, execute the following command:
	
	/$ ./CdeepWalk [path/to/graph/] [graph_file_name] [number of walks] [steps per walk]

#### Inputs: 
- The graph as an adjacency or edge list.

#### Outputs: 
- The walks recorded in a text file walks.txt.
- The resulting feature vectors in a file fv.txt as specified inside TestDWC.cpp.  
