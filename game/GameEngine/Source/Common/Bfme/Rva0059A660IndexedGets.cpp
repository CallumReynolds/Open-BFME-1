// cl: /DNDEBUG /MD /EHsc

// Three cdecl field getters at retail 0x0059A660, 0x0059A670 and 0x0059A680,
// beside ButtonFlashTransition's destructor and update.  Each has an ILT thunk
// (0x00036FED, 0x00036494, 0x00041010) that nothing references, and no caller
// names them, so the owners are address-derived.

class Rva0059A660
{
public:
	static unsigned get(const unsigned *value);
};

unsigned Rva0059A660::get(const unsigned *value)
{
	return value[18];
}

class Rva0059A670
{
public:
	static unsigned get(const unsigned *value);
};

unsigned Rva0059A670::get(const unsigned *value)
{
	return value[33];
}

class Rva0059A680
{
public:
	static unsigned get(const unsigned *value);
};

unsigned Rva0059A680::get(const unsigned *value)
{
	return value[36];
}
