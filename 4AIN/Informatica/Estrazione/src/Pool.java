import java.util.*;

public class Pool {
    private Set<Integer> pool;

    public Pool(int n, int min, int max) {
        pool = new HashSet<>();
        while(pool.size() != n)
            pool.add(new Random().nextInt(min, max));
    }

    public Integer estrai() {
        int i = new Random().nextInt(0, pool.size());
        for (Integer value : pool) {
            if (i == 0) {
                pool.remove(value);
                return value;
            }
            --i;
        }
        return null;
    }

    public int howManyOdds() {
        int n = 0;
        for (Integer i : pool) {
            if (i % 2 != 0)
                ++n;
        }
        return n;
    }

    @Override
    public String toString() {
        return pool.toString();
    }
}
