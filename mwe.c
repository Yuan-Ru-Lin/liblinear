#include "linear.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
    struct feature_node** x = malloc(sizeof(struct feature_node*)*2);
    x[0] = malloc(sizeof(struct feature_node)*2);
    x[1] = malloc(sizeof(struct feature_node)*2);
    x[0][0] = (struct feature_node) { .index = 1, .value = 1.0};
    x[0][1] = (struct feature_node) { .index = 2, .value = 2.0};
    x[1][0] = (struct feature_node) { .index = 1, .value = -1.0};
    x[1][1] = (struct feature_node) { .index = 2, .value = -2.0};

    double* y = malloc(sizeof(double)*2);
    y[0] = -1.0;
    y[1] = 1.0;

    struct problem prob = {
        .l = 2,
        .n = 2,
        .y = y,
        .x = x,
        .bias = -1
    };

    struct parameter param = {
        .solver_type = L2R_LR,
        .eps = 0.01,
        .C = 1.0,
        .nr_weight = 0,
        .weight_label = NULL,
        .weight = NULL,
        .p = 0.1,
        .nu = 0.5,
        .init_sol = NULL,
        .regularize_bias = 1
    };

    const char* error_msg;
    error_msg = check_parameter(&prob, &param);
    if (error_msg)
    {
        fprintf(stderr, "%s", error_msg);
        exit(1);
    }

    struct model* model_ = train(&prob, &param);
    if (save_model("yo.model", model_))
    {
        fprintf(stderr, "ohoh");
        exit(1);
    }

    free(model_);
    free(y);
    free(x[1]);
    free(x[0]);
    free(x);

    return 0;
}
