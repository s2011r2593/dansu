#include <stdint.h>

#include "pch.h"
#include "gtest/gtest.h"

#include "dansu-helpers.h"
#include "dansu-helpers.c"
#include "dansu-user.h"
#include "dansu-user.c"

TEST(DansuHelpers_SimpleHash, EmptyString) {
	char x[1] = {'\0'};
	uint64_t res = SimpleHash(x);

	EXPECT_EQ(res, 5381);
}

TEST(DansuHelpers_SimpleHash, BasicString) {
	char x[4] = {'a', 'b', 'c', '\0'};
	uint64_t res = SimpleHash(x);

	EXPECT_EQ(res, 0xb885c8b);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);

	return RUN_ALL_TESTS();
}
