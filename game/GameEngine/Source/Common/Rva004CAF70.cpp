// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD
// Open-BFME5: BFME's lanUpdateSlotList, the 125-byte guard/overlay callback at retail 0x004CAF70.
//
// The tail is Zero Hour's
//   UpdateSlotList(TheLAN->GetMyGame(), comboBoxPlayer, ..., buttonStart, ...);
//   updateMapStartSpots(TheLAN->GetMyGame(), buttonMapStartPosition, 0);
// (identity_evidence/004caf70.md).  Both callees are reached through untyped
// ILT placeholders, so the calls go through the cdecl signatures retail's
// 0x20/0x0C stack cleanup proves.

struct Rva004CAF70Obj
{
	char m_pad[0x26c];
	char m_flag;
};

// retail loads the LAN singleton (0x012F7730, defined as
// `LANAPI *TheLAN` in game/GameEngine/Source/GameNetwork/LANAPICallbacks.cpp)
// and calls GetMyGame at vtable +0xC0 (slot 48, as in
// GenerateGameOptionsString.cpp).  Slots 0..47 are deliberately unnamed; this
// declaration never instantiates LANAPI.
class LANGameInfo;
class LANAPI
{
public:
	virtual void slot00(void) = 0;
	virtual void slot01(void) = 0;
	virtual void slot02(void) = 0;
	virtual void slot03(void) = 0;
	virtual void slot04(void) = 0;
	virtual void slot05(void) = 0;
	virtual void slot06(void) = 0;
	virtual void slot07(void) = 0;
	virtual void slot08(void) = 0;
	virtual void slot09(void) = 0;
	virtual void slot10(void) = 0;
	virtual void slot11(void) = 0;
	virtual void slot12(void) = 0;
	virtual void slot13(void) = 0;
	virtual void slot14(void) = 0;
	virtual void slot15(void) = 0;
	virtual void slot16(void) = 0;
	virtual void slot17(void) = 0;
	virtual void slot18(void) = 0;
	virtual void slot19(void) = 0;
	virtual void slot20(void) = 0;
	virtual void slot21(void) = 0;
	virtual void slot22(void) = 0;
	virtual void slot23(void) = 0;
	virtual void slot24(void) = 0;
	virtual void slot25(void) = 0;
	virtual void slot26(void) = 0;
	virtual void slot27(void) = 0;
	virtual void slot28(void) = 0;
	virtual void slot29(void) = 0;
	virtual void slot30(void) = 0;
	virtual void slot31(void) = 0;
	virtual void slot32(void) = 0;
	virtual void slot33(void) = 0;
	virtual void slot34(void) = 0;
	virtual void slot35(void) = 0;
	virtual void slot36(void) = 0;
	virtual void slot37(void) = 0;
	virtual void slot38(void) = 0;
	virtual void slot39(void) = 0;
	virtual void slot40(void) = 0;
	virtual void slot41(void) = 0;
	virtual void slot42(void) = 0;
	virtual void slot43(void) = 0;
	virtual void slot44(void) = 0;
	virtual void slot45(void) = 0;
	virtual void slot46(void) = 0;
	virtual void slot47(void) = 0;
	virtual LANGameInfo *GetMyGame(void);
};

extern char g_rva004CAF70_gate;
class BfmeAptScreenLanLobby;
extern BfmeAptScreenLanLobby *g_rva012F4998LanLobby;

extern LANAPI *TheLAN;
class GameWindow;
extern GameWindow *comboBoxPlayer[8];
extern GameWindow *buttonStart;
extern char g_rva004CAF70_b[];
extern char g_rva004CAF70_c[];
extern char g_rva004CAF70_d[];
extern char g_rva004CAF70_e[];
extern char g_rva004CAF70_f[];

extern void j_000056c8(void);
extern void j_0001e4bb(void);
extern void j_00022ab6(void);

typedef char (*Rva004CAF70Gate)(void);
typedef void (__cdecl *Rva004CAF70UpdateSlotList)(LANGameInfo *game,
	GameWindow **comboPlayer, char *comboColor, char *comboTemplate,
	char *comboTeam, char *buttonAccept, GameWindow *start, char *startPositions);
typedef void (__cdecl *Rva004CAF70UpdateMapStartSpots)(LANGameInfo *game,
	char *startPositions, int onLoadScreen);

void lanUpdateSlotList004CAF70(void)
{
	if (((Rva004CAF70Gate)j_000056c8)() == 0)
		return;
	if (g_rva004CAF70_gate != 0)
		return;
	Rva004CAF70Obj *p = reinterpret_cast<Rva004CAF70Obj * &>(g_rva012F4998LanLobby);
	if (p != 0)
	{
		p->m_flag = 1;
		return;
	}

	((Rva004CAF70UpdateSlotList)j_0001e4bb)(TheLAN->GetMyGame(), comboBoxPlayer,
		g_rva004CAF70_b, g_rva004CAF70_c, g_rva004CAF70_d, g_rva004CAF70_e,
		buttonStart, g_rva004CAF70_f);
	((Rva004CAF70UpdateMapStartSpots)j_00022ab6)(TheLAN->GetMyGame(),
		g_rva004CAF70_f, 0);
}
