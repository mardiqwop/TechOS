#ifndef HELP_H
#define HELP_H

#include "queue.h"

#define COMPLETIONDATE "12/7/2017"
#define VERSION "5.0"

#define BLUECOLOR "\e[34m"
#define YELLOWCOLOR "\e[93m"
#define MAGENTACOLOR "\e[95m"
#define DEFAULTCOLOR "\e[39m"
#define REDCOLOR "\e[91m"

#define NUMCOMMANDS (24)
#define MAXPROCESSNAMESIZE (8)

#define HELPCOMMAND "help"
#define VERSIONCOMMAND "version"
#define SHOWDATECOMMAND "date"
#define SETDATECOMMAND "setdate"
#define TIMECOMMAND "time"
#define TERMINATECOMMAND "exit"
// R2 commands
#define SETPRIORITYCOMMAND "priority"
#define SHOWPCBCOMMAND "pcb"
#define SHOWPROCESSESCOMMAND "processes"
#define SHOWREADYPROCESSESCOMMAND "ready"
#define SHOWBLOCKEDPROCESSESCOMMAND "blocked"
#define CREATEPCBCOMMAND "create"
#define DELETEPCBCOMMAND "delete"
#define BLOCKPCBCOMMAND "block"
#define UNBLOCKPCBCOMMAND "unblock"
#define SUSPENDPCBCOMMAND "suspend"
#define RESUMEPCBCOMMAND "resume"
#define DISPATCHCOMMAND "dispatch"
// R3 commands
#define LOADCOMMAND "load"
// R4 commands
#define VIEWDIRCOMMAND "ls"
#define CHANGEDIRCOMMAND "cd"
#define CREATEFOLDERCOMMAND "mkdir"
#define REMOVEFOLDERCOMMAND "rmdir"
#define CREATEFILECOMMAND "mkfile"
#define REMOVEFILECOMMAND "rmfile"
// R5 commands
#define CREATEUSERCOMMAND "newuser"
#define REMOVEUSERCOMMAND "removeuser"
#define CHANGEPASSWORDCOMMAND "password"
#define ADDADMINCOMMAND "promote"
#define REMOVEADMINCOMMAND "demote"

#define DISPATCHUSAGE "\nUsage for " DISPATCHCOMMAND	\
    "\n " DISPATCHCOMMAND "\nBegins all processes that are ready.\n"

#define SETDATEUSAGE "\nUsage for " SETDATECOMMAND	\
    ":\n" SETDATECOMMAND " -m <month> -d <day> -y <year>\n"

#define TIMEUSAGE "\nUsage for " TIMECOMMAND		\
    ":\n" TIMECOMMAND " (-t | -T | -S)\n\nExample:\ntime -T\n"

#define TERMINATEUSAGE "\nUsage for " TERMINATECOMMAND			\
    ":\n" TERMINATECOMMAND "\nYou will be asked if you're sure you want to exit. "   	\
    "Enter the letter \"y\" if you are sure.\n"

#define DATEUSAGE "\nUsage for " SHOWDATECOMMAND		\
    ":\n" SHOWDATECOMMAND " (-d | -D | -f | -F | -g | -G | -m | -s | -y)\n"

#define HELPUSAGE "\nUsage for " HELPCOMMAND		\
    ":\n" HELPCOMMAND " [-c <command>]\n\nExample:\nhelp -c time\n"

#define VERSIONUSAGE "\nUsage for " VERSIONCOMMAND ":\n" VERSIONCOMMAND

#define SETPRIORITYUSAGE "\nUsage for " SETPRIORITYCOMMAND	\
    ":\n" SETPRIORITYCOMMAND " -n <name> -p <priority>\n"

#define SHOWPCBUSAGE "\nUsage for " SHOWPCBCOMMAND	\
    ":\n" SHOWPCBCOMMAND " -n <name>"

#define SHOWPROCESSESUSAGE "\nUsage for " SHOWPROCESSESCOMMAND	\
    ":\n" SHOWPROCESSESCOMMAND

#define SHOWREADYPROCESSESUSAGE "\nUsage for " SHOWREADYPROCESSESCOMMAND \
    ":\n" SHOWREADYPROCESSESCOMMAND

#define SHOWBLOCKEDPROCESSESUSAGE "\nUsage for " SHOWBLOCKEDPROCESSESCOMMAND \
    ":\n" SHOWBLOCKEDPROCESSESCOMMAND

#define CREATEPCBUSAGE "\nCreates a PCB\nUsage for " CREATEPCBCOMMAND	\
    ":\n" CREATEPCBCOMMAND " -n <name> -p<priority> -c<class>\n" \
    " \nThe priority is a number from 0 to 9."							\
    "\nThere is no space between the -p and the priority or -c and the class.\n"

#define DELETEPCBUSAGE "\nUsage for " DELETEPCBCOMMAND	\
    ":\n" DELETEPCBCOMMAND " -n <name>"

#define BLOCKPCBUSAGE "\nUsage for " BLOCKPCBCOMMAND	\
    ":\n" BLOCKPCBCOMMAND " -n <name>"

#define UNBLOCKPCBUSAGE "\nUsage for " UNBLOCKPCBCOMMAND	\
    ":\n" UNBLOCKPCBCOMMAND " -n <name>"

#define SUSPENDPCBUSAGE "\nUsage for " SUSPENDPCBCOMMAND	\
    ":\n" SUSPENDPCBCOMMAND " -n <name>"

#define RESUMEPCBUSAGE "\nUsage for " RESUMEPCBCOMMAND	\
    ":\n" RESUMEPCBCOMMAND " -n <name>"

#define LOADUSAGE "\nUsage for " LOADCOMMAND  \
    ":\n" LOADCOMMAND " -n <process_name> -p <priority> -f <filename>"

#define VIEWDIRUSAGE "\nUsage for " VIEWDIRCOMMAND	\
    ":\n " VIEWDIRCOMMAND "(-p)  (-s) "		\
    "\nIf you specify -p you will be prompted for the path to view."\
    "\nSpecifying -s will show the sizes of files.\n"

#define CHANGEDIRUSAGE "\nUsage for " CHANGEDIRCOMMAND	\
    ":\n " CHANGEDIRCOMMAND " \nYou will be prompted for the path.\n"

#define CREATEFOLDERUSAGE "\nUsage for " CREATEFOLDERCOMMAND	\
    ":\n " CREATEFOLDERCOMMAND "\nYou will be prompted for the path.\n" \
    "Creates a folder in the current directory with name <name>.\n"

#define REMOVEFOLDERUSAGE "\nUsage for " REMOVEFOLDERCOMMAND	\
    ":\n " REMOVEFOLDERCOMMAND " \nYou will be prompted for the path.\n" \
    "Removes a folder in the current directory with name <name>.\n"

#define CREATEFILEUSAGE "\nUsage for " CREATEFILECOMMAND	\
    ":\n " CREATEFILECOMMAND " -n <name>"			\
    "\nCreates a file in the current directory with name <name>.\n"

#define REMOVEFILEUSAGE "\nUsage for " REMOVEFILECOMMAND	\
    ":\n " REMOVEFILECOMMAND " -n <name>"				\
    "\nRemoves a file in the current directory with name <name>.\n"

#define CREATEUSERUSAGE "\nUsage for " CREATEUSERCOMMAND    \
    ":\n " CREATEUSERCOMMAND" -n <name> -p <password> -a" \
    "\nCreates a new user that can login to the system." \
    "\n     -a makes a new admin"

#define REMOVEUSERUSAGE "\nUsage for " REMOVEUSERCOMMAND    \
    ":\n " REMOVEUSERCOMMAND" -n <name>\n"  \
    "\nRemoves a user."

#define CHANGEPASSWORDUSAGE "\nUsage for " CHANGEPASSWORDCOMMAND    \
    ":\n " CHANGEPASSWORDCOMMAND" -n <name>"    \
    "\nOpens a program that requests information about password changes\n"

#define ADDADMINUSAGE "\nUsage for " ADDADMINCOMMAND    \
    ":\n " ADDADMINCOMMAND" -n <name>"  \
    "\nGives administrator privleges to a user.\n"

#define REMOVEADMINUSAGE "\nUsage for " REMOVEADMINCOMMAND    \
    ":\n " REMOVEADMINCOMMAND" -n <name>"   \
    "\nGives administrator privleges to a user.\n"

int isValidCommand(char *);
int matches(char *, char *);
void help(char *, int);
void displayVersion();
int isValidInt(char* str);


#endif
