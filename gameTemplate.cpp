#include "gameTemplate.h"

using namespace vectorTemplate;
using namespace gameGlobals;

HandleScope scope;
Handle<ObjectTemplate> gameGlobals::global;
Handle<ObjectTemplate> gameGlobals::gameTime;
double gameGlobals::elapsedTime;
double gameGlobals::currentTime;

void gameGlobals::setUpGolbals(void){
	global = ObjectTemplate::New();
	global->Set(String::New("log"), FunctionTemplate::New(log), ReadOnly);
	gameTime = ObjectTemplate::New();
	global->Set(String::New("gameTime"), gameTime, ReadOnly);
	gameTime->SetAccessor(String::New("elapsedTime"), geteTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	gameTime->SetAccessor(String::New("eTime"), geteTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	gameTime->SetAccessor(String::New("currentTime"), getcTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	gameTime->SetAccessor(String::New("cTime"), getcTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	
	vectorTemplateSetUp(global);
	elapsedTime = 0;
	currentTime = 0;
}

Handle<Value> gameGlobals::getcTime(Local<String> property, const AccessorInfo& info){
	return Number::New(currentTime);
}
Handle<Value> gameGlobals::geteTime(Local<String> property, const AccessorInfo& info){
	return Number::New(elapsedTime);
}

Handle<Value> gameGlobals::log(const Arguments &args){
	if(args.Length() == 1){
		String::Utf8Value val(args[0]);
		printf("%s\n", *val);
	}else{
		return ThrowException(Exception::ReferenceError(v8::String::New("One argument needed")));
	}
}

/*
static gameGlobals *self;
gameGlobals::gameGlobals(){
	self = this;
	global = ObjectTemplate::New();
	global->Set(String::New("log"), FunctionTemplate::New(log), ReadOnly);
	gameTime = ObjectTemplate::New();
	global->Set(String::New("gameTime"), gameTime, ReadOnly);
	gameTime->SetAccessor(String::New("elapsedTime"), geteTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	gameTime->SetAccessor(String::New("eTime"), geteTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	gameTime->SetAccessor(String::New("currentTime"), getcTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	gameTime->SetAccessor(String::New("cTime"), getcTime, 0, Handle<Value>(), DEFAULT, ReadOnly);
	
	vectorTemplateSetUp(global);
	
	elapsedTime = 10;
	currentTime = 0;
};

Handle<ObjectTemplate> gameGlobals::getTemplate(){
	return global;
};

Handle<Value> gameGlobals::getcTime(Local<String> property, const AccessorInfo& info){
	return Number::New(self->currentTime);
}
Handle<Value> gameGlobals::geteTime(Local<String> property, const AccessorInfo& info){
	return Number::New(self->elapsedTime);
}

Handle<Value> gameGlobals::log(const Arguments &args){
	if(args.Length() == 1){
		String::Utf8Value val(args[0]);
		printf("%s\n", *val);
	}else{
		printf("Wrong number of arguments");
	}
}*/