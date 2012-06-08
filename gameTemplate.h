#include <stdio.h>
#include <stdlib.h>
#include "v8.h"
#include "vector.h"

using namespace v8;
using namespace std;

class gameGlobals{
	public:
		gameGlobals();
		Handle<ObjectTemplate> getTemplate();
		
		double elapsedTime;
		double currentTime;
	private:
		Handle<ObjectTemplate> global;
		Handle<ObjectTemplate> gameTime;
		static Handle<Value> log(const Arguments &args);
		static Handle<Value> geteTime(Local<String> property, const AccessorInfo& info);
		static Handle<Value> getcTime(Local<String> property, const AccessorInfo& info);
};