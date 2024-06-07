class Foo {

private:
    mutex myMutex;
    int currIndex = 1;

    bool orderPrints(int number) {
        myMutex.lock();
        if (currIndex == number) {
            ++currIndex;
            return true;
        }
        myMutex.unlock();
        return false;
    }

public:
    Foo() {
    }

    void first(function<void()> printFirst) {
        while(!orderPrints(1));
        printFirst();
        myMutex.unlock();
    }

    void second(function<void()> printSecond) {
        while(!orderPrints(2));
        printSecond();
        myMutex.unlock();
    }

    void third(function<void()> printThird) {
        while(!orderPrints(3));
        printThird();
        myMutex.unlock();
    }
};