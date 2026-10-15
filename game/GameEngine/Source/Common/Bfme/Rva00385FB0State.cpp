// Retail 0x00385FB0/151: fastcall initializer for the 0x98-byte state block
// that the dynamic initializer at 0x00C6B240 builds at 0x012F08A0. It
// returns the block in EAX (retail mov eax, ecx). Bool and int fields at
// 0x00-0x4C and 0x88-0x94 and seven doubles at 0x50-0x80 are cleared; 0x2C
// is untouched. The doubles are written through a local pointer to the
// array, which keeps retail's store order. Field names are offsets only.
// cl: /O2 /DNDEBUG /MD /EHsc

struct Rva00385FB0State
{
	bool m_b00; unsigned char p01[3];
	int m_i04;
	int m_i08;
	bool m_b0C; unsigned char p0D[3];
	int m_i10;
	bool m_b14; unsigned char p15[3];
	int m_i18;
	int m_i1C;
	int m_i20;
	int m_i24;
	bool m_b28; unsigned char p29[3];
	int m_i2C;
	int m_i30;
	int m_i34;
	int m_i38;
	int m_i3C;
	int m_i40;
	int m_i44;
	int m_i48;
	int m_i4C;
	double m_values[7];
	int m_i88;
	int m_i8C;
	int m_i90;
	int m_i94;
};
extern "C" Rva00385FB0State * __fastcall Rva00385FB0Initialize(Rva00385FB0State *self)
{
	double *values = self->m_values;
	self->m_b00 = false;
	self->m_i04 = 0;
	self->m_i08 = 0;
	values[0] = 0.0;
	self->m_b0C = false;
	values[1] = 0.0;
	self->m_i10 = 0;
	self->m_b14 = false;
	values[2] = 0.0;
	self->m_i18 = 0;
	self->m_i1C = 0;
	values[3] = 0.0;
	self->m_i20 = 0;
	self->m_i24 = 0;
	values[4] = 0.0;
	self->m_b28 = false;
	self->m_i30 = 0;
	values[5] = 0.0;
	self->m_i34 = 0;
	self->m_i38 = 0;
	values[6] = 0.0;
	self->m_i3C = 0;
	self->m_i40 = 0;
	self->m_i44 = 0;
	self->m_i48 = 0;
	self->m_i4C = 0;
	self->m_i88 = 0;
	self->m_i8C = 0;
	self->m_i90 = 0;
	self->m_i94 = 0;
	return self;
}
