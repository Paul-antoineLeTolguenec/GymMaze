#include "Agent.h"
#include "Maze.h"
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
#include <cstdio>
#include <stdlib.h>


using namespace std;

Agent::Agent(Maze *maze, float xinit, float yinit, float dt, float vmax):maze(maze),x(xinit),y(yinit),dt(dt),vmax(vmax){
	beams=linspace(0.0, 2*M_PI, 5);
}


void Agent::move(vector<float>action){
	// velocity
	xdot+=dt*(float)action[0];
	ydot+=dt*(float)action[1];
	xdot=min(vmax,xdot);
	ydot=min(vmax,ydot);
	float xnew=x+dt*xdot;
	float ynew=y+dt*ydot;
	// // norm action
	// float amax=1;
	// // acceleration
	// action[0]=min(amax,action[0]);
	// // thetap
	// action[1]=min(amax,action[1]);
	// action[1]=max(-amax,action[1]);
	// // velocity
	// v+=dt*action[0];
	// theta+=dt*action[1];
	// // check
	// v=max(v,vmax);
	// theta=fmod(theta,2*M_PI);
	// // new position 
	// float xnew=x+dt*v*cos(theta);
	// float ynew=y+dt*v*sin(theta);
	// check Maze frontier
	if (xnew<r)
		{xnew=r;
		xdot=0;}
	else if (xnew>maze->width-r)
		{xnew=maze->width-r;
		xdot=0;}
	if (ynew<r)
		{ynew=r;
		ydot=0;}
	else if (ynew>maze->height-r)
		{ynew=maze->height-r;
		ydot=0;}
	// check blocks
	for(Block b : maze->block_list){
		vector<float> start{x,y};
		vector<float> end{xnew,ynew};
		tuple<bool,vector<float>,int> intersection=b.intersect(start,end,r);
		if(get<0>(intersection)){
			// cases already against the block 
			// sides
			if(get<2>(intersection)==1 )
				{xnew=get<1>(intersection)[0]-r;
				 xdot=0;}
			else if(get<2>(intersection)==2 )
				{xnew=get<1>(intersection)[0]+r;
				 xdot=0;}
			// top and bottom
			else if(get<2>(intersection)==3 )
				{ynew=get<1>(intersection)[1]-r;
				 ydot=0;}
			else if(get<2>(intersection)==4 )
				{ynew=get<1>(intersection)[1]+r;
				 ydot=0;}
			}}
	x=xnew;
	y=ynew;
}

vector<float> Agent::lidar_observation(){
	vector<float> d_beams;
	float d_beam=0;
	float d=0;
	vector<float> start{x,y};
	vector<float> end;
	tuple<bool,vector<float>,int> intersection;
	vector<Block> blocks=maze->block_list;
	// add maze
	blocks.push_back(Block(0,0,(float)maze->width,(float)maze->height));
	for (float theta : beams)
	{	d_beam=0;
		end={x + lidar_range * cos(theta), y + lidar_range*sin(theta)};
		// Blocks
		for (Block block : blocks)
		{
			intersection = block.intersect(start, end,r);
			d=dist(start,get<1>(intersection));
			if(get<0>(intersection) && (d_beam==0||d<d_beam)){
				d_beam=d;}
		}

		d_beams.push_back(d_beam);
	}
	

	return d_beams;}