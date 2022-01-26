#include<bits/stdc++.h>
#include<cstring>
#include<string>
#include<utility>
#include<algorithm>
#include<limits>

using namespace std;


class RoutingTable{
    private:
        int *dist;
        int numberOfNodes;
        vector<vector<int> >*path;	//2-D vector to store the routes
        
    public:

        RoutingTable(){
		dist = NULL;
		numberOfNodes = 0;
        }
        RoutingTable(int numberOfNodes) :numberOfNodes(numberOfNodes){
            dist = new int[numberOfNodes];
            for(int i=0;i<numberOfNodes;i++)
                dist[i] = INT32_MAX;
            path = new vector<vector<int> >(numberOfNodes);
        }

        vector<int>& getPath(int node){
            return (*path)[node];
        }

        int getDistance(int node){
            return dist[node];
        }

        void setDistance(int node,int distance){
            dist[node] = distance;
        }

        void print(){
            for(int i=0;i<numberOfNodes;i++){
                cout<<"Distance to "<<i<<" is "<<(dist[i] == INT32_MAX ? "INFINITY" : to_string(dist[i]))<<" and path is ";
                for(int j: (*path)[i])
                    cout<<j<<" ";
                cout<<endl;
            }
        }
        void setPath(int node,vector<int>& newPath){
            (*path)[node] = newPath;
        }
        ~RoutingTable(){
            delete dist;
            delete path;
        }
};

class Network{
    private:
        int distanceVectorRouting(Network &network,int src,int dest);
        int numberOfNodes;
        map<int,vector<pair<int,int> > >adjacencyList;
        bool *working;
        RoutingTable **routingTables;
        
    public:
        void ShortestDistance(int source,int destination,int &time){
            vector<int>parent(numberOfNodes);
            for(int i=0;i<numberOfNodes;i++)
                parent[i] = -1;
            set<pair<int,int> >distance;
            map<int,int>dist;
            for(int node=0;node<numberOfNodes;node++)
                dist[node] = INT32_MAX;
            dist[source] = 0;
            distance.insert({0,source});

            while(!distance.empty()){
                int currentNode = (*distance.begin()).second;
                for(pair<int,int> adjacentNodeDetails: adjacencyList[currentNode]){
                    int adjNode = adjacentNodeDetails.first;
                    int adjNodeDist = adjacentNodeDetails.second;
                    time++;
                    if((dist[currentNode] + adjNodeDist < dist[adjNode])){
                        if(distance.find({dist[adjNode],adjNode}) != distance.end())
                            distance.erase(distance.find({dist[adjNode],adjNode}));
                        dist[adjNode] = dist[currentNode] + adjNodeDist;
                        distance.insert({dist[adjNode],adjNode});
                        parent[adjNode] = currentNode;
                    }
                }
                distance.erase(distance.begin());
            }

            vector<int> path;
            if(parent[destination] == -1)
                return;
            int aux = destination;
            while(destination!=source){
                path.push_back(destination);
                destination = parent[destination];
            }
            path.push_back(source);
            reverse(path.begin(),path.end());
            routingTables[source]->setPath(aux,path);
            routingTables[source]->setDistance(aux,dist[aux]);
        }
    public:
        Network(int numberOfNodes): numberOfNodes(numberOfNodes){

                working = new bool[numberOfNodes];
                for(int i=0;i<numberOfNodes ;i++)
                    working[i] = true;
                routingTables = new RoutingTable*[numberOfNodes];
                for(int node =0 ; node< numberOfNodes; node++)
                    routingTables[node] = new RoutingTable(numberOfNodes);
        }

        void addEdge(int first,int second,int distance){
            adjacencyList[first].push_back({second,distance});
            adjacencyList[second].push_back({first,distance});
        }
        void alterWorkingNode(int node){
            working[node] = !working[node];
        }

        void updateRoutingTable(int node,int &time){
            for(int i=0;i<numberOfNodes;i++)
                ShortestDistance(node,i,time);
        }
        RoutingTable* getRoutingTable(int node){
            return routingTables[node];
        }
        void displayRoutingTable(int node){
            cout<<"Routing Table for "<<node<<endl;
            routingTables[node]->print();
        }
        
        ~Network(){
            for(int node = 0;node< numberOfNodes;node++){
                delete routingTables[node];
            }
            delete routingTables;
            delete working;
        }

};

int distanceVectorRouting(Network &network,int src,int dest){
    int time = 0;

    network.updateRoutingTable(src,time);
    RoutingTable *routingTable = network.getRoutingTable(src);
    vector<int>path = routingTable->getPath(dest);
    for(int node: path){
        cout<<"packet is at router number: "<<node<<endl;
    }
    return time;
}

int main(){
    int nodes,edges;
    cout<< "Enter nodes and edges"<<endl;
    cin>>nodes>>edges;
    Network network(nodes);
    while(edges--){
        int src,dest,cost;	//Building the routing table by initilaizing the network with given info
        cin>>src>>dest>>cost;
        network.addEdge(src,dest,cost);
    }
    
    int src,dest;	//Source and Destination we want to find the delay
    cin>>src>>dest;
    
    int DVR_Delay = distanceVectorRouting(network,src,dest);
    cout<<"End to end delay for Distance Vector Routing is: "<<DVR_Delay<<" time units"<<endl;
}
