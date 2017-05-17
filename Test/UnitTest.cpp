#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;
using namespace AudioProcessor;

namespace Test
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

		[TestMethod]
		void InputOutputTest()
		{
			AProcessor;
			AProcessor^ processor = gcnew AProcessor();
			processor->UlawToRaw("C:\\Test\\ostapenko.bmp", "C:\\Test\\Ostapenko.raw");
			processor->RawToUlaw("C:\\Test\\Ostapenko.raw", "C:\\Test\\OstapenkoBACK.bmp");
		};
		[TestMethod]
		void AmplifyTest()
		{
			AProcessor;
			AProcessor^ processor = gcnew AProcessor();
			//2.3713737056616551
			processor->UlawToRaw("C:\\Test\\ostapenko.bmp", "C:\\Test\\Ostapenko.raw");
			processor->Amplify("C:\\Test\\Ostapenko.raw", "C:\\Test\\OstapenkoAmplified.raw", 2.3713737056616551, 54);
			processor->RawToUlaw("C:\\Test\\OstapenkoAmplified.raw", "C:\\Test\\OstapenkoAmplifiedMine.bmp");
		};
		[TestMethod]
		void AmplifyExtremeTest()
		{
			AProcessor;
			AProcessor^ processor = gcnew AProcessor();
			//2.3713737056616551
			processor->UlawToRaw("C:\\Test\\ostapenko.bmp", "C:\\Test\\Ostapenko.raw");
			processor->Amplify("C:\\Test\\Ostapenko.raw", "C:\\Test\\OstapenkoAmplifiedExtreme.raw", 46, 54);
			processor->RawToUlaw("C:\\Test\\OstapenkoAmplifiedExtreme.raw", "C:\\Test\\OstapenkoAmplifiedExtreme.bmp");
		};
		[TestMethod]
		void FloatExportAsShortTest()
		{
			AProcessor;
			AProcessor^ processor = gcnew AProcessor();
			processor->UlawToRaw("C:\\Test\\ostapenko.bmp", "C:\\Test\\Ostapenko.raw");
			processor->ShortRawToUlaw("C:\\Test\\Ostapenko.raw", "C:\\Test\\OstapenkoFloatToShort.bmp");
			processor->CopyHeader("C:\\Test\\ostapenko.bmp", "C:\\Test\\OstapenkoFloatToShort.bmp", 54);
		};

	};
}
