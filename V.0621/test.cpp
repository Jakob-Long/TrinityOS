//////////////////////////////////////////
// Module name: test.cpp                //
//                                      //
// Date created: 05/12/21               //
// Author:       Jakob Long             //
//                                      //
// Copright (c) Jakob Long, 2021 - 2023 //
//////////////////////////////////////////

extern "C" int caller();
class Desktop {
    public:
        int a;
        void DEMO();
};

void Desktop::DEMO() {
    // Code here
}

int caller() {
    Desktop run;
    run.a = 5;
    return run.a;
}