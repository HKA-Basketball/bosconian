#ifndef BOSCONIAN_LEVELINFO_H
#define BOSCONIAN_LEVELINFO_H

#include <vector>

#include "../../Utilities/Vector2D.h"

struct LevelInfo {
    int levelNumber;
    std::vector<Vector2D> basePositions;
    Vector2D playerSpawn;
};

const std::vector<LevelInfo> levelInfoListDef = {
        {1,
                {{1167.63, 3082.39}, {1655.11, 2685.28}, {767.853, 2271.38}},
                {1500, 3800}},
        {2,
                {{2174.95, 1654.63}, {2758.78, 1653.37}, {538.006, 1837.99}, {550.276, 1314.9}},
                {1500.52, 2000.15}},
        {3,
                {{1311.71, 1672.51}, {1784.4, 1823.47}, {2098.92, 2160.79}, {1598.64, 2620.08}, {1154.95, 2620.08}, {637.557, 2620.08}, {319.138, 2189.38}, {653.958, 1837.07}},
                {1500.06, 2000.43}},
        {4,
                {{315.937, 494.167}, {2307.27, 875.59}, {1751.2, 2231.9}, {1200.94, 2431.26}, {667.758, 2663.2}, {1201.82, 3368.87}, {410.226, 3807.96}, {2338.15, 3581.61}},
                {1500.26, 2000.56}},
        {5,
                {{1269.28, 1081}, {2304.23, 1357.33}, {2702.94, 1909.2}, {2337.02, 2598.83}, {1513.83, 2976.34}, {570.518, 2666.21}, {408.708, 1840.81}, {564.717, 1220.16}},
                {1500.43, 2000.98}},
        {6,
                {{252.215, 181.51}, {1837.86, 329.714}, {2561.09, 525.726}, {2553.89, 1180.92}, {1916.64, 1523.03}, {1524.74, 3601.33}, {1092.65, 3042.66}, {1552.93, 2415.22}},
                {1500.75, 0.0326856}},
        {7,
                {{2724.48, 2000.76}, {2281.59, 2000.76}, {1824.7, 2000.76}, {1411.8, 2000.76}, {1037.89, 2000.76}, {646.272, 2000.76}, {267.249, 2000.76}},
                {1500.89, 3800.5}},
        {8,
                {{1965.24, 1566.98}, {1175.03, 1566.98}, {764.449, 1162.87}, {1564.13, 2325.19}, {601.639, 2325.19}, {2560.69, 2325.19}},
                {1500.35, 2000.67}},
        {9,
                {{2030.62, 1469.6}, {2679.46, 820.695}, {1110.37, 2389.22}, {454.151, 3045.26}, {1039.98, 1520.43}, {389.347, 869.942}, {2017.38, 2376.5}, {2650.43, 3053.54}},
                {1500.74, 2000.07}},
        {10,
                {{1400.95, 3413.15}, {1400.95, 3030.05}, {1400.95, 2593.75}, {1400.95, 2196.05}, {1726.27, 1870.53}, {2072.58, 1524.21}, {1043.83, 1842.54}, {698.615, 1497.42}},
                {1500.52, 3800.46}},
        {11,
                {{1971.32, 1527.67}, {2457.6, 1041.39}, {1378.27, 1052.18}, {480.118, 1052.18}, {1062.61, 2438.17}, {449.583, 3053.42}, {1400.53, 3051.22}, {2425.08, 3051.22}},
                {1500.24, 2000.15}},
        {12,
                {{2371.8, 1020.12}, {2672.11, 2720.23}, {2077.44, 3186.02}, {1336.16, 3313.46}, {690.065, 3119.6}, {280.276, 2753.33}, {271.171, 1025.53}},
                {1500.92, 2000.65}},
        {13,
                {{1017.69, 765.185}, {2395.05, 1765.38}, {2121.34, 3145.32}, {1799.42, 3655.84}, {1277.49, 3649.03}, {922.738, 3154.56}, {632.101, 1784.45}},
                {1500.28, 3800.32}},
        {14,
                {{1419.16, 3126.85}, {1419.16, 2564.79}, {1693.1, 2110.1}, {2024.62, 1743.59}, {2226.97, 1256.11}, {1711.49, 782.35}, {949.253, 782.35}, {356.417, 1202.32}},
                {1500.34, 3800.49}}
};

std::vector<LevelInfo> levelInfoList = levelInfoListDef;

#endif //BOSCONIAN_LEVELINFO_H
