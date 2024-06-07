class Foo {

    private Object lock = new Object();
    volatile private int currIndex = 1;

    public Foo() {
        
    }

    public void first(Runnable printFirst) throws InterruptedException {
        synchronized(lock) {
            printFirst.run();
            ++currIndex;
            lock.notifyAll();
        }
    }

    public void second(Runnable printSecond) throws InterruptedException {
        synchronized(lock) {
            while(currIndex != 2) {
                lock.wait();
            }
            printSecond.run();
            ++currIndex;
            lock.notifyAll();
        }
    }

    public void third(Runnable printThird) throws InterruptedException {
        synchronized(lock) {
            while(currIndex != 3) {
                lock.wait();
            }
            printThird.run();
        }
    }
}