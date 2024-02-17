#include <stdio.h>

typedef long long ll;

typedef struct {
    ll vote_to;
    int vote_count;
} vote_info;

int main()
{
    ll n, m;
    scanf("%lld%lld", &n, &m);
    vote_info votes[m];
    for (int i = 0; i < m; i++) {
        scanf("%lld", &votes[i].vote_to);
        votes[i].vote_count = 1;
    }
    int cursor = 0;
    for (int i = 0; i < m; i++) {
        if (votes[i].vote_count == 0)
            continue;
        const ll vote_to = votes[i].vote_to;
        int total_vote = 0;
        for (int j = i; j < m; j++) {
            if (votes[j].vote_to == vote_to) {
                total_vote += votes[j].vote_count;
            }
        }
        votes[i].vote_count = total_vote;
        cursor++;
    }
    for (int i = 0; i < cursor; i++) {
        if (votes[i].vote_count > m / 2) {
            printf("%lld", votes[i].vote_to);
            return 0;
        }
    }
    printf("-1");
    return 0;
}