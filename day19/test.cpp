#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <array>
#include <sstream>
#include <string>
#include <string_view>

using namespace Day19;

constexpr std::array SMALL_EXAMPLE_SCANNER_0 = {
        Point{0, 2},
        Point{4, 1},
        Point{3, 3},
};

constexpr std::array SMALL_EXAMPLE_SCANNER_1 = {
        Point{-1, -1},
        Point{-5, 0},
        Point{-2, 1},
};

constexpr std::string_view EXAMPLE_INPUT = R"(--- scanner 0 ---
404,-588,-901
528,-643,409
-838,591,734
390,-675,-793
-537,-823,-458
-485,-357,347
-345,-311,381
-661,-816,-575
-876,649,763
-618,-824,-621
553,345,-567
474,580,667
-447,-329,318
-584,868,-557
544,-627,-890
564,392,-477
455,729,728
-892,524,684
-689,845,-530
423,-701,434
7,-33,-71
630,319,-379
443,580,662
-789,900,-551
459,-707,401

--- scanner 1 ---
686,422,578
605,423,415
515,917,-361
-336,658,858
95,138,22
-476,619,847
-340,-569,-846
567,-361,727
-460,603,-452
669,-402,600
729,430,532
-500,-761,534
-322,571,750
-466,-666,-811
-429,-592,574
-355,545,-477
703,-491,-529
-328,-685,520
413,935,-424
-391,539,-444
586,-435,557
-364,-763,-893
807,-499,-711
755,-354,-619
553,889,-390

--- scanner 2 ---
649,640,665
682,-795,504
-784,533,-524
-644,584,-595
-588,-843,648
-30,6,44
-674,560,763
500,723,-460
609,671,-379
-555,-800,653
-675,-892,-343
697,-426,-610
578,704,681
493,664,-388
-671,-858,530
-667,343,800
571,-461,-707
-138,-166,112
-889,563,-600
646,-828,498
640,759,510
-630,509,768
-681,-892,-333
673,-379,-804
-742,-814,-386
577,-820,562

--- scanner 3 ---
-589,542,597
605,-692,669
-500,565,-823
-660,373,557
-458,-679,-417
-488,449,543
-626,468,-788
338,-750,-386
528,-832,-391
562,-778,733
-938,-730,414
543,643,-506
-524,371,-870
407,773,750
-104,29,83
378,-903,-323
-778,-728,485
426,699,580
-438,-605,-362
-469,-447,-387
509,732,623
647,635,-688
-868,-804,481
614,-800,639
595,780,-596

--- scanner 4 ---
727,592,562
-293,-554,779
441,611,-461
-714,465,-776
-743,427,-804
-660,-479,-426
832,-632,460
927,-485,-438
408,393,-506
466,436,-512
110,16,151
-258,-428,682
-393,719,612
-211,-452,876
808,-476,-593
-575,615,604
-485,667,467
-680,325,-822
-627,-443,-432
872,-547,-609
833,512,582
807,604,487
839,-516,451
891,-625,532
-652,-548,-490
30,-46,-14
)";

constexpr std::array EXAMPLE_SCANNER_0 = {
        Point{404, -588, -901},  Point{528, -643, 409},   Point{-838, 591, 734},
        Point{390, -675, -793},  Point{-537, -823, -458}, Point{-485, -357, 347},
        Point{-345, -311, 381},  Point{-661, -816, -575}, Point{-876, 649, 763},
        Point{-618, -824, -621}, Point{553, 345, -567},   Point{474, 580, 667},
        Point{-447, -329, 318},  Point{-584, 868, -557},  Point{544, -627, -890},
        Point{564, 392, -477},   Point{455, 729, 728},    Point{-892, 524, 684},
        Point{-689, 845, -530},  Point{423, -701, 434},   Point{7, -33, -71},
        Point{630, 319, -379},   Point{443, 580, 662},    Point{-789, 900, -551},
        Point{459, -707, 401},
};

constexpr std::array EXAMPLE_SCANNER_1 = {
        Point{686, 422, 578},    Point{605, 423, 415},    Point{515, 917, -361},
        Point{-336, 658, 858},   Point{95, 138, 22},      Point{-476, 619, 847},
        Point{-340, -569, -846}, Point{567, -361, 727},   Point{-460, 603, -452},
        Point{669, -402, 600},   Point{729, 430, 532},    Point{-500, -761, 534},
        Point{-322, 571, 750},   Point{-466, -666, -811}, Point{-429, -592, 574},
        Point{-355, 545, -477},  Point{703, -491, -529},  Point{-328, -685, 520},
        Point{413, 935, -424},   Point{-391, 539, -444},  Point{586, -435, 557},
        Point{-364, -763, -893}, Point{807, -499, -711},  Point{755, -354, -619},
        Point{553, 889, -390},
};

constexpr std::array EXAMPLE_SCANNER_2 = {
        Point{649, 640, 665},    Point{682, -795, 504},   Point{-784, 533, -524},
        Point{-644, 584, -595},  Point{-588, -843, 648},  Point{-30, 6, 44},
        Point{-674, 560, 763},   Point{500, 723, -460},   Point{609, 671, -379},
        Point{-555, -800, 653},  Point{-675, -892, -343}, Point{697, -426, -610},
        Point{578, 704, 681},    Point{493, 664, -388},   Point{-671, -858, 530},
        Point{-667, 343, 800},   Point{571, -461, -707},  Point{-138, -166, 112},
        Point{-889, 563, -600},  Point{646, -828, 498},   Point{640, 759, 510},
        Point{-630, 509, 768},   Point{-681, -892, -333}, Point{673, -379, -804},
        Point{-742, -814, -386}, Point{577, -820, 562},
};

constexpr std::array EXAMPLE_SCANNER_3 = {
        Point{-589, 542, 597},   Point{605, -692, 669},   Point{-500, 565, -823},
        Point{-660, 373, 557},   Point{-458, -679, -417}, Point{-488, 449, 543},
        Point{-626, 468, -788},  Point{338, -750, -386},  Point{528, -832, -391},
        Point{562, -778, 733},   Point{-938, -730, 414},  Point{543, 643, -506},
        Point{-524, 371, -870},  Point{407, 773, 750},    Point{-104, 29, 83},
        Point{378, -903, -323},  Point{-778, -728, 485},  Point{426, 699, 580},
        Point{-438, -605, -362}, Point{-469, -447, -387}, Point{509, 732, 623},
        Point{647, 635, -688},   Point{-868, -804, 481},  Point{614, -800, 639},
        Point{595, 780, -596},
};

constexpr std::array EXAMPLE_SCANNER_4 = {
        Point{727, 592, 562},    Point{-293, -554, 779}, Point{441, 611, -461},
        Point{-714, 465, -776},  Point{-743, 427, -804}, Point{-660, -479, -426},
        Point{832, -632, 460},   Point{927, -485, -438}, Point{408, 393, -506},
        Point{466, 436, -512},   Point{110, 16, 151},    Point{-258, -428, 682},
        Point{-393, 719, 612},   Point{-211, -452, 876}, Point{808, -476, -593},
        Point{-575, 615, 604},   Point{-485, 667, 467},  Point{-680, 325, -822},
        Point{-627, -443, -432}, Point{872, -547, -609}, Point{833, 512, 582},
        Point{807, 604, 487},    Point{839, -516, 451},  Point{891, -625, 532},
        Point{-652, -548, -490}, Point{30, -46, -14},
};

constexpr std::array<std::span<Point const>, 5> EXAMPLE_SCANNERS = {
        EXAMPLE_SCANNER_0, EXAMPLE_SCANNER_1, EXAMPLE_SCANNER_2,
        EXAMPLE_SCANNER_3, EXAMPLE_SCANNER_4,
};

constexpr std::array EXAMPLE_OVERLAP_BETWEEN_SCANNERS_0_AND_1_RELATIVE_TO_SCANNER_0 = {
        Point{-618, -824, -621}, Point{-537, -823, -458}, Point{-447, -329, 318},
        Point{404, -588, -901},  Point{544, -627, -890},  Point{528, -643, 409},
        Point{-661, -816, -575}, Point{390, -675, -793},  Point{423, -701, 434},
        Point{-345, -311, 381},  Point{459, -707, 401},   Point{-485, -357, 347},
};

constexpr std::array EXAMPLE_OVERLAP_BETWEEN_SCANNERS_0_AND_1_RELATIVE_TO_SCANNER_1 = {
        Point{686, 422, 578},  Point{605, 423, 415},   Point{515, 917, -361},
        Point{-336, 658, 858}, Point{-476, 619, 847},  Point{-460, 603, -452},
        Point{729, 430, 532},  Point{-322, 571, 750},  Point{-355, 545, -477},
        Point{413, 935, -424}, Point{-391, 539, -444}, Point{553, 889, -390},
};

constexpr std::array EXAMPLE_OVERLAP_BETWEEN_SCANNERS_1_AND_4_RELATIVE_TO_SCANNER_0 = {
        Point{459, -707, 401},   Point{-739, -1745, 668}, Point{-485, -357, 347},
        Point{432, -2009, 850},  Point{528, -643, 409},   Point{423, -701, 434},
        Point{-345, -311, 381},  Point{408, -1815, 803},  Point{534, -1912, 768},
        Point{-687, -1600, 576}, Point{-447, -329, 318},  Point{-635, -1737, 486},
};

constexpr std::array EXAMPLE_BEACONS_RELATIVE_TO_SCANNER_0 = {
        Point{-892, 524, 684},    Point{-876, 649, 763},    Point{-838, 591, 734},
        Point{-789, 900, -551},   Point{-739, -1745, 668},  Point{-706, -3180, -659},
        Point{-697, -3072, -689}, Point{-689, 845, -530},   Point{-687, -1600, 576},
        Point{-661, -816, -575},  Point{-654, -3158, -753}, Point{-635, -1737, 486},
        Point{-631, -672, 1502},  Point{-624, -1620, 1868}, Point{-620, -3212, 371},
        Point{-618, -824, -621},  Point{-612, -1695, 1788}, Point{-601, -1648, -643},
        Point{-584, 868, -557},   Point{-537, -823, -458},  Point{-532, -1715, 1894},
        Point{-518, -1681, -600}, Point{-499, -1607, -770}, Point{-485, -357, 347},
        Point{-470, -3283, 303},  Point{-456, -621, 1527},  Point{-447, -329, 318},
        Point{-430, -3130, 366},  Point{-413, -627, 1469},  Point{-345, -311, 381},
        Point{-36, -1284, 1171},  Point{-27, -1108, -65},   Point{7, -33, -71},
        Point{12, -2351, -103},   Point{26, -1119, 1091},   Point{346, -2985, 342},
        Point{366, -3059, 397},   Point{377, -2827, 367},   Point{390, -675, -793},
        Point{396, -1931, -563},  Point{404, -588, -901},   Point{408, -1815, 803},
        Point{423, -701, 434},    Point{432, -2009, 850},   Point{443, 580, 662},
        Point{455, 729, 728},     Point{456, -540, 1869},   Point{459, -707, 401},
        Point{465, -695, 1988},   Point{474, 580, 667},     Point{496, -1584, 1900},
        Point{497, -1838, -617},  Point{527, -524, 1933},   Point{528, -643, 409},
        Point{534, -1912, 768},   Point{544, -627, -890},   Point{553, 345, -567},
        Point{564, 392, -477},    Point{568, -2007, -577},  Point{605, -1665, 1952},
        Point{612, -1593, 1893},  Point{630, 319, -379},    Point{686, -3108, -505},
        Point{776, -3184, -501},  Point{846, -3110, -434},  Point{1135, -1161, 1235},
        Point{1243, -1093, 1063}, Point{1660, -552, 429},   Point{1693, -557, 386},
        Point{1735, -437, 1738},  Point{1749, -1800, 1813}, Point{1772, -405, 1572},
        Point{1776, -675, 371},   Point{1779, -442, 1789},  Point{1780, -1548, 337},
        Point{1786, -1538, 337},  Point{1847, -1591, 415},  Point{1889, -1729, 1762},
        Point{1994, -1805, 1792},
};

constexpr std::array SYMMETRY_EQUIVALENTS = {
        std::array{
                Point{-1, -1, 1},
                Point{-2, -2, 2},
                Point{-3, -3, 3},
                Point{-2, -3, 1},
                Point{5, 6, -4},
                Point{8, 0, 7},
        },
        std::array{
                Point{1, -1, 1},
                Point{2, -2, 2},
                Point{3, -3, 3},
                Point{2, -1, 3},
                Point{-5, 4, -6},
                Point{-8, -7, 0},
        },
        std::array{
                Point{-1, -1, -1},
                Point{-2, -2, -2},
                Point{-3, -3, -3},
                Point{-1, -3, -2},
                Point{4, 6, 5},
                Point{-7, 0, 8},
        },
        std::array{
                Point{1, 1, -1},
                Point{2, 2, -2},
                Point{3, 3, -3},
                Point{1, 3, -2},
                Point{-4, -6, 5},
                Point{7, 0, 8},
        },
        std::array{
                Point{1, 1, 1},
                Point{2, 2, 2},
                Point{3, 3, 3},
                Point{3, 1, 2},
                Point{-6, -4, -5},
                Point{0, 7, -8},
        },
};

constexpr std::array ISOMETRIES = {
        std::array{
                Point{1, 0, 0},
                Point{0, 1, 0},
                Point{0, 0, 1},
        },
        std::array{
                Point{1, 0, 0},
                Point{0, 0, -1},
                Point{0, 1, 0},
        },
        std::array{
                Point{0, 1, 0},
                Point{0, 0, -1},
                Point{-1, 0, 0},
        },
        std::array{
                Point{-1, 0, 0},
                Point{0, 0, -1},
                Point{0, -1, 0},
        },
        std::array{
                Point{0, 0, 1},
                Point{-1, 0, 0},
                Point{0, -1, 0},
        },
        std::array{
                Point{0, 0, 1},
                Point{0, 1, 0},
                Point{-1, 0, 0},
        },
        std::array{
                Point{0, 0, 1},
                Point{1, 0, 0},
                Point{0, 1, 0},
        },
        std::array{
                Point{0, -1, 0},
                Point{1, 0, 0},
                Point{0, 0, 1},
        },
        std::array{
                Point{0, -1, 0},
                Point{0, 0, 1},
                Point{-1, 0, 0},
        },
        std::array{
                Point{0, 0, -1},
                Point{0, -1, 0},
                Point{-1, 0, 0},
        },
        std::array{
                Point{0, 0, -1},
                Point{1, 0, 0},
                Point{0, -1, 0},
        },
        std::array{
                Point{1, 0, 0},
                Point{0, 0, 1},
                Point{0, -1, 0},
        },
        std::array{
                Point{1, 0, 0},
                Point{0, -1, 0},
                Point{0, 0, -1},
        },
        std::array{
                Point{0, 1, 0},
                Point{1, 0, 0},
                Point{0, 0, -1},
        },
        std::array{
                Point{-1, 0, 0},
                Point{0, 1, 0},
                Point{0, 0, -1},
        },
        std::array{
                Point{-1, 0, 0},
                Point{0, 0, 1},
                Point{0, 1, 0},
        },
        std::array{
                Point{-1, 0, 0},
                Point{0, -1, 0},
                Point{0, 0, 1},
        },
        std::array{
                Point{0, 1, 0},
                Point{-1, 0, 0},
                Point{0, 0, 1},
        },
        std::array{
                Point{0, 0, -1},
                Point{-1, 0, 0},
                Point{0, 1, 0},
        },
        std::array{
                Point{0, -1, 0},
                Point{-1, 0, 0},
                Point{0, 0, -1},
        },
        std::array{
                Point{0, -1, 0},
                Point{0, 0, -1},
                Point{1, 0, 0},
        },
        std::array{
                Point{0, 0, -1},
                Point{0, 1, 0},
                Point{1, 0, 0},
        },
        std::array{
                Point{0, 1, 0},
                Point{0, 0, 1},
                Point{1, 0, 0},
        },
        std::array{
                Point{0, 0, 1},
                Point{0, -1, 0},
                Point{1, 0, 0},
        },
};

TEST(Day19, parse_scanners) {
  using ::testing::ElementsAre;
  using ::testing::ElementsAreArray;
  std::stringstream stream{std::string{EXAMPLE_INPUT}};
  EXPECT_THAT(parse_scanners(stream),
              ElementsAre(ElementsAreArray(EXAMPLE_SCANNER_0), ElementsAreArray(EXAMPLE_SCANNER_1),
                          ElementsAreArray(EXAMPLE_SCANNER_2), ElementsAreArray(EXAMPLE_SCANNER_3),
                          ElementsAreArray(EXAMPLE_SCANNER_4)));
}

TEST(Day19, generate_all_orientations_of_orthogonal_tripod) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  EXPECT_THAT(orientations(ISOMETRIES.front())
                      | std::views::transform([](std::span<Point const> rotated_span) {
                          std::array<Point, 3> rotated_array;
                          std::ranges::copy(rotated_span, rotated_array.begin());
                          return rotated_array;
                        })
                      | to<std::vector>(),
              ElementsAreArray(ISOMETRIES));
}

TEST(Day19, generate_some_orientations_of_example) {
  using cor3ntin::rangesnext::to;
  using ::testing::IsSupersetOf;
  EXPECT_THAT(orientations(SYMMETRY_EQUIVALENTS.front())
                      | std::views::transform([](std::span<Point const> rotated_span) {
                          std::array<Point, 6> rotated_array;
                          std::ranges::copy(rotated_span, rotated_array.begin());
                          return rotated_array;
                        })
                      | to<std::vector>(),
              IsSupersetOf(SYMMETRY_EQUIVALENTS));
}

TEST(Day19, translations_small_example) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAre;
  using ::testing::UnorderedElementsAre;
  EXPECT_THAT(translations(SMALL_EXAMPLE_SCANNER_0, SMALL_EXAMPLE_SCANNER_1) | to<std::vector>(),
              UnorderedElementsAre(ElementsAre(Point{-1, -1}, Point{3, -2}, Point{2, 0}),
                                   ElementsAre(Point{-5, 0}, Point{-1, -1}, Point{-2, 1}),
                                   ElementsAre(Point{-2, 1}, Point{2, 0}, Point{1, 2}),
                                   ElementsAre(Point{-5, 0}, Point{-1, -1}, Point{-2, 1}),
                                   ElementsAre(Point{-9, 1}, Point{-5, 0}, Point{-6, 2}),
                                   ElementsAre(Point{-6, 2}, Point{-2, 1}, Point{-3, 3}),
                                   ElementsAre(Point{-4, -2}, Point{0, -3}, Point{-1, -1}),
                                   ElementsAre(Point{-8, -1}, Point{-4, -2}, Point{-5, 0}),
                                   ElementsAre(Point{-5, 0}, Point{-1, -1}, Point{-2, 1})));
  EXPECT_THAT(translations(SMALL_EXAMPLE_SCANNER_1, SMALL_EXAMPLE_SCANNER_0) | to<std::vector>(),
              UnorderedElementsAre(ElementsAre(Point{0, 2}, Point{-4, 3}, Point{-1, 4}),
                                   ElementsAre(Point{4, 1}, Point{0, 2}, Point{3, 3}),
                                   ElementsAre(Point{3, 3}, Point{-1, 4}, Point{2, 5}),
                                   ElementsAre(Point{4, 1}, Point{0, 2}, Point{3, 3}),
                                   ElementsAre(Point{8, 0}, Point{4, 1}, Point{7, 2}),
                                   ElementsAre(Point{7, 2}, Point{3, 3}, Point{6, 4}),
                                   ElementsAre(Point{1, 0}, Point{-3, 1}, Point{0, 2}),
                                   ElementsAre(Point{5, -1}, Point{1, 0}, Point{4, 1}),
                                   ElementsAre(Point{4, 1}, Point{0, 2}, Point{3, 3})));
}

TEST(Day19, overlap_small_example) {
  using cor3ntin::rangesnext::to;
  auto sorted_scanner_0 = SMALL_EXAMPLE_SCANNER_0 | to<std::vector>();
  std::ranges::sort(sorted_scanner_0);

  EXPECT_EQ(overlap(SMALL_EXAMPLE_SCANNER_1, sorted_scanner_0, 3), sorted_scanner_0);
}

TEST(Day19, overlap_example) {
  using cor3ntin::rangesnext::to;
  using ::testing::IsSupersetOf;
  auto sorted_scanner_0 = EXAMPLE_SCANNER_0 | to<std::vector>();
  auto sorted_scanner_1 = EXAMPLE_SCANNER_1 | to<std::vector>();
  std::ranges::sort(sorted_scanner_0);
  std::ranges::sort(sorted_scanner_1);

  auto overlap_0_and_1_relative_to_0 = overlap(EXAMPLE_SCANNER_1, sorted_scanner_0, 12);
  ASSERT_TRUE(std::ranges::is_sorted(overlap_0_and_1_relative_to_0));
  EXPECT_THAT(overlap_0_and_1_relative_to_0,
              IsSupersetOf(EXAMPLE_OVERLAP_BETWEEN_SCANNERS_0_AND_1_RELATIVE_TO_SCANNER_0));

  EXPECT_THAT(overlap(EXAMPLE_SCANNER_0, sorted_scanner_1, 12),
              IsSupersetOf(EXAMPLE_OVERLAP_BETWEEN_SCANNERS_0_AND_1_RELATIVE_TO_SCANNER_1));

  EXPECT_THAT(overlap(EXAMPLE_SCANNER_4, overlap_0_and_1_relative_to_0, 12),
              IsSupersetOf(EXAMPLE_OVERLAP_BETWEEN_SCANNERS_1_AND_4_RELATIVE_TO_SCANNER_0));
}

TEST(Day19, reconstruct_points_from_example_scanner_data) {
  using ::testing::ElementsAreArray;
  auto reconstructed = reconstruct(EXAMPLE_SCANNERS, 12);
  EXPECT_THAT(reconstructed, ElementsAreArray(EXAMPLE_BEACONS_RELATIVE_TO_SCANNER_0));
}
