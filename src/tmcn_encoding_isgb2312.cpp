
#include <stdio.h>
#include <string.h>

int IsGB2312(const void* pBuffer, long size)
{
	int IsGB2312 = 1;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
 
	while (start < end)
	{
		if (*start < 0x80)
			start++;
		else if (*start < 0xA1)
		{
			IsGB2312 = 0;
			break;
		}
		else if (*start < 0xAA)
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0xA1 || start[1] > 0xFE)
			{
				IsGB2312 = 0;
				break;
			}
 
			start += 2;
		}
		else if (*start < 0xB0)
		{
			IsGB2312 = 0;
			break;
		}
		else if (*start < 0xF8)	
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0xA1 || start[1] > 0xFE)
			{
				IsGB2312 = 0;
				break;
			}
 
			start += 2;
		}
		else
		{
			IsGB2312 = 0;
			break;
		}
	}
 
	return IsGB2312;
}


extern "C" {
	void CWrapper_encoding_isgb2312(char **characters, int *numres)
	{
		char* s = *characters;
		int l;
		l = strlen(s);
		*numres = IsGB2312(s,l);
	}
}

