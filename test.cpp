#include<iostream>
#include<algorithm>
using namespace std;
int N;
int D;
// int totPrice[1010];
// int weight[1010];
// double perPrice[1010];

struct P{
    int totPrice;
    int weight;
    double perPrice;
} product[2000];

bool cmp(struct P a, struct P b) {
    return a.perPrice > b.perPrice;
}
int main() {
    cin >> N >> D;
    for(int i = 0; i < N; i++) {
        cin >> product[i].weight;
    }
    for(int i = 0; i < N; i++) {
        cin >> product[i].totPrice;
    }

    for(int i = 0; i < N; i++) {
        product[i].perPrice = product[i].totPrice * 1.0 / product[i].weight; 
        // printf("per price: %d  %f\n", i, product[i].perPrice);
    }

    double earn = 0;
    sort(product, product + N, cmp);
    // printf("sort0:%f\n", )
    int i = 0;
    while(D > 0 && i < N) {
        int purchaseweight = min(D, product[i].weight);
        D -= purchaseweight;
        earn += purchaseweight * product[i].perPrice;
        i++;
    }
    printf("%.2f", earn);
}
