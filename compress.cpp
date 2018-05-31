#include <string.h>
#include "functions.h"
#include <iostream>
#include <vector>

using namespace std;

vector<Triple> get_compressed_data(string input)
{
	int i = 0;
	string window = "";
	vector<Triple> output;
	while(i < input.length())
	{
		int maxpos = -1;
		int maxlen = 0;
		int T[WINDOW_PARAMS.WINDOW_SIZE] = {};
		T[0] = -1;
		int tpos = 1;
		int tcnd = 0;
		int j = 0;
		int k = 0;
		bool last_matched = false;
		while(j < window.length() && i+k < input.length())
		{
			if( k >= tpos)
			{
				if(input[i + tpos] == input[i + tcnd])
				{
					T[tpos] = T[tcnd];
					tpos++;
					tcnd++;
				}
				else
				{
					T[tpos] = tcnd;
					tcnd = T[tcnd];
					while(tcnd >= 0 && input[i+tpos] != input[i+tcnd])
						tcnd = T[tcnd];
					tpos++;
					tcnd++;
				}
			}
			if(input[i+k] == window[j])
			{
				j++;
				k++;
				if(k > maxlen)
				{
					maxlen = k;
					maxpos = j - k;
				}
				last_matched = true;
			}
			else
			{
				k = T[k];
				if(k < 0)
				{
					j++;
					k++;
				}
				last_matched = false;
			}
		}
		int start = j-k;
		int idx = 0;
		int len = k;
		while(last_matched && i+k+idx < input.length())
		{
			if(input[i+k+idx] == window[start+idx])
			{
				len++;
				last_matched = true;
				idx++;
				if(len > maxlen)
				{
					maxlen = len;
					maxpos = start;
				}
			}
			else
			{
				last_matched = false;
			}
		}
		if(maxlen == 0)
		{
			Triple to_add = {0,0,input[i]};
			output.push_back(to_add);
			i++;
		}
		else
		{
			Triple to_add = {i-maxpos,maxlen,input[i+maxlen]};
			output.push_back(to_add);
			i = i + maxlen + 1;	
		}
		if(i < WINDOW_PARAMS.WINDOW_SIZE)
			window = input.substr(0,i);
		else
			window = input.substr(i-WINDOW_PARAMS.WINDOW_SIZE, WINDOW_PARAMS.WINDOW_SIZE);
	}
	return output;
}
