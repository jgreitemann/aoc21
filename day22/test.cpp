#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "solution.h"

#include <span>

using namespace Day22;

constexpr std::string_view SMALL_EXAMPLE_INPUT = R"(on x=10..12,y=10..12,z=10..12
on x=11..13,y=11..13,z=11..13
off x=9..11,y=9..11,z=9..11
on x=10..10,y=10..10,z=10..10
)";

constexpr std::array SMALL_EXAMPLE_SEQ = {
        std::pair{true, Cuboid{10, 12, 10, 12, 10, 12}},
        std::pair{true, Cuboid{11, 13, 11, 13, 11, 13}},
        std::pair{false, Cuboid{9, 11, 9, 11, 9, 11}},
        std::pair{true, Cuboid{10, 10, 10, 10, 10, 10}},
};

constexpr std::array FIRST_CUBOID_POINTS = {
        Point3D{10, 10, 10}, Point3D{10, 10, 11}, Point3D{10, 10, 12}, Point3D{10, 11, 10},
        Point3D{10, 11, 11}, Point3D{10, 11, 12}, Point3D{10, 12, 10}, Point3D{10, 12, 11},
        Point3D{10, 12, 12}, Point3D{11, 10, 10}, Point3D{11, 10, 11}, Point3D{11, 10, 12},
        Point3D{11, 11, 10}, Point3D{11, 11, 11}, Point3D{11, 11, 12}, Point3D{11, 12, 10},
        Point3D{11, 12, 11}, Point3D{11, 12, 12}, Point3D{12, 10, 10}, Point3D{12, 10, 11},
        Point3D{12, 10, 12}, Point3D{12, 11, 10}, Point3D{12, 11, 11}, Point3D{12, 11, 12},
        Point3D{12, 12, 10}, Point3D{12, 12, 11}, Point3D{12, 12, 12},
};

constexpr std::array SMALL_EXAMPLE_POINTS_AFTER_REBOOT = {
        Point3D{10, 10, 12}, Point3D{10, 11, 12}, Point3D{10, 12, 10}, Point3D{10, 12, 11},
        Point3D{10, 12, 12}, Point3D{11, 10, 12}, Point3D{11, 11, 12}, Point3D{11, 12, 10},
        Point3D{11, 12, 11}, Point3D{11, 12, 12}, Point3D{12, 10, 10}, Point3D{12, 10, 11},
        Point3D{12, 10, 12}, Point3D{12, 11, 10}, Point3D{12, 11, 11}, Point3D{12, 11, 12},
        Point3D{12, 12, 10}, Point3D{12, 12, 11}, Point3D{12, 12, 12}, Point3D{11, 11, 13},
        Point3D{11, 12, 13}, Point3D{11, 13, 11}, Point3D{11, 13, 12}, Point3D{11, 13, 13},
        Point3D{12, 11, 13}, Point3D{12, 12, 13}, Point3D{12, 13, 11}, Point3D{12, 13, 12},
        Point3D{12, 13, 13}, Point3D{13, 11, 11}, Point3D{13, 11, 12}, Point3D{13, 11, 13},
        Point3D{13, 12, 11}, Point3D{13, 12, 12}, Point3D{13, 12, 13}, Point3D{13, 13, 11},
        Point3D{13, 13, 12}, Point3D{13, 13, 13}, Point3D{10, 10, 10},
};

constexpr std::string_view LARGE_EXAMPLE_INPUT = R"(on x=-20..26,y=-36..17,z=-47..7
on x=-20..33,y=-21..23,z=-26..28
on x=-22..28,y=-29..23,z=-38..16
on x=-46..7,y=-6..46,z=-50..-1
on x=-49..1,y=-3..46,z=-24..28
on x=2..47,y=-22..22,z=-23..27
on x=-27..23,y=-28..26,z=-21..29
on x=-39..5,y=-6..47,z=-3..44
on x=-30..21,y=-8..43,z=-13..34
on x=-22..26,y=-27..20,z=-29..19
off x=-48..-32,y=26..41,z=-47..-37
on x=-12..35,y=6..50,z=-50..-2
off x=-48..-32,y=-32..-16,z=-15..-5
on x=-18..26,y=-33..15,z=-7..46
off x=-40..-22,y=-38..-28,z=23..41
on x=-16..35,y=-41..10,z=-47..6
off x=-32..-23,y=11..30,z=-14..3
on x=-49..-5,y=-3..45,z=-29..18
off x=18..30,y=-20..-8,z=-3..13
on x=-41..9,y=-7..43,z=-33..15
on x=-54112..-39298,y=-85059..-49293,z=-27449..7877
on x=967..23432,y=45373..81175,z=27513..53682
)";

constexpr std::array LARGE_EXAMPLE_SEQ = {
        std::pair{true, Cuboid{-20, 26, -36, 17, -47, 7}},
        std::pair{true, Cuboid{-20, 33, -21, 23, -26, 28}},
        std::pair{true, Cuboid{-22, 28, -29, 23, -38, 16}},
        std::pair{true, Cuboid{-46, 7, -6, 46, -50, -1}},
        std::pair{true, Cuboid{-49, 1, -3, 46, -24, 28}},
        std::pair{true, Cuboid{2, 47, -22, 22, -23, 27}},
        std::pair{true, Cuboid{-27, 23, -28, 26, -21, 29}},
        std::pair{true, Cuboid{-39, 5, -6, 47, -3, 44}},
        std::pair{true, Cuboid{-30, 21, -8, 43, -13, 34}},
        std::pair{true, Cuboid{-22, 26, -27, 20, -29, 19}},
        std::pair{false, Cuboid{-48, -32, 26, 41, -47, -37}},
        std::pair{true, Cuboid{-12, 35, 6, 50, -50, -2}},
        std::pair{false, Cuboid{-48, -32, -32, -16, -15, -5}},
        std::pair{true, Cuboid{-18, 26, -33, 15, -7, 46}},
        std::pair{false, Cuboid{-40, -22, -38, -28, 23, 41}},
        std::pair{true, Cuboid{-16, 35, -41, 10, -47, 6}},
        std::pair{false, Cuboid{-32, -23, 11, 30, -14, 3}},
        std::pair{true, Cuboid{-49, -5, -3, 45, -29, 18}},
        std::pair{false, Cuboid{18, 30, -20, -8, -3, 13}},
        std::pair{true, Cuboid{-41, 9, -7, 43, -33, 15}},
        std::pair{true, Cuboid{-54112, -39298, -85059, -49293, -27449, 7877}},
        std::pair{true, Cuboid{967, 23432, 45373, 81175, 27513, 53682}},
};

TEST(Day22, parse_sequence) {
  auto test = [](std::string_view input, RebootSequenceView expected) {
    std::stringstream stream{std::string{input}};
    using ::testing::ElementsAreArray;
    EXPECT_THAT(parse_sequence(stream), ElementsAreArray(expected));
  };
  test(SMALL_EXAMPLE_INPUT, SMALL_EXAMPLE_SEQ);
  test(LARGE_EXAMPLE_INPUT, LARGE_EXAMPLE_SEQ);
}

TEST(Day22, points_in_cuboid) {
  using cor3ntin::rangesnext::to;
  using ::testing::ElementsAreArray;
  EXPECT_THAT(points(SMALL_EXAMPLE_SEQ.front().second) | to<std::vector>(),
              ElementsAreArray(FIRST_CUBOID_POINTS));
}

TEST(Day22, clipping_cuboids_forms_intersection_of_points) {
  using cor3ntin::rangesnext::to;
  using ::testing::UnorderedElementsAreArray;

  Cuboid a{0, 10, 0, 10, 0, 10};
  Cuboid b{3, 20, 1, 8, -4, 5};
  std::vector<Point3D> intersection;
  std::ranges::set_intersection(points(a), points(b), std::back_inserter(intersection));
  EXPECT_THAT(points(a.clip(b)) | to<std::vector>(), UnorderedElementsAreArray(intersection));
}

TEST(Day22, clipping_non_overlapping_cuboids_results_in_empty_intersection) {
  using cor3ntin::rangesnext::to;
  using ::testing::IsEmpty;

  Cuboid a{0, 10, 0, 10, 0, 10};
  Cuboid b{11, 20, 1, 8, -4, 5};
  EXPECT_THAT(points(a.clip(b)) | to<std::vector>(), IsEmpty());

  EXPECT_THAT(points(LARGE_EXAMPLE_SEQ.back().second.clip(bounding_box)) | to<std::vector>(),
              IsEmpty());
}

TEST(Day22, reboot) {
  using ::testing::UnorderedElementsAreArray;
  EXPECT_THAT(points(reboot(SMALL_EXAMPLE_SEQ)),
              UnorderedElementsAreArray(SMALL_EXAMPLE_POINTS_AFTER_REBOOT));
}

TEST(Day22, apply_reboot_step) {
  constexpr std::array seq = {
          std::pair{true, Cuboid{0, 1, 0, 1, 0, 1}},  std::pair{true, Cuboid{2, 3, 2, 3, 2, 3}},
          std::pair{true, Cuboid{2, 3, 2, 3, 2, 3}},  std::pair{false, Cuboid{1, 2, 1, 2, 1, 2}},
          std::pair{false, Cuboid{1, 2, 1, 2, 1, 2}}, std::pair{true, Cuboid{1, 2, 1, 2, 1, 2}},
  };
  auto state = apply_reboot_step({}, seq[0]);
  EXPECT_EQ(number_of_points(state), 8);
  state = apply_reboot_step(std::move(state), seq[1]);
  EXPECT_EQ(number_of_points(state), 16);
  state = apply_reboot_step(std::move(state), seq[2]);
  EXPECT_EQ(number_of_points(state), 16);
  state = apply_reboot_step(std::move(state), seq[3]);
  EXPECT_EQ(number_of_points(state), 14);
  state = apply_reboot_step(std::move(state), seq[4]);
  EXPECT_EQ(number_of_points(state), 14);
  state = apply_reboot_step(std::move(state), seq[5]);
  EXPECT_EQ(number_of_points(state), 22);
}

TEST(Day22, number_of_points_after_reboot) {
  EXPECT_EQ(number_of_points(reboot(SMALL_EXAMPLE_SEQ)), 39);
  EXPECT_EQ(number_of_points(reboot(LARGE_EXAMPLE_SEQ | clipped_steps(bounding_box))), 590784);
}
