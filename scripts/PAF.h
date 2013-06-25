//
//
//

#ifndef _PAF_H_
#define _PAF_H_

#define PAFDEBUG "PAF [D] "
#define PAFINFO  "PAF [I] "
#define PAFERROR "PAF [E] "
#define PAFWARN  "PAF [W] "

// XXX howto get this debug from user!?
#ifdef DEBUG
#define DEBUGUTILS DEBUG
#else
#undef DEBUGUTILS
#endif

#endif
