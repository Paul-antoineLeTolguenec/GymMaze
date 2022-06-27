from CMaze import CMaze




env=CMaze(filename="hard")

env.reset()

action=[5,5]
for k in range(500):
    state,reward,done,info=env.step(action)
    # if k>=45:
    #     action=[10,-5]
    # if k>90:
    #     print(k)
    #     break

    env.render("C")

env.render("C")