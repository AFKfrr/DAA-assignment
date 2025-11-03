BEGIN PROGRAM
// ----------- INPUT GRAPH ------------
INPUT V ← number of intersections (vertices)
CREATE TrafficNetwork city with V vertices
INPUT E ← number of roads (edges)
PRINT &quot;Enter edges (source destination weight):&quot;
FOR i = 1 TO E DO
INPUT u, v, w
city.addEdge(u, v, w) // add bidirectional road
END FOR
// ----------- HOSPITAL LOCATIONS ------------
INPUT numHospitals
PRINT &quot;Enter hospital locations:&quot;
FOR i = 1 TO numHospitals DO
INPUT hospitalNode
city.addHospital(hospitalNode)
END FOR
// ----------- AMBULANCE START ------------
INPUT ambulanceLocation

6

// ----------- INITIAL SHORTEST PATH ------------
CALL city.shortestPathToNearestHospital(ambulanceLocation) → (distance, path)
IF distance ≠ -1 THEN
PRINT &quot;Initial shortest travel time:&quot; distance
PRINT &quot;Path:&quot; path
ELSE
PRINT &quot;No hospital reachable&quot;
END IF
// ----------- REAL-TIME UPDATE ------------
PRINT &quot;Enter edge to update (u v newWeight):&quot;
INPUT u, v, newWeight
city.updateEdgeWeight(u, v, newWeight)
// ----------- RECOMPUTE PATH ------------
CALL city.shortestPathToNearestHospital(ambulanceLocation) → (newDistance,
newPath)
IF newDistance ≠ -1 THEN
PRINT &quot;After update shortest travel time:&quot; newDistance
PRINT &quot;Path:&quot; newPath
ELSE
PRINT &quot;No hospital reachable after update&quot;
END IF
END PROGRAM
// FUNCTIONS INSIDE TrafficNetwork CLASS
FUNCTION addEdge(u, v, w):
ADD (v, w) to adjacency list of u
ADD (u, w) to adjacency list of v // because graph is undirected
END FUNCTION

FUNCTION updateEdgeWeight(u, v, newWeight):
FOR each edge in adjacency list of u DO
IF edge.to == v THEN
edge.weight ← newWeight
END IF

7

END FOR
FOR each edge in adjacency list of v DO
IF edge.to == u THEN
edge.weight ← newWeight
END IF
END FOR
END FUNCTION

FUNCTION addHospital(node):
ADD node to hospital set
END FUNCTION

FUNCTION shortestPathToNearestHospital(source):
CREATE array dist[V], initialized with ∞
CREATE array parent[V], initialized with -1
SET dist[source] = 0
CREATE priority queue pq
INSERT (0, source) into pq
WHILE pq is not empty DO
(curDist, u) ← REMOVE node with smallest distance from pq
IF curDist &gt; dist[u] THEN
CONTINUE
END IF
IF u is in hospital set THEN
path ← empty list
v ← u
WHILE v ≠ -1 DO
ADD v to path
v ← parent[v]
END WHILE
REVERSE path
RETURN (dist[u], path)
END IF
FOR each neighbor v of u with weight w DO

8

IF dist[u] + w &lt; dist[v] THEN
dist[v] ← dist[u] + w
parent[v] ← u
INSERT (dist[v], v) into pq
END IF
END FOR
END WHILE
RETURN (-1, empty path) // No hospital reachable
END FUNCTION
