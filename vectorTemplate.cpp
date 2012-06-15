#include "vectorTemplate.h"

using namespace vectorTemplate;

Handle<ObjectTemplate> vectorTemplate::vectorObjTemp;
int vectorTemplate::isSetup;


void vectorTemplate::vectorTemplateSetUp(Handle<ObjectTemplate> global){
	if(isSetup == 0){
		vectorObjTemp = ObjectTemplate::New();
		
		vectorObjTemp->SetCallAsFunctionHandler(callAsFuncHandler);
		global->Set("Vector", vectorObjTemp);
		vectorObjTemp->Set("add", FunctionTemplate::New(addVectors));
		vectorObjTemp->Set("sub", FunctionTemplate::New(subVectors));
		vectorObjTemp->Set("subtract", FunctionTemplate::New(subVectors));
		vectorObjTemp->Set("dist", FunctionTemplate::New(distanceVectors));
		vectorObjTemp->Set("mag", FunctionTemplate::New(magVectors));
		isSetup = 1;
	}
	
};

Handle<Value> vectorTemplate::callAsFuncHandler(const Arguments &args){
	HandleScope handle_scope;
	
	vector<double> *instVect = new vector<double>(0.0, 0.0);
	
	if(args.Length() == 2){
		if(args[0]->IsNumber() && args[1]->IsNumber()){
			instVect->x = (args[0]->ToNumber())->Value();
			instVect->y = (args[1]->ToNumber())->Value();
		}
	}
	return handle_scope.Close(makeVectorObject(instVect));
	
}
Handle<ObjectTemplate> vectorTemplate::makeVectorObjectTemplate(vector<double>* instVect, PropertyAttribute attributes){
	HandleScope scope;
	Handle<External> data = External::New(reinterpret_cast<void *>(instVect));
	
	Handle<ObjectTemplate> vectOjbTempInst = ObjectTemplate::New();
	vectOjbTempInst->Set("add", FunctionTemplate::New(addVectors));
	vectOjbTempInst->Set("sub", FunctionTemplate::New(subVectors));
	vectOjbTempInst->Set("subtract", FunctionTemplate::New(subVectors));
	vectOjbTempInst->Set("dist", FunctionTemplate::New(distanceVectors));
	vectOjbTempInst->Set("mag", FunctionTemplate::New(magVectors));
	vectOjbTempInst->SetAccessor(String::New("x"), getVectorX, setVectorX, data, DEFAULT, attributes);
	vectOjbTempInst->SetAccessor(String::New("y"), getVectorY, setVectorY, data, DEFAULT, attributes);
	
	return scope.Close(vectOjbTempInst);
}

//Used to make a new vector object
Handle<Object> vectorTemplate::makeVectorObject(vector<double>* instVect){
	HandleScope scope;
	
	//This is the prototype for the object
	Handle<Object> objProto = vectorObjTemp->NewInstance();
	//This is the vector data that will be associated with this object
	Handle<External> data = External::New(reinterpret_cast<void *>(instVect));
	
	Handle<ObjectTemplate> vectOjbTempInst = ObjectTemplate::New();
	
	//Set up the setters
	vectOjbTempInst->SetAccessor(String::New("x"), getVectorX, setVectorX, data);
	vectOjbTempInst->SetAccessor(String::New("y"), getVectorY, setVectorY, data);
	
	Handle<Object> obj = vectOjbTempInst->NewInstance();
	obj->SetPrototype(objProto);
	
	return scope.Close(obj);
}
//Returns a vector from a Handle<Object>
vector<double> vectorTemplate::getVectorFromObject(Handle<Object> obj){
	vector<double> vect(obj->Get(String::New("x"))->ToNumber()->Value(), obj->Get(String::New("y"))->ToNumber()->Value());
	return vect;
}
//Getters and Setters for x and y
Handle<Value> vectorTemplate::getVectorX(Local<String> property, const AccessorInfo &info){
	vector<double> *vect = reinterpret_cast<vector<double> *>(External::Unwrap(info.Data()));
	return Number::New(vect->x);	
}
void vectorTemplate::setVectorX(Local<String> property, Local<Value> value, const AccessorInfo &info){
	vector<double> *vect = reinterpret_cast<vector<double> *>(External::Unwrap(info.Data()));
	if(value->IsNumber()){
		vect->x = value->ToNumber()->Value();
	}
}
Handle<Value> vectorTemplate::getVectorY(Local<String> property, const AccessorInfo &info){
	vector<double> *vect = reinterpret_cast<vector<double> *>(External::Unwrap(info.Data()));
	return Number::New(vect->y);	
}
void vectorTemplate::setVectorY(Local<String> property, Local<Value> value, const AccessorInfo &info){
	vector<double> *vect = reinterpret_cast<vector<double> *>(External::Unwrap(info.Data()));
	if(value->IsNumber()){
		vect->y = value->ToNumber()->Value();
	}
}

//Add vectors
//vector.add(vector)
Handle<Value> vectorTemplate::addVectors(const Arguments &args){
	HandleScope scope;
	if(args.Length() == 1){
		if(args[0]->IsObject()){
			//Get the object
			Handle<Object> sVect = args.This();
			Handle<Object> oVect = args[0]->ToObject();
			//Get the vectors
			vector<double> sV = getVectorFromObject(sVect);
			vector<double> oV = getVectorFromObject(oVect);
			
			vector<double> add = sV + oV; //Add the vectors
			vector<double> *pointAns = new vector<double>(add.x, add.y); //Make it a pointer
			return scope.Close(makeVectorObject(pointAns));
			
		}else{
			return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("Need to be an object"))));
		}
	}else{
		return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("Needs one argument"))));
	}
}
//subtract the vectors
//vector.sub(vector)
Handle<Value> vectorTemplate::subVectors(const Arguments &args){
	HandleScope scope;
	if(args.Length() == 1){
		if(args[0]->IsObject()){
			//Get the object
			Handle<Object> sVect = args.This();
			Handle<Object> oVect = args[0]->ToObject();
			//Get the vectors
			vector<double> sV = getVectorFromObject(sVect);
			vector<double> oV = getVectorFromObject(oVect);
			
			vector<double> add = sV - oV; //Add the vectors
			vector<double> *pointAns = new vector<double>(add.x, add.y); //Make it a pointer
			return scope.Close(makeVectorObject(pointAns));
			
		}else{
			return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("Need to be an object"))));
		}
	}else{
		return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("Needs one argument"))));
	}
}
Handle<Value> vectorTemplate::distanceVectors(const Arguments &args){
	HandleScope scope;
	if(args.Length() == 1){
		if(args[0]->IsObject()){
			//Get the object
			Handle<Object> sVect = args.This();
			Handle<Object> oVect = args[0]->ToObject();
			//Get the vectors
			vector<double> sV = getVectorFromObject(sVect);
			vector<double> oV = getVectorFromObject(oVect);
			
			double dist = sV.distance(oV); //Add the vectors
			return scope.Close(Number::New(dist));
			
		}else{
			return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("Need to be an object"))));
		}
	}else{
		return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("Needs one argument"))));
	}
}
Handle<Value> vectorTemplate::magVectors(const Arguments &args){
	HandleScope scope;
	if(args.Length() == 0){
		//Get the object
		Handle<Object> sVect = args.This();
		//Get the vectors
		vector<double> sV = getVectorFromObject(sVect);
		
		double mag = sV.mag(); //Find the magnitude of the vector
		return scope.Close(Number::New(mag));
	}else{
		return scope.Close(ThrowException(Exception::ReferenceError(v8::String::New("vector.mag doesn't need any arguments"))));
	}
}