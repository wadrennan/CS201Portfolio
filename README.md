# CS201Portfolio
--Will Drennan
--Video tutorial : https://www.youtube.com/watch?v=yDmBjiAGFjg&feature=share

# AI
--AI uses a depth first search
--- A DFS was chosen because it allows for an easier traversal of the graph using 
    any vertex as the source. This allows for an exhaustive check for winning moves and 
    defensive moves. The process of the algorithm also allows for easier checking of path lengths
    than a BFS would, since the DFS traverses a subtree fully before moving on to another subsection
    of the graph.
--The AI defends first, meaning it will block the other player from winning before looking for a move
  itself

# Graph Structure
--An adjacency list representation was used in this project. The reasoning behind this was that
  it is much more space efficient than an adjacency matrix, especially with the board sizes being 
  unpredictable. Although arguably harder to implement, the adjacency list was effective since the 
  vertices of the graph had the potential to be so dispersed and/or disconnected. There would be a large 
  time sacrifice if a matrix had to be iterated through for every check.
    
# Instructions
1. Make using the make file
2. Launch using the connectfour executable
3.Choose a mode using the number keys
4. Enter board width and height (minimum of 4 for each, no maximum)
5. Play your friends or the computer!

# Rules
1. To win, one player must connect four spots of their color diagonally, horizontally, or vertically
2. Pieces stack, they don't overlap
