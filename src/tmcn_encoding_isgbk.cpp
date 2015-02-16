
#include <stdio.h>
#include <string.h>

int IsGBK(const void* pBuffer, long size)
{
	int IsGBK = 1;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
 
	while (start < end)
	{
		if (*start < 0x80)
			start++;
		else if (*start < 0x81)
		{
			IsGBK = 0;
			break;
		}
		else if (*start < 0xA1)
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0x40 || start[1] > 0xFE || start[1] == 0x7F)
			{
				IsGBK = 0;
				break;
			}
 
			start += 2;
		}
		else if (*start < 0xAA)	
		{
			if (start >= end -1)
				break;
 
			if (*start < 0xA8)
			{

				if (start[1] < 0xA1 || start[1] > 0xFE)
				{
					IsGBK = 0;
					break;
				}
			}
			else
			{
				if (start[1] < 0x40 || start[1] > 0xEF || start[1] == 0x7F)
				{
					IsGBK = 0;
					break;
				}
			}
 
			start += 2;
		}
		else if (*start < 0xB0)	
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0x40 || start[1] > 0xA0 || start[1] == 0x7F)
			{
				IsGBK = 0;
				break;
			}
 
			start += 2;
		}
		else if (*start < 0xF8)
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0x40 || start[1] > 0xFE || start[1] == 0x7F)
			{
				IsGBK = 0;
				break;
			}
 
			start += 2;
		}
		else if (*start < 0xFF)	
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0x40 || start[1] > 0xA0 || start[1] == 0x7F)
			{
				IsGBK = 0;
				break;
			}
 
			start += 2;
		}
		else
		{
			IsGBK = 0;
			break;
		}
	}
 
	return IsGBK;
}


extern "C" {
	void CWrapper_encoding_isgbk(char **characters, int *numres)
	{
		char* s = *characters;
		int l;
		l = strlen(s);
		*numres = IsGBK(s,l);
	}
}

