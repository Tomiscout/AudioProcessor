#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\AudioProcessor\AudioProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace AudioProcessor;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			AudioProcessor::
			Assert::AreEqual(true, AProcessor::ImportUlaw())
		}

	};
}