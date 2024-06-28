class FooBar {
private:
    int n;
    mutex gMutex;
    condition_variable cv;
    int turn;

public:
    FooBar(int n) {
        this->n = n;
        this->turn = 0;
    }

    void foo(function<void()> printFoo) {
        for (int i = 0; i < n; i++) {
            {
                unique_lock lk(gMutex);
                cv.wait(lk, [this](){return turn == 0;});
            }
        	printFoo();
            {
                unique_lock lk(gMutex);
                turn = 1;
            }
            cv.notify_all();
        }
    }

    void bar(function<void()> printBar) {
        for (int i = 0; i < n; i++) {
            {
                unique_lock lk(gMutex);
                cv.wait(lk, [this](){return turn == 1;});
            }
        	printBar();
            {
                unique_lock lk(gMutex);
                turn = 0;
            }
            cv.notify_all();
        }
    }
};