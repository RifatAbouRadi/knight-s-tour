// knight_tour.c
// Backtracking Knight's Tour with optional Warnsdorff heuristic.
// Compile:  gcc -O2 -Wall knight_tour.c -o knight_tour
// Run:      ./knight_tour 8 1      (N=8, use_warnsdorff=1)
//           ./knight_tour 4 0      (N=4, pure backtracking)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const int kdx[8] = {+2,+1,-1,-2,-2,-1,+1,+2};
static const int kdy[8] = {+1,+2,+2,+1,-1,-2,-2,-1};

typedef struct { int x, y, deg; } Move;

static int inside(int n, int x, int y){ return x>=0 && y>=0 && x<n && y<n; }

static int onward_degree(int n, int *vis, int x, int y){
    int d=0;
    for(int i=0;i<8;i++){
        int nx=x+kdx[i], ny=y+kdy[i];
        if(inside(n,nx,ny) && !vis[ny*n+nx]) d++;
    }
    return d;
}

static int cmp_moves(const void *a, const void *b){
    const Move *ma=a, *mb=b;
    if (ma->deg != mb->deg) return ma->deg - mb->deg; // ascending
    return 0;
}

// depth-first search; if use_warnsdorff=1, order next moves by onward degree
static int dfs(int n, int *board, int *vis, int x, int y, int step, int use_warnsdorff){
    board[y*n+x] = step;
    vis[y*n+x] = 1;
    if(step == n*n) return 1;

    Move cand[8]; int c=0;
    for(int i=0;i<8;i++){
        int nx=x+kdx[i], ny=y+kdy[i];
        if(inside(n,nx,ny) && !vis[ny*n+nx]){
            cand[c].x=nx; cand[c].y=ny;
            cand[c].deg = use_warnsdorff ? onward_degree(n,vis,nx,ny) : 0;
            c++;
        }
    }
    if(use_warnsdorff) qsort(cand,c,sizeof(Move),cmp_moves);

    for(int i=0;i<c;i++){
        if(dfs(n,board,vis,cand[i].x,cand[i].y,step+1,use_warnsdorff)) return 1;
    }
    vis[y*n+x]=0; board[y*n+x]=0;
    return 0;
}

static void print_board(int n, int *board){
    for(int y=0;y<n;y++){
        for(int x=0;x<n;x++){
            printf("%3d ", board[y*n+x]);
        }
        puts("");
    }
}

int main(int argc, char **argv){
    int n = (argc>1) ? atoi(argv[1]) : 8;
    int use_warnsdorff = (argc>2) ? atoi(argv[2]) : 1;

    int *board = calloc(n*n, sizeof(int));
    int *vis   = calloc(n*n, sizeof(int));
    if(!board || !vis){ fprintf(stderr,"alloc failed\n"); return 1; }

    // Try every start square until we find a tour (or give up)
    int found = 0, sx=0, sy=0;
    for(int y=0;y<n && !found;y++){
        for(int x=0;x<n && !found;x++){
            memset(board,0,n*n*sizeof(int));
            memset(vis,0,n*n*sizeof(int));
            if(dfs(n,board,vis,x,y,1,use_warnsdorff)){
                found=1; sx=x; sy=y;
            }
        }
    }

    if(found){
        printf("Tour found on %dx%d (start %d,%d, %s):\n",
               n,n,sx,sy, use_warnsdorff?"Warnsdorff":"Backtracking");
        print_board(n,board);
    }else{
        printf("No full tour exists (or not found) on %dx%d.\n", n,n);
    }

    free(board); free(vis);
    return 0;
}
