#ifndef LOCKING_H
#define LOCKING_H

#include <pthread.h>
#include <semaphore.h>

typedef pthread_mutex_t replay_mutex;
typedef sem_t replay_sem;

inline void replay_initmutex(replay_mutex *m);
inline void replay_lock(replay_mutex *m);
inline void replay_unlock(replay_mutex *m);

inline void replay_sem_init(replay_sem *s, unsigned int num);
inline void replay_sem_destroy(replay_sem *s);
inline void replay_sem_p(replay_sem *s);
inline void replay_sem_v(replay_sem *s);


#endif
