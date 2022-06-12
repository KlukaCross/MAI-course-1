#ifndef VILLAGES_H
#define VILLAGES_H

#define FOREACH_VIL(VIL) \
        VIL(ABALAK) \
        VIL(BAEVO) \
        VIL(VELIKOE) \
        VIL(GORELOE) \
        VIL(DOBROE) \
        VIL(ELOVO) \
        VIL(ZAVETNOE) \
        VIL(ILEK) \
        VIL(KABANSK) \
        VIL(LESNOE) \
        VIL(MAKAROVO) \
        VIL(NOVIKOVO) \
        VIL(OMMI) \
        VIL(PAVLOVO) \
        VIL(RODINO) \
        VIL(SADOVOE) \
        VIL(TUPIK) \
        VIL(URIK) \
        VIL(FILISOVO) \
        VIL(HORINSK) \
        VIL(TSAREV) \
        VIL(CHARA) \
        VIL(SHAMANKA) \
        VIL(YUDINO) \
        VIL(YAMS) \
        VIL(VILLAGE_0)

#define GENERATE_ENUM(ENUM) ENUM,
#define GENERATE_STRING(STRING) #STRING,

typedef enum {
    FOREACH_VIL(GENERATE_ENUM)
} VILLAGES;

extern const char *NAMES_VILLAGES[];

#endif
