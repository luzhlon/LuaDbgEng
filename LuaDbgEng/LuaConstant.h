#include "dbgeng.h"
#include "LuaAPI.h"

LuaAPI::LUA_CONSTANT lua_constant[] = 
{
	//DEBUG_ENGOPT_XXX:
	{ "DEBUG_ENGOPT_KD_QUIET_MODE", DEBUG_ENGOPT_KD_QUIET_MODE },
	{ "DEBUG_ENGOPT_INITIAL_MODULE_BREAK", DEBUG_ENGOPT_INITIAL_MODULE_BREAK },
	{ "DEBUG_ENGOPT_DISABLE_MODULE_SYMBOL_LOAD", DEBUG_ENGOPT_DISABLE_MODULE_SYMBOL_LOAD },
	{ "DEBUG_ENGOPT_IGNORE_DBGHELP_VERSION", DEBUG_ENGOPT_IGNORE_DBGHELP_VERSION },
	{ "DEBUG_ENGOPT_DISABLE_STEPLINES_OPTIONS", DEBUG_ENGOPT_DISABLE_STEPLINES_OPTIONS },
	{ "DEBUG_ENGOPT_PREFER_DML", DEBUG_ENGOPT_PREFER_DML },
	{ "DEBUG_ENGOPT_ALL", DEBUG_ENGOPT_ALL },
	{ "DEBUG_ENGOPT_DISABLESQM", DEBUG_ENGOPT_DISABLESQM },
	{ "DEBUG_ENGOPT_NO_EXECUTE_REPEAT", DEBUG_ENGOPT_NO_EXECUTE_REPEAT },
	{ "DEBUG_ENGOPT_DISALLOW_IMAGE_FILE_MAPPING", DEBUG_ENGOPT_DISALLOW_IMAGE_FILE_MAPPING },
	{ "DEBUG_ENGOPT_FINAL_BREAK", DEBUG_ENGOPT_FINAL_BREAK },
	{ "DEBUG_ENGOPT_DISALLOW_SHELL_COMMANDS", DEBUG_ENGOPT_DISALLOW_SHELL_COMMANDS },
	{ "DEBUG_ENGOPT_SYNCHRONIZE_BREAKPOINTS", DEBUG_ENGOPT_SYNCHRONIZE_BREAKPOINTS },
	{ "DEBUG_ENGOPT_FAIL_INCOMPLETE_INFORMATION", DEBUG_ENGOPT_FAIL_INCOMPLETE_INFORMATION },
	{ "DEBUG_ENGOPT_IGNORE_LOADER_EXCEPTIONS", DEBUG_ENGOPT_IGNORE_LOADER_EXCEPTIONS },
	{ "DEBUG_ENGOPT_INITIAL_BREAK", DEBUG_ENGOPT_INITIAL_BREAK },
	{ "DEBUG_ENGOPT_DISABLE_MANAGED_SUPPORT", DEBUG_ENGOPT_DISABLE_MANAGED_SUPPORT },
	{ "DEBUG_ENGOPT_NETWORK_PATHS", DEBUG_ENGOPT_NETWORK_PATHS },
	{ "DEBUG_ENGOPT_IGNORE_EXTENSION_VERSIONS", DEBUG_ENGOPT_IGNORE_EXTENSION_VERSIONS },
	{ "DEBUG_ENGOPT_DISABLE_EXECUTION_COMMANDS", DEBUG_ENGOPT_DISABLE_EXECUTION_COMMANDS },
	{ "DEBUG_ENGOPT_ALLOW_READ_ONLY_BREAKPOINTS", DEBUG_ENGOPT_ALLOW_READ_ONLY_BREAKPOINTS },
	{ "DEBUG_ENGOPT_ALLOW_NETWORK_PATHS", DEBUG_ENGOPT_ALLOW_NETWORK_PATHS },
	{ "DEBUG_ENGOPT_DISALLOW_NETWORK_PATHS", DEBUG_ENGOPT_DISALLOW_NETWORK_PATHS },
	//DEBUG_SYMBOL_XXX:
	{ "DEBUG_SYMBOL_IS_ARGUMENT", DEBUG_SYMBOL_IS_ARGUMENT },
	{ "DEBUG_SYMBOL_IS_FLOAT", DEBUG_SYMBOL_IS_FLOAT },
	{ "DEBUG_SYMBOL_IS_LOCAL", DEBUG_SYMBOL_IS_LOCAL },
	{ "DEBUG_SYMBOL_EXPANSION_LEVEL_MASK", DEBUG_SYMBOL_EXPANSION_LEVEL_MASK },
	{ "DEBUG_SYMBOL_READ_ONLY", DEBUG_SYMBOL_READ_ONLY },
	{ "DEBUG_SYMBOL_IS_ARRAY", DEBUG_SYMBOL_IS_ARRAY },
	{ "DEBUG_SYMBOL_EXPANDED", DEBUG_SYMBOL_EXPANDED },
	//DEBUG_DUMP_XXX:
	{ "DEBUG_DUMP_DEFAULT", DEBUG_DUMP_DEFAULT },
	{ "DEBUG_DUMP_TRACE_LOG", DEBUG_DUMP_TRACE_LOG },
	{ "DEBUG_DUMP_FILE_LOAD_FAILED_INDEX", DEBUG_DUMP_FILE_LOAD_FAILED_INDEX },
	{ "DEBUG_DUMP_FULL", DEBUG_DUMP_FULL },
	{ "DEBUG_DUMP_FILE_PAGE_FILE_DUMP", DEBUG_DUMP_FILE_PAGE_FILE_DUMP },
	{ "DEBUG_DUMP_WINDOWS_CE", DEBUG_DUMP_WINDOWS_CE },
	{ "DEBUG_DUMP_FILE_BASE", DEBUG_DUMP_FILE_BASE },
	{ "DEBUG_DUMP_IMAGE_FILE", DEBUG_DUMP_IMAGE_FILE },
	{ "DEBUG_DUMP_SMALL", DEBUG_DUMP_SMALL },
	{ "DEBUG_DUMP_FILE_ORIGINAL_CAB_INDEX", DEBUG_DUMP_FILE_ORIGINAL_CAB_INDEX },
	//DEBUG_ATTACH_XXX:
	{ "DEBUG_ATTACH_DEFAULT", DEBUG_ATTACH_DEFAULT },
	{ "DEBUG_ATTACH_INVASIVE_NO_INITIAL_BREAK", DEBUG_ATTACH_INVASIVE_NO_INITIAL_BREAK },
	{ "DEBUG_ATTACH_INVASIVE_RESUME_PROCESS", DEBUG_ATTACH_INVASIVE_RESUME_PROCESS },
	{ "DEBUG_ATTACH_KERNEL_CONNECTION", DEBUG_ATTACH_KERNEL_CONNECTION },
	{ "DEBUG_ATTACH_EXDI_DRIVER", DEBUG_ATTACH_EXDI_DRIVER },
	{ "DEBUG_ATTACH_EXISTING", DEBUG_ATTACH_EXISTING },
	{ "DEBUG_ATTACH_NONINVASIVE_ALLOW_PARTIAL", DEBUG_ATTACH_NONINVASIVE_ALLOW_PARTIAL },
	{ "DEBUG_ATTACH_LOCAL_KERNEL", DEBUG_ATTACH_LOCAL_KERNEL },
	{ "DEBUG_ATTACH_INSTALL_DRIVER", DEBUG_ATTACH_INSTALL_DRIVER },
	{ "DEBUG_ATTACH_NONINVASIVE", DEBUG_ATTACH_NONINVASIVE },
	{ "DEBUG_ATTACH_NONINVASIVE_NO_SUSPEND", DEBUG_ATTACH_NONINVASIVE_NO_SUSPEND },
	//DEBUG_FORMAT_XXX:
	{ "DEBUG_FORMAT_USER_SMALL_FILTER_PATHS", DEBUG_FORMAT_USER_SMALL_FILTER_PATHS },
	{ "DEBUG_FORMAT_CAB_SECONDARY_FILES", DEBUG_FORMAT_CAB_SECONDARY_FILES },
	{ "DEBUG_FORMAT_USER_SMALL_HANDLE_DATA", DEBUG_FORMAT_USER_SMALL_HANDLE_DATA },
	{ "DEBUG_FORMAT_USER_SMALL_CODE_SEGMENTS", DEBUG_FORMAT_USER_SMALL_CODE_SEGMENTS },
	{ "DEBUG_FORMAT_USER_SMALL_IGNORE_INACCESSIBLE_MEM", DEBUG_FORMAT_USER_SMALL_IGNORE_INACCESSIBLE_MEM },
	{ "DEBUG_FORMAT_USER_SMALL_FILTER_MEMORY", DEBUG_FORMAT_USER_SMALL_FILTER_MEMORY },
	{ "DEBUG_FORMAT_USER_SMALL_MODULE_HEADERS", DEBUG_FORMAT_USER_SMALL_MODULE_HEADERS },
	{ "DEBUG_FORMAT_USER_SMALL_NO_OPTIONAL_DATA", DEBUG_FORMAT_USER_SMALL_NO_OPTIONAL_DATA },
	{ "DEBUG_FORMAT_USER_SMALL_FILTER_TRIAGE", DEBUG_FORMAT_USER_SMALL_FILTER_TRIAGE },
	{ "DEBUG_FORMAT_USER_SMALL_FULL_AUXILIARY_STATE", DEBUG_FORMAT_USER_SMALL_FULL_AUXILIARY_STATE },
	{ "DEBUG_FORMAT_USER_SMALL_NO_AUXILIARY_STATE", DEBUG_FORMAT_USER_SMALL_NO_AUXILIARY_STATE },
	{ "DEBUG_FORMAT_NO_OVERWRITE", DEBUG_FORMAT_NO_OVERWRITE },
	{ "DEBUG_FORMAT_USER_SMALL_THREAD_INFO", DEBUG_FORMAT_USER_SMALL_THREAD_INFO },
	{ "DEBUG_FORMAT_WRITE_CAB", DEBUG_FORMAT_WRITE_CAB },
	{ "DEBUG_FORMAT_USER_SMALL_UNLOADED_MODULES", DEBUG_FORMAT_USER_SMALL_UNLOADED_MODULES },
	{ "DEBUG_FORMAT_USER_SMALL_FULL_MEMORY_INFO", DEBUG_FORMAT_USER_SMALL_FULL_MEMORY_INFO },
	{ "DEBUG_FORMAT_USER_SMALL_PRIVATE_READ_WRITE_MEMORY", DEBUG_FORMAT_USER_SMALL_PRIVATE_READ_WRITE_MEMORY },
	{ "DEBUG_FORMAT_USER_SMALL_INDIRECT_MEMORY", DEBUG_FORMAT_USER_SMALL_INDIRECT_MEMORY },
	{ "DEBUG_FORMAT_USER_SMALL_FULL_MEMORY", DEBUG_FORMAT_USER_SMALL_FULL_MEMORY },
	{ "DEBUG_FORMAT_USER_SMALL_DATA_SEGMENTS", DEBUG_FORMAT_USER_SMALL_DATA_SEGMENTS },
	{ "DEBUG_FORMAT_CAB_SECONDARY_ALL_IMAGES", DEBUG_FORMAT_CAB_SECONDARY_ALL_IMAGES },
	{ "DEBUG_FORMAT_USER_SMALL_PROCESS_THREAD_DATA", DEBUG_FORMAT_USER_SMALL_PROCESS_THREAD_DATA },
	{ "DEBUG_FORMAT_DEFAULT", DEBUG_FORMAT_DEFAULT },
	//DEBUG_STATUS_XXX:
	{ "DEBUG_STATUS_REVERSE_GO", DEBUG_STATUS_REVERSE_GO },
	{ "DEBUG_STATUS_GO_NOT_HANDLED", DEBUG_STATUS_GO_NOT_HANDLED },
	{ "DEBUG_STATUS_MASK", DEBUG_STATUS_MASK },
	{ "DEBUG_STATUS_OUT_OF_SYNC", DEBUG_STATUS_OUT_OF_SYNC },
	{ "DEBUG_STATUS_GO_HANDLED", DEBUG_STATUS_GO_HANDLED },
	{ "DEBUG_STATUS_REVERSE_STEP_OVER", DEBUG_STATUS_REVERSE_STEP_OVER },
	{ "DEBUG_STATUS_STEP_BRANCH", DEBUG_STATUS_STEP_BRANCH },
	{ "DEBUG_STATUS_WAIT_INPUT", DEBUG_STATUS_WAIT_INPUT },
	{ "DEBUG_STATUS_NO_CHANGE", DEBUG_STATUS_NO_CHANGE },
	{ "DE BUG_STATUS_NO_DEBUGGEE", DEBUG_STATUS_NO_DEBUGGEE },
	{ "DEBUG_STATUS_REVERSE_STEP_INTO", DEBUG_STATUS_REVERSE_STEP_INTO },
	{ "DEBUG_STATUS_STEP_INTO", DEBUG_STATUS_STEP_INTO },
	{ "DEBUG_STATUS_WAIT_TIMEOUT", DEBUG_STATUS_WAIT_TIMEOUT },
	{ "DEBUG_STATUS_BREAK", DEBUG_STATUS_BREAK },
	{ "DEBUG_STATUS_IGNORE_EVENT", DEBUG_STATUS_IGNORE_EVENT },
	{ "DEBUG_STATUS_INSIDE_WAIT", DEBUG_STATUS_INSIDE_WAIT },
	{ "DEBUG_STATUS_TIMEOUT", DEBUG_STATUS_TIMEOUT },
	{ "DEBUG_STATUS_RESTART_REQUESTED", DEBUG_STATUS_RESTART_REQUESTED },
	{ "DEBUG_STATUS_REVERSE_STEP_BRANCH", DEBUG_STATUS_REVERSE_STEP_BRANCH },
	{ "DEBUG_STATUS_STEP_OVER", DEBUG_STATUS_STEP_OVER },
	{ "DEBUG_STATUS_GO", DEBUG_STATUS_GO },
	//DEBUG_EVENT_XXX:
	{ "DEBUG_EVENT_CREATE_THREAD", DEBUG_EVENT_CREATE_THREAD },
	{ "DEBUG_EVENT_BREAKPOINT", DEBUG_EVENT_BREAKPOINT },
	{ "DEBUG_EVENT_UNLOAD_MODULE", DEBUG_EVENT_UNLOAD_MODULE },
	{ "DEBUG_EVENT_CHANGE_SYMBOL_STATE", DEBUG_EVENT_CHANGE_SYMBOL_STATE },
	{ "DEBUG_EVENT_LOAD_MODULE", DEBUG_EVENT_LOAD_MODULE },
	{ "DEBUG_EVENT_EXIT_PROCESS", DEBUG_EVENT_EXIT_PROCESS },
	{ "DEBUG_EVENT_CHANGE_DEBUGGEE_STATE", DEBUG_EVENT_CHANGE_DEBUGGEE_STATE },
	{ "DEBUG_EVENT_SESSION_STATUS", DEBUG_EVENT_SESSION_STATUS },
	{ "DEBUG_EVENT_SYSTEM_ERROR", DEBUG_EVENT_SYSTEM_ERROR },
	{ "DEBUG_EVENT_CREATE_PROCESS", DEBUG_EVENT_CREATE_PROCESS },
	{ "DEBUG_EVENT_EXIT_THREAD", DEBUG_EVENT_EXIT_THREAD },
	{ "DEB UG_EVENT_CHANGE_ENGINE_STATE", DEBUG_EVENT_CHANGE_ENGINE_STATE },
	{ "DEBUG_EVENT_EXCEPTION", DEBUG_EVENT_EXCEPTION },
	//DEBUG_OUTCTL_XXX:
	{ "DEBUG_OUTCTL_AMBIENT_TEXT", DEBUG_OUTCTL_AMBIENT_TEXT },
	{ "DEBUG_OUTCTL_SEND_MASK", DEBUG_OUTCTL_SEND_MASK },
	{ "DEBUG_OUTCTL_DML", DEBUG_OUTCTL_DML },
	{ "DEBUG_OUTCTL_IGNORE", DEBUG_OUTCTL_IGNORE },
	{ "DEBUG_OUTCTL_ALL_CLIENTS", DEBUG_OUTCTL_ALL_CLIENTS },
	{ "DEBUG_OUTCTL_OVERRIDE_MASK", DEBUG_OUTCTL_OVERRIDE_MASK },
	{ "DEBUG_OUTCTL_AMBIENT", DEBUG_OUTCTL_AMBIENT },
	{ "DEBUG_OUTCTL_LOG_ONLY", DEBUG_OUTCTL_LOG_ONLY },
	{ "DEBUG_OUTCTL_AMBIENT_DML", DEBUG_OUTCTL_AMBIENT_DML },
	{ "DEBUG_OUTCTL_ALL_OTHER_CLIENTS", DEBUG_OUTCTL_ALL_OTHER_CLIENTS },
	{ "DEBUG_OUTCTL_NOT_LOGGED", DEBUG_OUTCTL_NOT_LOGGED },
	{ "DEBUG_OUTCTL_THIS_CLIENT", DEBUG_OUTCTL_THIS_CLIENT },
	//DEBUG_PROCESS_XXX:
	{ "DEBUG_PROCESS_DETACH_ON_EXIT", DEBUG_PROCESS_DETACH_ON_EXIT },
	{ "DEBUG_PROCESS_ONLY_THIS_PROCESS", DEBUG_PROCESS_ONLY_THIS_PROCESS },
	//DEBUG_OUTPUT_XXX :
	//{ "DEBUG_OUTPUT_NAME_END_WIDE", DEBUG_OUTPUT_NAME_END_WIDE },
	{ "DEB UG_OUTPUT_IDENTITY_DEFAULT", DEBUG_OUTPUT_IDENTITY_DEFAULT },
	{ "DEBUG_OUTPUT_SYMBOLS_NO_OFFSETS", DEBUG_OUTPUT_SYMBOLS_NO_OFFSETS },
	{ "DEBUG_OUTPUT_SYMBOLS_NO_VALUES", DEBUG_OUTPUT_SYMBOLS_NO_VALUES },
	{ "DEBUG_OUTPUT_DEBUGGEE_PROMPT", DEBUG_OUTPUT_DEBUGGEE_PROMPT },
	{ "DEBUG_OUTPUT_WARNING", DEBUG_OUTPUT_WARNING },
	{ "DEBUG_OUTPUT_VERBOSE", DEBUG_OUTPUT_VERBOSE },
	//{ "DEBUG_OUTPUT_OFFSET_END", DEBUG_OUTPUT_OFFSET_END },
	{ "DEBUG_OUTPUT_STATUS", DEBUG_OUTPUT_STATUS },
	{ "DEBUG_OUTPUT_SYMBOLS_DEFAULT", DEBUG_OUTPUT_SYMBOLS_DEFAULT },
	{ "DEBUG_OUTPUT_DEBUGGEE", DEBUG_OUTPUT_DEBUGGEE },
	//{ "DEBUG_OUTPUT_NAME_END_T", DEBUG_OUTPUT_NAME_END_T },
	{ "DEBUG_OUTPUT_PROMPT_REGISTERS", DEBUG_OUTPUT_PROMPT_REGISTERS },
	{ "DEBUG_OUTPUT_SYMBOLS_NO_TYPES", DEBUG_OUTPUT_SYMBOLS_NO_TYPES },
	//{ "DEBUG_OUTPUT_TYPE_END", DEBUG_OUTPUT_TYPE_END },
	//{ "DEBUG_OUTPUT_NAME_END", DEBUG_OUTPUT_NAME_END },
	{ "DEBUG_OUTPUT_PROMPT", DEBUG_OUTPUT_PROMPT },
	{ "DEBUG_OUTPUT_NORMAL", DEBUG_OUTPUT_NORMAL },
	//{ "DEBUG_OUTPUT_VALUE_END", DEBUG_OUTPUT_VALUE_END },
	{ "DEBUG_OUTPUT_EXTENSION_WARNING", DEBUG_OUTPUT_EXTENSION_WARNING },
	{ "DEBUG_OUTPUT_SYMBOLS_NO_NAMES", DEBUG_OUTPUT_SYMBOLS_NO_NAMES },
	{ "DEBUG_OUTPUT_ERROR", DEBUG_OUTPUT_ERROR },
	{ "DEBUG_OUTPUT_SYMBOLS", DEBUG_OUTPUT_SYMBOLS },
	//DEBUG_ASMOPT_XXX:
	{ "DEBUG_ASMOPT_NO_CODE_BYTES", DEBUG_ASMOPT_NO_CODE_BYTES },
	{ "DEBUG_ASMOPT_IGNORE_OUTPUT_WIDTH", DEBUG_ASMOPT_IGNORE_OUTPUT_WIDTH },
	{ "DEBUG_ASMOPT_DEFAULT", DEBUG_ASMOPT_DEFAULT },
	{ "DEBUG_ASMOPT_SOURCE_LINE_NUMBER", DEBUG_ASMOPT_SOURCE_LINE_NUMBER },
	{ "DEBUG_ASMOPT_VERBOSE", DEBUG_ASMOPT_VERBOSE },
	//DEBUG_FILTER_XXX :
	{ "DEBUG_FILTER_LOAD_MODULE", DEBUG_FILTER_LOAD_MODULE },
	{ "DEBUG_FILTER_SYSTEM_ERROR", DEBUG_FILTER_SYSTEM_ERROR },
	{ "DEBUG_FILTER_CREATE_PROCESS", DEBUG_FILTER_CREATE_PROCESS },
	{ "DEBUG_FILTER_EXIT_PROCESS", DEBUG_FILTER_EXIT_PROCESS },
	{ "DEBUG_FILTER_REMOVE", DEBUG_FILTER_REMOVE },
	{ "DEBUG_FILTER_DEBUGGEE_OUTPUT", DEBUG_FILTER_DEBUGGEE_OUTPUT },
	{ "DEBUG_FILTER_IGNORE", DEBUG_FILTER_IGNORE },
	{ "DEBUG_FILTER_SECOND_CHANCE_BREAK", DEBUG_FILTER_SECOND_CHANCE_BREAK },
	{ "DEBUG_FILTER_BREAK", DEBUG_FILTER_BREAK },
	{ "DEBUG_FILTER_GO_NOT_HANDLED", DEBUG_FILTER_GO_NOT_HANDLED },
	{ "DEBUG_FILTER_GO_HANDLED", DEBUG_FILTER_GO_HANDLED },
	{ "DEBUG_FILTER_OUTPUT", DEBUG_FILTER_OUTPUT },
	{ "DEBUG_FILTER_UNLOAD_MODULE", DEBUG_FILTER_UNLOAD_MODULE },
	{ "DEBUG_FILTER_INITIAL_MODULE_LOAD", DEBUG_FILTER_INITIAL_MODULE_LOAD },
	{ "DEBUG_FILTER_CREATE_THREAD", DEBUG_FILTER_CREATE_THREAD },
	{ "DEBUG_FILTER_INITIAL_BREAKPOINT", DEBUG_FILTER_INITIAL_BREAKPOINT },
	{ "DEBUG_FILTER_EXIT_THREAD", DEBUG_FILTER_EXIT_THREAD },
	//DEBUG_FIND_SOURCE_XXX:
	{ "DEBUG_FIND_SOURCE_TOKEN_LOOKUP", DEBUG_FIND_SOURCE_TOKEN_LOOKUP },
	{ "DEBUG_FIND_SOURCE_DEFAULT", DEBUG_FIND_SOURCE_DEFAULT },
	{ "DEBUG_FIND_SOURCE_NO_SRCSRV", DEBUG_FIND_SOURCE_NO_SRCSRV },
	{ "DEBUG_FIND_SOURCE_FULL_PATH", DEBUG_FIND_SOURCE_FULL_PATH },
	{ "DEBUG_FIND_SOURCE_BEST_MATCH", DEBUG_FIND_SOURCE_BEST_MATCH },
	//DEBUG_TYPEOPTS_XXX :
	{ "DEBUG_TYPEOPTS_MATCH_MAXSIZE", DEBUG_TYPEOPTS_MATCH_MAXSIZE },
	{ "DEBUG_TYPEOPTS_FORCERADIX_OUTPUT", DEBUG_TYPEOPTS_FORCERADIX_OUTPUT },
	{ "DEBUG_TYPEOPTS_UNICODE_DISPLAY", DEBUG_TYPEOPTS_UNICODE_DISPLAY },
	{ "DEBUG_TYPEOPTS_LONGSTATUS_DISPLAY", DEBUG_TYPEOPTS_LONGSTATUS_DISPLAY },

	{ "EXCEPTION_NONCONTINUABLE", EXCEPTION_NONCONTINUABLE },
	{ "EXCEPTION_UNWINDING", EXCEPTION_UNWINDING },
	{ "EXCEPTION_EXIT_UNWIND", EXCEPTION_EXIT_UNWIND },
	{ "EXCEPTION_STACK_INVALID", EXCEPTION_STACK_INVALID },
	{ "EXCEPTION_NESTED_CALL", EXCEPTION_NESTED_CALL },
	{ "EXCEPTION_TARGET_UNWIND", EXCEPTION_TARGET_UNWIND },
	{ "EXCEPTION_COLLIDED_UNWIND", EXCEPTION_COLLIDED_UNWIND },
	{ "EXCEPTION_UNWIND", (EXCEPTION_UNWINDING | EXCEPTION_EXIT_UNWIND | EXCEPTION_TARGET_UNWIND | EXCEPTION_COLLIDED_UNWIND) },
	{ "EXCEPTION_MAXIMUM_PARAMETERS", EXCEPTION_MAXIMUM_PARAMETERS },

//#define IS_UNWINDING(Flag) ((Flag & EXCEPTION_UNWIND) != 0)
//#define IS_DISPATCHING(Flag) ((Flag & EXCEPTION_UNWIND) == 0)
//#define IS_TARGET_UNWIND(Flag) (Flag & EXCEPTION_TARGET_UNWIND)

	{ "INFINITE", INFINITE },
	{ 0, 0 }
};
