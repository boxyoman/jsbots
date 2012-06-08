#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
#include "v8.h"
#include "vector.h"

#ifndef _BOT_H_
#define _BOT_H_

using namespace v8;
using namespace std;

class gamePrototype{
	public:
		void shoot(double ang, double distance, void* bot);
		double scan(double ang, double width, void* bot);
};

class jsbot{
	public:
		vector<double> pos;
		vector<double> vel;
		jsbot();
		jsbot(string);
		~jsbot();
		
		Local<Script> script;
		
		string name;
		string src;
		
		void init(Handle<ObjectTemplate>);

	private:
		Persistent<Context> context;
		Local<ObjectTemplate> bot;
		void setupBotTemplate(Handle<ObjectTemplate>);
		
};

#endif