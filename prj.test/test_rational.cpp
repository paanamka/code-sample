/*

void testing() {
	std::cout << Rational(4) << std::endl;

	std::cout << Rational(4, 3) << std::endl;

	try {
		std::cout << Rational(4, 0) << std::endl;
	}
	catch (ForbiddenDenominator & e) {
		std::cout << "Forbidden denominator: zero" << std::endl;
	}

	try {
		std::cout << Rational(4, -1) << std::endl;
	}
	catch (ForbiddenDenominator & e) {
		std::cout << "ForbiddenDenominator: negative" << std::endl;
	}
}

TEST_CASE("rational ctor") {
	Rational r_def;
	CHECK(0 == r_def.num());
	CHECK(1 == r_def.den());

	Rational r_int(3);
	CHECK(3 == r_int.num());
	CHECK(1 == r_int.den());

	Rational r_minus_int(-3);
	CHECK(-3 == r_minus_int.num());
	CHECK(1 == r_minus_int.den());


	CHECK_THROWS(void(Rational(1, 0)));
}

TEST_CASE("rational reduction") {
	Rational r(15, 6);
	CHECK(5 == r.num());
	CHECK(2 == r.den());
}

TEST_CASE("rational output") {
	std::ostringstream output;
	Rational z(2, 3);
	output << z;
	CHECK(output.str() == "2/3");
}

TEST_CASE("rational input") {
	std::istringstream istream("7/8");
	Rational z;
	istream >> z;
	CHECK(istream.failbit == std::ios_base::failbit);
}

TEST_CASE("arithmetics") {
	Rational w1(2, 3);
	Rational w2(1, 3);
	w1 += w2;
	CHECK(w1.num() == 1);
	CHECK(w1.den() == 1);

	Rational x1(7, 15);
	Rational x2(4, 7);
	x1 -= x2;
	CHECK(x1.num() == -11);
	CHECK(x1.den() == 105);

	Rational y1(9, 10);
	Rational y2(3, 5);
	y1 *= y2;
	CHECK(y1.num() == 27);
	CHECK(y1.den() == 50);

	Rational z1(21, 31);
	Rational z2(0, 4);
	CHECK_THROWS(z1 /= z2);

	int64_t number = 9;
	Rational rat(9, 10);
	rat += 9;
	CHECK(rat.num() == 99);
	CHECK(rat.den() == 10);
	rat -= 9;
	rat *= 100;
	CHECK(rat.num() == 90);
	CHECK(rat.den() == 1);
	rat /= Rational(3, 1);
	CHECK(rat.num() == 30);
	CHECK(rat.den() == 1);
}
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <rational/rational.hpp>
#include <sstream>


TEST_CASE("rational ctor") {
  CHECK(Rational() == Rational(0, 1));
  CHECK(Rational(3) == Rational(3, 1));
  CHECK(Rational(-3) == Rational(-3, 1));
  CHECK(Rational(10, 6) == Rational(5, 3));
  CHECK(Rational(-10, 6) == Rational(-5, 3));
  CHECK(Rational(10, -6) == Rational(-5, 3));
  CHECK(Rational(-10, -6) == Rational(5, 3));
  CHECK_THROWS(Rational(1, 0));
}

TEST_CASE("addsub") {
  CHECK((Rational(1, 2) + Rational(1, 2)) == Rational(1, 1));
  CHECK((Rational(11, 3) + Rational(1, 2)) == Rational(25, 6));
  CHECK((Rational(-8, 3) + Rational(1, 5)) == Rational(-37, 15));
  CHECK((Rational(13, 5) - Rational(1, 2)) == Rational(21, 10));
}

TEST_CASE("multdiv") {
  CHECK((Rational(14, 36) * Rational(81, 193)) == Rational(63, 386));
  CHECK((Rational(13, 36) * Rational(0, 193)) == Rational(0, 1));
  CHECK((Rational(3, 4) /= Rational(-3, 4)) == Rational(-1));
  CHECK((Rational(3, 4) /= Rational(3, -4)) == Rational(-1));
  CHECK((Rational(3, 4) / Rational(-3, 4)) == Rational(-1));
  CHECK((Rational(3, 4) / Rational(3, -4)) == Rational(-1));
  CHECK_THROWS(Rational(64, 95) / Rational(0, 0));
}

TEST_CASE("outinput") {
  Rational output_obj = Rational(1, 2);
  std::stringstream out;
  std::stringstream out1;
  out << output_obj;
  CHECK((out1 << output_obj).good());
  CHECK(out.str() == "1/2");
}

TEST_CASE("[rational] - Rational add") {
  CHECK(Rational(3, 2) + Rational(5, 7) == Rational(31, 14));
  CHECK(Rational(5, 7) + Rational(3, 2) == Rational(31, 14));
  CHECK(Rational() + Rational() == Rational());
  CHECK((Rational(0, 1) + Rational(29, 41)) == Rational(29, 41));
  CHECK(Rational(5, 1) + Rational(3, 2) == Rational(13, 2));
}

TEST_CASE("[rational] - Rational subtract") {
  CHECK(Rational(31, 14) - Rational(5, 7) == Rational(3, 2));
  CHECK(Rational(25, 7) - Rational(2, 9) == Rational(211, 63));
  CHECK(Rational(2, 3) - Rational(7, 4) == Rational(-13, 12));
}

TEST_CASE("[rational] - Rational division") {
  CHECK(Rational(5, 2) / Rational(5, 2) == Rational(1, 1));
  CHECK(Rational(3, 2) / Rational(9, 8) == Rational(4, 3));
  CHECK_THROWS(Rational(3, 2) / Rational(5, 0));
}

TEST_CASE("[rational] - Rational minus") {
  CHECK(-Rational() == Rational());
  CHECK(Rational(-5, 3) == -Rational(5, 3));
  CHECK(Rational(25, 7) == -(-(Rational(25, 7))));
  CHECK(Rational(29, 41) == -Rational(-29, 41));
}

TEST_CASE("[rational] - I/O") {

  SUBCASE("Output") {

    std::stringstream sstrm;

    SUBCASE("Simple") {
      sstrm << Rational(23, 7);
      CHECK(sstrm.str() == "23/7");
    }

    sstrm.clear();

    SUBCASE("Default constructor") {
      sstrm << Rational();
      CHECK(sstrm.str() == "0/1");
    }

    sstrm.clear();


    SUBCASE("Negative") {
      sstrm << -Rational(3, 8);
      CHECK(sstrm.str() == "-3/8");
    }

    sstrm.clear();

}

  SUBCASE("Correct inputs") {

    Rational r;
    std::stringstream sstrm;

    SUBCASE("Simple") {
      sstrm.str("2/3");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::eofbit);
      CHECK(r == Rational(2, 3));
    }

    sstrm.clear();

    SUBCASE("Input with reducing") {
      sstrm.str("36/48");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::eofbit);
      CHECK(r == Rational(3, 4));
    }

    sstrm.clear();

    SUBCASE("Negative input") {
      sstrm.str("-8/7");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::eofbit);
      CHECK(r == Rational(-8, 7));
    }
  }

  SUBCASE("Correct inputs with extra spaces on begin and trash on end") {

    Rational r;
    std::stringstream sstrm;

    SUBCASE("Extra spaces on begin") {
      sstrm.str(" 1/3");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::eofbit);
      CHECK(r == Rational(1, 3));
    }

    sstrm.clear();

    SUBCASE("Extra extra spaces on begin") {
      sstrm.str("   -3/4");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::eofbit);
      CHECK(r == Rational(-3, 4));
    }

    sstrm.clear();

    SUBCASE("Extra spaces on both ends") {
      sstrm.str(" 5/9  ");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::goodbit);
      CHECK(r == Rational(5, 9));
    }

    sstrm.clear();

    SUBCASE("Extra spaces on both ends and negative number") {
      sstrm.str(" -3/9  ");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::goodbit);
      CHECK(r == Rational(-1, 3));
    }

    sstrm.clear();

    SUBCASE("Extra spaces on begin and trash on end") {
      sstrm.str(" 23/9abc");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::goodbit);
      CHECK(r == Rational(23, 9));
    }

    sstrm.clear();

    SUBCASE("Extra spaces on end") {
      sstrm.str("3/7 ");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::goodbit);
      CHECK(r == Rational(3, 7));
    }

    sstrm.clear();

    SUBCASE("Trash on end") {
      sstrm.str("9/2&");
      sstrm >> r;
      CHECK(sstrm.rdstate() == std::ios_base::goodbit);
      CHECK(r == Rational(9, 2));
    }
  }

  SUBCASE("Uncorrect inputs") {
    Rational r;
    std::stringstream sstrm;

    SUBCASE("Trash") {
      sstrm.str("kek");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Bad delimiter") {
      sstrm.str("5\\3");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Numerator is trash") {
      sstrm.str("a/3");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Denominator is trash") {
      sstrm.str("3/*");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Spaces between 1") {
      sstrm.str("3 /2");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Spaces between 2") {
      sstrm.str("3/ 2");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Spaces between 3") {
      sstrm.str("3 / 2");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

    sstrm.clear();

    SUBCASE("Denominator is negative") {
      sstrm.str("3/-2");
      sstrm >> r;
      CHECK(sstrm.fail());
      CHECK(!sstrm.bad());
    }

  }
}
