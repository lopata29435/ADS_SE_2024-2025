#include <iostream>
#include <cstdlib>

using namespace std;

struct Item
{
  int cnt, Value, Priority;
  long long Summa;
  Item *l, *r;
  Item() { }
  Item (int Value) : Priority((rand() << 16u) + unsigned(rand())),
                     Value(Value), Summa(Value), l(NULL), r(NULL) { }
};

typedef Item* Pitem;
Pitem T1, T2;

int cnt(Pitem t)
{
  return t ? t->cnt : 0;
}

long long GetSum(Pitem t)
{
  return t ? t->Summa : 0;
}

void upd(Pitem t)
{
  if (t)
  {
    t->cnt = 1 + cnt(t->l) + cnt (t->r);
    t->Summa = t->Value + GetSum(t->l) + GetSum(t->r);
  }
}

void Merge(Pitem l, Pitem r, Pitem &t)
{
  if (!l || !r) {
    t = l ? l : r;
  }
  else if (l->Priority > r->Priority) {
    Merge(l->r, r, l->r),  t = l;
  }
  else {
    Merge(l, r->l, r->l),  t = r;
  }
  upd(t);
}

void Split(Pitem t, Pitem &l, Pitem &r, int pos)
{
  if (!t) {
    return void( l = r = 0 );
  } 
  if (pos <= cnt(t->l)) {
    Split(t->l, l, t->l, pos),  r = t;
  }
  else {
    Split(t->r, t->r, r, pos - 1 - cnt(t->l)),  l = t;
  }
  upd(t);
}

long long Sum(int L, int R)
{
  if (L > R) {
    return 0;
  }
  int L1 = (L + 1) / 2, R1 = R / 2;
  int L2 = L / 2, R2 = (R + 1) / 2 - 1;
  Pitem A1, B1, C1, A2, B2, C2;
  Split(T1,A1,B1,L1);
  Split(B1,B1,C1,R1 - L1 + 1);
  Split(T2,A2,B2,L2);
  Split(B2,B2,C2,R2 - L2 + 1);

  long long res = GetSum(B1) + GetSum(B2);

  Merge(A1,B1,B1); Merge(B1,C1,T1);
  Merge(A2,B2,B2); Merge(B2,C2,T2);
  return res;
}

void Swap(int L, int R)
{
  int L1 = (L + 1) / 2, R1 = R / 2;
  int L2 = L / 2, R2 = (R + 1) / 2 - 1;
  Pitem A1, B1, C1, A2, B2, C2;

  Split(T1,A1,B1,L1);
  Split(B1,B1,C1,R1 - L1 + 1);
  Split(T2,A2,B2,L2);
  Split(B2,B2,C2,R2 - L2 + 1);

  Merge(A1,B2,B2);
  Merge(B2,C1,T1);
  Merge(A2,B1,B1);
  Merge(B1,C2,T2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, m, cs = 1, type, a, b, val;
    while (cin >> n >> m && n + m) {
        T1 = nullptr;
        T2 = nullptr;

        if (cs != 1) {
            cout << '\n';
        }

        cout << "Swapper " << cs++ << ":\n";
        for (int i = 1; i <= n; i++) {
            cin >> val;
            if (i&1) {
                Merge(T1, new Item(val), T1);
            } else {
                Merge(T2, new Item(val), T2);
            }
        }

        for (int i = 0; i < m; i++) {
            cin >> type >> a >> b;
            a--; b--;

            if (type == 1) {
                Swap(a, b);
            } else {
                cout << Sum(a, b) << '\n';
            }
        }
    }

    return 0;
}