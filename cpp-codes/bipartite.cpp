queue<int> q;
q.push(x);
vis[x] = 1;
color[x] = 1;
while (!q.empty()) {
    int t = q.front();
    q.pop();
    for (auto i : g[t] ){
        if (vis[i]) continue;
        vis[i] = 1;
        color[i] = !color[t];
        q.push(i);
    }
}
