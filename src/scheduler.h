// TODO: Add time structs for day-hour times and hour-hour periods

/*
 * Personal situation
 *
 * name: char* = Name of person
 * clothes_remaining: int = Clothes remaining (days)
 * laundry_loads: int = Loads of laundry to do
 */
typedef struct Person {
    char* name;
    int clothes_remaining;
    int laundry_loads;
} person_t;

/*
 * Laundry specification
 *
 * washer_time: int = Time to wash one load (hr)
 * dryer_time: int = Time to dry one load (hr)
 * number_people: int = Number of people to schedule
 * people: person_t** = Personal information for scheduled people
 */
typedef struct Laundry {
    int washer_time;
    int dryer_time;
    int number_people;
    person_t** people;
} laundry_t;
