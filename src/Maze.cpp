#include "Maze.h"
#include "Agent.h"
#include "Block.h"
#include "utils.h"
#include <cstdlib>
#include <unistd.h> // for usleep
#include <math.h>
#include <bits/stdc++.h>
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include "vibes.h"


using namespace std;

Maze::Maze(float xinit, float yinit, float xgoal, float ygoal, int time_horizon ): xinit(xinit), yinit(yinit), xgoal(xgoal), ygoal(ygoal), time_horizon(time_horizon){
	agent=new Agent(this,xinit,yinit,dt,vmax);
	}
vector<float> Maze::reset(){
	// init agent 
	agent->x=xinit;
	agent->y=yinit;
	// state
	vector<float> state;
	// position
	state.push_back(agent->x);
	state.push_back(agent->y);
	state.push_back(agent->xdot);
	state.push_back(agent->ydot);
	// lidar
	vector<float> lidar= agent->lidar_observation();
	for(float beam : lidar){state.push_back(beam);}
	// time_horizon
	time=0;
	// lidar
	// TODO
	return state;

}

tuple<vector<float>,float,bool,string> Maze::step(const vector<float> &action){
	// update time
	time+=1;
	// move agent
	agent->move(action);
	// state
	vector<float> state;
	// position
	state.push_back(agent->x);
	state.push_back(agent->y);
	state.push_back(agent->xdot);
	state.push_back(agent->ydot);
	// lidar
	vector<float> lidar= agent->lidar_observation();
	for(float beam : lidar){state.push_back(beam);}

	// reward
	
	float distance=sqrt(pow(xgoal-agent->x,2)+pow(ygoal-agent->y,2));
	float reward=-0.01;
	if (distance<treshold)
		{reward+=1000.0;}
	
	// done
	bool done=false;
	if (time>=time_horizon || distance<treshold)
		{done=true;}
	


	// info
	string info="nothing";

	tuple<vector<float>,float,bool,string> output(state,reward,done,info);
	return output;
}

void Maze::add_block(float x, float y, float w, float h){
	block_list.push_back(Block(x,y,w,h));
}

void Maze::render(){
	if (!figure)
	{	vibes::beginDrawing();
		vibes::newFigure("Maze");
		vibes::setFigureProperties("Maze", vibesParams("x",200, "y", 200, "width", 400, "height", 400));
		vibes::axisLimits(0., width, 0., height);
		figure=true;}
		
	vibes::clearFigure("Maze");
	// Agent
	vibes::drawCircle(agent->x, agent->y, agent->r, "red[blue]", vibesParams("figure", "Maze"));
	// goal
	vibes::drawCircle(xgoal, ygoal, agent->r, "red[green]", vibesParams("figure", "Maze"));
	// Blocks
	for (Block block : block_list)
	{
		vibes::drawBox(block.x,block.x+block.w,block.y,block.y+block.h, "black[black]", vibesParams("figure", "Maze"));
	}
	vector<float> lidar= agent->lidar_observation();
	for (int i = 0; i < agent->n_beams; i++)
	{	vector<double> x={agent->x,agent->x+lidar[i]*cos(agent->beams[i])};
		vector<double> y={agent->y,agent->y+lidar[i]*sin(agent->beams[i])};
		vibes::drawLine(x,y,"red[red]", vibesParams("figure", "Maze"));
	}
	
	usleep(dt * 500000.); 
	
}