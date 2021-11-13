#pragma warning(disable:4996)

#include "public/steam/steam_api.h"
#include "public/steam/steamclientpublic.h"
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <fstream>

int main(int argc, char** argv)
{
	if (!SteamAPI_Init()) {
		printf("Failed to init");
		return 0;
	}
	if (argc != 2) {
		printf("there's no voice packet");
		return 0;
	}

	// Decalration
	EVoiceResult res = k_EVoiceResultOK; //0
	uint32 cbCompressed; 
	uint8* pCompressed; // 압축된 음성데이터

	uint32 cbDestBufferSize = 100000;
	uint8* pDestBuffer = (uint8*)malloc(cbDestBufferSize);  // 최종 음성데이터
	uint32 nBytesWritten = -1;
	uint32 nDesiredSampleRate = 10000;
	
	//File Read
	FILE* fp1 = fopen(argv[1], "rb");
	if (fp1 <= 0) {
		printf("cannot open file\n");
		return 0;
	}
	
	//길이 측정
	std::ifstream in(argv[1], std::ifstream::binary);
	in.seekg(0, in.end);
	cbCompressed = (unsigned int)in.tellg();
	in.close();

	//압축된 음성 데이터 복사
	pCompressed = (uint8*)malloc(cbCompressed);
	fread(pCompressed, 1, cbCompressed, fp1); //pCompressed read
	fclose(fp1);

	// 함수 실행
	res = SteamUser()->DecompressVoice(pCompressed, cbCompressed, pDestBuffer, cbDestBufferSize, &nBytesWritten, nDesiredSampleRate);
	printf("\n\nDecompressVoice() result = %d\n\nCompressed data size = %d\n\nBytesWritten = %d\n\n", res, cbCompressed, nBytesWritten);

	SteamAPI_Shutdown();
	return 0;
}