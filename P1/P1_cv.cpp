class Foo {

private:
    mutex myMutex;
    condition_variable myCv;
    int currIndex = 1;

    void orderPrints(int number) {
        unique_lock<mutex> lock(myMutex);
        while(number != currIndex) {
            myCv.wait(lock);
        }
    }

public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        orderPrints(1);
        printFirst();
        ++currIndex;
        myCv.notify_all();
    }

    void second(function<void()> printSecond) {
        orderPrints(2);
        printSecond();
        ++currIndex;
        myCv.notify_all();
    }

    void third(function<void()> printThird) {
        orderPrints(3);
        printThird();
    }
};