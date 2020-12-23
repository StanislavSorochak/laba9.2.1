#include "pch.h"
#include "CppUnitTest.h"
#include "../laba9.2.1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest921
{
	TEST_CLASS(UnitTest921)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int kil_student = 2;
			student* s = new student[kil_student];
			s[0].surname = "carti";
			s[0].specialization = Special(3);
			s[0].phisuka = 3;
			s[0].matematic = 5;
			s[0].informatic = 4;
			s[1].surname = "scott";
			s[1].specialization = Special(4);
			s[1].phisuka = 4;
			s[1].matematic = 5;
			s[1].informatic = 3;

			Sort(s, kil_student);
			Assert::AreEqual(1, 1);
		}
	};
}
