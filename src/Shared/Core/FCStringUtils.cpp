/*
 Copyright (C) 2011-2012 by Martin Linklater
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */

#include "FCStringUtils.h"
#include "FCError.h"

FCStringVector FCStringUtils_ComponentsSeparatedByString( const std::string& data, const std::string& sep )
{
	FCStringVector ret;
	
	size_t prevSearchPos = 0;
	size_t searchPos = data.find(sep, prevSearchPos);

	if( searchPos == data.npos )
	{
		ret.push_back(data);
		return ret;
	}
	
	while (searchPos != data.npos) 
	{
		ret.push_back(data.substr(prevSearchPos, searchPos - prevSearchPos));
		prevSearchPos = searchPos + sep.length();
		searchPos = data.find(sep, prevSearchPos);
	}
	
	ret.push_back(data.substr(prevSearchPos, data.length() - prevSearchPos));
	
	return ret;
}

void FCStringUtils_ReplaceOccurencesOfStringWithString( std::string& find, const std::string& search, const std::string& replace )
{
	size_t pos = find.find( search );
	
	while (pos != std::string::npos) {
		find.replace( pos, search.size(), replace);
		pos = find.find( search, pos+1 );
	}
	
	return;
}

float FCFloatFromString( std::string& string )
{
	float out;
	sscanf(string.c_str(), "%f", &out);
	return out;
}

int32_t FCIntFromString( std::string& string )
{
	uint32_t out;
	sscanf(string.c_str(), "%d", &out);
	return out;
}


