// Rva00511830Owner::handle -- retail 0x00511830, 74 bytes (thiscall, ret 0xc).
// Identity unknown, so the address token stays. The body has the shape of a
// GWM_CHAR (0x15) input handler: the key byte is tested against 1, 0x1c and
// 0x9c (DIK escape/return/numpad-enter), the state byte against 1 and 0xc,
// and a hit moves the state word at +0x258 from 1 to 2 (the same store as
// Rva005114A0::apply). Returns 1 for the handled message and 0 otherwise.

class Rva00511830Owner
{
public:
	int handle(unsigned int msg, unsigned int data1, unsigned int data2);

	unsigned char m_head[0x258];
	int m_state;
};

int Rva00511830Owner::handle(unsigned int msg, unsigned int data1, unsigned int data2)
{
	switch (msg)
	{
		case 0x15:
		{
			unsigned char key = (unsigned char)data1;
			unsigned char state = (unsigned char)data2;
			if ((state & 1) != 0)
			{
				switch (key)
				{
					case 1:
						if (m_state == 1)
							m_state = 2;
						break;
					case 0x1c:
					case 0x9c:
						if ((state & 0xc) != 0)
						{
							if (m_state == 1)
								m_state = 2;
						}
						break;
				}
			}
			return 1;
		}
	}
	return 0;
}
