#ifndef KP6_MA_STRUCT_H
#define KP6_MA_STRUCT_H
typedef struct{
        int id;
        long long price;
        int repair;
        int dist_to_subway;
        int subway_dist_to_center;
        int rooms;
        double footage;
        int floor;
        char ao[10];
} Apartment;

#endif //KP6_MA_STRUCT_H
