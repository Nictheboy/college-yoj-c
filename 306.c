#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef long long ll;

#define CACHE_SIZE 0
#define CACHE_OFFSET 0

typedef struct {
    ll value;
    int count;
} record;

typedef struct {
    int cache[CACHE_SIZE];
    int n_other;
    record otherdata[];
} unordered;

unordered *init_unordered(const int capacity)
{
    unordered *self = (unordered *)malloc(sizeof(unordered) + sizeof(record) * capacity);
    memset(&self->cache, 0, sizeof(int) * CACHE_SIZE);
    self->n_other = 0;
    return self;
}

void add(unordered *self, ll value)
{
    ll cache_index = value + CACHE_OFFSET;
    if (cache_index >= 0 && cache_index < CACHE_SIZE) {
        // CACHE IS HITTED!
        self->cache[cache_index] += 1;
    } else {
        record r = {.value = value, .count = 1};
        self->otherdata[self->n_other++] = r;
    }
}

void trim(unordered *self)
{
    int cursor = 0;
    for (int i = 0; i < self->n_other; i++) {
        const record r = self->otherdata[i];
        if (r.count == 0)
            continue;
        else {
            record trimmed = {.count = 0, .value = r.value};
            for (int j = i; j < self->n_other; j++) {
                if (self->otherdata[j].value == r.value) {
                    trimmed.count += self->otherdata[j].count;
                    self->otherdata[j].count = 0;
                }
            }
            self->otherdata[cursor++] = trimmed;
        }
    }
    self->n_other = cursor;
}

typedef struct {
    bool already_find_one;
    // bool two_same_frequency; // only meaningful if already_find_one == true
    // bool too_many_same;      // only meaningful if two_same_frequency == true
    // record best[2];
    record best;
} find_helper;

typedef struct {
    bool exist;
    record r;
} find_result;

void init_find_helper(find_helper *self)
{
    self->already_find_one = false;
    // self->two_same_frequency = false; // only meaningful if already_find_one == true
    // self->too_many_same = false;      // only meaningful if two_same_frequency == true
}

void handle(find_helper *self, const record r)
{
    const int value = r.value;
    const int count = r.count;
    if (r.count >= 2) {
        if (self->already_find_one == false) {
            self->best.value = value;
            self->best.count = count;
            self->already_find_one = true;
        } else {
            if (count > self->best.count || (count == self->best.count && value >= self->best.value)) {
                self->best.value = value;
                self->best.count = count;
            }
        }
    }
}

find_result get_result(find_helper *self)
{
    if (self->already_find_one == false) {
        find_result result = {.exist = false};
        return result;
    } else {
        find_result result = {.exist = true, .r = self->best};
        return result;
    }
}

find_result find(unordered *self)
{
    trim(self);

    find_helper helper;
    init_find_helper(&helper);
    for (int i = 0; i < CACHE_SIZE; i++) {
        const record r = {.value = i - CACHE_OFFSET, .count = self->cache[i]};
        if (r.count != 0)
            handle(&helper, r);
    }
    for (int i = 0; i < self->n_other; i++) {
        handle(&helper, self->otherdata[i]);
    }
    return get_result(&helper);
}

int main()
{
    int n;
    scanf("%d", &n);
    unordered *set = init_unordered(n);
    for (int i = 0; i < n; i++) {
        ll value;
        scanf("%lld", &value);
        add(set, value);
    }
    find_result result = find(set);
    if (result.exist) {
        printf("%lld %d", result.r.value, result.r.count);
    } else {
        printf("NO");
    }
    return 0;
}
