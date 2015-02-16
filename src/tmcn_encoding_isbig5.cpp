
#include <stdio.h>
#include <string.h>

int IsBIG5(const void* pBuffer, long size)
{
	int IsBIG5 = 1;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
 
	while (start < end)
	{
		if (*start < 0x80)
			start++;
		else if (*start < 0xA1)
		{
			IsBIG5 = 0;
			break;
		}
		else if (*start < 0xAA)
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0X40 || start[1] > 0X7E && start[1] < 0XA1 || start[1] > 0xFE)
			{
				IsBIG5 = 0;
				break;
			}
 
			start += 2;
		}
		else if (*start < 0xB0)
		{
			IsBIG5 = 0;
			break;
		}
		else if (*start <= 0XF9)	
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0X40 || start[1] > 0X7E && start[1] < 0XA1 || start[1] > 0xFE)
			{
				IsBIG5 = 0;
				break;
			}
 
			start += 2;
		}
		else
		{
			IsBIG5 = 0;
			break;
		}
	}
 
	return IsBIG5;
}


extern "C" {
	void CWrapper_encoding_isbig5(char **characters, int *numres)
	{
		char* s = *characters;
		int l;
		l = strlen(s);
		*numres = IsBIG5(s,l);
	}
}

