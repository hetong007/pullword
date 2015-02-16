
#include <stdio.h>
#include <string.h>

int IsUTF8(const void* pBuffer, long size) {
	int IsUTF8 = 1;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
	while (start < end)
	{
		if (*start < 0x80) 
		{
			start++;
		}
		else if (*start < (0xC0))
		{
			IsUTF8 = 0;
			break;
		}
		else if (*start < (0xE0)) 
		{
			if (start >= end - 1) 
				break;
			if ((start[1] & (0xC0)) != 0x80)
			{
				IsUTF8 = 0;
				break;
			}
			start += 2;
		} 
		else if (*start < (0xF0))
		{
			if (start >= end - 2) 
				break;
			if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
			{
				IsUTF8 = 0;
				break;
			}
			start += 3;
		} 
		else
		{
			IsUTF8 = 0;
			break;
		}
	}
	return IsUTF8;
}

extern "C" {
	void CWrapper_encoding_isutf8(char **characters, int *numres)
	{
		char* s = *characters;
		int l;
		l = strlen(s);
		*numres = IsUTF8(s,l);
	}
}

