#include <iostream>
#include "GitVersionRefs.h"

int main(void)
{
	GitVersionRefs refs;
	refs.demote();
	cout << refs;
}

