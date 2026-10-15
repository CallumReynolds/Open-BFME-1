// ?bfme_appendGameOverDetails@GameLogic@@QAEXXZ
// partial score=1.0 date=2026-10-15
// cl: /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Igame/Libraries/Source/WWVegas/WWLib
// stlport
// GameLogic Game Over Details formatter at retail 0x00387A50 (657 bytes).
// ecx = TheGameLogic at both call sites: the peer CRC handler
// GameLogic::bfme_processLogicCRC (0x0038B597) and the gameplay dispatcher
// (0x00397789), both through ILT 0x0004A10B. The original method name is not
// in the image; bfme_appendGameOverDetails is the ledger's descriptive pin.
// The lifted ledger name EstablishConnectionsMenu::endMenu was wrong: ZH's
// endMenu is a tiny window teardown. Runs once (+0x68 flag), appends to the
// last line of the AsciiString vector at +0x54 one line per slot from the
// PlayerLeaveStatus records at +0x1B0 and copies each record's quit frame to
// Player+0x484. Literals are decoded from retail.
#include <vector>
#include "ascii_string.h"
extern "C" __declspec(dllimport) __declspec(nothrow) int __cdecl sprintf(char *, const char *, ...);

class PlayerTemplate {
  public:
    AsciiString getName() const;
};
class Player {
  public:
    char m_pad00[4];
    PlayerTemplate *m_playerTemplate; // +0x04
    char m_pad08[0x340];
    int m_scoreKeeper;                 // +0x348, address-tested only
    char m_pad34C[0x138];
    int m_quitFrame;                   // +0x484
};
class PlayerList {
  public:
    Player *getNthPlayer(int);
};
extern PlayerList *ThePlayerList;
// 0x012F0958: the player-template name scratch buffer filled by sprintf.
extern char g_rva012F0958PlayerTemplateName[];

// Twelve dwords per slot from +0x1B0; status 0 n/a, 1 graceful, 2 voted out.
struct PlayerLeaveStatus {
    int status, quitFrame, defeatFrame, victoryFrame;
    bool notPresent;
    char pad[3];
    int isHuman;
    void *name;
};
class GameLogic {
  public:
    void bfme_appendGameOverDetails();
    PlayerLeaveStatus *getPlayerLeaveStatus(int i) {
        if (i < 0 || i >= 8)
            return 0;
        return &m_leaveStatus[i];
    }
    char m_pad00[0x54];
    _STL::vector<AsciiString> m_lines; // +0x54
    char m_pad60[8];
    bool m_gameOverDetailsAppended;    // +0x68
    char m_pad69[0x147];
    PlayerLeaveStatus m_leaveStatus[8]; // +0x1B0
};

void GameLogic::bfme_appendGameOverDetails() {
    if (m_gameOverDetailsAppended || m_lines.size() == 0)
        return;
    AsciiString *last = &m_lines[m_lines.size() - 1];
    if (!last)
        return;
    m_gameOverDetailsAppended = true;
    AsciiString line;
    last->concat("    Game Over Details:\n");
    for (int i = 0; i < 8; ++i) {
        PlayerLeaveStatus *info = getPlayerLeaveStatus(i);
        if (info) {
            Player *player = ThePlayerList->getNthPlayer(i);
            if (player && &player->m_scoreKeeper && player->m_playerTemplate) {
                sprintf(g_rva012F0958PlayerTemplateName, "%s",
                        player->m_playerTemplate->getName().str());
                // A named copy, not a direct member-to-member store: it shifts
                // the scratch-register rotation of the switch arms below.
                int quitFrame = info->quitFrame;
                player->m_quitFrame = quitFrame;
            }
            AsciiString reason;
            switch (info->status) {
            case 0:
                reason.format("n/a");
                break;
            case 1:
                reason.format("graceful");
                break;
            case 2:
                reason.format("voted out");
                break;
            default:
                reason.format("unknown");
                break;
            }
            if (info->victoryFrame)
                line.format("      Slot %d: Victory frame: %d, Quit frame: %d(%s)\n", i,
                            info->victoryFrame, info->quitFrame, reason.str());
            else if (info->defeatFrame)
                line.format("      Slot %d: Defeat frame: %d, Quit frame: %d(%s)\n", i,
                            info->defeatFrame, info->quitFrame, reason.str());
            else if (info->notPresent)
                line.format("      Slot %d: n/a\n", i);
            else
                line.format("      Slot %d: Present at final frame\n", i);
        } else
            line.format("      Slot %d: PlayerLeaveStatus does not exist.\n", i);
        last->StringBase<char>::concat(line.str(), line.getLength());
    }
}
