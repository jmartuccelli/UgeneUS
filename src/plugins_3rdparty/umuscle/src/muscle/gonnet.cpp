#include <U2Core/disable-warnings.h>
U2_DISABLE_WARNINGS

#include "muscle.h"
#include "gonnet.h"

#define ROW(A, C, D, E, F, G, H, I, K, L, M, N, P, Q, R, S, T, V, W, Y) \
	{ A/4.0, C/4.0, D/4.0, E/4.0, F/4.0, G/4.0, H/4.0, I/4.0, K/4.0, L/4.0, M/4.0, N/4.0, P/4.0, Q/4.0, R/4.0, S/4.0, T/4.0, V/4.0, W/4.0, Y/4.0 },

static double Gonnet80[20][20] =
	{
//        A       C       D       E       F       G       H       I       K       L
//        M       N       P       Q       R       S       T       V       W       Y
ROW(   1990,   1140,    930,   1070,    600,   1130,    850,    810,    940,    810,
        980,    900,   1080,   1020,    880,   1380,   1190,   1180,    370,    590) // A

ROW(   1140,   2780,    310,    300,    850,    630,    810,    700,    360,    690,
        850,    690,    310,    480,    640,   1090,    900,   1030,    810,    920) // C

ROW(    930,    310,   2200,   1550,    130,    980,   1070,    180,   1030,    150,
        360,   1450,    820,   1150,    800,   1100,   1000,    350,      0,    550) // D

ROW(   1070,    300,   1550,   2120,    220,    770,   1070,    510,   1280,    490,
        710,   1110,    890,   1470,   1010,   1050,    970,    730,    260,    500) // E

ROW(    600,    850,    130,    220,   2380,     90,    980,   1090,    350,   1310,
       1270,    490,    310,    540,    340,    470,    620,    930,   1400,   1730) // F

ROW(   1130,    630,    980,    770,     90,   2210,    710,    100,    740,    200,
        410,   1060,    660,    800,    810,   1080,    720,    380,    430,    300) // G

ROW(    850,    810,   1070,   1070,    980,    710,   2510,    600,   1120,    670,
        860,   1330,    790,   1380,   1140,    990,   1000,    590,    810,   1450) // H

ROW(    810,    700,    180,    510,   1090,    100,    600,   2100,    650,   1460,
       1490,    530,    490,    640,    530,    620,    960,   1650,    610,    770) // I

ROW(    940,    360,   1030,   1280,    350,    740,   1120,    650,   2090,    660,
        870,   1220,    870,   1410,   1570,   1040,   1090,    700,    350,    640) // K

ROW(    810,    690,    150,    490,   1310,    200,    670,   1460,    660,   2010,
       1550,    450,    660,    850,    660,    600,    750,   1270,    800,    890) // L

ROW(    980,    850,    360,    710,   1270,    410,    860,   1490,    870,   1550,
       2410,    620,    460,   1050,    710,    830,    990,   1250,    790,    870) // M

ROW(    900,    690,   1450,   1110,    490,   1060,   1330,    530,   1220,    450,
        620,   2210,    760,   1180,   1020,   1290,   1170,    550,    380,    850) // N

ROW(   1080,    310,    820,    890,    310,    660,    790,    490,    870,    660,
        460,    760,   2380,   1000,    790,   1100,   1040,    670,    120,    480) // P

ROW(   1020,    480,   1150,   1470,    540,    800,   1380,    640,   1410,    850,
       1050,   1180,   1000,   2190,   1350,   1090,   1060,    730,    620,    710) // Q

ROW(    880,    640,    800,   1010,    340,    810,   1140,    530,   1570,    660,
        710,   1020,    790,   1350,   2210,    970,    970,    640,    830,    740) // R

ROW(   1380,   1090,   1100,   1050,    470,   1080,    990,    620,   1040,    600,
        830,   1290,   1100,   1090,    970,   2020,   1490,    810,    520,    780) // S

ROW(   1190,    900,   1000,    970,    620,    720,   1000,    960,   1090,    750,
        990,   1170,   1040,   1060,    970,   1490,   2050,   1150,    370,    660) // T

ROW(   1180,   1030,    350,    730,    930,    380,    590,   1650,    700,   1270,
       1250,    550,    670,    730,    640,    810,   1150,   2040,    440,    770) // V

ROW(    370,    810,      0,    260,   1400,    430,    810,    610,    350,    800,
        790,    380,    120,    620,    830,    520,    370,    440,   2970,   1470) // W

ROW(    590,    920,    550,    500,   1730,    300,   1450,    770,    640,    890,
        870,    850,    480,    710,    740,    780,    660,    770,   1470,   2470) // Y
	};

static double Gonnet120[20][20] =
	{
//        A       C       D       E       F       G       H       I       K       L
//        M       N       P       Q       R       S       T       V       W       Y
ROW(   1550,    950,    780,    870,    480,    930,    700,    690,    770,    660,
        790,    760,    900,    840,    730,   1120,    980,    960,    280,    480) // A

ROW(    950,   2400,    270,    280,    700,    510,    650,    600,    320,    570,
        700,    550,    280,    400,    510,    890,    750,    850,    670,    760) // C

ROW(    780,    270,   1780,   1310,     90,    820,    890,    160,    880,    140,
        320,   1220,    680,    970,    690,    910,    830,    310,      0,    430) // D

ROW(    870,    280,   1310,   1680,    180,    650,    900,    410,   1070,    390,
        560,    950,    740,   1210,    860,    870,    810,    580,    180,    400) // E

ROW(    480,    700,     90,    180,   1980,     40,    820,    930,    290,   1110,
       1070,    380,    240,    430,    280,    380,    490,    790,   1230,   1510) // F

ROW(    930,    510,    820,    650,     40,   1860,    590,     90,    620,    140,
        310,    890,    550,    660,    660,    900,    610,    310,    300,    220) // G

ROW(    700,    650,    890,    900,    820,    590,   2060,    480,    940,    540,
        680,   1100,    650,   1130,    950,    820,    820,    490,    680,   1220) // H

ROW(    690,    600,    160,    410,    930,     90,    480,   1680,    520,   1240,
       1250,    410,    400,    530,    430,    520,    790,   1380,    500,    650) // I

ROW(    770,    320,    880,   1070,    290,    620,    940,    520,   1650,    520,
        690,   1010,    720,   1160,   1320,    860,    900,    570,    280,    520) // K

ROW(    660,    570,    140,    390,   1110,    140,    540,   1240,    520,   1620,
       1300,    350,    520,    660,    520,    490,    620,   1090,    670,    760) // L

ROW(    790,    700,    320,    560,   1070,    310,    680,   1250,    690,   1300,
       1910,    500,    400,    820,    580,    670,    800,   1060,    650,    740) // M

ROW(    760,    550,   1220,    950,    380,    890,   1100,    410,   1010,    350,
        500,   1760,    640,    970,    860,   1060,    960,    460,    280,    680) // N

ROW(    900,    280,    680,    740,    240,    550,    650,    400,    720,    520,
        400,    640,   2010,    820,    660,    910,    860,    540,     70,    370) // P

ROW(    840,    400,    970,   1210,    430,    660,   1130,    530,   1160,    660,
        820,    970,    820,   1700,   1120,    890,    870,    600,    470,    580) // Q

ROW(    730,    510,    690,    860,    280,    660,    950,    430,   1320,    520,
        580,    860,    660,   1120,   1790,    810,    800,    520,    660,    590) // R

ROW(   1120,    890,    910,    870,    380,    900,    820,    520,    860,    490,
        670,   1060,    910,    890,    810,   1560,   1220,    680,    390,    610) // S

ROW(    980,    750,    830,    810,    490,    610,    820,    790,    900,    620,
        800,    960,    860,    870,    800,   1220,   1600,    930,    290,    540) // T

ROW(    960,    850,    310,    580,    790,    310,    490,   1380,    570,   1090,
       1060,    460,    540,    600,    520,    680,    930,   1610,    370,    630) // V

ROW(    280,    670,      0,    180,   1230,    300,    680,    500,    280,    670,
        650,    280,     70,    470,    660,    390,    290,    370,   2620,   1290) // W

ROW(    480,    760,    430,    400,   1510,    220,   1220,    650,    520,    760,
        740,    680,    370,    580,    590,    610,    540,    630,   1290,   2070) // Y
	};

static SCORE Gonnet160[20][20] =
	{
//        A       C       D       E       F       G       H       I       K       L
//        M       N       P       Q       R       S       T       V       W       Y
ROW(   1240,    810,    670,    740,    400,    800,    600,    600,    660,    560,
        660,    660,    770,    710,    620,    940,    830,    790,    230,    410) // A

ROW(    810,   2130,    250,    260,    600,    440,    550,    530,    300,    490,
        590,    470,    260,    360,    430,    760,    640,    720,    570,    650) // C

ROW(    670,    250,   1480,   1120,     80,    710,    770,    160,    770,    130,
        280,   1040,    590,    840,    620,    780,    720,    290,      0,    360) // D

ROW(    740,    260,   1120,   1370,    160,    570,    770,    350,    910,    330,
        470,    830,    640,   1010,    750,    750,    700,    480,    140,    340) // E

ROW(    400,    600,     80,    160,   1690,     20,    710,    810,    250,    970,
        920,    310,    200,    370,    250,    330,    420,    700,   1100,   1340) // F

ROW(    800,    440,    710,    570,     20,   1600,    510,     80,    540,    110,
        260,    760,    480,    570,    570,    770,    540,    260,    230,    180) // G

ROW(    600,    550,    770,    770,    710,    510,   1710,    410,    800,    460,
        570,    930,    560,    950,    810,    700,    700,    430,    590,   1050) // H

ROW(    600,    530,    160,    350,    810,     80,    410,   1370,    430,   1080,
       1070,    340,    350,    460,    370,    450,    660,   1180,    440,    580) // I

ROW(    660,    300,    770,    910,    250,    540,    800,    430,   1330,    440,
        570,    860,    620,    980,   1130,    740,    760,    480,    240,    430) // K

ROW(    560,    490,    130,    330,    970,    110,    460,   1080,    440,   1350,
       1120,    300,    430,    540,    430,    420,    540,    950,    580,    670) // L

ROW(    660,    590,    280,    470,    920,    260,    570,   1070,    570,   1120,
       1540,    420,    360,    660,    490,    550,    670,    920,    560,    650) // M

ROW(    660,    470,   1040,    830,    310,    760,    930,    340,    860,    300,
        420,   1430,    560,    830,    740,    890,    810,    400,    230,    560) // N

ROW(    770,    260,    590,    640,    200,    480,    560,    350,    620,    430,
        360,    560,   1740,    700,    570,    780,    740,    460,     40,    300) // P

ROW(    710,    360,    840,   1010,    370,    570,    950,    460,    980,    540,
        660,    830,    700,   1340,    950,    760,    740,    510,    380,    490) // Q

ROW(    620,    430,    620,    750,    250,    570,    810,    370,   1130,    430,
        490,    740,    570,    950,   1490,    690,    690,    440,    540,    490) // R

ROW(    940,    760,    780,    750,    330,    770,    700,    450,    740,    420,
        550,    890,    780,    760,    690,   1220,   1010,    580,    310,    500) // S

ROW(    830,    640,    720,    700,    420,    540,    700,    660,    760,    540,
        670,    810,    740,    740,    690,   1010,   1280,    780,    240,    460) // T

ROW(    790,    720,    290,    480,    700,    260,    430,   1180,    480,    950,
        920,    400,    460,    510,    440,    580,    780,   1310,    330,    540) // V

ROW(    230,    570,      0,    140,   1100,    230,    590,    440,    240,    580,
        560,    230,     40,    380,    540,    310,    240,    330,   2360,   1160) // W

ROW(    410,    650,    360,    340,   1340,    180,   1050,    580,    430,    670,
        650,    560,    300,    490,    490,    500,    460,    540,   1160,   1780) // Y
	};

double Gonnet16[21][21] =
	{
//       A      C      D      E      F      G      H      I      K      L
//       M      N      P      Q      R      S      T      V      W      Y
ROW(   124,    81,    67,    74,    40,    80,    60,    60,    66,    56,
        66,    66,    77,    71,    62,    94,    83,    79,    23,    41) // A

ROW(    81,   213,    25,    26,    60,    44,    55,    53,    30,    49,
        59,    47,    26,    36,    43,    76,    64,    72,    57,    65) // C

ROW(    67,    25,   148,   112,     8,    71,    77,    16,    77,    13,
        28,   104,    59,    84,    62,    78,    72,    29,     0,    36) // D

ROW(    74,    26,   112,   137,    16,    57,    77,    35,    91,    33,
        47,    83,    64,   101,    75,    75,    70,    48,    14,    34) // E

ROW(    40,    60,     8,    16,   169,     2,    71,    81,    25,    97,
        92,    31,    20,    37,    25,    33,    42,    70,   110,   134) // F

ROW(    80,    44,    71,    57,     2,   160,    51,     8,    54,    11,
        26,    76,    48,    57,    57,    77,    54,    26,    23,    18) // G

ROW(    60,    55,    77,    77,    71,    51,   171,    41,    80,    46,
        57,    93,    56,    95,    81,    70,    70,    43,    59,   105) // H

ROW(    60,    53,    16,    35,    81,     8,    41,   137,    43,   108,
       107,    34,    35,    46,    37,    45,    66,   118,    44,    58) // I

ROW(    66,    30,    77,    91,    25,    54,    80,    43,   133,    44,
        57,    86,    62,    98,   113,    74,    76,    48,    24,    43) // K

ROW(    56,    49,    13,    33,    97,    11,    46,   108,    44,   135,
       112,    30,    43,    54,    43,    42,    54,    95,    58,    67) // L

ROW(    66,    59,    28,    47,    92,    26,    57,   107,    57,   112,
       154,    42,    36,    66,    49,    55,    67,    92,    56,    65) // M

ROW(    66,    47,   104,    83,    31,    76,    93,    34,    86,    30,
        42,   143,    56,    83,    74,    89,    81,    40,    23,    56) // N

ROW(    77,    26,    59,    64,    20,    48,    56,    35,    62,    43,
        36,    56,   174,    70,    57,    78,    74,    46,     4,    30) // P

ROW(    71,    36,    84,   101,    37,    57,    95,    46,    98,    54,
        66,    83,    70,   134,    95,    76,    74,    51,    38,    49) // Q

ROW(    62,    43,    62,    75,    25,    57,    81,    37,   113,    43,
        49,    74,    57,    95,   149,    69,    69,    44,    54,    49) // R

ROW(    94,    76,    78,    75,    33,    77,    70,    45,    74,    42,
        55,    89,    78,    76,    69,   122,   101,    58,    31,    50) // S

ROW(    83,    64,    72,    70,    42,    54,    70,    66,    76,    54,
        67,    81,    74,    74,    69,   101,   128,    78,    24,    46) // T

ROW(    79,    72,    29,    48,    70,    26,    43,   118,    48,    95,
        92,    40,    46,    51,    44,    58,    78,   131,    33,    54) // V

ROW(    23,    57,     0,    14,   110,    23,    59,    44,    24,    58,
        56,    23,     4,    38,    54,    31,    24,    33,   236,   116) // W

ROW(    41,    65,    36,    34,   134,    18,   105,    58,    43,    67,
        65,    56,    30,    49,    49,    50,    46,    54,   116,   178) // Y
	};

static double Gonnet250[20][20] =
	{
//        A       C       D       E       F       G       H       I       K       L
//        M       N       P       Q       R       S       T       V       W       Y
ROW(    760,    570,    490,    520,    290,    570,    440,    440,    480,    400,
        450,    490,    550,    500,    460,    630,    580,    530,    160,    300) // A

ROW(    570,   1670,    200,    220,    440,    320,    390,    410,    240,    370,
        430,    340,    210,    280,    300,    530,    470,    520,    420,    470) // C

ROW(    490,    200,    990,    790,     70,    530,    560,    140,    570,    120,
        220,    740,    450,    610,    490,    570,    520,    230,      0,    240) // D

ROW(    520,    220,    790,    880,    130,    440,    560,    250,    640,    240,
        320,    610,    470,    690,    560,    540,    510,    330,     90,    250) // E

ROW(    290,    440,     70,    130,   1220,      0,    510,    620,    190,    720,
        680,    210,    140,    260,    200,    240,    300,    530,    880,   1030) // F

ROW(    570,    320,    530,    440,      0,   1180,    380,     70,    410,     80,
        170,    560,    360,    420,    420,    560,    410,    190,    120,    120) // G

ROW(    440,    390,    560,    560,    510,    380,   1120,    300,    580,    330,
        390,    640,    410,    640,    580,    500,    490,    320,    440,    740) // H

ROW(    440,    410,    140,    250,    620,     70,    300,    920,    310,    800,
        770,    240,    260,    330,    280,    340,    460,    830,    340,    450) // I

ROW(    480,    240,    570,    640,    190,    410,    580,    310,    840,    310,
        380,    600,    460,    670,    790,    530,    530,    350,    170,    310) // K

ROW(    400,    370,    120,    240,    720,     80,    330,    800,    310,    920,
        800,    220,    290,    360,    300,    310,    390,    700,    450,    520) // L

ROW(    450,    430,    220,    320,    680,    170,    390,    770,    380,    800,
        950,    300,    280,    420,    350,    380,    460,    680,    420,    500) // M

ROW(    490,    340,    740,    610,    210,    560,    640,    240,    600,    220,
        300,    900,    430,    590,    550,    610,    570,    300,    160,    380) // N

ROW(    550,    210,    450,    470,    140,    360,    410,    260,    460,    290,
        280,    430,   1280,    500,    430,    560,    530,    340,     20,    210) // P

ROW(    500,    280,    610,    690,    260,    420,    640,    330,    670,    360,
        420,    590,    500,    790,    670,    540,    520,    370,    250,    350) // Q

ROW(    460,    300,    490,    560,    200,    420,    580,    280,    790,    300,
        350,    550,    430,    670,    990,    500,    500,    320,    360,    340) // R

ROW(    630,    530,    570,    540,    240,    560,    500,    340,    530,    310,
        380,    610,    560,    540,    500,    740,    670,    420,    190,    330) // S

ROW(    580,    470,    520,    510,    300,    410,    490,    460,    530,    390,
        460,    570,    530,    520,    500,    670,    770,    520,    170,    330) // T

ROW(    530,    520,    230,    330,    530,    190,    320,    830,    350,    700,
        680,    300,    340,    370,    320,    420,    520,    860,    260,    410) // V

ROW(    160,    420,      0,     90,    880,    120,    440,    340,    170,    450,
        420,    160,     20,    250,    360,    190,    170,    260,   1940,    930) // W

ROW(    300,    470,    240,    250,   1030,    120,    740,    450,    310,    520,
        500,    380,    210,    350,    340,    330,    330,    410,    930,   1300) // Y
	};

static double Gonnet350[20][20] =
	{
//        A       C       D       E       F       G       H       I       K       L
//        M       N       P       Q       R       S       T       V       W       Y
ROW(    450,    390,    350,    360,    210,    400,    310,    310,    340,    280,
        310,    350,    380,    350,    330,    410,    390,    350,    110,    210) // A

ROW(    390,   1280,    160,    180,    320,    230,    270,    300,    190,    280,
        310,    240,    170,    210,    220,    360,    330,    370,    310,    340) // C

ROW(    350,    160,    640,    540,     50,    390,    400,    110,    410,    100,
        160,    500,    330,    430,    370,    400,    370,    170,      0,    170) // D

ROW(    360,    180,    540,    550,    100,    330,    390,    180,    440,    170,
        220,    440,    350,    460,    410,    380,    360,    230,     60,    180) // E

ROW(    210,    320,     50,    100,    860,      0,    360,    460,    140,    530,
        490,    150,    100,    190,    150,    170,    220,    400,    700,    770) // F

ROW(    400,    230,    390,    330,      0,    860,    280,     60,    310,     50,
        120,    400,    280,    310,    310,    400,    300,    140,     50,     80) // G

ROW(    310,    270,    400,    390,    360,    280,    680,    220,    400,    240,
        270,    430,    300,    420,    410,    350,    340,    240,    320,    500) // H

ROW(    310,    300,    110,    180,    460,     60,    220,    620,    220,    570,
        540,    170,    190,    240,    200,    240,    320,    570,    260,    340) // I

ROW(    340,    190,    410,    440,    140,    310,    400,    220,    530,    210,
        260,    420,    330,    450,    530,    370,    370,    250,    120,    210) // K

ROW(    280,    280,    100,    170,    530,     50,    240,    570,    210,    630,
        560,    160,    200,    240,    210,    220,    280,    510,    340,    400) // L

ROW(    310,    310,    160,    220,    490,    120,    270,    540,    260,    560,
        580,    210,    210,    280,    240,    260,    310,    490,    320,    370) // M

ROW(    350,    240,    500,    440,    150,    400,    430,    170,    420,    160,
        210,    550,    320,    410,    390,    410,    390,    220,    110,    250) // N

ROW(    380,    170,    330,    350,    100,    280,    300,    190,    330,    200,
        210,    320,    910,    350,    310,    390,    370,    240,     10,    150) // P

ROW(    350,    210,    430,    460,    190,    310,    420,    240,    450,    240,
        280,    410,    350,    470,    450,    370,    360,    260,    160,    240) // Q

ROW(    330,    220,    370,    410,    150,    310,    410,    200,    530,    210,
        240,    390,    310,    450,    630,    360,    350,    230,    230,    230) // R

ROW(    410,    360,    400,    380,    170,    400,    350,    240,    370,    220,
        260,    410,    390,    370,    360,    450,    430,    290,    130,    230) // S

ROW(    390,    330,    370,    360,    220,    300,    340,    320,    370,    280,
        310,    390,    370,    360,    350,    430,    460,    350,    120,    230) // T

ROW(    350,    370,    170,    230,    400,    140,    240,    570,    250,    510,
        490,    220,    240,    260,    230,    290,    350,    560,    210,    310) // V

ROW(    110,    310,      0,     60,    700,     50,    320,    260,    120,    340,
        320,    110,     10,    160,    230,    130,    120,    210,   1590,    740) // W

ROW(    210,    340,    170,    180,    770,     80,    500,    340,    210,    400,
        370,    250,    150,    240,    230,    230,    230,    310,    740,    920) // Y
	};

const t_ROW *GetGonnetMatrix(unsigned N)
	{
	switch (N)
		{
	case 80:
		return Gonnet80;
	case 120:
		return Gonnet120;
	//case 16:
	//	return Gonnet16;
	//case 160:
	//	return Gonnet160;
	case 250:
		return Gonnet250;
	case 350:
		return Gonnet350;
		}
	Quit("Invalid Gonnet%u", N);
	return 0;
	}

//SCORE GetGonnetGapOpen(unsigned N)
//	{
//	switch (N)
//		{
//	case 80:
//		return -639;
//	case 120:
//		return -863;
//	case 160:
//		return -611;
//	case 250:
//		return -308;
//	case 350:
//		return -158;
//		}
//	Quit("Invalid Gonnet%u", N);
//	return 0;
//	}

SCORE GetGonnetGapOpen(unsigned N)
	{
	switch (N)
		{
	case 80:
		return -1000;
	case 120:
		return -800;
	case 160:
		return -700;
	case 250:
		return -200;
	case 350:
		return -175;
		}
	Quit("Invalid Gonnet%u", N);
	return 0;
	}

SCORE GetGonnetGapExtend(unsigned N)
	{
	switch (N)
		{
	case 80:
		return 350;
	case 120:
		return 200;
	case 160:
		return 175;
	case 250:
		return 20;
	case 350:
		return 20;
		}
	Quit("Invalid Gonnet%u", N);
	return 0;
	}

//double GonnetLookup[400][400];
//
//static bool InitGonnetLookup()
//	{
//	for (unsigned i = 0; i < 400; ++i)
//		{
//		const unsigned A1 = i/20;
//		const unsigned A2 = i%20;
//		for (unsigned j = 0; j <= i; ++j)
//			{
//			const unsigned B1 = j/20;
//			const unsigned B2 = j%20;
//			
//			const double s00 = Gonnet16[A1][B1];
//			const double s01 = Gonnet16[A1][B2];
//			const double s10 = Gonnet16[A2][B1];
//			const double s11 = Gonnet16[A2][B2];
//
//			GonnetLookup[i][j] = GonnetLookup[j][i] = (s00 + s01 + s10 + s11)/4;
//			}
//		}
//	return true;
//	}
//
//static bool bGonnetLookupInitialized = InitGonnetLookup();
