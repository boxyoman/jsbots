#ifndef _VECTORTEMPLATE_H_
#define _VECTORTEMPLATE_H_

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "v8.h"

using namespace v8;
using namespace std;

namespace vectorTemplate{
	extern Handle<ObjectTemplate> vectorObjTemp;
	extern int isSetup;

	void vectorTemplateSetUp(Handle<ObjectTemplate> global);
	Handle<Value> callAsFuncHandler(const Arguments &args);
	
	Handle<Object> makeVectorObject(vector<double>*);
	
	vector<double> getVectorFromObject(Handle<Object>);
	
	Handle<Value> getVectorX(Local<String> property, const AccessorInfo &info);
	void setVectorX(Local<String> property, Local<Value> value, const AccessorInfo &info);
	Handle<Value> getVectorY(Local<String> property, const AccessorInfo &info);
	void setVectorY(Local<String> property, Local<Value> value, const AccessorInfo &info);
	
	Handle<Value> addVectors(const Arguments &args);
	Handle<Value> subVectors(const Arguments &args);
};

#endif