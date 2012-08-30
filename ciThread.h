#pragma once

#include <pthread.h>

class ciThread {
public:
	ciThread() { 
	   threadRunning = false; 
	   verbose = false;
	   pthread_mutex_init(&myMutex, NULL); 
	} 

	virtual void unload() { 
	   stopThread(); 
	} 

	bool isRunning() { 
	   return threadRunning; 
	} 

	void startThread(bool _blocking = true, bool _verbose = true) { 
	   if(threadRunning) {
           if(verbose) {printf("Thread already running.\n");}
           return;
       } 
	   threadRunning = true; 
	   pthread_create(&myThread, NULL, thread, (void *)this); 
	   blocking = _blocking; 
	   verbose  = _verbose; 
	} 

	bool lock() { 
	   if(blocking){ 
	      if(verbose) {printf("Waiting for mutex to unlock...\n");}
	      pthread_mutex_lock(&myMutex); 
	      if(verbose) {printf("Mutex locked.\n");}
	   }
       else{ 
	      int value = pthread_mutex_trylock(&myMutex); 
	      if(value == 0) { 
	         if(verbose) {printf("Mutex locked.\n");}
	      } 
	      else { 
	         if(verbose) {printf("Mutex is busy.\n");} 
	         return false; 
	      } 
	   } 
	   return true; 
	} 

	bool unlock() { 
	   pthread_mutex_unlock(&myMutex); 
	   if(verbose) {printf("Mutex unlocked.\n");}
	   return true; 
	} 

	void stopThread(bool close = true) {
		if(threadRunning) {
			if(close) {
				pthread_detach(myThread);
			}
			if(verbose) {printf("Thread stopped.\n");}
			threadRunning = false;
		}
        else {
			if(verbose) {printf("Thread already stopped.\n");}
		}
	}

	void wait(bool stop = true) {
		if(threadRunning) {
			// Reset the thread state
			if(stop){
				threadRunning = false;
				if(verbose) {printf("Stopping thread...\n");}
			}
			if(verbose) {printf("Waiting for thread to stop...\n");}
			if(pthread_self()==myThread) {printf("Wait cannot be called from within thread.\n");}
		    pthread_join(myThread, NULL);
			if(verbose) {printf("Thread stopped.\n");}
			myThread = NULL;
	    }
		else{
			if(verbose) {printf("Thread already stopped.\n");}
		}
	}

protected:
	virtual void threadedFunction() {
		if(verbose) {printf("Overload this function.\n");}
	}

	static void * thread(void * objPtr) {
		ciThread* me = (ciThread*)objPtr;
		me->threadedFunction();
		me->stopThread(false);
		pthread_exit(NULL);
		return 0;
	}

	pthread_t        	myThread;
	pthread_mutex_t  	myMutex;
	bool 				threadRunning;
	bool 				blocking;
	bool 				verbose;
};
