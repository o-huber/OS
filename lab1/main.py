import threading
import time
import numpy as np
from threading import Thread
from termcolor import colored

time_of_sitting = 12  # seconds to stop console
speedThinking = 0.02
speedEating = 0.05
counts_eating = np.zeros(5)
colors = ['green', 'blue', 'magenta', 'red', 'cyan']
printL = threading.Lock();
threads = []
forks = [threading.Lock() for i in range(5)]


# const_diff=2 #starving flag
# wait_time=0.05
# min=max=0


def dining_philosophers(num, name, Lfork, Rfork):
    start = time.time()
    with printL:  # using locks in the with statement, we do not need to explicitly acquire and release the lock
        print(colored(f'{name} sat at the table', colors[num]))
    time.sleep(1)  # синхронізуємо початок
    while (time.time() - start < time_of_sitting):
        hungry = 1
        with printL:
            print(colored(f'...{name} is thinking...', colors[num]))

        time.sleep(np.random.random() * speedThinking)

        # max = np.argmax(counts_eating)
        # if (np.amax(counts_eating) - np.amin(counts_eating) >= const_diff and max == num):
        #     time.sleep(wait_time)

        while hungry != 0:
            Lfork.acquire()
            if Rfork.locked():
                Lfork.release()
                time.sleep(0)  # np.random.random()*speedThinking)
            else:
                Rfork.acquire()
                hungry = 0
                printL.acquire()
                print(colored(f'+ {name} is eating', colors[num]))
                printL.release()
                time.sleep(np.random.random() * speedEating)
                Rfork.release()
                Lfork.release()

        with printL:
            print(colored(f'- {name} finished to eat', colors[num]))

        counts_eating[num] += 1


start = time.time()

for i in range(4):
    t = Thread(target=dining_philosophers, name=f'Phil{i}', args=(i, f'Phil{i}', forks[i], forks[i + 1]))
    threads.append(t)
    t.start()
t = Thread(target=dining_philosophers, name=f'Phil{4}', args=(4, f'Phil{4}', forks[0], forks[4]))
threads.append(t)
t.start()

for i in threads:
    i.join()
end = time.time()

print('time is {}'.format(end - start))
print(counts_eating)
