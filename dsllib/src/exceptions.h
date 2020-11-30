#include <exception>

struct AmbiguousCall : public std::exception {
	virtual const char* what() const throw() { return "Ambiguous call"; }
}