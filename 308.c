#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    bool exist;
    int index;
    bool activated; // true if can be used
    int capacity;
    int price_basic;
    int price_per;
} Info;

void InfoInit(Info *self)
{
    self->exist = true;
    int temp_for_bool;
    scanf("%d%d%d%d%d", &self->index, &temp_for_bool, &self->capacity, &self->price_basic, &self->price_per);
    self->activated = temp_for_bool == 1 ? false : true;
}

int num_pig[3];
int n;
Info *infos;

Info best_3_for[3][3]; // [pig-index][nbest]

bool is_able(const Info info, const int pig_index)
{
    if (info.activated == false)
        return false;
    if (info.capacity < num_pig[pig_index])
        return false;
    return true;
}

int price(const Info info, const int pig_index)
{
    return info.price_basic + num_pig[pig_index] * info.price_per;
}

bool is_better(const Info old_info, const Info new_info, const int pig_index)
{
    if (price(new_info, pig_index) < price(old_info, pig_index))
        return true;
    if (price(new_info, pig_index) > price(old_info, pig_index))
        return false;
    if (new_info.index < old_info.index)
        return true;
    else
        return false;
}

void init_best_3_for(const int pig_index, const int nbest)
{
    if (nbest > 0) {
        init_best_3_for(pig_index, nbest - 1);
        if (best_3_for[pig_index][nbest - 1].exist == false) {
            best_3_for[pig_index][nbest].exist = false;
            return;
        }
    }
    Info best;
    bool find_one_able = false;
    for (int i = 0; i < n; i++) {
        Info info = infos[i];
        if (is_able(info, pig_index)
            && (nbest == 0 || info.index != best_3_for[pig_index][0].index)
            && (nbest == 1 || info.index != best_3_for[pig_index][1].index)) {
            if (false == find_one_able) {
                best = info;
                find_one_able = true;
            } else {
                if (is_better(best, info, pig_index)) {
                    best = info;
                }
            }
        }
    }
    if (find_one_able)
        best_3_for[pig_index][nbest] = best;
    else
        best_3_for[pig_index][nbest].exist = false;
}

typedef struct {
    bool able;
    int total_price;
} result_for_combination;

const result_for_combination NotAble = {.able = false};

result_for_combination cal_for(const Info for_pig_0, const Info for_pig_1, const Info for_pig_2)
{
    if (false == for_pig_0.exist
        || false == for_pig_1.exist
        || false == for_pig_2.exist) {
        return NotAble;
    }
    if (for_pig_0.index == for_pig_1.index
        || for_pig_0.index == for_pig_2.index
        || for_pig_1.index == for_pig_2.index)
        return NotAble;
    result_for_combination result = {.able = true, .total_price = price(for_pig_0, 0) + price(for_pig_1, 1) + price(for_pig_2, 2)};
    return result;
}

bool index_less(int old_0, int old_1, int old_2, int new_0, int new_1, int new_2)
{
    if (new_0 < old_0)
        return true;
    if (new_0 > old_0)
        return false;
    if (new_1 < old_1)
        return true;
    if (new_1 > old_1)
        return false;
    if (new_2 < old_2)
        return true;
    if (new_2 > old_2)
        return false;
}

int main()
{
    scanf("%d%d%d", &num_pig[0], &num_pig[1], &num_pig[2]);
    scanf("%d", &n);
    infos = (Info *)malloc(sizeof(Info) * n);
    for (int i = 0; i < n; i++) {
        InfoInit(&infos[i]);
    }

    init_best_3_for(0, 2);
    init_best_3_for(1, 2);
    init_best_3_for(2, 2);

    result_for_combination results[3][3][3];
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                results[i][j][k] = cal_for(best_3_for[0][i], best_3_for[1][j], best_3_for[2][k]);
            }
        }
    }

    bool find = false;
    int best_total_price;
    int min_index_0;
    int min_index_1;
    int min_index_2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                result_for_combination result = results[i][j][k];
                if (result.able) {
                    if (find == false) {
                        find = true;
                        best_total_price = result.total_price;
                        min_index_0 = best_3_for[0][i].index;
                        min_index_1 = best_3_for[1][j].index;
                        min_index_2 = best_3_for[2][k].index;
                    } else {
                        if (result.total_price < best_total_price) {
                            best_total_price = result.total_price;
                            min_index_0 = best_3_for[0][i].index;
                            min_index_1 = best_3_for[1][j].index;
                            min_index_2 = best_3_for[2][k].index;
                        } else if (result.total_price == best_total_price) {
                            if (index_less(min_index_0, min_index_1, min_index_2,
                                           best_3_for[0][i].index, best_3_for[1][i].index, best_3_for[2][i].index)) {
                                min_index_0 = best_3_for[0][i].index;
                                min_index_1 = best_3_for[1][j].index;
                                min_index_2 = best_3_for[2][k].index;
                            }
                        }
                    }
                }
            }
        }
    }

    if (find) {
        printf("%d\n%d %d %d", best_total_price, min_index_0, min_index_1, min_index_2);
    } else {
        printf("NO");
    }

    free(infos);
    return 0;
}
