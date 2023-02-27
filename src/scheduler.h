/*
 * Personal laundry situation
 */
typedef struct Person {
    char* name;
    int clothes_remaining;
    int laundry_loads;
    int time_needed;
} person_t;

/*
 * Information used to produce schedule
 */
typedef struct Information {
    int washer_time;
    int dryer_time;
    int number_people;
    person_t** people;
} information_t;
