#ifndef __BASE64_H_INCLUDED__
#define __BASE64_H_INCLUDED__


#include <string>

//  http://www.adp-gmbh.ch/cpp/common/base64.html
//####################################################################
//####################################################################


std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


//####################################################################
//####################################################################
#endif // __BASE64_H_INCLUDED__