Language/Version: Python 3.10.12

Code is structured in a single file, where all different algorithms are built in its own function. There are also functions that handle certain
tasks such as calculating heuristics or tupling. 2 heuristics were made: Modified Displaced Tiles and Weighted Manhattan Distance. A* uses
Manhattan Distance and Greedy uses Displaced Tile heuristics for different implementations.

To run the code:
python3 expense_8_puzzle.py <start file> <goal file> <algorithm> <dump flag>

example, run A* with dumpfile: python3 expense_8_puzzle.py start.txt goal.txt A* true

-Available algorithms to run: bfs, dfs, A*, greedy, and dfs (Case Sensitive)
-Optional: use "true" for creating a dump file (without quotations). It will create a dumpfile showing all actions.
-Start and goal files must be named accordingly on command line, and placed correctly or results may not be accurate.
    -Additionally, the start and goal files must be formated correctly and cannot contain any duplicate numbers, or have any illegal start states.
    -NOTE: if the start or goal states have an illegal condition, the algorithm will continue until the queue is empty, which then no solution is found, returning an error

1 2 3
4 5 0
7 8 6
END OF FILE