# Project Proposal

1. **Leading Question** Given two trafic intersections in San Francisco, this project seek to find the shortest route between them via driving. Then we would like to display a map of California with the two intersections connected via the shortest route.

2. **Dataset Acquistion and processing** We propose to use data sets of San Francisco road network found in Real Datasets for Spatial Databases: Road Network and Points of Interest(https://www.cs.utah.edu/~lifeifei/SpatialDataset.htm) for this project. Dataset will be in .txt file that contain all nodes or edges between trafic intersections. We will load the edges data into two vectors, one contain the node's ID at the start of each edge; the other contain the node's ID at the end of each edge. For our graph structure, we propose that a node's ID is the FromNodID in the dataset; its location is its given normalized x-y location found in the node dataset and a edge exist between it and another node if the edge dataset contain a edge between their IDs. The weight of a edge will be based on its L2 distance found in the edge dataset.

3. **Graph Algorithms** For our graph traversal, we plan on implementing a DFS iterator. Its constructor should take the root node's ID as input and everytime operator++ is called, the iterator should move to the next node until there is no node left to traverse. 
For one of our algorism, we will implement a Dijikstra's algorism that take the IDs of the two intersections as inputs and return the shortest route between them as output. 
For our final algorism, we will attempt to project the shortest route between two intersections onto a map. However, the dataset we are working with lack reference to what each nodes refer to in term of real world location, so projecting the route onto a real world map may not be possible. If we are unable to find a reference between the nodes in the dataset and real world location, we will attempt to construct our own visual graph based on the node informations and project the shortest route onto this graph.

4. **Timeline**
April 12: set up MakeFile

April 15: read the dataset into vectors and set up test cases to check the accuracy of the vector.

April 20: convert vectors into graph format and pass simple tests.

April 23: write DFS iterator and varify with test.

April 30: write Dijikstra's algorism and varify with test. Write code for visual graph if necessary.

May 5: write projection algorism and varify with test.

May 8: finish report

May 9: Meet to record final presentation

May 11: Turn in project. 