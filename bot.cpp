#include "bot.h"

using namespace v8;
using namespace std;
using namespace vectorTemplate;

jsbot *selfBot;

double abs(double a){
	if(a<0){
		return -1*a;
	}
	return a;
}

jsbot::jsbot(){
	pos = vector<double>(50,50);
	vel = vector<double>(0,0);
	force = vector<double>(0,0);
}
jsbot::jsbot(string srca){
	pos = vector<double>(50,50);
	vel = vector<double>(0,0);
	force = vector<double>(0,0);
	src = srca;
}

void jsbot::init(Handle<ObjectTemplate> global){
	
	//read file and get the js source
	char *jsSource;
	
	FILE  *jsSourceFile = fopen(src.c_str(), "r");
	fseek (jsSourceFile , 0, SEEK_END);
	long fileSize = ftell (jsSourceFile);
	rewind(jsSourceFile);
	
	jsSource = (char*)malloc(sizeof(char)*fileSize);
	if(jsSource == NULL){printf("error"); exit(2);}
	
	long resultFile = fread (jsSource,1,fileSize,jsSourceFile);
	if (resultFile != fileSize) {fputs ("Reading error",stderr); exit (3);}
	fclose(jsSourceFile);
	
	//Get the name from the file name
	size_t startPos = src.rfind("/");
	name = src;
	if(startPos != string::npos){
		name.replace(0, startPos, "");
	}
	
	size_t endPos = src.rfind(".");
	if(endPos != string::npos){
		name.replace(endPos, endPos+3, "");
	}
	
	//set up the jsbot so it can be accessed through javascript
	setupBotTemplate(global);
	
	//v8 stuff
	context = Context::New(NULL, global);
	//HandleScope scope;
	
	Local<String> source = String::New(jsSource, fileSize);
	if(source.IsEmpty()){
		printf("Error in source to string\n");
		return ;
	}
	Context::Scope contextScope(context);
	
	Local<Script> script = Script::Compile(source);
	if(script.IsEmpty()){
		printf("Error in compiling js source");
	}
	TryCatch tryCatch;
	
	Local<Value> result = script->Run();
	if(result.IsEmpty()){
		String::Utf8Value error(tryCatch.Exception());
		printf("%s had an error\n %s \n\n", name.c_str(), *error);
		exit(3);
	}
	
	free(jsSource);
	
	printf("%s initiated\n", name.c_str());
}

void jsbot::update(){
	HandleScope scope;
	
	Context::Scope contextScope(context);
	
	selfBot = this;
	
	//Static and kenetic friction
	vector<double> sFriction(20,20);
	vector<double> kFriction(20,20);
	if(vel.mag()<.01){
		kFriction = kFriction*0;
		
		if(abs(force.x) < sFriction.x){
			sFriction.x = -force.x;
		}else if(force.x>0){
			sFriction.x = sFriction.x *-1;
		}
		if(abs(force.y) < sFriction.y){
			sFriction.y = -force.y;
		}else if(force.y>0){
			sFriction.y = sFriction.y *-1;
		}
	}else{
		sFriction = sFriction*0;
	}
	
	//Calculate positions assuming constant forc
	pos = pos + vel*gameGlobals::elapsedTime + (kFriction*vel.sign()*-1 + sFriction + force)*gameGlobals::elapsedTime*gameGlobals::elapsedTime*.5;
	vel = vel + (kFriction*vel.sign()*-1 + sFriction + force)*gameGlobals::elapsedTime;
	
	Handle<Object> glob = context->Global();
	if(glob->Has(String::New("main"))){
		Handle<Value> mainVal = glob->Get(String::New("main"));
		Handle<Object> mainFun = mainVal->ToObject();
		mainFun->CallAsFunction(glob, 0 ,NULL);
	}
}

void jsbot::setupBotTemplate(Handle<ObjectTemplate> global){
	bot = Persistent<ObjectTemplate>::New(ObjectTemplate::New());
	
	selfBot = this; 
	
	global->Set(String::New("bot"), bot);
	bot->Set(String::New("pos"), makeVectorObjectTemplate(&selfBot->pos, ReadOnly), ReadOnly);
	bot->Set(String::New("vel"), makeVectorObjectTemplate(&selfBot->vel, ReadOnly), ReadOnly);
	bot->Set(String::New("force"), makeVectorObjectTemplate(&selfBot->force, None), None);
	//bot.scan(ang, width)
	Handle<External> botPointer = External::New(this);
	
	bot->Set(String::New("scan"), FunctionTemplate::New(botScanCallback, botPointer));
	bot->Set(String::New("shoot"), FunctionTemplate::New(botShootcallback, botPointer));
};

Handle<Value> jsbot::botScanCallback(const Arguments &args){
	HandleScope scope;
	jsbot *botPointer = reinterpret_cast<jsbot*>(External::Unwrap(args.Data()));
	if(args.Length() == 2){
		if(args[0]->IsNumber() && args[1]->IsNumber()){
			double ang = args[0]->ToNumber()->Value();
			double width = args[1]->ToNumber()->Value();
			
			double dist = botPointer->game->scan(ang, width, botPointer);
			return Number::New(dist);
		}
	}else{
		return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("bot.scan needs two arguments"))));
	}
};

Handle<Value> jsbot::botShootcallback(const Arguments &args){
	HandleScope scope;
	jsbot *botPointer = reinterpret_cast<jsbot*>(External::Unwrap(args.Data()));
	if(args.Length() == 2){
		if(args[0]->IsNumber() && args[1]->IsNumber()){
			double ang = args[0]->ToNumber()->Value();
			double dist = args[1]->ToNumber()->Value();
			
			double temp = botPointer->game->shoot(ang, dist, botPointer);
			//1 if bullet shot, 0 if there was already a bullet, -1 unknown error
			return Number::New(temp);
		}
	}else{
		return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("bot.shoot needs two arguments"))));
	}
};

jsbot::~jsbot(){
	context.Dispose();
	bot.Dispose();
}