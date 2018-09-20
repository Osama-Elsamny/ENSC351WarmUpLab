#include <fstream>
#include "trace.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>
using namespace std;

ofstream myOutputStream;
int traceCount = 0;
const int maxTrace = 10;
string buffer[maxTrace];
auto start = std::chrono::high_resolution_clock::now();

void trace_start(char* filename){
    myOutputStream.open(filename);
    if(myOutputStream.fail()){
        cout << "failed to open the file" << endl;
    }
    buffer[0] = "[";
    traceCount++;
}
void trace_event_start(char* name, char* categories, char* arguments){
    if(traceCount == maxTrace ){
        trace_flush();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto BeginTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    BeginTime = BeginTime/1000;
    string temp = "{\"name\": \"";
    temp.append(name);
    temp += "\", \"cat\": \"";
    temp.append(categories);
    temp += "\", \"ph\": \"";
    temp.append("B");
    temp += "\", \"pid\": \"";
    temp.append(to_string(getpid()));
    temp += "\", \"tid\": \"";
    temp.append("1");
    temp += "\", \"ts\": \"";
    temp.append(to_string(BeginTime));
    temp.append("\"}");
    buffer[traceCount] = temp;
    traceCount++;
}
void trace_event_end(char* arguments){
    if(traceCount == maxTrace ){
        trace_flush();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto endTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    endTime = endTime/1000;
    string temp = "{\"ph\": \"";
    temp.append("E");
    temp += "\", \"pid\": \"";
    temp.append(to_string(getpid()));
    temp += "\", \"tid\": \"";
    temp.append("1");
    temp += "\", \"ts\": \"";
    temp.append(to_string(endTime));
    temp.append("\"}");
    buffer[traceCount] = temp;
    traceCount++;
}
void trace_instant_global(char* name){
    if(traceCount == maxTrace ){
        trace_flush();
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto BeginTime = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
    BeginTime = BeginTime/1000;
    string temp = "{\"name\": \"";
    temp.append(name);
    temp += "\", \"s\": \"";
    temp.append("g");
    temp += "\", \"ph\": \"";
    temp.append("i");
    temp += "\", \"pid\": \"";
    temp.append(to_string(getpid()));
    temp += "\", \"tid\": \"";
    temp.append("1");
    temp += "\", \"ts\": \"";
    temp.append(to_string(BeginTime));
    temp.append("\"}");
    buffer[traceCount] = temp;
    traceCount++;
}
void trace_object_new(char* name, void* obj_pointer){
}
void trace_object_gone(char* name, void* obj_pointer){
}
void trace_counter(char* name, char* key,char* value){
}
void trace_flush(){
    print(1);
}
void trace_end(){
    print(0);
    myOutputStream.close();
}
void print(int function){
    int i = 0;
    while (i < traceCount){
        if (buffer[i] == "["){
            myOutputStream << buffer[i++] << endl;
        } else if ((i == traceCount -1) && (function == 0)){
            myOutputStream << buffer[i++] << endl << "]" << endl;
            break;
        } else {
            myOutputStream << buffer[i++] << "," << endl;
        }
    }
    traceCount = 0;
}