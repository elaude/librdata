#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>

#include <rdata.h>

const int debug = 0;

static int handle_table(const char *name, void *ctx) {
    if (debug) printf("Read table: %s\n", name);
    return 0;
}

// Called once for all columns. "data" is NULL for text columns.
static int handle_column(const char *name, rdata_type_t type,
                         void *data, long count, void *ctx) {
    if (debug) printf("Read column: %s with %ld elements of type %d\n", name, count, type);
    /* Do something... */
    return 0;
}

static int handle_column_name(const char *name, int index, void *ctx) {
    if (debug) printf("Read column name: %s\n", name);
    /* Do something... */
    return 0;
}

// Called once per row for a text column
static int handle_text_value(const char *value, int index, void *ctx) {
    if (debug) printf("Read text value: %s at %d\n", value, index);
    /* Do something... */
    return 0;
}

// Called for factor variables, once for each level
static int handle_value_label(const char *value, int index, void *ctx) {
    if (debug) printf("Read value label: %s at %d\n", value, index);
    /* Do something... */
    return 0;
}

int main() {
    rdata_parser_t *parser = rdata_parser_init();

    rdata_set_table_handler(parser, &handle_table);
    rdata_set_column_handler(parser, &handle_column);
    rdata_set_column_name_handler(parser, &handle_column_name);
    rdata_set_text_value_handler(parser, &handle_text_value);
    rdata_set_value_label_handler(parser, &handle_value_label);

    if (access("somewhere.rdata", F_OK) != -1) {
        rdata_error_t err = rdata_parse(parser, "somewhere.rdata", NULL);
        if (debug) printf("Error code %d\n", err);
    }

    if (access("some.rds", F_OK) != -1) {
        rdata_error_t err = rdata_parse(parser, "some.rds", NULL);
        if (debug) printf("Error code %d\n", err);
    }

    exit(0);
}
