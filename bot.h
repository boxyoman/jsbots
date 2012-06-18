#ifndef _BOT_H_
#define _BOT_H_

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <math.h>
#include "v8.h"
#include "vector.h"
#include "vectorTemplate.h"
#include "gameTemplate.h"

using namespace v8;
using namespace std;

class gamePrototype{
	public:
		virtual int shoot(double ang, double distance, void* bot){
			return 0;
		}
		virtual double scan(double ang, double width, void* bot){
			return 0;
		};
};

class jsbot{
	public:
		vector<double> pos;
		vector<double> vel;
		vector<double> force;
		double health;
		
		jsbot();
		jsbot(string);
		~jsbot();
		
		gamePrototype *game;
		
		void update();
		
		string name;
		string src;
		
		static Handle<Value> botScanCallback(const Arguments &args);
		static Handle<Value> botShootcallback(const Arguments &args);
		static Handle<Value> getHealth(Local<String> property, const AccessorInfo &info);
		void init(Handle<ObjectTemplate>);
		
	private:
		Persistent<Context> context;
		Persistent<ObjectTemplate> bot;
		
		void setupBotTemplate(Handle<ObjectTemplate>);
		
};

#endif