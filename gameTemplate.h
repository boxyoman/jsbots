#ifndef _GAMETEMPLATE_H_
#define _GAMETEMPLATE_H_

#include <stdio.h>
#include <stdlib.h>
#include "v8.h"
#include "vector.h"
#include "vectorTemplate.h"

using namespace v8;
using namespace std;

namespace gameGlobals{
	extern Handle<ObjectTemplate> global;
	extern Handle<ObjectTemplate> gameTime;
	
	extern double elapsedTime;
	extern double currentTime;
	
	void setUpGolbals();
	

	
	static Handle<Value> log(const Arguments &args);
	static Handle<Value> geteTime(Local<String> property, const AccessorInfo& info);
	static Handle<Value> getcTime(Local<String> property, const AccessorInfo& info);
};


#endif