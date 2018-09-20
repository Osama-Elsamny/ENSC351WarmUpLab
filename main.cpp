#include <fstream>
#include "trace.h"
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <chrono>
using namespace std;
int main(void){
    char filenameformUser[100] = "";

    cout << "Welcome to the testing file" << endl;
    /*--------------------------------------------------------------------*/
    cout << "Testing if the porgram can open a file correctly" << endl;
    cout << "Ask the user for a file name" << endl;
    cin >> filenameformUser;
    trace_start(filenameformUser);
    /*--------------------------------------------------------------------*/

    /**
     * the following test case is for testing the trace_event_start function
     * trying to see if the time will show up in the test case
    */
    for(int i = 0; i < 20; i++){
        trace_event_start("task 1", "catasdf", "shit for now");
        trace_event_end("shit for now");
    }
    
    trace_end();
    return 0;
}