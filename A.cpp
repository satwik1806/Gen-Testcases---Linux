/*  Author - Satwik_Tiwari  */

#include<bits/stdc++.h>
using namespace std;

#define sim template < class c
#define ris return * this
#define dor > debug & operator <<
#define eni(x) sim > typename \
  enable_if<sizeof dud<c>(0) x 1, debug&>::type operator<<(c i) {
sim > struct rge { c b, e; };
sim > rge<c> range(c i, c j) { return rge<c>{i, j}; }
sim > auto dud(c* x) -> decltype(cerr << *x, 0);
sim > char dud(...);
struct debug {
#ifndef ONLINE_JUDGE
    ~debug() { cerr << endl; }
    eni(!=) cerr << boolalpha << i; ris; }
    eni(==) ris << range(begin(i), end(i)); }
    sim, class b dor(pair < b, c > d) {
        ris << "(" << d.first << ", " << d.second << ")";
    }
    sim dor(rge<c> d) {
        *this << "[";
        for (auto it = d.b; it != d.e; ++it)
            *this << ", " + 2 * (it == d.b) << *it;
        ris << "]";
    }
#else
    sim dor(const c&) { ris; }
#endif
};
#define print(...) " [" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] "

#define int long long
#define FastIO ios_base::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define ff first
#define ss second
#define all(x) (x).begin(),(x).end()
#define minheap priority_queue <int, vector<int>, greater<>>
#define endl "\n"
#define google cout << "Case #" << casee << ": " ;

int power(int x, int y, int M) {int res = 1; x%=M; if(not x) return 0; while (y > 0) {if (y & 1) res = (res * x) % M; y >>= 1; x = (x * x) % M;} return res % M;}
int power(int x, int y) {int res = 1; if(not x) return 0; while (y > 0) {if (y & 1) res = (res * x); y >>= 1; x = (x * x);} return res;}
const int mxn = 210, mod = 998244353, inf = 1e18 ; int t,casee = 1;

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}

template<typename T>
class Segment_Tree{
private:
    vector<T> arr; vector<T> seg_tree;
    int N; int def;
public:
    // change default accordingly. set for sum intially.
    Segment_Tree(vector<T> a, int deff = 0){ //make sure not to pass global vector of size = mxn;
        N = a.size();
        def = deff;
        arr = a;
        seg_tree.resize(4*N + 10,0);
        build();
    }

    int func(int a, int b){
        return gcd(a,b);
    }

    void build(){
        build_it_for_me(0,N-1,1);
    }

    void build_it_for_me(int lo, int hi, int pos){
        assert(lo <= hi);
        if(lo == hi) {
            seg_tree[pos] = arr[lo]; return;
        }
        int mid = (lo + hi)/2;
        build_it_for_me(lo,mid,2*pos); build_it_for_me(mid+1,hi,2*pos+1);
        seg_tree[pos] = func(seg_tree[2*pos],seg_tree[2*pos+1]);
    }

    void update(int ind, int val){
        update_it_for_me(ind,val,0,N-1,1);
    }
    void update_it_for_me(int ind, int val, int lo, int hi, int pos){ //0 indexed. arr[ind] = val.
        if(lo == hi){
            seg_tree[pos] = val; arr[ind] = val; return;
        }
        int mid = (lo + hi)/2;
        if(mid >= ind) update_it_for_me(ind,val,lo,mid,2*pos);
        else update_it_for_me(ind,val,mid+1,hi,2*pos+1);
        seg_tree[pos] = func(seg_tree[2*pos],seg_tree[2*pos+1]);
    }

    T query(int l, int r){
        return query_it_for_me(l,r,1,0,N-1);
    }

    T query_it_for_me(int l, int r, int pos, int lo, int hi){ // 0 indexed [l,r].
        if(lo > r || hi < l) return def; //no overlap
        if(lo >= l && hi <= r) return seg_tree[pos]; //total overlap
        int mid = (lo + hi)/2;
        return func(query_it_for_me(l,r,2*pos,lo,mid),query_it_for_me(l,r,2*pos+1,mid+1,hi)); //partial overlap
    }
};

bool chck(int i, int len, Segment_Tree<int> &segtree, int n, int g){
    if(i + len - 1 < n){
        if(segtree.query(i,i + len - 1) == g) return 1;
        return 0;
    }
    else{
        int left = len - (n-i);
        if(gcd(segtree.query(i,n-1), segtree.query(0,left - 1)) == g) return 1;
        return 0;
    }
}

void test_case() {
    int n; cin >> n;
    vector<int> a(n); for(int i=0;i<n;i++) cin >> a[i];
    Segment_Tree<int> segtree(a);

    int ans = 0;
    int g = 0; for(int i=0;i<n;i++) g = gcd(g,a[i]);

    for(int i=0;i<n;i++){
        int lo = 1;
        int hi = n;
        int curr = hi;
        while(lo <= hi){
            int mid = (lo + hi)/2;
            if(chck(i,mid,segtree,n,g)){
                curr = mid;
                hi = mid - 1;
            }
            else lo = mid + 1;
        }
        ans = max(ans,curr - 1);
    }
    cout << ans << endl;
}

int32_t main() {
    FastIO;
    t = 1;
//    cin >> t;
    while (t--) {
        test_case();
        casee++;
    }
    return 0;
}
