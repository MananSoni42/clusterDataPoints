# Cluster given Data Points
#### Problem Statement:
Implement given algorithm in any programming language for clustering data points given in a dataset D. Assume an ordering of D where i th data point has index i.
#### Parameters:
  * K
  + ε (≤ K)
  - MinPts (≤ K)
#### Algorithm:
1. Sparsify Similarity Matrix   
a. Construct the similarity matrix M between every pair of data points.
      The value of M[i][j] = d(p i , p j ) where d is the Euclidean distance function.
      Assumed(p i , p i ) = ∞ ∀ p i ∈ D.    
b. Sparsify the matrix by keeping only K- nearest neighbours for each data point.
        Each row M[i] should contain K points with least Euclidean distance from point
        p i . If two points have same Euclidean distance then data point with lower index
        will be preferred. Let KNN(i) = M[i].  
2. Construct the shared neighbor graph G  
        a. The graph is given by G = (V, E) where V is the set of indices of data points in D
        and edge relation E is defined as :  
        ∀ p, q ∈ D (p, q) ∈ E iff [(p ≠ q) and p ∈ KNN(q) and q ∈ KNN(p)]  
        b. If (p, q) ∈ E then the weight of this edge (p, q) is
        W(p, q) = | KNN(p) ∩ KNN(q) |. Let similarity between two data points be
        given by sim(p, q) = W(p, q).  
3. Identify core points  
        a. The density of each data point is :
        density(p) = |{q | (p, q) ∈ E(G) and W(p, q) ≥ ε}| where E(G) represents the
        edge set of the shared neighbour graph G.  
        b. p is a core point iff density(p) ≥ MinPts.  
4. Form clusters using core points  
        a. Two core points c 0 and c k belong to the same cluster iff there exists a sequence
        of core points c = (c 0 , c 1 , ... , c k−1 , c k )(k ≥ 1) where ∀ i ∈ [0, k − 1]
        (c i , c i+1 ) ∈ E(G) and W(c i , c i+1 ) ≥ ε.  
        b. Clusters are numbered from 1 to n c where n c are the total number of clusters. Let
        Core be the set of indices of all core points sorted in ascending order, the
        numbering of clusters can be done as -  
            ```
            index = 1
            while(core is not empty):
                c = core.first
                cluster[index++] = Cluster(c)
                core = core - Cluster(c)
            ```  
5. Identify noise points  
        a. A point p is a noise point iff p is not a core point and
        {q | (p, q) ∈ E(G) and W(p, q) ≥ ε} = φ  
        b. A noise point does not belong to any cluster.  
6. Assign border points to clusters  
        a. A point is a border point if it is neither a core point nor a noise point.  
        b. Assign the border point p to the cluster of the core point c if the sim(p, c)is
        maximum among all such core points. If multiple core points have the same
        similarity with border point p, assign it to the core point with lower index.  
#### Implementation
The problem is implemented using c in `gcc version 7.2.0` 
#### Running the Program
here is an example on how to run the program:  
```./knn < Sample_input.txt```  
you can replace the Sample_input.txt with your own file given that it has the correct format  
#### Input Format
Input Format:
Each input would be given in a file in the following format. First line would contain five space
separated parameters as follows.  
 `N D K ε MinPts`  
  N = Number of points in the dataset  
	 D = Dimensions of each point  
	 K, ε, MinPts are parameters for the algorithm  
	This is followed by N lines each representing a data point of D dimensions.
 
#### Authors
  - **Manan Soni** - [MananSoni42](https://github.com/MananSoni42/)
  - **Abhishek V Joshi** - [jbnerd](https://github.com/jbnerd)
