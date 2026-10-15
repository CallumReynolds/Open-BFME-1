// ?rva0007B420@Rva01075C14Owner@@QAEXXZ
// cl: /DNDEBUG /MD /EHsc
//
// Retail 0x0007B420, 295 bytes (plain RET at +0x126, INT3 after). Reached only
// from slot 0 of the vtable at 0x01075C14 through ILT 0x000442F1 (and the
// jump stub 0x006BAB30). The body never reads ECX and returns with a plain
// RET, so it is not that class's deleting destructor; the owner and method
// keep the addresses.
// It tears down the engine singletons in the order Zero Hour's
// GameEngine::~GameEngine (GameEngine.cpp) does -- TheMapCache,
// TheGameResultsQueue, TheSubsystemList (released then deleted), TheNetwork,
// TheCommandList, TheNameKeyGenerator, TheFileSystem, TheGameLODManager,
// Drawable::killStaticImages, timeEndPeriod(1) -- plus BFME's watchdog, script
// engine pointer, attribute-modifier store and the object at 0x012ED5F4.
// TheSubsystemList's release and destructor are the matched
// Rva009A2030OwnedRecord bodies (0x009A1F90/0x009A2030); the attribute
// store is cleared through the matched Rva0036B6B0OwnedPointerCollection
// helper; the LOD manager's out-of-line destructor 0x0007C150 is a bare RET.
extern "C" __declspec(dllimport) unsigned int __stdcall timeEndPeriod(unsigned int period);

class Watchdog { public: virtual ~Watchdog(); };
class MapCache { public: ~MapCache(); };
class GameResultsInterface
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09();
	virtual void endThreads();
};
class ScriptEngine;
class AttributeModifierDefinitionStore;
class Rva0036B6B0OwnedPointerCollection { public: void clearOwnedRecords(); };
class SubsystemInterfaceList;
class Rva01075C14Owner;
class Rva009A2030OwnedRecord
{
	friend class Rva01075C14Owner;
public:
	~Rva009A2030OwnedRecord();
private:
	void releaseContents();
};
class GameLODManager { public: ~GameLODManager(); };
class NetworkInterface { public: virtual ~NetworkInterface(); };
class CommandList { public: virtual ~CommandList(); };
class Rva012ED5F4Object { public: virtual ~Rva012ED5F4Object(); };
class NameKeyGenerator { public: virtual ~NameKeyGenerator(); };
class FileSystem { public: virtual ~FileSystem(); };
class Drawable { public: static void killStaticImages(); };

extern Watchdog *Watchdog0040F780;
extern MapCache *TheMapCache;
extern GameResultsInterface *TheGameResultsQueue;
extern ScriptEngine *TheScriptEngine;
extern AttributeModifierDefinitionStore *TheAttributeModifierDefinitionStore;
extern SubsystemInterfaceList *TheSubsystemList;
extern GameLODManager *TheGameLODManager;
extern NetworkInterface *TheNetwork;
extern CommandList *TheCommandList;
extern char *CommandsAt012ED5F4;
extern NameKeyGenerator *TheNameKeyGenerator;
extern FileSystem *TheFileSystem;

class Rva01075C14Owner
{
public:
	void rva0007B420();
};

void Rva01075C14Owner::rva0007B420()
{
	delete Watchdog0040F780;
	Watchdog0040F780 = 0;

	delete TheMapCache;
	TheMapCache = 0;

	if (TheGameResultsQueue)
		TheGameResultsQueue->endThreads();
	TheScriptEngine = 0;

	if (TheAttributeModifierDefinitionStore)
		((Rva0036B6B0OwnedPointerCollection *)TheAttributeModifierDefinitionStore)->clearOwnedRecords();

	((Rva009A2030OwnedRecord *)TheSubsystemList)->releaseContents();
	delete (Rva009A2030OwnedRecord *)TheSubsystemList;
	TheSubsystemList = 0;

	delete TheGameLODManager;
	TheGameLODManager = 0;

	delete TheNetwork;
	TheNetwork = 0;

	delete TheCommandList;
	TheCommandList = 0;

	delete (Rva012ED5F4Object *)CommandsAt012ED5F4;
	CommandsAt012ED5F4 = 0;

	delete TheNameKeyGenerator;
	TheNameKeyGenerator = 0;

	delete TheFileSystem;
	TheFileSystem = 0;

	Drawable::killStaticImages();

	timeEndPeriod(1);
}
