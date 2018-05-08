#include<string.h>
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
			}
			else
			{
				k = T[k];
				if(k < 0)
				{
					j++;
					k++;
				}
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

void compress_input(string input, string path)
{
	
}