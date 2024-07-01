class Foo {
    int currTurn;

    private void printsWrapper(Runnable printFunction, int turn) throws InterruptedException {
        synchronized(this) {
            while(turn != currTurn) {
                wait();
            }
        }
        printFunction.run();
        synchronized(this) {
            currTurn += 1;
            notifyAll();
        }
    }

    public Foo() {
        this.currTurn = 1;
    }

    public void first(Runnable printFirst) throws InterruptedException {
        printsWrapper(printFirst, 1);
    }

    public void second(Runnable printSecond) throws InterruptedException {
        printsWrapper(printSecond, 2);
    }

    public void third(Runnable printThird) throws InterruptedException {
        printsWrapper(printThird, 3);
    }
}