/*
* CLI RPG
* Macarthur Inbody
* LGPL v3 or Later
*/
//This file will contain all of the vector related templates we need.
#ifndef CPP_CLI_RPG_VECTORS_HXX
#define CPP_CLI_RPG_VECTORS_HXX
//allow vectors to be sent to std::cout
template <class T,class Allocator> std::ostream& operator<<(std::ostream& os, const std::vector<T,Allocator> &m){
	size_t m_size=m.size();
	os << "[";
	for(size_t i=0; i < m.size(); i++) {
		os << m[i]  <<(i == m_size - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}
//allow std::cin to be put into vectors
template <class T,class Allocator> std::istream& operator>>(std::istream& is, std::vector<T,Allocator> &m){
	size_t n=m.size();
	for(size_t i=0;i<n;i++){
		is >> m[i];
	}
	return is;
}

#endif //CPP_CLI_RPG_VECTORS_HXX
