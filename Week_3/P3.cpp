class FizzBuzz {
private:
    int n;
    mutex m;
    condition_variable cv;
    int i = 1;

    void printWrapper(function<void()> printFunc, function<bool()> conditionFunc) {
        while(true) {
            {
                unique_lock lk(m);
                cv.wait(lk, [conditionFunc, this](){ return (conditionFunc() || (i > n)); });
                if(i > n) {
                    cv.notify_all();
                    return;
                }
            }
            printFunc();
            {
                unique_lock lk(m);
                i += 1;
            }
            cv.notify_all();
        }
    }

public:
    FizzBuzz(int n) {
        this->n = n;
    }

    void fizz(function<void()> printFizz) {
        auto condition = [&] { return ((i % 3) == 0) && ((i % 5) != 0); };
        printWrapper(printFizz, condition);
    }

    void buzz(function<void()> printBuzz) {
        auto condition = [&] { return ((i % 3) != 0) && ((i % 5) == 0); };
        printWrapper(printBuzz, condition);
    }

	void fizzbuzz(function<void()> printFizzBuzz) {
        auto condition = [&] { return ((i % 3) == 0) && ((i % 5) == 0); };
        printWrapper(printFizzBuzz, condition);
    }

    void number(function<void(int)> printNumber) {
        auto condition = [&] { return ((i % 3) != 0) && ((i % 5) != 0); };
        printWrapper([printNumber, this](){ return printNumber(i); }, condition);
    }
};