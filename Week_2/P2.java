class FooBar {
    private int n;
    private int turn;

    public FooBar(int n) {
        this.n = n;
        this.turn = 0;
    }

    public void foo(Runnable printFoo) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            synchronized(this) {
                while(turn != 0) {
                    wait();
                }
            }
            printFoo.run();
            synchronized(this) {
                turn = 1;
                notifyAll();
            }
        }
    }

    public void bar(Runnable printBar) throws InterruptedException {
        for (int i = 0; i < n; i++) {
            synchronized(this) {
                while(turn != 1) {
                    wait();
                }
            }
        	printBar.run();
            synchronized(this) {
                turn = 0;
                notifyAll();
            }
        }
    }
}