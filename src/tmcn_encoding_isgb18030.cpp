
#include <stdio.h>
#include <string.h>

int IsGB18030(const void* pBuffer, long size)
{
	int IsGB18030 = 1;
	unsigned char* start = (unsigned char*)pBuffer;
	unsigned char* end = (unsigned char*)pBuffer + size;
 
	while (start < end)
	{
		if (*start < 0x80)
			start++;
		else if (*start < 0x81)	
		{
			IsGB18030 = 0;
			break;
		}

		else if ((*start < 0xFF) && (start < end - 3) && (start[1] >= 0x30 && start[1] <= 0x39))
		{
			if (start[2] < 0x81 || start[2] > 0xFE)
			{
				IsGB18030 = 0;
				break;
			}

			else if (start[3] < 0x30 || start[3] > 0x39)
			{
				IsGB18030 = 0;
				break;
			}
 
			if (start[0] >= 0x81 && start[0] <= 0x84 &&
				start[1] >= 0x30 && start[1] <= 0x39 &&
				start[2] >= 0x81 && start[2] <= 0xFE &&
				start[3] >= 0x30 && start[3] <= 0x39 )
			{
				;
			}
			else if(start[0] >= 0x90 && start[0] <= 0xE3 &&
				start[1] >= 0x30 && start[1] <= 0x39 &&
				start[2] >= 0x81 && start[2] <= 0xFE &&
				start[3] >= 0x30 && start[3] <= 0x39 )
			{
				;
			}
			else
			{
				IsGB18030 = 0;
				break;
			}
 
			start += 4;
		}
		else if (*start < 0xA1)	
		{
			if (start >= end -1)
				break;
 
			if (start[1] < 0x40 || start[1] > 0xFE || start[1] == 0x7F)
			{
				IsGB18030 = 0;
				break;
			}
 
			start += 2;
		}
		else if (*start < 0xAA)	
		{
			if (start >= end -1)
				break;
 
			if ((start[0] == 0xA2 && start[1] == 0xE3)
				|| (start[0] == 0xA6 && start[1] >= 0xD9 && start[1] <= 0xDF)
				|| (start[0] == 0xA6 && start[1] == 0xF3))
			{
				;
			}
			else if (*start < 0xA8)
			{
				if (start[1] < 0xA1 || start[1] > 0xFE)
				{
					IsGB18030 = 0;
					break;
				}
			}
			else
			{
				if (start[1] < 0x40 || start[1] > 0xEF || start[1] == 0x7F)
				{
					IsGB18030 = 0;
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
				IsGB18030 = 0;
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
				IsGB18030 = 0;
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
				IsGB18030 = 0;
				break;
			}
 
			start += 2;
		}
		else
		{
			IsGB18030 = 0;
			break;
		}
	}
 
	return IsGB18030;
}


extern "C" {
	void CWrapper_encoding_isgb18030(char **characters, int *numres)
	{
		char* s = *characters;
		int l;
		l = strlen(s);
		*numres = IsGB18030(s,l);
	}
}

