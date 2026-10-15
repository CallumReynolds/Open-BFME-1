// cl: /O2
// 0x007EB310: scalar-deleting wrapper around the 0x007EB270 singleton
// teardown. Stores the object vptr, then optionally operator-delete this.

class T_007ea120
{
public:
	virtual void release(int);
	void m();
};

class Rva007EB310Owner
{
public:
	void *destroy(unsigned int flags);
};

// Named by retail's hubsingle.cpp assertion; defined in createServiceHubImpl.cpp.
class ServiceHubImpl
{
public:
	static ServiceHubImpl *gInstance;
};
extern unsigned char g_Va0130A58D;
extern unsigned char g_Va0130A58C;
// BFME2 identifies singleton teardown table storage; BFME1's complete
// destructor already emits the table at VA 0x01129CB4 under this name.
extern "C" const void *__identifier("??_7Rva007EB2C0Object@@6B@")[];

void Rva007EB830Release(void);
void Rva007F0060();
void __cdecl operator delete(void *block);

void *Rva007EB310Owner::destroy(unsigned int flags)
{
	*(int *)this = (int)__identifier("??_7Rva007EB2C0Object@@6B@");
	T_007ea120 *p = reinterpret_cast<T_007ea120 *>(ServiceHubImpl::gInstance);
	if (p)
	{
		p->m();
		p = reinterpret_cast<T_007ea120 *>(ServiceHubImpl::gInstance);
		if (p)
			p->release(1);
		ServiceHubImpl::gInstance = 0;
	}
	if (g_Va0130A58D)
		Rva007EB830Release();
	if (g_Va0130A58C)
		Rva007F0060();
	if (flags & 1)
		operator delete(this);
	return this;
}
