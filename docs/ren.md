# uta-bind

## 策略

全局数组`activeHeads[n]`

+ 新线程加入
1. 核k上新加入一个线程A，首先通过原子操作进入active队列，再检查`activeHeads[k]`是否为空
2. 如果不为空，那么自己进入阻塞；如果为空，那么原子操作设为自己

+ 线程自我唤醒
1. secondary队列中，核k上线程A把自己唤醒，原子操作将`activeHeads[k]`设为自己
2. 如果原值不为空，那么让原值指向的线程B阻塞

+ 线程放锁
1. 在active队列向后找到第一个活跃线程B
2. 假设这个线程在核k上，原子操作判断`activeHeads[k]`是否为B，如果是B那么把`activeHeads[k]`设为空，如果不是B，则跳过B重复1
