#ifndef SYNTHLIB_H
#define SYNTHLIB_h

#include <arm_math.h>

enum key_note {
    C0, CSH0, D0, DSH0, E0, F0, FSH0, G0, GSH0, A0, ASH0, B0,
    C1, CSH1, D1, DSH1, E1, F1, FSH1, G1, GSH1, A1, ASH1, B1,
    C2, CSH2, D2, DSH2, E2, F2, FSH2, G2, GSH2, A2, ASH2, B2,
    C3, CSH3, D3, DSH3, E3, F3, FSH3, G3, GSH3, A3, ASH3, B3,
    C4, CSH4, D4, DSH4, E4, F4, FSH4, G4, GSH4, A4, ASH4, B4,
    C5, CSH5, D5, DSH5, E5, F5, FSH5, G5, GSH5, A5, ASH5, B5,
    C6, CSH6, D6, DSH6, E6, F6, FSH6, G6, GSH6, A6, ASH6, B6,
    C7, CSH7, D7, DSH7, E7, F7, FSH7, G7, GSH7, A7, ASH7, B7,
    C8, CSH8, D8, DSH8, E8, F8, FSH8, G8, GSH8, A8, ASH8, B8
};

extern const float note_freq_table[];

float note_to_freq_calc(enum key_note note);
float note_to_freq_lut(enum key_note note);

#endif
