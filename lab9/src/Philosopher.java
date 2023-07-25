
/**
 *
 * @author h8saini
 */

package coe628.lab9;

import static coe628.lab9.Main.mutex;
import static coe628.lab9.Main.phil;
import static coe628.lab9.Main.RIGHT;
import static coe628.lab9.Main.LEFT;


class Philosopher extends Thread {

    private final int philNum;
    private final int leftForkNum;
    private final int rightForkNum;
    private static int numFinished = 0;

    private enum phil_state {
        THINKING, HUNGRY, EATING
    }
    private phil_state state; // phil_state state[N] 

    private final Semaphore s; // One per philosopher, all 0

    public Philosopher(int i) {
        philNum = i + 1;
        state = phil_state.THINKING; // Default state
        s = new Semaphore(0);
        leftForkNum = RIGHT(i) + 1;
        rightForkNum = i + 1;
    }

    public void get_forks(int i) {
        phil[i].state = phil_state.HUNGRY;
        System.out.println("Fork " + rightForkNum + " taken by Philosopher " + philNum);
        while (phil[i].state == phil_state.HUNGRY) {
            mutex.down(); // P(mutex)            
            if (phil[i].state == phil_state.HUNGRY
                    && phil[LEFT(i)].state != phil_state.EATING
                    && phil[RIGHT(i)].state != phil_state.EATING) {
                phil[i].state = phil_state.EATING;
                phil[i].s.up(); // V[s(i)]
                System.out.println("Fork " + leftForkNum + " taken by Philosopher " + philNum);
            } else {
                System.out.println("Philosopher " + philNum + " is waiting for fork " + leftForkNum);
            }
            mutex.up(); // V(mutex)
            phil[i].s.down(); // P[s(i)]
        }
    }

    public void put_forks(int i) {
        mutex.down(); // P(mutex)
        phil[i].state = phil_state.THINKING;
        if (phil[LEFT(i)].state == phil_state.HUNGRY) {
            phil[LEFT(i)].s.up(); // V(s[LEFT(i)])
        }
        if (phil[RIGHT(i)].state == phil_state.HUNGRY) {
           
phil[RIGHT(i)].s.up(); // V(s[RIGHT(i)])
        }
        System.out.println("Philosopher " + philNum + " released fork " + leftForkNum + " and fork " + rightForkNum);
        mutex.up();
    }

    public void think() {
        //uncomment to see how each Phil goes from state to state
       // System.out.println("Philosopher " + philNum + " is thinking...");
        // Simulate thinking by sleeping for a random amount of time
        try {
            Thread.sleep((long) (Math.random() * 3000));
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
    }

    public void eat() {
        //uncomment to see how each Phil goes from state to state
       // System.out.println("Philosopher " + philNum + " is eating...");
        // Simulate eating by sleeping for a random amount of time
        try {
            Thread.sleep((long) (Math.random() * 3000));
        } catch (InterruptedException ex) {
            ex.printStackTrace();
        }
        System.out.println("Philosopher " + philNum + " completed his dinner");
        numFinished++;
    }

    public void philosopher(int process) {
        while (true) {
            think();
            get_forks(process);
            eat();
            put_forks(process);
            System.out.println("Till now num of philosophers completed dinner are " + numFinished);
        }
    }
    //Its just how the problem is designed, 
    //you pretty much want x amount to manage x resources indefinitely such that it should never get a deadlock, 
    //or all of them to be indefinitely waiting. 
    //So while the loop runs indefinitely, they should all get to eat/etc one by one
    /*
    public void philosopher(int process) {
    int numIterations = 0;
    while (numIterations < 1) {
        think();
        get_forks(process);
        eat();
        put_forks(process);
        System.out.println("Till now num of philosophers completed dinner are " + numFinished);
        numIterations++;
    }
  }
    */
}