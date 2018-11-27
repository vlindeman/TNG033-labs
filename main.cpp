// doctest tutorial:
// https://github.com/onqtam/doctest/blob/master/doc/markdown/tutorial.md
// https://github.com/onqtam/doctest/blob/master/doc/markdown/main.md

#define DOCTEST_CONFIG_IMPLEMENT

#include "doctest.hpp"
#include "set.hpp"

int main(int argc, char** argv)
{
	doctest::Context context(argc, argv);

	//context.setOption("success", true);    // Print all test cases even successful ones

	//context.setOption("no-breaks", true);  // Don't break in the debugger when assertions fail

	//context.setOption("no-path-filenames", true);  // Use short paths

	return context.run();

}

TEST_SUITE("Phase 1: Constructors") {

	TEST_CASE("Default Constructor") {
		const Set s1;

		SUBCASE("Test whether empty set") {
			CHECK(s1.empty());
		}
	}

	TEST_CASE("Single Element Constructor") {
		const Set s1(999);

		SUBCASE("Check set cardinality") {
			CHECK(s1.cardinality() == 1);
		}
		SUBCASE("Check set members") {
			CHECK(s1.member(999));
			CHECK_FALSE(s1.member(998));
		}
	}

	TEST_CASE("List Constructor") {
		const int list[] = { 4, 11, 9 };
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Check set cardinality") {
			CHECK(s1.cardinality() == listSize);
		}
		SUBCASE("Check set members") {
			CHECK(s1.member(4));
			CHECK(s1.member(11));
			CHECK(s1.member(9));
		}
	}

	TEST_CASE("Copy Constructor") {
		const int list[] = { 4, 11, 9 };
		const int listSize = 3;

		const Set s1(list, listSize);
		const Set s2(s1);

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == listSize);
		}
		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(11));
			CHECK(s2.member(9));
		}
	}
}


TEST_SUITE("Phase 2: Assignment") {

	TEST_CASE("Assignment operator: empty set on LHS") {
		const int list[] = { 4, 11, 9 };
		const int listSize = 3;

		const Set s1(list, listSize);
		Set s2;

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 0);
		}

		s2 = s1;

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == listSize);
		}

		SUBCASE("Check set members") {
			CHECK(s1.member(4));
			CHECK(s1.member(11));
			CHECK(s1.member(9));
		}
	}


	TEST_CASE("Assignment operator: non-empty set on LHS") {
		const int list1[] = { 4, 11, 9 };
		const int listSize1 = 3;

		Set s1(list1, listSize1);

		const int list2[] = { 4, 3, 2, 11, 9 };
		const int listSize2 = 5;

		const Set s2(list2, listSize2);

		s1 = s2;

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == s1.cardinality());
		}

		SUBCASE("Check set members") {
			CHECK(s1.member(3));
			CHECK(s1.member(2));
			CHECK(s1.member(4));
			CHECK(s1.member(9));
			CHECK(s1.member(11));
		}
	}
}


TEST_SUITE("Phase 3: Set Operations") {

	TEST_CASE("Union: S + {x}") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);
		const Set s2(999);

		const Set s3 = s1 + s2;

		SUBCASE("Check set cardinality") {
			CHECK(s3.cardinality() == listSize + 1);
		}
		SUBCASE("Check set members") {
			CHECK(s3.member(4));
			CHECK(s3.member(11));
			CHECK(s3.member(9));
			CHECK(s3.member(999));
		}
	}

	TEST_CASE("Union: S1 + S2") {
		const int list1[] = { 1, 3, 5 };
		const int listSize1 = 3;

		const int list2[] = { 4, 3, 2, 11, 9 };
		const int listSize2 = 5;

		const Set s1(list1, listSize1);
		const Set s2(list2, listSize2);

		const Set s3 = s1 + s2;

		SUBCASE("Check set cardinality") {
			CHECK(s3.cardinality() == 7);
		}

		SUBCASE("Check set members") {
			CHECK(s3.member(1));
			CHECK(s3.member(2));
			CHECK(s3.member(3));
			CHECK(s3.member(4));
			CHECK(s3.member(5));
			CHECK(s3.member(9));
			CHECK(s3.member(11));
		}
	}

	TEST_CASE("Union: S + int") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Add non-existing element") {
			const Set s3 = s1 + 999;

			SUBCASE("Check set cardinality") {
				CHECK(s3.cardinality() == listSize + 1);
			}
			SUBCASE("Check set members") {
				CHECK(s3.member(4));
				CHECK(s3.member(11));
				CHECK(s3.member(9));
				CHECK(s3.member(999));
			}
		}
		SUBCASE("Add existing element") {
			const Set s3 = s1 + 4;

			SUBCASE("Check set cardinality") {
				CHECK(s3.cardinality() == listSize);
			}
			SUBCASE("Check set members") {
				CHECK(s3.member(4));
				CHECK(s3.member(11));
				CHECK(s3.member(9));
			}
		}
	}

	TEST_CASE("Difference: S1 - S2") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const int list2[] = {1, 7, 11, 5, 9};
		const int listSize2 = 5;

		const Set s1(list, listSize);
		const Set s2(list2, listSize2);

		const Set s3 = s1 - s2;

		SUBCASE("Check set cardinality") {
			CHECK(s3.cardinality() == 1);
		}
		SUBCASE("Check set members") {
			CHECK(s3.member(4));
		}
	}

	TEST_CASE("Difference: S - int") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Remove existing member") {
			const Set s2 = s1 - 11;

			SUBCASE("Check set cardinality") {
				CHECK(s2.cardinality() == 2);
			}
			SUBCASE("Check set members") {
				CHECK(s2.member(4));
				CHECK(s2.member(9));
			}
		}
		SUBCASE("Remove non-existing member") {
			const Set s2 = s1 - 42;

			SUBCASE("Check set cardinality") {
				CHECK(s2.cardinality() == 3);
			}
			SUBCASE("Check set members") {
				CHECK(s2.member(4));
				CHECK(s2.member(11));
				CHECK(s2.member(9));
			}
		}
	}

	TEST_CASE("Intersection: S1 * S2") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Emtpy intersection") {
			const Set s2(999);
			const Set s3 = s1 * s2;

			SUBCASE("Check set cardinality") {
				CHECK(s3.cardinality() == 0);
			}
		}

		SUBCASE("Partial intersection") {
			const int list2[] = {5, 4, 11, 2};
			const Set s2(list2, 4);
			const Set s3 = s1 * s2;

			SUBCASE("Check s cardinality") {
				CHECK(s3.cardinality() == 2);
			}
			SUBCASE("Check set members") {
				CHECK(s3.member(4));
				CHECK(s3.member(11));
			}
		}
		SUBCASE("Intersection of two sets with same elements") {
			const Set s2 = s1;
			const Set s3 = s1 * s2;

			SUBCASE("Check set cardinality") {
				CHECK(s3.cardinality() == listSize);
			}
			SUBCASE("Check set members") {
				CHECK(s3.member(4));
				CHECK(s3.member(11));
				CHECK(s3.member(9));
			}
		}
	}
}



TEST_SUITE("Phase 4: Relational Operators") {

	TEST_CASE("Equality: S1 == S2") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Identical sets") {
			const Set s2 = s1;

			CHECK(s1 == s2);
			CHECK(s2 == s2);
		}
		SUBCASE("Non-identical sets (same cardinality)") {
			const int list2[] = {4, 12, 10};
			const int listSize2 = 3;
			const Set s2(list2, listSize2);

			CHECK_FALSE(s1 == s2);
			CHECK_FALSE(s2 == s1);
		}
		SUBCASE("Non-identical sets (different cardinality)") {
			const int list2[] = {4, 11};
			const int listSize2 = 2;
			const Set s2(list2, listSize2);

			CHECK_FALSE(s1 == s2);
			CHECK_FALSE(s2 == s1);
		}
	}

	TEST_CASE("Non-equality: S1 != S2") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Identical sets") {
			const Set s2 = s1;

			CHECK_FALSE(s1 != s2);
			CHECK_FALSE(s2 != s1);
		}
		SUBCASE("Non-identical sets (same cardinality)") {
			const int list2[] = {4, 12, 10};
			const int listSize2 = 3;
			const Set s2(list2, listSize2);

			CHECK(s1 != s2);
			CHECK(s2 != s1);
		}
		SUBCASE("Non-identical sets (different cardinality)") {
			const int list2[] = {4, 11};
			const int listSize2 = 2;
			const Set s2(list2, listSize2);

			CHECK(s1 != s2);
			CHECK(s2 != s1);
		}
	}

	TEST_CASE("Proper subset (operator<)") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Identical sets") {
			const Set s2 = s1;

			CHECK_FALSE(s1 < s2);
			CHECK_FALSE(s2 < s1);
		}
		SUBCASE("Empty set") {
			const Set empty;

			CHECK(empty < s1);
			CHECK_FALSE(empty < empty);
		}
		SUBCASE("Proper subset (single element)") {
			const Set s2(4);

			CHECK(s2 < s1);
			CHECK_FALSE(s1 < s2);
		}
		SUBCASE("Proper subset (cardinality 2)") {
			const int list2[] = {4, 11};
			const int listSize2 = 2;
			const Set s2(list2, listSize2);

			CHECK(s2 < s1);
			CHECK_FALSE(s1 < s2);
		}
		SUBCASE("Distinct sets") {
			const int list2[] = {5, 10, 42};
			const int listSize2 = 3;
			const Set s2(list2, listSize2);

			CHECK_FALSE(s1 < s2);
			CHECK_FALSE(s2 < s1);
		}
	}

	TEST_CASE("Subset (operator<=)") {
		const int list[] = {4, 11, 9};
		const int listSize = 3;

		const Set s1(list, listSize);

		SUBCASE("Identical sets") {
			const Set s2 = s1;

			CHECK(s1 <= s2);
			CHECK(s2 <= s1);
		}
		SUBCASE("Empty set") {
			const Set empty;
			CHECK(empty <= s1);
			CHECK(empty <= empty);
		}
		SUBCASE("Subset (single element)") {
			const Set s2(4);

			CHECK(s2 <= s1);
			CHECK_FALSE(s1 <= s2);
		}
		SUBCASE("Subset (cardinality 2)") {
			const int list2[] = {4, 11};
			const int listSize2 = 2;
			const Set s2(list2, listSize2);

			CHECK(s2 <= s1);
			CHECK_FALSE(s1 <= s2);
		}
		SUBCASE("Distinct sets") {
			const int list2[] = {5, 10, 42};
			const int listSize2 = 3;
			const Set s2(list2, listSize2);

			CHECK_FALSE(s1 <= s2);
			CHECK_FALSE(s2 <= s1);
		}
	}
}



TEST_SUITE("Phase 5: Insertion Deletion") {

	TEST_CASE("Set operations test 1") {
		const int list[] = {4, 3, 2, 11, 9};
		const int listSize = 5;

		const Set s1(list, listSize);
		const Set s2 = s1 - 2 + 1 - 9999;

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 5);
		}
		SUBCASE("Check set members") {
			CHECK(s2.member(4));
			CHECK(s2.member(3));
			CHECK(s2.member(1));
			CHECK(s2.member(11));
			CHECK(s2.member(9));
		}
	}

	TEST_CASE("Set operations test 2") {
		const int list[] = {1, 3, 5};
		const int listSize = 3;

		const Set s1(list, listSize);
		const Set s2 = s1 + 4 - 5 - 9999 + Set(999);

		SUBCASE("Check set cardinality") {
			CHECK(s2.cardinality() == 4);
		}
		SUBCASE("Check set members") {
			CHECK(s2.member(1));
			CHECK(s2.member(3));
			CHECK(s2.member(4));
			CHECK(s2.member(999));
		}
	}
}

