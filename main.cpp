#include "SinglyLinkedList.h"
#include <iostream>

using namespace TP;

int main (int argc, char** argv) {
    SinglyLinkedList<int> sll;
    sll.append(5);
    sll.append(10);
    sll.for_each_value([](int val) {
        printf("Node->data: %d\n", val);
    });
    return 0;
}
