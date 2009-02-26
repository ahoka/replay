#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

/* Wrap locking functions. Only POSIX backed versions are implemented. */

inline void
replay_initmutex(replay_mutex *m)
{
	pthread_init_mutex(m, NULL);
	/* Error reporting? */
}

inline void
replay_lock(replay_mutex *m)
{
	pthread_mutex_lock(m);
}

inline void
replay_unlock(replay_mutex *m)
{
	pthread_mutex_unlock(m);
}

/* init a semaphore
 * (needs to call destroy on it after use)
 */
inline void
replay_sem_init(replay_sem *s, unsigned int num)
{
	sem_init(&s, 0, num);
}

/* destroy a semaphore
 * (the pointer becomes invalid after the operation)
 */
inline void
replay_sem_destroy(replay_sem *s)
{
	sem_destroy(s);
}

/* probeer te verlagen */
inline void
replay_sem_p(replay_sem *s)
{
	sem_try(s);
}

/* verhogen */
inline void
replay_sem_v(replay_sem *s)
{
	sem_post(s);
}
