class Foo {

    private Object lock;
    private int currTurn;

    private void printsWrapper(Runnable printFunction, int turn) throws InterruptedException {
        synchronized(lock) {
            while(currTurn != turn) {
                lock.wait();
            }
            printFunction.run();
            ++currTurn;
            lock.notifyAll();
        }
    }

    public Foo() {
        this.lock = new Object();
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