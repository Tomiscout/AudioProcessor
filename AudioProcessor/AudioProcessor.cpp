// This is the main DLL file.

#include "stdafx.h"
#include <string>
#include <msclr\marshal_cppstd.h>
#include <fstream>
#include "AudioProcessor.h"


using namespace AudioProcessor;
using namespace msclr::interop;
using namespace std;

long GetFileSize(string filename)
{
	ifstream in(filename, ifstream::ate | ifstream::binary);
	return in.tellg();
}

float* ReadFloatFile(string path, long bufferLength){
	//Creates buffer with length
	//bufferLength = ceil((float)(GetFileSize(path)) / sizeof(float));
	float* buffer = new float[bufferLength];
	memset(buffer, 0, sizeof(buffer)); //Clears buffer data

	//Reads raw file into buffer
	FILE *file = fopen(path.c_str(), "rb");
	if (file != NULL){
		fread(buffer, sizeof(float), bufferLength, file);
		fclose(file);
	}
	else{
		return false;
	}

	return buffer;
}
bool WriteFloatFile(string path, float* buffer, long bufferLength){
	FILE *file = fopen(path.c_str(), "wb");
	if (file != NULL){
		fwrite(buffer, sizeof(float), bufferLength, file);
		fclose(file);
	}
	else{
		return false;
	}
}

bool AProcessor::UlawToRaw(String ^inPath, String ^outPath){
	//Convert path to string
	string inPathStr = marshal_as<string>(inPath);
	string outPathStr = marshal_as<string>(outPath);

	//Creates buffer with length
	//long bufferLength = ceil((float)(GetFileSize(inPathStr)) / sizeof(float));
	long bufferLength = GetFileSize(inPathStr);
	float* buffer = new float[bufferLength];
	memset(buffer, 0, sizeof(buffer)); //Clears buffer data

	//Imports file as raw
	SndfileHandle file1 = SndfileHandle(inPathStr, SFM_READ, (SF_FORMAT_RAW | SF_FORMAT_ULAW), 1, 44100);
	if (file1 != NULL){
		file1.read(buffer, bufferLength);
	}
	else{
		return false;
	}

	bool write = WriteFloatFile(outPathStr.c_str(), buffer, bufferLength);
	if (!write)
		return false;

	puts("");
	return true;
}
bool AProcessor::RawToUlaw(String ^inPath, String ^outPath){
	//Convert path to string
	std::string inPathStr = marshal_as<std::string>(inPath);
	std::string outPathStr = marshal_as<std::string>(outPath);

	long bufferLength = GetFileSize(inPathStr);
	float* buffer = ReadFloatFile(inPathStr, bufferLength);

	//transcodes buffer to ulaw data
	SndfileHandle file2 = SndfileHandle(outPathStr, SFM_WRITE, (SF_FORMAT_RAW | SF_FORMAT_ULAW), 1, 44100);
	if (file2 != NULL){
		file2.write(buffer, ceil((float)(bufferLength) / sizeof(float))); //Need to divide by 4 because ulaw .raw file is 4 times bigger
	}
	else{
		return false;
	}

	puts("");
	return true;
}


short* ReadShortFile(string path, long &bufferLength){
	//Creates buffer with length
	bufferLength = GetFileSize(path);
	short* buffer = new short[bufferLength];
	memset(buffer, 0, sizeof(buffer)); //Clears buffer data

	//Reads raw file into buffer
	FILE *file = fopen(path.c_str(), "rb");
	if (file != NULL){
		fread(buffer, sizeof(short), bufferLength, file);
		fclose(file);
	}
	else{
		return false;
	}

	return buffer;
}



bool WriteShortFile(string path, short* buffer, long bufferLength){
	FILE *file = fopen(path.c_str(), "wb");
	if (file != NULL){
		fwrite(buffer, sizeof(short), bufferLength, file);
		fclose(file);
	}
	else{
		return false;
	}
}

bool AProcessor::CopyHeader(String ^inPath, String ^outPath, long length){
	//Convert path to string
	std::string inPathStr = marshal_as<std::string>(inPath);
	std::string outPathStr = marshal_as<std::string>(outPath);

	byte* buffer = new byte[length];
	memset(buffer, 0, sizeof(buffer)); //Clears buffer data

	//Reads raw file into buffer
	FILE *file = fopen(inPathStr.c_str(), "rb");
	if (file != NULL){
		fread(buffer, sizeof(byte), length, file);
		fclose(file);
	}
	else{
		return false;
	}

	FILE *file2 = fopen(outPathStr.c_str(), "rb+");
	if (file2 != NULL){
		fwrite(buffer, sizeof(byte), length, file2);
		fclose(file2);
	}
	else{
		return false;
	}
	return true;
}


bool AProcessor::UlawToShortRaw(String ^inPath, String ^outPath){
	//Convert path to string
	std::string inPathStr = marshal_as<std::string>(inPath);
	std::string outPathStr = marshal_as<std::string>(outPath);

	//Creates buffer with length
	long bufferLength = GetFileSize(inPathStr);
	short* buffer = new short[bufferLength];
	memset(buffer, 0, sizeof(buffer)); //Clears buffer data

	//Imports file as raw
	SndfileHandle file1 = SndfileHandle(inPathStr, SFM_READ, (SF_FORMAT_RAW | SF_FORMAT_ULAW), 1, 44100);
	if (file1 != NULL){
		file1.read(buffer, bufferLength);
	}
	else{
		return false;
	}

	//Saves raw buffer into file
	FILE *file = fopen(outPathStr.c_str(), "wb");
	if (file != NULL){
		fwrite(buffer, sizeof(short), bufferLength, file);
		fclose(file);
	}
	else{
		return false;
	}

	puts("");
	return true;
}



bool AProcessor::ShortRawToUlaw(String ^inPath, String ^outPath){
	//Convert path to string
	std::string inPathStr = marshal_as<std::string>(inPath);
	std::string outPathStr = marshal_as<std::string>(outPath);

	long bufferLength = 0;
	short* buffer = ReadShortFile(inPathStr, bufferLength);

	//transcodes buffer to ulaw data
	SndfileHandle file2 = SndfileHandle(outPathStr, SFM_WRITE, (SF_FORMAT_RAW | SF_FORMAT_ULAW), 1, 44100);
	if (file2 != NULL){
		file2.write(buffer, bufferLength);
	}
	else{
		return false;
	}

	puts("");
	return true;
}


//Amplifies 32bit float file
bool AProcessor::Amplify(String ^inPath, String ^outPath, double mRatio, long seek){
	//Convert path to string
	string inPathStr = marshal_as<string>(inPath);
	string outPathStr = marshal_as<string>(outPath);

	long bufferLength = GetFileSize(inPathStr);
	float* buffer = ReadFloatFile(inPathStr, bufferLength);

	for (long i = seek; i < bufferLength; i++){
		buffer[i] *= mRatio;
	}

	WriteFloatFile(outPathStr, buffer, ceil((float)(bufferLength) / sizeof(float)));
	return true;
}

//Amplifies file after calling RawToUlaw()
bool AProcessor::AmplifyShort(String ^inPath, String ^outPath, double mRatio, long seek){
	//Convert path to string
	std::string inPathStr = marshal_as<std::string>(inPath);
	std::string outPathStr = marshal_as<std::string>(outPath);

	long bufferLength;
	short* buffer = ReadShortFile(inPathStr, bufferLength);

	for (long i = seek; i < bufferLength; i++){
		buffer[i] *= mRatio;
	}

	WriteShortFile(outPathStr, buffer, bufferLength);
	return true;
}