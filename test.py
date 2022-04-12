from build.Game import Maze
from build.Game import LineIntersection
maze=Maze(xinit=40,yinit=80)

# add_block
maze.add_block(30,30,30,30)
# maze.add_block(10,0,10,90)
# maze.add_block(10,80,80,10)
# maze.add_block(30,60,70,10)
# maze.add_block(10,40,80,10)
# maze.add_block(30,20,70,10)



# # reset()
state=maze.reset()
# print(state)
# maze.render()
# state,reward,done,info=maze.step([55,40])
# maze.render()
# print(state)

# state, reward,done,info=maze.step([55,70])
# maze.render()
# print(state)

# maze.render()
# print(state)
for k in range(4000):
    action=[0,-100]
    state,reward,done,info=maze.step(action)
    # print(state)
    # maze.render()

# state=maze.reset()
print(state)

# print(state)
# # # step
# state,reward,done,info=maze.step([1,2,3])
# print(state)

# # render
maze.render()
# maze.render()
# print(l)
# print(type(l))
# print(type(l[0]))
# print(b.get_x())

# check line
# print(LineIntersection([2,2],[0,5],[3,5],[3,7]))