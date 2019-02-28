#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ARGO/VelComponent.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ScoreUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:

		VelocityComponent * vc = new VelocityComponent();

		//cfg suggests that each of this methods only need one test

		TEST_METHOD(TestGetDistanceMethod)
		{
			// TODO: Your test code here
			Assert::AreEqual(vc->getDistance(), vc->distance);
		}
		TEST_METHOD(TestMethodgetVelXMethod)
		{
			// TODO: Your test code here
			vc->getVelX();
			Assert::AreEqual(vc->getVelX(), 0.f);
		}
		TEST_METHOD(TestGetIDMethod)
		{
			// TODO: Your test code here
			std::string id = "Vel";
			std::string name = vc->getID();
			Assert::AreEqual(id, name);
		}
		TEST_METHOD(TestMethodgetVelYMethod)
		{
			// vc->velY is intiatalized as 0
			vc->getVelY();
			Assert::AreEqual(vc->getVelY(), 0.f);
		}
		TEST_METHOD(TestMethodsetVelXMethod)
		{
			// TODO: Your test code here
			vc->setVelX(5.f);
			Assert::AreEqual(vc->getVelX(), 5.f);
		}
		TEST_METHOD(TestMethodsetVelYMethod)
		{
			// vc->velY is intiatalized as 0
			vc->setVelY(5.f);
			Assert::AreEqual(vc->getVelY(), 5.f);
		}

	};
}