#include "bot.h"

using namespace v8;
using namespace std;

jsbot::jsbot(){
	pos = vector<double>(50,50);
	vel = vector<double>(0,0);
}
jsbot::jsbot(string srca){
	pos = vector<double>(50,50);
	vel = vector<double>(0,0);
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
	HandleScope scope;
	
	Local<String> source = String::New(jsSource, fileSize);
	if(source.IsEmpty()){
		printf("Error in source to string\n");
		return ;
	}
	Context::Scope contextScope(context);
	
	script = Script::Compile(source);
	if(script.IsEmpty()){
		printf("Error in compiling js source");
	}
	TryCatch tryCatch;
	
	Local<Value> result = script->Run();
	if(result.IsEmpty()){
		String::Utf8Value error(tryCatch.Exception());
		printf("\n%s \n", *error);
	}
	
	free(jsSource);
	
	printf("%s initiated\n", name.c_str());
}

void jsbot::setupBotTemplate(Handle<ObjectTemplate> global){
	bot = ObjectTemplate::New();
	global->Set(String::New("bot"), bot, ReadOnly);
	
}

jsbot::~jsbot(){
	context.Dispose();
}