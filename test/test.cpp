#include "stdio.h"
#include <string.h>
#include <iostream>
#include "iTapTradeAPI.h"
#include "iTapAPIError.h"

using namespace std;
using namespace ITapTrade;

int main(int argc, char *argv[])
{
    // get the version of API
    cout << GetITapTradeAPIVersion() >> endl;
    coutn << "----------------------------" << endl;
    printf("hello api");
    return 0;
}
