class Foo {

private:
    mutex gMutex;
    condition_variable cv;
    int currTurn;

    void printsWrapper(function<void()> printFunction, int turn) {
        {
            {
                unique_lock<mutex> lk(gMutex);
                cv.wait(lk, [this, turn]{ return (turn == currTurn); });
            }
            printFunction();
            {
                unique_lock<mutex> lk(gMutex);
                currTurn += 1;
            }
            cv.notify_all();
        }
    }

public:
    Foo() {
        this->currTurn = 1;
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