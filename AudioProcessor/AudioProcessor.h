// AudioProcessor.h

#pragma once

#include <string>

using namespace System;

namespace AudioProcessor {

	public ref class AProcessor
	{
	public:
		bool AProcessor::CopyHeader(String ^inPath, String ^outPath, long length);
		//bool AProcessor::TruncateFileEndFromOtherFile(String ^inPath, String ^outPath, long length);

		bool AProcessor::UlawToRaw(String ^inPath, String ^outPath);
		bool AProcessor::UlawToShortRaw(String ^inPath, String ^outPath);

		bool AProcessor::RawToUlaw(String ^inPath, String ^outPath);
		bool AProcessor::ShortRawToUlaw(String ^inPath, String ^outPath);

		bool AProcessor::Amplify(String ^inPath, String ^outPath, double mRatio, long seek);
		bool AProcessor::AmplifyShort(String ^inPath, String ^outPath, double mRatio, long seek);
	};
}
