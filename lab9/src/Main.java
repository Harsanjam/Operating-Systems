/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author h8saini
 */

package coe628.lab9;

public class Main {
    
    public static final int N = 5; // #define N 5
    public static Philosopher[] phil;
    public static Semaphore mutex = new Semaphore(1); // semaphore mutex = 1

    public static void main(String[] args) {

        phil = new Philosopher[N];
        for (int i = 0; i < N; i++) {
            phil[i] = new Philosopher(i);
        }

        // Create and start a thread for each philosopher       
        for (int i = 0; i < N; i++) {
            final int index = i;
            Thread t = new Thread(() -> phil[index].philosopher(index));
            t.start();
        }
    }

    public static int RIGHT(int i) {
        return (i + 1) % N;
    }

    public static
int LEFT(int i) {
        return (i == 0) ? N - 1 : i - 1;
    }
}