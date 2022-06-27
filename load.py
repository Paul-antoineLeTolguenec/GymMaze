from CMaze import CMaze
import cv2
import time
import matplotlib.pyplot as plt
env=CMaze(filename="SNAKE", n_beams=0)
# env.yinit=0
# env.xgoal=100
# env.ygoal=100


state=env.reset_cv()
# traj=[[env.agent.x,env.agent.y]]
# while env.agent.y<195:
# 	state,reward,done,info=env.step([0,5])
# 	traj.append([env.agent.x,env.agent.y])
# while env.agent.x<195:
# 	state,reward,done,info=env.step([5,0])
# 	traj.append([env.agent.x,env.agent.y])


# # matplotlib
# fig,ax = plt.subplots()
# fig.suptitle('log')
# env.render_matplot(ax=ax,behaviours=traj)

# # show
# plt.show()


done=False
for k in range(100) : 
	action=[0,1]
	state,reward,done,info=env.step_cv(action)
	# print(reward)
	
print(state[0].shape)
plt.imshow( state[0]) 
plt.show()
# # # waits for user to press any key
# # # (this is necessary to avoid Python kernel form crashing)
# cv2.waitKey(0)
	# env.render(type="C")
#     env.render(type="C")
# print("TIME : "+str(time.time()-t0))
# for k in range(100):
#     action=[-1,1]
#     state,reward,done,info=env.step(action)

