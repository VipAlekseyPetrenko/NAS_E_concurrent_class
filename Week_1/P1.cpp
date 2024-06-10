class Foo {

private:
    mutex gMutex;
    condition_variable gCv;
    int currTurn = 1;

    void printsWrapper(function<void()> printFunction, int turn) {
        unique_lock<mutex> lock(gMutex);
        gCv.wait(lock, [this, turn]{ return turn == currTurn; });
        printFunction();
        ++currTurn;
        gCv.notify_all();
    }

public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        printsWrapper(printFirst, 1);
    }

    void second(function<void()> printSecond) {
        printsWrapper(printSecond, 2);
    }

    void third(function<void()> printThird) {
        printsWrapper(printThird, 3);
    }
};