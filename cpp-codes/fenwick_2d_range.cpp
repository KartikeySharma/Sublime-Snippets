template <typename T>
struct Fenwick2d {
    vector<vector<T>> bit[4]; // xy, x, y, const
    int n, m;

    Fenwick2d(int _n, int _m) : n(_n), m(_m) {
        for (int i = 0; i < 4; i++) {
            bit[i].resize(n);
            for (int j = 0; j < n; j++) {
                bit[i][j].resize(m);
            }
        }
    }

    void update(int i, int j, T v, int b) {
        int x = i;
        while (x < n) {
            int y = j;
            while (y < m) {
                bit[b][x][y] += v;
                y += (y & -y);
            }
            x += (x & -x);
        }
    }

    T pquery(int i, int j, int b) {
        T v{};
        int x = i;
        while (x > 0) {
            int y = j;
            while (y > 0) {
                v += bit[b][x][y];
                y -= (y & -y);
            }
            x -= (x & -x);
        }
        return v;
    }

    // Range Update and Range Query

    void updater(int x1, int y1, int x2, int y2, T v) {
        update(x1, y1, v, 0);
        update(x1, y2+1, -v, 0);
        update(x2+1, y1, -v, 0);
        update(x2+1, y2+1, v, 0);

        update(x1, y1, -v*(y1-1), 1);
        update(x1, y2+1, v*(y1-1), 1);
        update(x2+1, y1, v*(y1-1), 1);
        update(x2+1, y2+1, -v*(y1-1), 1);
        update(x1, y2+1, v*(y2-y1+1), 1);
        update(x2+1, y2+1, -v*(y2-y1+1), 1);

        update(x1, y1, -v*(x1-1), 2);
        update(x1, y2+1, v*(x1-1), 2);
        update(x2+1, y1, v*(x1-1), 2);
        update(x2+1, y2+1, -v*(x1-1), 2);
        update(x2+1, y1, v*(x2-x1+1), 2);
        update(x2+1, y2+1, -v*(x2-x1+1), 2);

        update(x1, y1, v*(x1-1)*(y1-1), 3);
        update(x1, y2+1, -v*(x1-1)*(y1-1), 3);
        update(x2+1, y1, -v*(x1-1)*(y1-1), 3);
        update(x2+1, y2+1, v*(x1-1)*(y1-1), 3);
        update(x2+1, y1, -v*(y1-1)*(x2-x1+1), 3);
        update(x2+1, y2+1, v*(y1-1)*(x2-x1+1), 3);
        update(x1, y2+1, -v*(x1-1)*(y2-y1+1), 3);
        update(x2+1, y2+1, v*(x1-1)*(y2-y1+1), 3);
        update(x2+1, y2+1, v*(x2-x1+1)*(y2-y1+1), 3);
    }

    T queryr(int x, int y) {
        T a = pquery(x, y, 0);
        T b = pquery(x, y, 1);
        T c = pquery(x, y, 2);
        T d = pquery(x, y, 3);
        return a*x*y + b*x + c*y + d;
    }

    T queryr(int x1, int y1, int x2, int y2) {
        int v1 = queryr(x2, y2);
        int v2 = queryr(x2, y1-1);
        int v3 = queryr(x1-1, y2);
        int v4 = queryr(x1-1, y1-1);
        return v1 - v2 - v3 + v4;
    }
};
