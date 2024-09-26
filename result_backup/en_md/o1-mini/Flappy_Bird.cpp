int main(){
    int n, m, k;
    scanf("%d %d %d", &n, &m, &k);
    int* x = new int[n];
    int* y = new int[n];
    for(int i=0;i<n;i++) scanf("%d %d", &x[i], &y[i]);
    struct Pipe{
        int p;
        int l;
        int h;
    };
    Pipe* pipes = new Pipe[k];
    for(int i=0;i<k;i++) scanf("%d %d %d", &pipes[i].p, &pipes[i].l, &pipes[i].h);
    // Sort pipes by p
    for(int i=0;i<k-1;i++) for(int j=i+1;j<k;j++) if(pipes[i].p > pipes[j].p){
        Pipe temp = pipes[i];
        pipes[i] = pipes[j];
        pipes[j] = temp;
    }
    // Create pipe map
    int** pipe_map = new int*[n+1];
    for(int i=0;i<=n;i++) pipe_map[i] = new int[2](); // 0 = no pipe, 1 = has pipe
    for(int i=0;i<k;i++){
        pipe_map[pipes[i].p][0] = pipes[i].l;
        pipe_map[pipes[i].p][1] = pipes[i].h;
    }
    // Initialize DP
    const int INF = 1000000000;
    int* current = new int[m+1];
    for(int i=0;i<=m;i++) current[i] = INF;
    for(int h=1; h<=m; h++) current[h] = 0;
    int pass_pipes =0;
    int pipe_idx=0;
    for(int i=0;i<n;i++){
        // Update pass_pipes
        while(pipe_idx <k && pipes[pipe_idx].p <i+1){
            pass_pipes++;
            pipe_idx++;
        }
        // Prepare next
        int* next = new int[m+1];
        for(int h=0; h<=m; h++) next[h] = INF;
        // Process current
        for(int h=1; h<=m; h++) if(current[h] < INF){
            // Option1: No tap
            int h1 = h - y[i];
            if(h1 >0){
                if(pipe_map[i+1][0] !=0 || pipe_map[i+1][1] !=0){
                    int l = pipe_map[i+1][0];
                    int hp = pipe_map[i+1][1];
                    if(l <= h1 && h1 <= hp){
                        if(next[h1] > current[h]){
                            next[h1] = current[h];
                        }
                    }
                }
                else{
                    if(next[h1] > current[h]){
                        next[h1] = current[h];
                    }
                }
            }
            // Option2: Tap
            if(pipe_map[i+1][0] !=0 || pipe_map[i+1][1] !=0){
                int l = pipe_map[i+1][0];
                int hp = pipe_map[i+1][1];
                // Calculate t_min
                int numerator = l - h;
                int t_min = 1;
                if(numerator >0){
                    t_min = (numerator + x[i] -1)/x[i];
                    if(t_min <1) t_min =1;
                }
                else{
                    t_min =1;
                }
                // Calculate h_after_t
                long long ht = (long long)h + (long long)t_min * x[i];
                if(ht > m) ht = m;
                if(ht <= hp && ht >= l){
                    if(ht <=m && ht >=1){
                        if(next[ht] > current[h] + t_min){
                            next[ht] = current[h] + t_min;
                        }
                    }
                }
                else{
                    if(m >= l && m <= hp){
                        // Need to tap to reach at least l and set to m
                        // Check if h + t*x[i] >= l
                        if((long long)h + (long long)t_min *x[i] >= l){
                            if(next[m] > current[h] + t_min){
                                next[m] = current[h] + t_min;
                            }
                        }
                    }
                }
            }
            else{
                if(h <m){
                    int h2 = h + x[i];
                    if(h2 >m) h2 = m;
                    if(h2 >=1 && h2 <=m){
                        if(next[h2] > current[h] +1){
                            next[h2] = current[h] +1;
                        }
                    }
                }
            }
        }
        // Check if next has any valid states
        bool has = false;
        for(int h=1; h<=m; h++) if(next[h] < INF){ has=true; break;}
        if(!has){
            printf("0\n%d\n", pass_pipes);
            return 0;
        }
        // Move to next
        for(int h=1; h<=m; h++) current[h] = next[h];
        delete[] next;
    }
    // Find minimum taps
    int min_taps = INF;
    for(int h=1; h<=m; h++) if(current[h] < min_taps) min_taps = current[h];
    if(min_taps < INF){
        printf("1\n%d\n", min_taps);
    }
    else{
        printf("0\n%d\n", pass_pipes);
    }
    // Cleanup
    delete[] x;
    delete[] y;
    delete[] pipes;
    for(int i=0;i<=n;i++) delete[] pipe_map[i];
    delete[] pipe_map;
    delete[] current;
    return 0;
}