#include "controller/controller.h"
#include "common.h"

int main(int argc, char** argv)
{
    LOG("Start");
    Controller controller;
    controller.start();
    LOG("Finish");
    return 0;
}
