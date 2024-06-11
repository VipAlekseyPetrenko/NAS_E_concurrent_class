class Foo {

    private Object lock = new Object();
    private int currTurn = 1;
    Boolean isPrinting = false; 

    private void printsWrapper(Runnable printFunction, int turn) throws InterruptedException {
        synchronized(lock) {
            while((turn != currTurn) && !isPrinting) {
                lock.wait();
            }
            isPrinting = true;
        }
        printFunction.run();
        synchronized(lock) {
            ++currTurn;
            isPrinting = false;
            lock.notifyAll();
        }
    }

    public Foo() {
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